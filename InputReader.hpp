//
//  InputReader.hpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef InputReader_hpp
#define InputReader_hpp

#include <map>
#include <string>
#include <vector>

#include "City.hpp"

class InputReaderResult{
public:
    unsigned long to, from;
    std::map<unsigned long, City *> cities;
    std::vector<Road *> optionalRoads;
    
    InputReaderResult(unsigned long to, unsigned long from, std::map<unsigned long, City *> cities, std::vector<Road *> optRoads);
};

class InputReader{
protected:
    static const char* getOptionalText(bool optional);
    static int logError(const char *format, ...);
    static void throwException(const char *format, ...);
};

#endif /* InputReader_hpp */
