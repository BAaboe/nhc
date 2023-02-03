#include "levelCleared.h"
#include <raylib.h>
#include <string>
#include <iostream>
#include "credits.h"

LevelCleared::LevelCleared(int screenWidth, int screenHeight, std::string time){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->time = time;
    

    entries[0].text = "NEXT";
    entries[0].entry = NEXT;
    entries[0].fontSize = 30;
    entries[1].text = "BACK";
    entries[1].entry = BACK;
    entries[1].fontSize = 20;
    entries[2].text = "QUIT";
    entries[2].entry = QUIT;
    entries[2].fontSize = 20;
    
    numOfEntries = 3;
    selected = NONE;
    isSelected = false;
    lastMousePos = GetMousePosition();
}

int LevelCleared::loop(){
    while(!WindowShouldClose()){
        int c = update();
        if(c == 1){
            return 1;
        }else if(c == 2){
            return 2;
        }
        draw();
    }
    return 2;
    
}

void LevelCleared::draw(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    std::string titleText = "Level Cleared";
    int titleFontSize = 50;
    int titleWidth = MeasureText(titleText.c_str(), titleFontSize);
    
    int titleX = screenWidth/2-titleWidth/2;
    int titleY = 25;
    
    std::string timeText = "Time: " + time;
    int timeFontSize = 40;
    int timeWidth = MeasureText(timeText.c_str(), timeFontSize);

    int timeX = screenWidth/2-timeWidth/2;
    int timeY = 80;

    DrawText(timeText.c_str(), timeX, timeY, timeFontSize, BLACK);    
    DrawText(titleText.c_str(), titleX,titleY,titleFontSize, BLACK);

    for(int i=0; i<numOfEntries; i++){

        entries[i].x = screenWidth/2 - MeasureText(entries[i].text.c_str(), entries[i].fontSize)/2;
        
        if(i != 0){
            entries[i].y = entries[i-1].y+entries[i-1].fontSize*2;
        }else{
            entries[i].y = 150;
        }
        
        Color color = BLACK;
        if(entries[i].entry == selected){
            color = MAROON;
        }

        DrawText(entries[i].text.c_str(), entries[i].x, entries[i].y, entries[i].fontSize, color);
    }

    EndDrawing();
    
    
}

int LevelCleared::update(){
    if(IsKeyPressed(KEY_DOWN)){
        switch(selected){
            case NONE:
                selected = NEXT;
                break;
            case QUIT:
                selected = NEXT;
                break;
            default:
                int sel = selected;
                selected = static_cast<Entries>(++sel);
                break;
        }
    }

    if(IsKeyPressed(KEY_UP)){
        switch(selected){
            case NONE:
                selected = NEXT;
                break;
            case NEXT:
                selected = QUIT;
                break;
            default:
                int sel = selected;
                selected = static_cast<Entries>(--sel);
                break;
        }
    }

    Vector2 mousePos = GetMousePosition();
    

    if(mousePos.x != lastMousePos.x && mousePos.y != lastMousePos.y){
        for(int i=0; i<numOfEntries; i++){
            int x1 = entries[i].x;
            int x2 = x1+MeasureText(entries[i].text.c_str(), entries[i].fontSize);
            int y1 = entries[i].y;
            int y2 = y1+entries[i].fontSize;
            if(mousePos.x > x1 && mousePos.x < x2){
                if(mousePos.y > y1 && mousePos.y < y2){
                    selected = entries[i].entry;
                    isSelected = true;
                    break;
                }else if(i == 2){
                    isSelected = false;
                }
            }    
        }

        if(!isSelected){
            selected = NONE;
        }
    }

    lastMousePos = mousePos;
    
    Entries pressed = NONE;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isSelected){
        switch (selected) {
            case NEXT:
                std::cout << "Next pressed" << std::endl;
                pressed = NEXT;
                break;
            case BACK:
                std::cout << "BACK pressed" << std::endl;
                pressed = BACK;
                break;
            case QUIT:
                std::cout << "Quit pressed" << std::endl;
                return 2;
                break;
            default:
                break;
        }
    }
    if(IsKeyPressed(KEY_ENTER)){
        switch (selected) {
            case NEXT:
                std::cout << "Next pressed" << std::endl;
                pressed = NEXT;
                break;
            case BACK:
                std::cout << "BACK pressed" << std::endl;
                pressed = BACK;
                break;
            case QUIT:
                std::cout << "Quit pressed" << std::endl;
                return 2;
                break;
            default:
                break;
        }
    }

}
