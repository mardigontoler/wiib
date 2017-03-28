
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

#include "GameObject.hpp"
#include <grrlib.h>
#include "ecs.h"
#include "misc.hpp"
#include <memory>
#include <wiiuse/wpad.h>
#include <ctime>
#include "player.hpp"
#include "properties.hpp"
#include "entityUtil.hpp"
#include <cstdlib>

f32 x;

void DrawingSystem::update(float time)
{
    for (auto entity : entities().with<Drawable, Status>())
    {
        Status &status = entity.get<Status>();
        Drawable &drawable = entity.get<Drawable>();
        GRRLIB_DrawImg(status.xpos, status.ypos, drawable.ptexture, 0, 1, 1, drawable.color);
    }
}

void PathSystem::update(float time)
{
    tuple<f32, f32> unitVect;
    f32 xcomp, ycomp;
    f32 speedFactor = 0.1;
    for (auto entity : entities().with<Path, Status>())
    {
        Status &status = entity.get<Status>();
        Path &path = entity.get<Path>();

        if (!path.vertices.empty())
        {
            shared_ptr<Vertex> currentDest = path.vertices.front();
            if (currentDest != nullptr)
            {
                if (calcDistance(status.xpos, status.ypos,
                             currentDest->xpos, 
                             currentDest->ypos) < path.radius)
                {
                    // we reached our destination
                    // we don't want to move towards
                    // this vertex anymore, so dequeue it
                    // Also, this vertex will now be the one that
                    // the entity is currently at
                    status.xpos = currentDest->xpos + status.xnoise;
                    status.ypos = currentDest->ypos;
                    path.nearestVertID = currentDest->id;
                    path.vertices.pop();
                }
                else
                {
                    // in this case, we're still trying to move towards
                    // the next vertex, so find from the entity
                    // to the vertex at the front of the queue
                    unitVect = calcUnitVector(status.xpos, status.ypos,
                                              currentDest->xpos,
                                              currentDest->ypos);
                    xcomp = get<0>(unitVect);
                    ycomp = get<1>(unitVect);
                    status.xpos += xcomp * speedFactor * time;
                    status.ypos += ycomp * speedFactor * time;
                }
            }
        }
    }
}


void MinionLogicSystem::update(float time){
    for(auto minion : entities().with<Path, Allegiance>()){
        Status& minionStatus = minion.get<Status>();
        // get the status of anything  with a different allegiance
        if(rand()%25 == 0){ // simulate a random cooldown
            for(auto enemy : entities().with<Allegiance, Status>()){
                Status& enemyStatus = enemy.get<Status>();
                if(calcDistance(minionStatus.xpos, minionStatus.ypos, enemyStatus.xpos, enemyStatus.ypos) < AGGRORADIUS
                        && minion.get<Allegiance>().alliedID != enemy.get<Allegiance>().alliedID){
                    // fire a projectile at the enemy entity
                    ecs::Entity projectile = entities().create();
                    projectile.add<Status>(minionStatus.xpos, minionStatus.ypos);
                    projectile.add<Allegiance>(minion.get<Allegiance>().alliedID);
                    projectile.add<Projectile>();
                    GRRLIB_texImg *texPtr = findTex(entities(), "bullet1");
                    projectile.add<Drawable>(texPtr);
                }
            }
        }
    }
}


void ProjectileSystem::update(float time){
    for(auto projectile : entities().with<Status, Allegiance, Projectile>()){

    }
}



