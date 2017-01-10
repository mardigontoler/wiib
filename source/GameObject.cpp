

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
    for (auto entity : entities().with<PathSystem, Status>()){

    }
}