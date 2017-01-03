#pragma once
#include <grrlib.h>
#include "properties.hpp"

class Player{
    public:
        unsigned int hp = 100; // player health. do fanfare and restart if 0
        u32 crosscolor = 0xFFFFFFFF;
        Player(int _x, int _y, GRRLIB_texImg * _crosshair):
            xpos(_x),
            ypos(_y),
            crosshairtex(_crosshair){

        }

        void draw(void);
        void movex(double amount);
        void movey(double amount);
        

    private:
        int xmin = 0;
        int ymin = 0;
        int xmax = WINDOWWIDTH;
        int ymax = WINDOWHEIGHT;

        f32 xpos;
        f32 ypos;

        GRRLIB_texImg * crosshairtex;

};