#include "levelSelect.h"
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
        ClearBackground(RAYWHITE);
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
                    code = update(rect);
                }
                Color color = BLACK;
                if(code == 1){
                    color = MAROON;
                } else if(code == 2){
                    return (i*3+ii+1 )*-1;
                }
                DrawRectangleRoundedLines(rect, .2, 1, 5, color);
                int textWidth = MeasureText(std::to_string(i*3+ii+1).c_str(), fontSize);
                DrawText(std::to_string(i*3+ii+1).c_str(), rect.x+width/2-textWidth/2, rect.y+height/2-fontSize/2, fontSize, color);
                
            }
        }
        EndDrawing();
        first = false;
        // update();
        //
        // draw();
    }
    return 2;
}

int LevelSelect::update(Rectangle rect){
    Vector2 mousePos = GetMousePosition();
    if(mousePos.x > rect.x && mousePos.x < rect.x+rect.width){
        if(mousePos.y > rect.y && mousePos.y < rect.y+rect.height){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                return 2;
            }
            return 1;
        }
    }
    return 0;
}

void LevelSelect::draw(){

}
