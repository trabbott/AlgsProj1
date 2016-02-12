//
//  InputReader.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef InputReader_hpp
#define InputReader_hpp

#include <cstdarg>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

#include "City.hpp"

//============================================================================================
// InputReaderResult
//
//  A simple class representing the output of an InputReader (including CommandLineReader and
//  FileReader).
//============================================================================================
class InputReaderResult{
public:
    unsigned long to, from;
    std::map<unsigned long, City *> cities;
    std::vector<Road *> optionalRoads;
    
    InputReaderResult(unsigned long to, unsigned long from, std::map<unsigned long, City *> cities, std::vector<Road *> optRoads);
};

//============================================================================================
// InputReader
//
// The super class of CommandLineReader and FileReader. Contains methods for logging errors and
// producing the appropriate text based on whether or not an input in question is optional or not.
//============================================================================================
class InputReader{
protected:
    static const char* getOptionalText(bool optional);
    static int logError(const char *format, ...);
    static void throwException(const char *format, ...);
};

#endif /* InputReader_hpp */
