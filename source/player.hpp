#pragma once
#include <grrlib.h>
#include <vector>
#include <memory>
#include <iostream>
#include "properties.hpp"
#include "GameObject.hpp"

using namespace std;

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
        void grab(vector<GameObject>& objects);
        

    protected:
        f32 xpos;
        f32 ypos;
        GRRLIB_texImg * crosshairtex;
        shared_ptr<GameObject> grabbed;

};