
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
std::map<unsigned long, City *> Dijkstra::run(InputReaderResult *params)
{
    std::map<unsigned long, City*> previous;
    std::map<unsigned long, City*> cities = params->cities;
    std::map<unsigned long, Node*> cityNodes;


    FibHeap* heap = new FibHeap();
    
    //dist[source] ← 0
    cities[params->from]->distance = 0;
    
    //create vertex set Q
    
    for(int city = 0; city < cities.size(); city++)
    {
        Node *node = new Node(cities[city]);
        
        heap->insert(node, heap);
        cityNodes[cities[city]->key] = node;
    }
    

    
    //while Q is not empty:
    while(heap->min != nullptr)
    {
        //u ← vertex in Q with min dist[u]
        //remove u from Q
        City *minItem = heap->deleteMin(heap);

        //for each neighbor v of u:
        for (auto it = minItem->roads.begin(); it != minItem->roads.end(); it++)
        {
            Road *road = *it;
            
            if(road->optional){
                continue;
            }
            
            City *neighbor = cities[road->to];
            
            if (neighbor->visited == false)
            {
                //alt ← dist[u] + length(u, v)
                unsigned long altDistance = minItem->distance + road->length;
                
                //if alt < dist[v]:
                if (altDistance < neighbor->distance)
                {
                    unsigned long sub = neighbor->distance - altDistance;
                    
                    //prev[v] ← u
                    previous[neighbor->key] = minItem;
                    
                    //dist[v] ← alt
                    FibHeap::decreaseKey(sub, cityNodes[neighbor->key], heap);
                }

            }
        }
        
        minItem->visited = true;
    }
    
    return previous;
}
