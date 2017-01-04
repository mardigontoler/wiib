

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

#include "player.hpp"
#include <grrlib.h>
#include <vector>
#include "properties.hpp"

void Player::draw(void)
{
    GRRLIB_DrawImg(xpos, ypos, crosshairtex, 0, 1, 1, crosscolor);
}

void Player::movex(double amount)
{
    xpos += amount;
    xpos = xpos < 0 ? 0 : xpos + SPRITESIZE > WINDOWWIDTH ? WINDOWWIDTH - SPRITESIZE : xpos;
}

void Player::movey(double amount)
{
    ypos += amount;
    ypos = ypos < 0 ? 0 : ypos + SPRITESIZE > WINDOWHEIGHT ? WINDOWHEIGHT - SPRITESIZE : ypos;
}
