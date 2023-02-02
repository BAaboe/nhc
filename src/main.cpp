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
        Texture2D cobal;

        Json::Value levelData;

        Player player;
        Camera2D camera;
    
        double deltaTime;

        double timeOnLevel;
       
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
    cobal = LoadTexture("assets/cobal.png"); 


    camera = { 0 };
    camera.target = player.getPosition();
    camera.offset = {(float)screenWidth/2, (float)screenHeight/2};
    camera.rotation = .0f;
    camera.zoom = 1.0f;

    timeOnLevel = 0;

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
    
    std::string timeStr = "";
    int mins = (int) timeOnLevel / 60;
    int secs = (int)timeOnLevel % 60;
    
    std::string minsStr = std::to_string(mins);
    if(mins < 10){
        minsStr = "0"+std::to_string(mins);
    }
    
    std::string secsStr = std::to_string(secs);
    if(secs < 10){
        secsStr = "0"+std::to_string(secs);    
    }

    timeStr = minsStr+ ":" + secsStr;   

    DrawText(timeStr.c_str(), 10, 10, 30, BLACK);

    BeginMode2D(camera);

    for(int i = 0; i<levelData["data"].size(); i++){
        Json::Value block = levelData["data"][i];

        int height, width, x, y;
        x = block[0].asInt();
        y = block[1].asInt();
        width = block[2].asInt();
        height = block[3].asInt(); 

        int blockWidth = 50;
        int blockHeight = 50;
        for(int ii=0; ii<width/blockWidth; ii++){
            for(int iii=0; iii<height/blockHeight; iii++){
                DrawTextureEx(cobal, {(float)x+blockWidth*ii, (float)y+blockHeight*iii}, 0, 1, WHITE);
            }
        }

        //Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.width};

        //Rectangle destRec = {block[0].asFloat(), block[1].asFloat(), block[2].asFloat(), block[3].asFloat()};

        //Vector2 origin = {(float)texture.width, (float)texture.width};

        //DrawTextureEx(texture, {block[0].asFloat(), block[1].asFloat()}, 0, block[3].asFloat()/texture.height, WHITE);
        //DrawTexturePro(texture, sourceRec, destRec, origin, 0.f, WHITE);
        // Rectangle rect = (Rectangle){block[0].asFloat(), block[1].asFloat(), block[2].asFloat(), block[3].asFloat()};
        // DrawRectangleRec(rect, GRAY);
    }
    player.draw();
    
    EndMode2D();

    EndDrawing();
}

void Game::update(){
    deltaTime = GetFrameTime();

    timeOnLevel += deltaTime;
    
    Json::Value *blocksOnScreen = &levelData["data"];

    // while(true){
    //     int size = levelData["data"].size();
    //     int firstHalfI = (int) size/2;
    //     int secondHalfI = (int)size-firstHalfI;
    //     Json::Value secondHalf = (blocksOnScreen+sizeof(levelData["data"][0])*secondHalfI);
    //     std::cout << &secondHalf[0] << std::endl; 
    //     if(player.getPosition().x+screenWidth/2 > blocksOnScreen[size/2])
    // }

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
