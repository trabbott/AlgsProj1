
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
void Dijkstra::Run()
{
    int startCity = 0; // Or whatever the start node is.

    int numberOfCities = 100;  // Replace with the number from file or console
    Node* allCities = new Node[numberOfCities];
    // Read in all nodes.

    allCities[startCity]->item->distance = 0;

    FibHeap* heap = new FibHeap();

    for(int city = 0; city < numberOfCities; city++)
    {
        /* Don't need. Cities (nodes) start out with distance and previous city already initialized via constructor)
        if (city != startCity)
        {
            allCities[city]->item->distance = INFINITE;
            allCities[city]->item->previousCity = NOT_DEFINED;
        }
        */
        
        // Need to confirm that this inserts with distance as priority
        heap->insert(new Item(allCities[city]->item->distance), heap); 
    }

    
    while(heap)
    {
        Item* minItem = heap->deleteMin(heap);

        //foreach (neighbor of minNode)  // How do we determine neighbor? Another data structure?
        {
            if (neighbor->item->visited == false)
            {
                int altDistance = minItem->distance + length(minItem->distance, neighbor);  // How do we determine len?
                if (altDistance < neighbor->item->distance) 
                {
                    neighbor->item->distance = altDistance;
                    // neighbor->item->previousCity = minNode;    How do I point back to the Node?
                    heap->decreaseKey(altDistance, neighbor, heap);
                    
                }

            }
        }
        
        minItem->visited = true;
    }


}
