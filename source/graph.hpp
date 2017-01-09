
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
#include <list>

using namespace std;

class Vertex
{
  public:
    Vertex(int _id, double x, double y):id(_id),
                                  xpos(x),
                                  ypos(y)
    {}
    int id;
    double xpos;
    double ypos;
    int parentid = -1; // resets a lot during the bfs algorithm
    bool visited = false; // distance value, gets reset a lot in the bfs algorithm
    list<Vertex*> adjVerticesPtrs;
};


// Simple graph
// implemented as an adjacency list
class Graph
{
  private:
    
  public:
	vector<Vertex*> vertices;
    Graph()
    {   
    }

    void addVertex(Vertex* v);

    // adds connections from id1 to id2 and also from id2 to id1
    void addConnection(int id1, int id2);

    // return a smart pointer to the vertex with the associated id
    Vertex* getVertex(int _id);

    void shortestPath(int id1);

    vector<Vertex*> getAdjTo(int _id);
};