#include <raylib.h>
#include <json/json.h>
class Player{
    public:
        
        void setPosition(const Vector2);
        Vector2 getPosition();

        void setStartPosition(const Vector2);

        int update(int, int, Camera2D*, Json::Value);
        void draw();

        Player();

        Texture2D slime;
        Texture2D slime2;

    private:
        Vector2 position;
        Vector2 dPosition;
        
        float height, width, dHeight, dWidth;

        float yForce;
        float xForce;
        float strength;
        float gravity;

        bool grounded;

        int spaceDown;
        
        bool direction;

        Rectangle checkHitbox(Json::Value);

        int frameWidth, frameHeight;

        Texture2D currentSlime;

        int rotation;

        
};
