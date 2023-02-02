#include <raylib.h>
#include <string>



class LevelCleared{
    

    public:
        LevelCleared(int screenWidth, int screenHeight, std::string time);
        int loop();
    private:
        enum Entries{
            NEXT,
            BACK,
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

        int screenHeight;
        int screenWidth;
        std::string time;
        void draw();
        int update();
        int numOfEntries;
        Entry entries[3];
        Entries selected;
        bool isSelected;
        Vector2 lastMousePos;
};
