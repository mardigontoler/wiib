
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

#pragma once
#include "ecs.h"
#include <grrlib.h>
#include "ecs.h"
#include "graph.hpp"
#include <queue>

/**
This file actually defines entities to be used with
an entity component system: OPENECS
https://github.com/Gronis/OpenEcs

**/

using namespace ecs;

struct HitPoints
{
  HitPoints(int _val) : hp(_val)
  {
  }
  int hp;
};

// the id of the player to ally with
struct Allegiance
{
  Allegiance(int _val) : alliedID(_val)
  {
  }
  int alliedID;
};

struct Status
{
  Status(f32 x, f32 y) : xpos(x), ypos(y)
  {
  }
  f32 xpos;
  f32 ypos;
  f32 stepSpeed = 5;
  bool grabbed = false;
};

struct Drawable
{
  Drawable(GRRLIB_texImg *_ptexture) : ptexture(_ptexture)
  {
  }
  GRRLIB_texImg *ptexture;
  u32 color = 0xFFFFFFFF;
};


// estinations include the destination Vertex itself
// as well as a path that leads to it, implemented
// as a queue of pointers to vertices
// The system that works with this component
// usually tries to move an entity towards the next
// vertex in the vector. 
struct Path{
  unsigned int nearestVertID;
  queue<shared_ptr<Vertex>> vertices;
  f32 radius = 8;
};

class PathSystem : public System
{
  public:
    void update(float time) override;
};


class DrawingSystem : public System
{
public:
  void update(float time) override;
};
