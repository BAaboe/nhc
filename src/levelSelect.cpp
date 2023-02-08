#include "levelSelect.h"
#include <exception>
#include <raylib.h>
#include <string>
#include <iostream>

LevelSelect::LevelSelect(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->numOfLevels = 10;
}

int LevelSelect::loop(){
    bool first = true;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        std::string titleText = "Level Select";
        int titleFontSize = 50;
        int titleWidth = MeasureText(titleText.c_str(), titleFontSize);
        
        int titleX = screenWidth/2-titleWidth/2;
        int titleY = 25;
        
        DrawText(titleText.c_str(), titleX,titleY,titleFontSize,BLACK);
        
        int width = 100;
        int height = 100;
        int padding = 25;
        int fontSize = 30;

        for(int i = 0; i<numOfLevels/3; i++){
            int x = screenWidth/2-(width*3+padding*2)/2;
            for(int ii=0; ii<numOfLevels/3; ii++){
                int y = screenHeight/2-(height*3+padding*2)/2;
                Rectangle rect = (Rectangle){(float)x+(padding+width)*ii, (float)y+(padding+height)*i, (float)width, (float)height};
                int code = 0;
                if(!first){
                    code = update(rect, i*3+ii+1);
                }
                Color color = BLACK;
                if(code == 1){
                    color = MAROON;
                } else if(code == 2){
                    EndDrawing();
                    return (i*3+ii+1 )*-1;
                }
                DrawRectangleRoundedLines(rect, .2, 1, 5, color);
                int textWidth = MeasureText(std::to_string(i*3+ii+1).c_str(), fontSize);
                DrawText(std::to_string(i*3+ii+1).c_str(), rect.x+width/2-textWidth/2, rect.y+height/2-fontSize/2, fontSize, color);
                
            }
        }
        
        int backFontSize = 30;
        int backWidth = MeasureText("Back", backFontSize);
        int backX = screenWidth/2-backWidth/2;
        int backY = screenHeight-backFontSize-25;

        int code = update((Rectangle){(float)backX, (float)backY, (float)backWidth, (float)backFontSize}, 10); 
        
        Color backColor = BLACK;
        if(code == 1){
            backColor = MAROON;
        } else if (code == 2) {
            EndDrawing();
            return 0;
        }
        
        DrawText("Back", backX, backY, backFontSize, backColor);

        EndDrawing();
        first = false;
        // update();
        //
        // draw();
    }
    return 2;
}

int LevelSelect::update(Rectangle rect, int curent){

    Vector2 mousePos = GetMousePosition();

    if(mousePos.x > rect.x && mousePos.x < rect.x+rect.width){
        if(mousePos.y > rect.y && mousePos.y < rect.y+rect.height){
            selected = curent;
        }
    }
    if(curent == 1){

        if(IsKeyPressed(KEY_LEFT)){
            if(selected-1 > 0){
                selected -= 1;
            }
        } else if(IsKeyPressed(KEY_RIGHT)){
            if(selected+1 < 10){
                selected += 1;
            }
        } else if(IsKeyPressed(KEY_DOWN)){
            if(selected+3 > 10){
                selected = 10;
            } else{
                selected+=3; 
            }
        } else if(IsKeyPressed(KEY_UP)){
            if(selected-3 > 0){
                selected -= 3;
            }
        }
    }
    std::cout << selected << std::endl;
    if(selected == curent){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return 2;
        } else if(IsKeyPressed(KEY_ENTER)){
            return 2;
        }
        return 1;
    }

    return 0;

}

void LevelSelect::draw(){

}
