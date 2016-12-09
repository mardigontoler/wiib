
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <fat.h>
#include <aesndlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <gcmodplay.h>

#include "stateStack.hpp"

// resource files converted to arrays

// color constants in hex
#define GRRLIB_WHITE 0xFFFFFFFF
#define GRRLIB_BLACK 0x000000FF

// prototypes for game states
void pauseState(void);
void playState(void);
void menuState(void);

static MODPlay modplay2;



int main(int argc, char **argv) {
	
	printf("Entering main\n");
	
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
    // Initialise the Wiimotes
    WPAD_Init();
    
    // init audio
    AESND_Init();
    
    
    //create a stack that's used to control the state of the game
    //the top item can be the menu, the game, or pause
    stateStack sstack;
    sstack.pushState(menuState);
    
    
    // try to load up sprite textures
    //GRRLIB_texImg * menutexture = GRRLIB_LoadTexture(menuImg);
    
    GRRLIB_SetBackgroundColour(0,0,0,255);
    // Loop forever
    while(1) {
        WPAD_ScanPads();  // Scan the Wiimotes
        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_2){
			
		}
        GRRLIB_FillScreen(GRRLIB_BLACK);
        
        
        //GRRLIB_DrawImg(xLoc,50,liptex,0,1,1,GRRLIB_WHITE);
        
        GRRLIB_Render();  // Render the frame buffer to the TV
    }
    
    
    //GRRLIB_FreeTexture(menutexture);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}



void menuState(void){
	printf("\nIn the menu...");
}
