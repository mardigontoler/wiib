
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

// resource files converted to arrays
#include "res/wiiblogo.h"

// color constants in hex
#define GRRLIB_WHITE 0xFFFFFFFF
#define GRRLIB_BLACK 0x000000FF

using namespace std;

class Wiib{
    private:
        GRRLIB_texImg * menutexture;
        static MODPlay modplay2;
        double xloc = 0;

        // using lambdas makes it easier to implement the stack of member methods
        function<void()> menulambda = [this]{menuState();};
        function<void()> playlambda = [this]{playState();};
        function<void()> pauselambda =[this]{pauseState();};
        
    public:
        //create a stack that's used to control the state of the game
        //the top item can be the menu, the game, or pause
        stateStack sstack;

        void playState(void){

        }

        void pauseState(void){

        }

        void menuState(void)
        {
            PAD_ScanPads();
            if(PAD_ButtonsHeld(1) & WPAD_BUTTON_A){
                GRRLIB_DrawImg(240,240, menutexture, 0, 2, 2, GRRLIB_WHITE);
            }


        }


        void run(void){
            // Initialise the Graphics & Video subsystem
            GRRLIB_Init();
            // Initialise the Wiimotes
            WPAD_Init();

            // init audio
            AESND_Init();
            
            sstack.pushState(menulambda);

            // try to load up sprite textures
            menutexture = GRRLIB_LoadTexture(wiiblogo);

            GRRLIB_SetBackgroundColour(0, 0, 0, 255);
            // Loop forever
            double x = 0;
            while (1)
            {
                WPAD_ScanPads(); // Scan the Wiimotes
                // If [HOME] was pressed on the first Wiimote, break out of the loop
                // if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
                //     break;
                // if (WPAD_ButtonsDown(0) & WPAD_BUTTON_2)
                // {
                // }
                GRRLIB_FillScreen(GRRLIB_BLACK);

                if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_A){
                    GRRLIB_DrawImg(240,240, menutexture, 0, 2, 2, GRRLIB_WHITE);
                }   
                //sstack.top()();
                //GRRLIB_DrawImg(xLoc,50,liptex,0,1,1,GRRLIB_WHITE);


                GRRLIB_Render(); // Render the frame buffer to the TV
            }

            //GRRLIB_FreeTexture(menutexture);
            GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
            exit(0);       // Use exit() to exit a program, do not use 'return' from main()
        }
};




int main(int argc, char **argv)
{

    printf("Entering main\n");
    Wiib game;
    game.run();
    
}

