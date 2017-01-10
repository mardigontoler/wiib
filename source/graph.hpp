
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
#include <grrlib.h>
#include <memory>
#include <vector>
#include <list>

using namespace std;

class Vertex
{
  public:
    Vertex(unsigned int _id, double x, double y):id(_id),
                                  xpos(x),
                                  ypos(y)
    {}
    unsigned int id;
    double xpos;
    double ypos;
    int parentid = -1; // resets a lot during the bfs algorithm
    bool visited = false; // distance value, gets reset a lot in the bfs algorithm
    list<shared_ptr<Vertex>> adjVerticesPtrs;
};


// Simple graph
// implemented as an adjacency list
class Graph
{
  private:
    
  public:
	vector<shared_ptr<Vertex>> vertices;
    Graph()
    {   
    }

    //Constructor for creating the graph from a vector
    //formatted to consider every 2 values the x and y
    //coordinates of each node.
    Graph(vector<double>& nodevector, vector<double>& nodeconnections);

    void addVertex(shared_ptr<Vertex> v);

    // adds connections from id1 to id2 and also from id2 to id1
    void addConnection(unsigned int id1, unsigned int id2);

    // return a smart pointer to the vertex with the associated id
    shared_ptr<Vertex> getVertex(unsigned int _id);

    void shortestPath(unsigned int id1);

    vector<shared_ptr<Vertex>> getAdjTo(unsigned int _id);
};