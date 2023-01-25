#include <cstdio>
#include <json/reader.h>
#include <json/value.h>
#include <raylib.h>
#include "player.h"
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <string>
#include "menu.h"

class Game {
    public:
        const int screenWidth = 800;
        const int screenHeight = 600;

        Texture2D brick1;
        Texture2D pillar1;
        Texture2D pillar2;

        Json::Value levelData;

        Player player;
        Camera2D camera;
        
        Game(){
            loadLevel(1);
            float startX, startY;
            startX = levelData["start_pos"][0].asFloat();
            startY = levelData["start_pos"][1].asFloat();
            player.setStartPosition({startX, startY});
            player.setPosition({startX, startY});            
        }
        int main();

        void draw();

        void update();

        void loadLevel(int);


};
 
int Game::main(){
    InitWindow(screenWidth, screenHeight, "Nokka Helt Crazy");
    
    SetTargetFPS(60);
    
    SetExitKey(0);

    Menu menu(screenWidth, screenHeight);
    int c = menu.loop();
    
    if(c == 2){
        CloseWindow();
    }

    player.slime = LoadTexture("assets/slime.png");
    player.slime2 = LoadTexture("assets/slime2.png");
    
    pillar1 = LoadTexture("assets/pillar1.png");
    pillar2 = LoadTexture("assets/pillar2.png");
    brick1 = LoadTexture("assets/bricks.png");
    
    camera = { 0 };
    camera.target = player.getPosition();
    camera.offset = {(float)screenWidth/2, (float)screenHeight/2};
    camera.rotation = .0f;
    camera.zoom = 1.0f;
    
    while(!WindowShouldClose()){
        update();

        draw();

    }

    CloseWindow();
    UnloadTexture(player.slime);

    return 0;
}
void Game::draw(){
    BeginDrawing();

            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);

                for(int i = 0; i<levelData["data"].size(); i++){
                    Json::Value block = levelData["data"][i];

                    Texture2D texture;
                    if(block[4] == "b"){
                        texture = brick1;
                    }else if(block[4] == "p1"){
                        texture = pillar1;
                    } else if(block[4] == "p2"){
                        texture = pillar2;
                    }

                    //Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.width};

                    //Rectangle destRec = {block[0].asFloat(), block[1].asFloat(), block[2].asFloat(), block[3].asFloat()};

                    //Vector2 origin = {(float)texture.width, (float)texture.width};

                    //DrawTextureEx(texture, {block[0].asFloat(), block[1].asFloat()}, 0, block[3].asFloat()/texture.height, WHITE);
                    //DrawTexturePro(texture, sourceRec, destRec, origin, 0.f, WHITE);
                    Rectangle rect = (Rectangle){block[0].asFloat(), block[1].asFloat(), block[2].asFloat(), block[3].asFloat()};
                    DrawRectangleRec(rect, MAROON);
                }


                player.draw();
            
            EndMode2D();


        
    EndDrawing();
}

void Game::update(){
    player.update(screenHeight, screenWidth, &camera, levelData["data"]);
}

void Game::loadLevel(int levelNum){
    std::string filename = "levels/level";
    filename += std::to_string(levelNum) + ".json";
    std::ifstream file(filename);

    Json::Reader reader;

    reader.parse(file, levelData);

    for(int i = 0; i < levelData["data"].size(); i++){
        levelData["data"][i][1] = screenHeight-levelData["data"][i][1].asFloat(); 
    }

    std::cout << levelData << std::endl;
}

int main(){
    Game g;

    g.main();

    return 0;
}


