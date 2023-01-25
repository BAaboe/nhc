#include <raylib.h>
#include <string>

enum Entries{
    PLAY,
    SETTINGS,
    CREDITS,
    QUIT,
    NONE
};

struct Entry{
    int x;
    int y;
    std::string text;
    int fontSize;
    Entries entry;
};

class Menu{
    public:
        Menu(int screenWidth, int screenHeight);
        int loop();
    private:
        int screenHeight;
        int screenWidth;
        void draw();
        int update();
        int numOfEntries;
        Entry entries[4];
        Entries selected;
        bool isSelected;
        Vector2 lastMousePos;
};