void InputSystem::update(float time){
    shared_ptr<Graph> gptr;
    // get a handle on the graph with a pointer entity
    for(auto graphEntity : entities().with<GraphPointer>()){
        GraphPointer &graphpoint = graphEntity.get<GraphPointer>();
        gptr = graphpoint.gptr;
    }

    for(auto playerEntity : entities().with<PlayerPtrComp>()){
        // One iteration for each player
        
        PlayerPtrComp &playerComp = playerEntity.get<PlayerPtrComp>();
        shared_ptr<Player> player = playerComp.pptr;
        u32 held = 0;
        u32 pressed = 0;
        int playerid = player->id;
        if(player->id == 1){
            held = WPAD_ButtonsHeld(0);
            pressed = WPAD_ButtonsDown(0);
        }
        if(player->id == 2){
            held = WPAD_ButtonsHeld(1);
            pressed = WPAD_ButtonsDown(1);
        }


        if(held & WPAD_BUTTON_DOWN){
            player->movey(CURSORSPEED);
        }
        if(held & WPAD_BUTTON_UP){
            player->movey(-CURSORSPEED);
        }
        if(held & WPAD_BUTTON_LEFT){
            player->movex(-CURSORSPEED);
        }
        if(held & WPAD_BUTTON_RIGHT){
            player->movex(CURSORSPEED);
        }

        if(pressed & WPAD_BUTTON_A){
            // player 1 or player 2 has pressed A
            // iterate through the minions but select the
            // appropriately allied ones
            for(auto minionEntity : entities().with<Path, Allegiance>()){
                Allegiance& alleg = minionEntity.get<Allegiance>();
                if(alleg.alliedID == playerid){
                    // When a player presses A, 1/4 of the available units
            	    // should start moving towards it.
                	// So, here we will perform the random selection on the fly
                    if(rand() % 4 == 1){
                        // determine the vertex nearest to the player's cursor
                        shared_ptr<Vertex> destVert = gptr->getNearestVertex(player->xpos, player->ypos);
                        Path &p = minionEntity.get<Path>();
                        unsigned int originID, nextID, destID; //vertex ID's
                        shared_ptr<Vertex> nextPtr = nullptr;
                        if(p.vertices.size() > 0){
                            nextPtr = p.vertices.front();
                        }
                        originID = p.nearestVertID;
                        nextID =  nextPtr->id;
                        destID = destVert->id;
                        // perform path algorithm. 
                        // however, if the entity is in transition, we need
                        // run the algorith twice: once for its destination
                        // and once for the vertex it came from
                        gptr->shortestPath(originID);
                        queue<shared_ptr<Vertex>> pathFromOrigin = gptr->getPath(originID, destID);
                        queue<shared_ptr<Vertex>> chosenPath = pathFromOrigin; // by default

                        if(nextPtr != nullptr){
                            // we need to run the algorithm again
                            gptr->shortestPath(nextID);
                            queue<shared_ptr<Vertex>> pathFromNext;
                            pathFromNext = gptr->getPath(nextID, destID);

                            // Then, choose the option with the fewest edges.
                            // If they have the same number of edges, choose the
                            // option with the least physical distance from the entity
                            queue<Vertex>::size_type lenFromOrigin = pathFromOrigin.size();
                            queue<Vertex>::size_type lenFromNext = pathFromNext.size();

                            if(lenFromOrigin == lenFromNext){
                                shared_ptr<Vertex> origPtr = gptr->getVertex(originID);
                                f32 x1, y1, x2, y2;
                                x1 = destVert->xpos;
                                y1 = destVert->ypos;

                                x2 = nextPtr->xpos;
                                y2 = nextPtr->ypos;
                                f32 distOrigin = calcDistance(x1,y1,x2,y2);

                                x2 = origPtr->xpos;
                                y2 = origPtr->ypos;
                                f32 distNext = calcDistance(x1, y1, x2, y2);

                                if(distOrigin < distNext){
                                    chosenPath = pathFromOrigin;
                                }
                                else{
                                    chosenPath = pathFromNext;
                                }
                            }
                            else if (lenFromOrigin < lenFromNext){
                                chosenPath = pathFromOrigin;
                            }
                            else{
                                chosenPath = pathFromNext;
                            }

                        }
                        p.vertices = chosenPath; // set to result of algorithm
                        // also, give the status some noise for positioning
                        Status& status = minionEntity.get<Status>();
                        tuple<f32, f32> n = noise(10);
                        status.xnoise = get<0>(n);
                        status.ynoise = get<1>(n);
                    }
                }
            }
        }
    }
}

