
#include <grrlib.h>

class Player{
    public:
        Player(int _x, int _y, GRRLIB_texImg * _crosshair):
            xpos(_x),
            ypos(_y),
            crosshairtex(_crosshair){

        }

        void draw(void);
        void movex(double amount);
        void movey(double amount);
        

    private:
        int xpos;
        int ypos;

        GRRLIB_texImg * crosshairtex;

};