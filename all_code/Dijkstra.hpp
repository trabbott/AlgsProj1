#ifndef Dijkstra_hpp
#define Dijkstra_hpp

#include <map>

#include "City.hpp"
#include "FibHeap.hpp"
#include "InputReader.hpp"

class Dijkstra{

public:
    static std::map<unsigned long, City *> run(InputReaderResult *params);
};

#endif /* Dijkstra_hpp */
