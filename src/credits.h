#include <raylib.h>
#include <string>

struct Contributer{
    std::string name;
    std::string role;
    int x;
    int y;
};

class Credits{
    public:
        Credits(int screenWidth, int screenHeight); 
        int loop();
    private:
        int update();
        void draw();
        int screenHeight;
        int screenWidth;
        Contributer contributers[2];
        int numOfContributers;       

        int backX, backY, backFontSize, backWidth;
        Color backColor;
};
