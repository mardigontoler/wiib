#include "player.hpp"
#include <grrlib.h>

void Player::draw(void){
    GRRLIB_DrawImg(xpos, ypos, crosshairtex, 0, 1, 1, 0xFFFFFFFF);
}

void Player::movex(double amount){
    xpos += amount;

}

void Player::movey(double amount){
    ypos += amount; 
}