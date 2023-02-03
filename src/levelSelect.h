#include <raylib.h>
#include <string>


class LevelSelect{
    public:
        LevelSelect(int screenWidth, int screenHeight);
        int loop();
    private:
        int screenHeight;
        int screenWidth;
        void draw();
        int update(Rectangle rect);
        int numOfLevels;
        bool isSelected;
        Vector2 lastMousePos;
};
