#include "graph.hpp"
#include <queue>
#include <list>
#include <memory>

// breadth first search to find the shortest path from id1 to id2
shared_ptr<list<Vertex>> Graph::shortestPath(int id1, int id2){
    for(Vertex& vertref : vertices){
        vertref.dvalue = 0;
    }
}