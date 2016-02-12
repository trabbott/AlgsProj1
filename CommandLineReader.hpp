//
//  CommandLineReader.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef CommandLineReader_hpp
#define CommandLineReader_hpp

#include <cstdio>
#include <map>
#include <stdexcept>
#include <stdio.h>

#include "City.hpp"
#include "InputReader.hpp"
#include "Road.hpp"

class CommandLineReader : InputReader{
public:
    static InputReaderResult *read();
    static void cleanBuffer();
private:
    static std::map<unsigned long, City *> promptCities();
    static unsigned long promptRoads(bool optional);
    static std::vector<Road *> promptRoadDetails(unsigned long numRoads, std::map<unsigned long, City *> cities, bool optional);
    static unsigned long promptLimit(unsigned long numCities, bool start);
};

#endif /* CommandLineReader_hpp */
