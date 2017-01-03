
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <fat.h>
#include <aesndlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h>
#include <unordered_map>
#include "stateStack.hpp"
#include <stack>
#include <math.h>
#include <vector>
#include "player.hpp"
#include <memory>
#include "properties.hpp"

// resource files converted to arrays
#include "res/wiiblogo.h"
#include "res/circle.h"

using namespace std;


class Wiib{
    private:
        bool finished = false;

        vector<GRRLIB_texImg*> texPointers;
        GRRLIB_texImg * menutexture;
        GRRLIB_texImg * crosshair1;

        static MODPlay modplay2;

        shared_ptr<Player> player1;
        shared_ptr<Player> player2;

        // using lambdas makes it easier to implement the stack of member methods
        function<void()> menulambda = [this]{menuState();};
        function<void()> playlambda = [this]{playState();};
        function<void()> pauselambda =[this]{pauseState();};
        
    public:
        //create a stack that's used to control the state of the game
        //the top item can be the menu, the game, or pause
        stateStack sstack;

        // this needs to be called before a texture i used in sprites and stuff
        // these will be cleaned up with the freAllTextures method
        GRRLIB_texImg *  registerTexture(const u8 * data){
            GRRLIB_texImg * ptex = GRRLIB_LoadTexture(data);
            texPointers.push_back(ptex);
            return ptex;
        }

        void freeAllTextures(void)
        {
            // for (auto &texture : texPointers)
            // {
            //     GRRLIB_FreeTexture(texture);
            // }
        }
        Wiib(){
            // try to load up sprite textures
            menutexture = GRRLIB_LoadTexture(wiiblogo);
            // menutexture = registerTexture(wiib;logo);
            // crosshair1 = registerTexture(circle);
            crosshair1 = GRRLIB_LoadTexture(circle);
            // player1.reset(new Player(10, 10, crosshair1)); // resetting shared_ptr
            // player2.reset(new Player(80, 80, crosshair1));
        }

        void playState(void){
            
            if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT){
                player1->movex(3);
            }
            // GRRLIB_DrawImg(150,150,menutexture,0,1,1,GRRLIB_WHITE);
            
            // drawing game entities
            // player1->draw();
            //player2->draw();

        }

        void pauseState(void){

        }

        void menuState(void)
        {
            if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A){
                // sstack.pushState(playlambda);
                
            }
            
        }


        void run(void){
            // Initialise the Graphics & Video subsystem
            GRRLIB_Init();
            // Initialise the Wiimotes
            WPAD_Init();
            WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

            // init audio
            AESND_Init();
            
            sstack.pushState(menulambda);

            GRRLIB_SetBackgroundColour(20,20,20, 255);
            double x = 0;
            // Loop forever
            while (1)
            {
                x += 0.1;
                WPAD_ScanPads(); // Scan the Wiimotes
                // If [HOME] was pressed on the first Wiimote, break out of the loop
                // if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
                    // break;

                GRRLIB_FillScreen(GRRLIB_BLACK);
 
                // sstack.top()();
                GRRLIB_DrawImg(150 + 10 * sin(x),150,menutexture,0,1,1,GRRLIB_WHITE);
                GRRLIB_Render(); // Render the frame buffer to the TV
            }
            GRRLIB_FreeTexture(menutexture);
            GRRLIB_FreeTexture(crosshair1);
            freeAllTextures();
            
            GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
            exit(0);       // Use exit() to exit a program, do not use 'return' from main()
        }
};



int main(int argc, char **argv)
{

    Wiib game;
    game.run();
    
}

