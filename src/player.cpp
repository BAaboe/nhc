#include "player.h"
#include <cstddef>
#include <cstdio>
#include <json/value.h>
#include <raylib.h>
#include <iostream>
#include <json/json.h>
#include <type_traits>

void Player::setPosition(const Vector2 position){
    this->position = position;
}

Vector2 Player::getPosition(){
    return this->position;
}



Player::Player(){
    grounded = false;
    yForce = 0.0f;
    xForce = 0.0f;
    strength = 20.0f;
    gravity = .981f;

    height = 40;
    width = 54;
    dHeight = 40;
    dWidth = 54;

    spaceDown = -1;

    rotation = 0;
     
}

int Player::update(int screenHeight, int screenWidth, Camera2D *camera, Json::Value levelData){
    
    Json::Value level = levelData["data"];
    
    Vector2 startPosition = (Vector2){levelData["start_pos"][0].asFloat(), levelData["start_pos"][1].asFloat()};
    
    Rectangle goalPosition = (Rectangle){levelData["goal"][0].asFloat(), 
                                         levelData["goal"][1].asFloat(), 
                                         levelData["goal"][2].asFloat(), 
                                         levelData["goal"][3].asFloat()};

    currentSlime = slime;
    position.y += yForce;

    if(IsKeyDown(KEY_RIGHT)){direction=false;}
    if(IsKeyDown(KEY_LEFT)){direction=true;}

    if(!grounded){
        if(direction){
            position.x += xForce;
        } else{
            position.x -= xForce;
        }
    }
    if(position.y + height >= screenHeight){
        // position.y = screenHeight - height;
        // grounded = true;
        position = startPosition;
        camera->target.x = position.x;
        xForce = 0;
    }


    Rectangle rect = checkHitbox(level);

    if(position.x <= 0){
        position.x = 0;
    }



    if(IsKeyDown(KEY_SPACE) && grounded){
        if(spaceDown == -1){
            spaceDown = 0;
            dHeight = height;
            dWidth = width;
            dPosition = position;
        }
        if(height >= dHeight/1.8){
            spaceDown += 1;
            position.y = dPosition.y + spaceDown/4;
            height = dHeight - spaceDown/4;
            width = dWidth + spaceDown/6;
        }
    }

    if(IsKeyUp(KEY_SPACE) && spaceDown != -1){
        yForce = -spaceDown/4.5;
        xForce = -spaceDown/10;
        grounded = false;
        height = dHeight;
        width = dWidth;
        position = dPosition;
        spaceDown = -1;
    }

    if(grounded){
        if(position.y + height > screenHeight){
            position.y = screenHeight - height;
        }
        if(position.y + height > rect.y){
            if(rect.y != -100){
                position.y = rect.y - height;
            }
        }
        yForce = 0;
    } else{
        yForce += gravity;
        if (xForce > 0){xForce = yForce;}
    }


    if(position.x+width/2 <= (float)screenWidth/2){
        camera->target.x = 0;
        camera->offset.x = 0;
    } else if(spaceDown == -1){
        camera->target.x = position.x+width/2;
        camera->offset.x = (float)screenWidth/2;
    }
    

    if(position.x < goalPosition.x+goalPosition.width && position.x+width > goalPosition.x){
        if(position.y+height == goalPosition.y)
        return 3;
    }
    return 0;
}

void Player::draw(){
    Rectangle sourceRec;
    if(direction){
        sourceRec = {0.0f, 0.0f, (float)-dWidth, (float)dHeight};
    } else{
        sourceRec = {0.0f, 0.0f, (float)dWidth, (float)dHeight};
    }

    Rectangle destRec = {position.x+dWidth, position.y+dHeight, (float)width, (float)height};

    Vector2 origin = {dWidth, dHeight};

    DrawTexturePro(currentSlime, sourceRec, destRec, origin, rotation, WHITE);

    //DrawRectangleLines(position.x, position.y, width, height, MAROON);
    //DrawRectangle(position.x, position.y, width, height, BLUE);
}

Rectangle Player::checkHitbox(Json::Value level){
    for(int i=0; i<level.size(); i++){
        if(position.x+width-(width/4) > level[i][0].asFloat() && position.x+(width/4) < level[i][0].asFloat()+level[i][2].asFloat()){
            if(position.y+height >= level[i][1].asFloat() && position.y <= level[i][1].asFloat()){
                grounded = true;
                Rectangle rect = (Rectangle){level[i][0].asFloat(), level[i][1].asFloat(), level[i][2].asFloat(), level[i][3].asFloat()};
                return rect;
            }else if(position.y > level[i][1].asFloat()){
                xForce = 0;
                if(position.x > level[i][0].asFloat()){
                    position.x = level[i][0].asFloat()+level[i][2].asFloat();
                } else if(position.x < level[i][0].asFloat()+level[i][2].asFloat()){
                    position.x = level[i][0].asFloat()-width;
                }
                return (Rectangle) {0,-100,0,0};
            } 
        }
    }
    return (Rectangle) {0,-100,0,0};
}

