
#include "Dijkstra.hpp"

/*
From Wikipedia

1  function Dijkstra(Graph, source):
2      dist[source] ← 0                                    // Initialization
3
4      create vertex set Q
5
6      for each vertex v in Graph:           
7          if v ≠ source
8              dist[v] ← INFINITY                          // Unknown distance from source to v
9              prev[v] ← UNDEFINED                         // Predecessor of v
10
11         Q.add_with_priority(v, dist[v])
12
13
14     while Q is not empty:                              // The main loop
15         u ← Q.extract_min()                            // Remove and return best vertex
16         for each neighbor v of u:                       // only v that is still in Q
17             alt = dist[u] + length(u, v) 
18             if alt < dist[v]
19                 dist[v] ← alt
20                 prev[v] ← u
21                 Q.decrease_priority(v, alt)
22
23     return dist[], prev[]
*/
DijkstraResult::DijkstraResult(std::map<unsigned long, City *> previous, std::map<unsigned long, unsigned long> distances){
    this->previous = previous;
    this->distances = distances;
}

DijkstraResult *Dijkstra::runForward(InputReaderResult *params){
    return Dijkstra::run(params->from, params->to, params->cities, true);
    
}

DijkstraResult *Dijkstra::runBackward(InputReaderResult *params){
    return Dijkstra::run(params->to, params->from, params->cities, false);
}

DijkstraResult *Dijkstra::run(unsigned long fromId, unsigned long toId, std::map<unsigned long, City *> cities, bool forward){
    std::map<unsigned long, City*> previous;
    std::map<unsigned long, Node*> cityNodes;
    std::map<unsigned long, unsigned long> distances;

    FibHeap* heap = new FibHeap();
    Node *temp;
    
    for(auto it = cities.begin(); it != cities.end(); it++){
        it->second->visited = false;
        
        if (it->second->key == fromId) {
            it->second->distance = 0;
        }
        else{
            it->second->distance = ULONG_MAX;
        }
        
        temp = new Node(it->second);
        FibHeap::insert(temp, heap);
        cityNodes[it->second->key] = temp;
    }
    
    City *minCity, *neighbor;
    Road *road;
    std::vector<Road *> roads;
    
    Node *orig = heap->min;
    int errCount = 0;
    
    while(heap->min != nullptr)
    {
        errCount++;
        if (heap->min->child == heap->min) {
            printf("%d\n", errCount);
        }
        minCity = heap->deleteMin(heap);
        
        if(forward){
            roads = minCity->fromRoads;
        }
        else{
            roads = minCity->toRoads;
        }

        for (auto it = roads.begin(); it != roads.end(); it++)
        {
            road = *it;
            
            if(forward){
                neighbor = cities[road->to];
            }else{
                neighbor = cities[road->from];
            }
            
            if (neighbor->visited == false)
            {
                unsigned long altDistance = minCity->distance + road->length;
                
                if (altDistance < neighbor->distance)
                {
                    unsigned long sub = neighbor->distance - altDistance;
                    
                    previous[neighbor->key] = minCity;
                    distances[neighbor->key] = altDistance;
                    FibHeap::decreaseKey(sub, cityNodes[neighbor->key], heap);
                }
            }
        }
        
        minCity->visited = true;
    }
    
    distances[toId] = cities[toId]->distance;
    
    return new DijkstraResult(previous, distances);
    
}