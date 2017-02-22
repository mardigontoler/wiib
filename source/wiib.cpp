
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
#include <cstdlib>
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

// resource files converted to arrays
#include "res/wiiblogo.h"
#include "res/circle.h"
#include "res/font/VTfont.hpp"
#include "res/tiles.h"
#include "res/gentlesir.h"
#include "res/testMapNodes.hpp"

using namespace std;

char buffer[256]; // temporary buffer used for printing

class Wiib
{
  private:
    bool finished = false;

    vector<GRRLIB_texImg *> texPointers;
    GRRLIB_texImg *menutexture;
    GRRLIB_texImg *crosshair1;
    GRRLIB_texImg *tilestexture;

    VTfont vtfont;
    GRRLIB_ttfFont *rawptrfont;
    MODPlay gentlesirMOD;

    shared_ptr<Player> player1;
    shared_ptr<Player> player2;

    shared_ptr<Graph> graphptr;

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
    //the top item can be the menu, the game, or pause, etc..
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
        tilestexture = registerTexture(tiles);
        crosshair1 = GRRLIB_LoadTexture(circle);
        
        player1.reset(new Player(10, 10, 1, crosshair1)); // resetting shared_ptr
        player2.reset(new Player(80, 80, 2, crosshair1));
        graphptr.reset(new Graph(nodes1, nodeConnections1));


        // init audio
        AESND_Init();
        MODPlay_Init(&gentlesirMOD);
        MODPlay_SetMOD(&gentlesirMOD, gentlesir);
        MODPlay_Start(&gentlesirMOD);
    }

    void playState(void)
    {
        // drawing game entities
        renderTiles(tilestexture, level1data, level1width);
        player1->draw();
        player2->draw();

        playSystems.update(0);
    }

    void pauseState(void)
    {
    }

    void exitState(void)
    {
        finished = true;
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


    // a 2D array is faked with a 1D array using division and
    // modulus with the intended width of the 2D array
    void renderTiles(GRRLIB_texImg* tilemap, vector<int>& tileIndices, int width)
    {
        unsigned int j = 0;
        unsigned int i = 0;
        for (; i < tileIndices.size(); i++)
        {
            j = i / width; // we use integer division for the vertical position
            // we use the remainder of this division for the horizontal position
            GRRLIB_DrawTile((i % width) * 32,
                            j * 32,
                            tilemap, 0, 1, 1, 0xFFFFFFFF,
                            tileIndices[i] - 1);
        }
    }

    void run(void)
    {
        // Initialise the Graphics & Video subsystem
        GRRLIB_Init();
        // Initialise the Wiimotes
        WPAD_Init();
        WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
        GRRLIB_InitTileSet(tilestexture, 32, 32, 0);

        // For some reason, the font won't load correctly in the constructor, so load it here
        rawptrfont = GRRLIB_LoadTTF(vtfont.data, vtfont.size);

        sstack.pushState(menulambda);

        GRRLIB_SetBackgroundColour(20, 20, 20, 255);

        // systems need to be added to the manager for
        // their update to work
        playSystems.add<DrawingSystem>();
        playSystems.add<PathSystem>();
        playSystems.add<InputSystem>();

        // create Player Entities out of the pointers to
        // the player objects
        ecs::Entity p1ent = entities.create();
        ecs::Entity p2ent = entities.create();
        p1ent.add<PlayerPtrComp>(player1);
        p2ent.add<PlayerPtrComp>(player2);


        ecs::Entity testent = entities.create();
        testent.add<HitPoints>(100);
        testent.add<Drawable>(crosshair1);
        testent.add<Path>();
        testent.add<Allegiance>(1);
        Path &p = testent.get<Path>();
        p.vertices = graphptr->getPath(0, 26);
        testent.add<Status>(200, 200);

        // we need to register the graph as an entity so that
        // systems can get at it
        ecs::Entity graphEnt = entities.create();
        graphEnt.add<GraphPointer>(graphptr);

        while (!finished)
        {
            WPAD_ScanPads(); // Scan the Wiimotes
            // If [HOME] was pressed on the first Wiimote, break out of the loop
            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
                sstack.pushState(exitlambda);

            GRRLIB_FillScreen(GRRLIB_BLACK);

            sstack.top()();
            // GRRLIB_DrawTile(275, 275, tilestexture, 0, 1, 1, 0xFFFFFFFF, 0);
            //Allegiance& alleg = testent.get<Allegiance>();
            //sprintf(buffer, "%d  ", alleg.alliedID);
            GRRLIB_PrintfTTF(200, 200, rawptrfont, buffer, 30, 0x55FFFFFF);
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
    srand(time(0)); // seed rng
    Wiib game;
    game.run();
}
