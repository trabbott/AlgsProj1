//
//  CommandLineReader.hpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef CommandLineReader_hpp
#define CommandLineReader_hpp

#include <cstdio>
#include <map>

#include "City.hpp"
#include "InputReader.hpp"
#include "Road.hpp"

class CommandLineReader : InputReader{
public:
    static InputReaderResult *read();
private:
    static std::map<unsigned long, City *> promptCities();
    static unsigned long promptRoads(bool optional);
    static void promptRoadDetails(unsigned long numRoads, std::map<unsigned long, City *> cities, bool optional);
    static unsigned long promptLimit(unsigned long numCities, bool start);
};

#endif /* CommandLineReader_hpp */
