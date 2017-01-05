
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
#include <memory>
#include <vector>
#include <grrlib.h>
#include <list>

using namespace std;

struct Vertex
{
    int id;
    f32 xpos;
    f32 ypos;
    bool visited = false;
    int dvalue; // distance value, gets reset a lot in the bfs algorithm
    list<shared_ptr<struct Vertex>> adjVerticesPtrs;
};
typedef struct Vertex Vertex;

// Simple graph
// implemented as an adjacency list
class Graph
{
  private:
    vector<Vertex> vertices;
  public:
    Graph()
    {   
    }

    // adds connections from id1 to id2 and also from id2 to id1
    void connect(int id1, int id2);

    shared_ptr<list<Vertex>> shortestPath(int id1, int id2);
};