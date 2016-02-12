//
//  InputReader.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "InputReader.hpp"

InputReaderResult::InputReaderResult(unsigned long to, unsigned long from, std::map<unsigned long, City *> cities, std::vector<Road *> optRoads){
    this->to= to;
    this->from = from;
    this->cities = cities;
    this->optionalRoads = optRoads;
}

const char* InputReader::getOptionalText(bool optional){
    return optional ? "optional" : "existing";
}

int InputReader::logError(const char *format, ...){
    va_list arg;
    int done;
    std::string mod = "\nERROR: " + std::string(format) + "\n\n";
    va_start (arg, format);
    done = vfprintf (stderr, mod.c_str(), arg);
    va_end (arg);
    
    return done;
}

void InputReader::throwException(const char *format, ...){
    char buff[4096];
    va_list arg;
    va_start (arg, format);
    vsprintf (buff, format, arg);
    va_end (arg);
    
    throw std::runtime_error(buff);
}
