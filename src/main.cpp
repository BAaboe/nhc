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
#include "levelCleared.h"
#include "config.h"

class Game {
    public:
        const int screenWidth = 800;
        const int screenHeight = 600;

        Texture2D cobal;

        Json::Value levelData;

        Player player;
        Camera2D camera;
    
        double deltaTime;

        double timeOnLevel;
       
        int main();

        void draw();

        int update();

        void loadLevel(int);
        
        int levelCleard();
        
        std::string getTimeString();
};
 
int Game::main(){
    InitWindow(screenWidth, screenHeight, "BAB");
     
    SetTargetFPS(60);
    
    SetExitKey(0);
    
    player.slime = LoadTexture("assets/slime.png");
    cobal = LoadTexture("assets/cobal.png"); 
    
    int autoLevel = 0;

    bool gameRunning = true;
    while(!WindowShouldClose() && gameRunning){
        std::cout << gameRunning << std::endl;
        
        int c;
        if(autoLevel == 0){
            Menu menu(screenWidth, screenHeight);
            c = menu.loop();
        }else{
            c = autoLevel*-1;
        }
        if(c == 2){
            gameRunning = false;
        }else if(c < 0){
            loadLevel(c*-1);
            float startX, startY;
            startX = levelData["start_pos"][0].asFloat();
            startY = levelData["start_pos"][1].asFloat();
            player.setPosition({startX, startY});            
        }



        camera = { 0 };
        camera.target = player.getPosition();
        camera.offset = {(float)screenWidth/2, (float)screenHeight/2};
        camera.rotation = .0f;
        camera.zoom = 1.0f;

        timeOnLevel = 0;

        while(!WindowShouldClose() && gameRunning){
            int code = update();
            if(code == 2){
                gameRunning = false;
                break;
            }else if(code == 3){
                break;
            }

            draw();
        }
    }
    UnloadTexture(player.slime);
    UnloadTexture(cobal);
    CloseWindow();
    

    return 0;
}

std::string Game::getTimeString(){
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
    
    return timeStr;
}

void Game::draw(){
    BeginDrawing();

    ClearBackground(BACKGROUNDCOLOR);
    

    DrawText(getTimeString().c_str(), 10, 10, 30, TEXTCOLOR);

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
    }
    player.draw();
    
    EndMode2D();

    EndDrawing();
}

int Game::update(){
    deltaTime = GetFrameTime();

    timeOnLevel += deltaTime;
    
    // Json::Value *blocksOnScreen = &levelData["data"];

    // while(true){
    //     int size = levelData["data"].size();
    //     int firstHalfI = (int) size/2;
    //     int secondHalfI = (int)size-firstHalfI;
    //     Json::Value secondHalf = (blocksOnScreen+sizeof(levelData["data"][0])*secondHalfI);
    //     std::cout << &secondHalf[0] << std::endl; 
    //     if(player.getPosition().x+screenWidth/2 > blocksOnScreen[size/2])
    // }

    int code = player.update(screenHeight, screenWidth, &camera, levelData);
    if(code == 3){
        int code2 = levelCleard();
        if(code2 == 2){
            return 2;
        }else if(code2 == 3){
            return 3;
        }
    }
    return 0;
}

int Game::levelCleard(){
    LevelCleared lc = LevelCleared(screenWidth, screenHeight, getTimeString());
    return lc.loop();

 //    while(!WindowShouldClose()){
 //    
 //        BeginDrawing();
 //        
 //        ClearBackground(RAYWHITE);
 //        
 //        std::string timeText = "You'r time was: " +getTimeString();
 //
 //        DrawText(timeText.c_str(), 0, 60, 50, TEXTCOLOR);
 // 
 //        DrawText("Leveld Cleard", 0, 0, 50, TEXTCOLOR);
 //
 //        EndDrawing();
 //    }
 //    return 2;
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

    levelData["goal"][1] = screenHeight-levelData["goal"][1].asFloat();
    levelData["start_pos"][1] = screenHeight-levelData["start_pos"][1].asFloat();

    std::cout << levelData << std::endl;
}

int main(){
    Game g;

    g.main();

    return 0;
}
