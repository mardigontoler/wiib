

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
                             currentDest->xpos, currentDest->ypos) < path.radius)
                {
                    // we reached our destination
                    // we don't want to move towards
                    // this vertex anymore, so dequeue it
                    // Also, this vertex will now be the one that
                    // the entity is currently at
                    path.nearestVert = currentDest;
                    path.vertices.pop();
                }
                else
                {
                    // in this case, we're still trying to move towards
                    // the next vertex, so find from the entity
                    // to the vertex at the front of the queue
                    unitVect = calcUnitVector(status.xpos, status.ypos,
                                              currentDest->xpos, currentDest->ypos);
                    xcomp = get<0>(unitVect);
                    ycomp = get<1>(unitVect);
                    status.xpos += xcomp;
                    status.ypos += ycomp;
                }
            }
        }
    }
}