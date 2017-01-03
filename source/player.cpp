#include "player.hpp"
#include <grrlib.h>
#include "properties.hpp"

void Player::draw(void){
    GRRLIB_DrawImg(xpos, ypos, crosshairtex, 0, 1, 1, crosscolor);
}

void Player::movex(double amount){
    xpos += amount;
    xpos = xpos < 0? 0 : xpos + SPRITESIZE> WINDOWWIDTH ?
        WINDOWWIDTH - SPRITESIZE : xpos;
}

void Player::movey(double amount){
    ypos += amount; 
    ypos = ypos < 0? 0 : ypos + SPRITESIZE > WINDOWHEIGHT ?
        WINDOWHEIGHT - SPRITESIZE : ypos;
}