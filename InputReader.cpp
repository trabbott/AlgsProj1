//
//  InputReader.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "InputReader.hpp"

//============================================================================================
// InputReaderResult::InputReaderResult
//
// Inputs:
//  to:         The target city id for Dijkstra's Algorithm.
//  from:       The source city id for Dijkstra's Algorithm.
//  cities:     A map with city ids as keys and City objects as values.
//  optRoads:   A vector of optional Road objects.
//
// Outputs:
//
// The InputReaderResult constructor. Initializes all attribtues to their appropriate values.
// ============================================================================================
InputReaderResult::InputReaderResult(unsigned long to, unsigned long from, std::map<unsigned long, City *> cities, std::vector<Road *> optRoads){
    this->to= to;
    this->from = from;
    this->cities = cities;
    this->optionalRoads = optRoads;
}

//============================================================================================
// InputReader::getOptionalText
//
// Inputs:
//  optional: A boolean flag describing whether or not the output of the function should be
//            "existing" or "optional"
//
// Outputs:
//  Either "optional" or "existing" depending on the optional parameter input.
//
// Simply utility method for generating the proper text in CommandLineReader or FileReader.
//============================================================================================
const char* InputReader::getOptionalText(bool optional){
    return optional ? "optional" : "existing";
}

//============================================================================================
// InputReader::logError
//
// Inputs:
//  format: The format of an output string. The same onventions that aplpy to printf apply to the
//          inputs of this function.
//  ...:    A variable length list of arguments that correspond to the values expected by format.
//
// Outputs:
//  An integer indicating whether or not the error logging was successful.
//
// Log an error in a specific, consistent format.
//============================================================================================
int InputReader::logError(const char *format, ...){
    va_list arg;
    int done;
    std::string mod = "\nERROR: " + std::string(format) + "\n\n";
    va_start (arg, format);
    done = vfprintf (stderr, mod.c_str(), arg);
    va_end (arg);
    
    return done;
}

//============================================================================================
// InputReader::throwException
//
// Inputs:
//  format: The format of an output string. The same onventions that aplpy to printf apply to the
//          inputs of this function.
//  ...:    A variable length list of arguments that correspond to the values expected by format.
//
// Outputs:
//
// Throw an exception in a specific, consistent format.
//============================================================================================
void InputReader::throwException(const char *format, ...){
    char buff[4096];
    va_list arg;
    va_start (arg, format);
    vsprintf (buff, format, arg);
    va_end (arg);
    
    throw std::runtime_error(buff);
}
