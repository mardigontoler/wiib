#include "graph.hpp"
#include <queue>
#include <list>
#include <memory>

shared_ptr<Vertex> Graph::getVertex(int _id){
    shared_ptr<Vertex> result;
    for(Vertex& vert: vertices){
        if(vert.id == _id){
            result.reset(&vert); // reset using address from the reference
            return result;
        }
    }
    return result; // should be empty
}

// get a list of pointers to all the adjacent vertices to the vertex with
// the specified id
vector<shared_ptr<Vertex>> Graph::getAdjTo(int _id){
    vector<shared_ptr<Vertex>> result;
    for(Vertex& vert : vertices){
        if(vert.id == _id){
            for(shared_ptr<Vertex> padj : vert.adjVerticesPtrs){
                result.push_back(padj);
            }
        }
    }
    return result; // should be empty if the id was invalid
}

// breadth first search to find the shortest path from id1 to id2
shared_ptr<list<Vertex>> Graph::shortestPath(int id1, int id2){
    for(Vertex& vert : vertices){
        vert.dvalue = -1;
        vert.parent.reset();
    }
    queue<shared_ptr<Vertex>> vertqueue;
    shared_ptr<Vertex> root = getVertex(id1); 
    vertqueue.push(root);
    while(vertqueue.size() != 0){
        shared_ptr<Vertex> current = vertqueue.front();
        vertqueue.pop();
        // get all adjacent vertices to the current vertex
        for(shared_ptr<Vertex> pvert : getAdjTo(current->id)){
            if(pvert->dvalue == -1){
                pvert->dvalue = (current->dvalue) + 1;
                pvert->parent = current;
                vertqueue.push(pvert);
            }
        }
    }
    // at this poin, this bfs is complete. now trace through p-values
    // to actually create a path through the vertices

}