#include "credits.h"
#include <raylib.h>
#include <string>

Credits::Credits(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    numOfContributers = 2;
    contributers[0].name = "Benjamin \"BAaboe\" Mjaatvedt";
    contributers[0].role = "Lead And Only Developer";
    contributers[1].name = "Azzazzin";
    contributers[1].role = "Art";
}

int Credits::loop(){
    while(!WindowShouldClose()){
        int c = update();
        if(c == 1){
            return 1;
        }
        draw();
    }
    return 1;
}

int Credits::update(){
    if(IsKeyPressed(KEY_ESCAPE)){
        return 1;
    }

    backFontSize = 30;
    backWidth = MeasureText("Back", backFontSize);
    backX = screenWidth/2-backWidth/2;
    backY = screenHeight-backFontSize-25;
    backColor = BLACK;

    Vector2 mousePos = GetMousePosition();

    if(mousePos.x > backX && mousePos.x < backX+backWidth){
        if(mousePos.y > backY && mousePos.y < backY+backFontSize){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                return 1;
            }
            backColor = MAROON;
        }
    }
    return 0;
}

void Credits::draw(){
    BeginDrawing();
        ClearBackground(DARKGRAY);

        std::string titleText = "Credits";
        int titleFontSize = 50;
        int titleWidth = MeasureText(titleText.c_str(), titleFontSize);

        int titleX = screenWidth/2-titleWidth/2;
        int titleY = 25;

        DrawText(titleText.c_str(), titleX,titleY,titleFontSize,BLACK);

        int fontSize = 20;
        for(int i=0; i<numOfContributers; i++){
            std::string text = contributers[i].role + ": " + contributers[i].name;
            contributers[i].x = screenWidth/2-MeasureText(text.c_str(), fontSize)/2;
            
            if(i != 0){
                contributers[i].y = contributers[i-1].y+fontSize*2;
            }else{
                contributers[i].y = 250;
            }
            
            DrawText(text.c_str(), contributers[i].x, contributers[i].y, fontSize, BLACK);
        }




        DrawText("Back", backX, backY, backFontSize, backColor);

    EndDrawing();

}
