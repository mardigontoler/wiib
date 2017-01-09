
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

Vertex* Graph::getVertex(int _id){
    for(Vertex* vert: vertices){
        if(vert->id == _id){
            return vert;
        }
    }
	return nullptr;
}

// get a list of pointers to all the adjacent vertices to the vertex with
// the specified id
vector<Vertex*> Graph::getAdjTo(int _id){
    vector<Vertex*> result;
    for(Vertex *vert : vertices){
        if(vert->id == _id){
            for(Vertex *padj : vert->adjVerticesPtrs){
                result.push_back(padj);
            }
            return result;
        }
    }
    return result; // should be empty if the id was invalid
}

// breadth first search to find the shortest path from id1 to id2
void Graph::shortestPath(int id1){
    for(Vertex *vert : vertices){
        vert->visited = false;
        vert->parentid = -1;
    }
    queue<Vertex*> vertqueue;
	Vertex *root = getVertex(id1);
    root->visited = true;
    vertqueue.push(root);
    while(!vertqueue.empty()){
        Vertex *current = vertqueue.front();
        vertqueue.pop();
        // get all adjacent vertices to the current vertex
        for(Vertex *pvert : getAdjTo(current->id)){
            if(!(pvert->visited)){
                pvert->visited = true;
                pvert->parentid = current->id;
                vertqueue.push(pvert);
            }
        }
    }

}

void Graph::addVertex(Vertex *v){
    vertices.push_back(v);
	
}


void Graph::addConnection(int id1, int id2){
    Vertex *v1 = getVertex(id1);
    Vertex *v2 = getVertex(id2);
    v1->adjVerticesPtrs.push_back(v2);
    v2->adjVerticesPtrs.push_back(v1);
}
