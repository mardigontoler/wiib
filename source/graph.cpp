
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

#include "graph.hpp"
#include <queue>
#include <list>
#include <memory>
#include <iostream>

Graph::Graph(vector<double>& nodevector, vector<double>& nodeconnections)
{
    // for loop increments by 2 at the end of each step
    unsigned int i;
    unsigned int idnum;
    for (i = 0, idnum = 0; i < nodevector.size(); i += 2, idnum++)
    {
        f32 xpos = nodevector[i];
        f32 ypos = nodevector[i + 1];
        shared_ptr<Vertex> v(new Vertex(idnum, xpos, ypos));
        addVertex(v);
    }
    // now, use the other param to connect the appropriate nodes together
    for (unsigned int j = 0; j < nodeconnections.size(); j += 2)
    {
        unsigned int id1 = nodeconnections[j];
        unsigned int id2 = nodeconnections[j + 1];
        addConnection(id1, id2);
    }
}

shared_ptr<Vertex> Graph::getVertex(unsigned int _id)
{
    for (shared_ptr<Vertex> vert : vertices)
    {
        if (vert->id == _id)
        {
            return vert;
        }
    }
    return nullptr;
}

// get a list of pointers to all the adjacent vertices to the vertex with
// the specified id
vector<shared_ptr<Vertex>> Graph::getAdjTo(unsigned int _id)
{
    vector<shared_ptr<Vertex>> result;
    for (shared_ptr<Vertex> vert : vertices)
    {
        if (vert->id == _id)
        {
            for (shared_ptr<Vertex> padj : vert->adjVerticesPtrs)
            {
                result.push_back(padj);
            }
            return result;
        }
    }
    return result; // should be empty if the id was invalid
}

// breadth first search to find the shortest path from id1 to id2
void Graph::shortestPath(unsigned int id1)
{
    for (shared_ptr<Vertex> vert : vertices)
    {
        vert->visited = false;
        vert->parentid = -1;
    }
    queue<shared_ptr<Vertex>> vertqueue;
    shared_ptr<Vertex> root = getVertex(id1);
    root->visited = true;
    vertqueue.push(root);
    while (!vertqueue.empty())
    {
        shared_ptr<Vertex> current = vertqueue.front();
        vertqueue.pop();
        // get all adjacent vertices to the current vertex
        for (shared_ptr<Vertex> pvert : getAdjTo(current->id))
        {
            if (!(pvert->visited))
            {
                pvert->visited = true;
                pvert->parentid = current->id;
                vertqueue.push(pvert);
            }
        }
    }
}

void Graph::addVertex(shared_ptr<Vertex> v)
{
    vertices.push_back(v);
}

void Graph::addConnection(unsigned int id1, unsigned int id2)
{
    shared_ptr<Vertex> v1 = getVertex(id1);
    shared_ptr<Vertex> v2 = getVertex(id2);
    v1->adjVerticesPtrs.push_back(v2);
    v2->adjVerticesPtrs.push_back(v1);
}
