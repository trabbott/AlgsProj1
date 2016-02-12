#ifndef Dijkstra_hpp
#define Dijkstra_hpp

#include <map>

#include "City.hpp"
#include "FibHeap.hpp"
#include "InputReader.hpp"

struct DijkstraResult{
    std::map<unsigned long, City *> previous;
    std::map<unsigned long, unsigned long> distances;
    
    DijkstraResult(std::map<unsigned long, City *> previous, std::map<unsigned long, unsigned long> distances);
};

class Dijkstra{

public:
    static DijkstraResult *runForward(InputReaderResult *params);
    static DijkstraResult *runBackward(InputReaderResult *params);
    //static DijkstraResult *run(InputReaderResult *params, bool forward);
    static DijkstraResult *run(unsigned long from, unsigned long to, std::map<unsigned long, City *> cities, bool forward);
};

#endif /* Dijkstra_hpp */
