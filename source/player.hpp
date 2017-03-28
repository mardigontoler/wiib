
//Wiib - a Wii Homebrew multiplayer game
//Copyright (C) 2017 Mardigon Toler

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <grrlib.h>
#include <vector>
#include <memory>
#include <iostream>
#include "properties.hpp"
#include "GameObject.hpp"
#include "ecs.h"


class Player
{
  public:
    u32 crosscolor = 0xFFFFFFFF;
    void draw(void);
    void movex(double amount);
    void movey(double amount);

    f32 xpos;
    f32 ypos;
    int id;
    GRRLIB_texImg *crosshairtex;
    shared_ptr<Entity> grabbed;

    Player(int _x, int _y, int _id, GRRLIB_texImg *_crosshair):
        xpos(_x),
        ypos(_y),
        id(_id),
        crosshairtex(_crosshair)
                                                        
    {
    }
};

// A component that lets systems access the players
struct PlayerPtrComp{
        shared_ptr<Player> pptr;
};


