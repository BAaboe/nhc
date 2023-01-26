#include "menu.h"
#include <raylib.h>
#include <string>
#include <iostream>
#include "credits.h"

Menu::Menu(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
    entries[0].text = "Play";
    entries[0].entry = PLAY;
    entries[0].fontSize = 30;
    entries[1].text = "Settings";
    entries[1].entry = SETTINGS;
    entries[1].fontSize = 30;
    entries[2].text = "Credits";
    entries[2].entry = CREDITS;
    entries[2].fontSize = 30;
    entries[3].text = "Quit";
    entries[3].entry = QUIT;
    entries[3].fontSize = 30;
    
    numOfEntries = 4;
    selected = NONE;
    isSelected = false;
    lastMousePos = GetMousePosition();
}

int Menu::loop(){
    while(!WindowShouldClose()){
        int c = update();
        if(c == 1){
            return 1;
        }else if(c == 2){
            return 2;
        }
        draw();
    }
    return 1;
    
}

void Menu::draw(){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        std::string titleText = "Nokka Helt Cracy";
        int titleFontSize = 50;
        int titleWidth = MeasureText(titleText.c_str(), titleFontSize);
        
        int titleX = screenWidth/2-titleWidth/2;
        int titleY = 25;
        
        DrawText(titleText.c_str(), titleX,titleY,titleFontSize,BLACK);

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

int Menu::update(){
    if(IsKeyPressed(KEY_DOWN)){
        switch(selected){
            case NONE:
                selected = PLAY;
                break;
            case QUIT:
                selected = PLAY;
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
                selected = PLAY;
                break;
            case PLAY:
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
            case PLAY:
                std::cout << "Play pressed" << std::endl;
                return 1;
                break;
            case SETTINGS:
                std::cout << "Settings pressed" << std::endl;
                pressed = SETTINGS;
                break;
            case CREDITS:
                std::cout << "Credits pressed" << std::endl;
                pressed = CREDITS;
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
            case PLAY:
                std::cout << "Play pressed" << std::endl;
                return 1;
                break;
            case SETTINGS:
                std::cout << "Settings pressed" << std::endl;
                pressed = SETTINGS;
                break;
            case CREDITS:
                std::cout << "Credits pressed" << std::endl;
                pressed = CREDITS;
                break;
            case QUIT:
                std::cout << "Quit pressed" << std::endl;
                return 2;
                break;
            default:
                break;
        }
    }

    if(pressed == CREDITS){
        Credits creds(screenWidth, screenHeight);
        creds.loop();
    }
}
