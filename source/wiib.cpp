
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
#include "player.hpp"
#include <memory>

// resource files converted to arrays
#include "res/wiiblogo.h"
#include "res/circle.h"

// color constants in hex
#define GRRLIB_WHITE 0xFFFFFFFF
#define GRRLIB_BLACK 0x000000FF

using namespace std;

class Wiib{
    private:
        GRRLIB_texImg * menutexture;
        GRRLIB_texImg * crosshair1;
        static MODPlay modplay2;
        shared_ptr<Player> player1;
        // unique_ptr<Player> player2;
        double xloc = 0;

        // using lambdas makes it easier to implement the stack of member methods
        function<void()> menulambda = [this]{menuState();};
        function<void()> playlambda = [this]{playState();};
        function<void()> pauselambda =[this]{pauseState();};
        
    public:
        //create a stack that's used to control the state of the game
        //the top item can be the menu, the game, or pause
        stateStack sstack;

        Wiib(){
            // try to load up sprite textures
            menutexture = GRRLIB_LoadTexture(wiiblogo);
            crosshair1 = GRRLIB_LoadTexture(circle);
            player1.reset(new Player(10, 10, crosshair1)); // resetting shared_ptr

        }

        void playState(void){
            static f32 xloc = 150;
            if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_1){
                xloc = 500;
                GRRLIB_ObjectViewScale(0.5,0.5,0.5);
            }
            else{
                xloc = 150;
                GRRLIB_ObjectViewScale(1,1,1);
            }
            if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT){
                player1->movex(3);
            }
            GRRLIB_DrawImg(xloc,150,menutexture,0,1,1,GRRLIB_WHITE);
            player1->draw();

        }

        void pauseState(void){

        }

        void menuState(void)
        {
            
            if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_A){
                sstack.pushState(playlambda);
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



            // // REMOVE LATER -- TESTING ONLY
            // Player player1(10,10,crosshair1);

            GRRLIB_SetBackgroundColour(0, 0, 0, 255);

            // Loop forever
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
 
                sstack.top()();
                //GRRLIB_DrawImg(150,150,menutexture,0,1,1,GRRLIB_WHITE);
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

