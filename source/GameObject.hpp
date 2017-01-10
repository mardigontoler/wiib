
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
  bool grabbed = false;
};

struct Drawable
{
};

class DrawingSystem : public System
{
  public:
    void update(float time) override;
};
