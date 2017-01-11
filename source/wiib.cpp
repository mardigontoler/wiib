

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

#include <grrlib.h>
#include <stdlib.h>
#include <cstdio>
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
#include "graph.hpp"
#include <memory>
#include "properties.hpp"

#include "ecs.h"

// resource files converted to arrays adfasdf
#include "res/wiiblogo.h"
#include "res/circle.h"
#include "res/font/VTfont.hpp"

using namespace std;

class Wiib
{
  private:
    bool finished = false;

    vector<GRRLIB_texImg *> texPointers;
    GRRLIB_texImg *menutexture;
    GRRLIB_texImg *crosshair1;

    VTfont vtfont;
    GRRLIB_ttfFont *rawptrfont;
    static MODPlay modplay2;

    shared_ptr<Player> player1;
    shared_ptr<Player> player2;

    ecs::EntityManager entities;
    ecs::SystemManager playSystems;

    // using lambdas makes it easier to implement the stack of member methods
    function<void()> menulambda = [this] { menuState(); };
    function<void()> playlambda = [this] { playState(); };
    function<void()> pauselambda = [this] { pauseState(); };
    function<void()> fanfarelambda = [this] { fanfareState(); };
    function<void()> exitlambda = [this] { exitState(); };

  public:
    //create a stack that's used to control the state of the game
    //the top item can be the menu, the game, or pause
    stateStack sstack;

    // this needs to be called before a texture is used in sprites and stuff
    // these will be cleaned up with the freAllTextures method
    GRRLIB_texImg *registerTexture(const u8 *data)
    {
        GRRLIB_texImg *ptex = GRRLIB_LoadTexture(data);
        texPointers.push_back(ptex);
        return ptex;
    }

    void freeAllTextures(void)
    {
        for (auto &texture : texPointers)
        {
            GRRLIB_FreeTexture(texture);
        }
    }

    Wiib() : playSystems(entities)
    {
        // try to load up sprite textures and the font
        menutexture = registerTexture(wiiblogo);
        crosshair1 = GRRLIB_LoadTexture(circle);
        player1.reset(new Player(10, 10, crosshair1)); // resetting shared_ptr
        player2.reset(new Player(80, 80, crosshair1));
    }

    void playState(void)
    {
        u32 p1held = WPAD_ButtonsHeld(0);
        if (p1held & WPAD_BUTTON_DOWN)
        {
            player1->movex(CURSORSPEED);
        }
        if (p1held & WPAD_BUTTON_UP)
        {
            player1->movex(-CURSORSPEED);
        }
        if (p1held & WPAD_BUTTON_RIGHT)
        {
            player1->movey(-CURSORSPEED);
        }
        if (p1held & WPAD_BUTTON_LEFT)
        {
            player1->movey(CURSORSPEED);
        }

        // drawing game entities
        player1->draw();
        player2->draw();

        playSystems.update(0);

    }

    void pauseState(void)
    {
    }

    void exitState(void){
    }


    void fanfareState(void)
    {
    }

    void menuState(void)
    {
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
        {
            sstack.pushState(playlambda);
        }
    }

    void run(void)
    {
        // Initialise the Graphics & Video subsystem
        GRRLIB_Init();
        // Initialise the Wiimotes
        WPAD_Init();
        WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

        // For some reason, the font won't load correctly in the constructor, so load it here
        rawptrfont = GRRLIB_LoadTTF(vtfont.data, vtfont.size);

        // init audio
        AESND_Init();

        sstack.pushState(menulambda);

        GRRLIB_SetBackgroundColour(20, 20, 20, 255);

        #include "res/testMapNodes.hpp"
        Graph g(nodes1, nodeConnections1);

        static char buffer[255]; // temporary buffer used for printing
        
        // systems need to be added to the manager for
        // their update to work
        playSystems.add<DrawingSystem>();
        playSystems.add<PathSystem>();

        ecs::Entity testent = entities.create();
        testent.add<HitPoints>(100);
        testent.add<Drawable>(crosshair1);
        testent.add<Path>();
        Path& p = testent.get<Path>();
        p.vertices = g.getPath(0, 2);
        testent.add<Status>(200, 200);

        while (true)
        {
            WPAD_ScanPads(); // Scan the Wiimotes
            // If [HOME] was pressed on the first Wiimote, break out of the loop
            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
                sstack.pushState(exitlambda);

            GRRLIB_FillScreen(GRRLIB_BLACK);

            sstack.top()();
            //Allegiance& alleg = testent.get<Allegiance>();
            //sprintf(buffer, "%d  ", alleg.alliedID);
            //GRRLIB_PrintfTTF(200, 200, rawptrfont, buffer, 30, 0x55FFFFFF);
            GRRLIB_Render(); // Render the frame buffer to the TV
        }
        freeAllTextures();
        GRRLIB_FreeTTF(rawptrfont);

        GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
        exit(0);       // Use exit() to exit a program, do not use 'return' from main()
    }
};

int main(int argc, char **argv)
{

    Wiib game;
    game.run();
}
