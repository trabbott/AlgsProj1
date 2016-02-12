
#include "Dijkstra.hpp"

//============================================================================================
// DijkstraResult::DijkstraResult
//
// Input:
//  previous:   A map using city ids as the key and City objects as the value.
//  distances:  A map using city ids as the key and the distance from the source of a Dijkstra's
//              Algorithm run to the Node containing that City as the value
//
// The constructor for a simple struct used to hold and return the results of Dijkstra's Algorithm.
//============================================================================================

DijkstraResult::DijkstraResult(std::map<unsigned long, City *> previous, std::map<unsigned long, unsigned long> distances){
    this->previous = previous;
    this->distances = distances;
}

//============================================================================================
// Dijkstra::runForward
//
// Input:
//  params: An InputReaderResult, used for configuring the way Dijkstra's algorithm runs.
//
// Run Dijkstra's Algorithm from the input source to the input destination. This will give us the
// shortest path from the input source to every node.
//============================================================================================
DijkstraResult *Dijkstra::runForward(InputReaderResult *params){
    return Dijkstra::_run(params->from, params->to, params->cities, true);
}

//============================================================================================
// Dijkstra::runBackward
//
// Input:
//  params: An InputReaderResult, used for configuring the way Dijkstra's algorithm runs.
//
// Run Dijkstra's Algorithm from the input destination to the input source. This will give us the
// shortest path from the input destination to every node.
//============================================================================================
DijkstraResult *Dijkstra::runBackward(InputReaderResult *params){
    return Dijkstra::_run(params->to, params->from, params->cities, false);
}

//============================================================================================
// Dijkstra::_run
//
// Input:
//  fromId:     The id of the starting city.
//  toId:       The id of the ending city
//  cities:     A vector of City objectrs representing all the cities in the graph.
//  forward:    A boolean value indicating whether or not the algorithm should be run by following
//              edges leading to a Node or edges leading away from that Node.
//
// Run Dijkstra's Algorithm from the City identified by the fromId parameter to the city identified by the
// toId parameter.
//============================================================================================
DijkstraResult *Dijkstra::_run(unsigned long fromId, unsigned long toId, std::map<unsigned long, City *> cities, bool forward){
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
    
    while(heap->min != nullptr)
    {
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
                    if(minCity->distance != ULONG_MAX){
                        unsigned long sub = neighbor->distance - altDistance;
                        
                        previous[neighbor->key] = minCity;
                        distances[neighbor->key] = altDistance;
                        FibHeap::decreaseKey(sub, cityNodes[neighbor->key], heap);
                    }
                }
            }
        }
        
        minCity->visited = true;
    }
    
    distances[toId] = cities[toId]->distance;
    
    return new DijkstraResult(previous, distances);
    
}