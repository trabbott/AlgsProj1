//
//  FileReader.hpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <fstream>
#include <map>
#include <string>

#include "City.hpp"
#include "InputReader.hpp"
#include "Road.hpp"


class FileReader : InputReader{
private:
    static unsigned long lineNo;
    
    static void readRoads(std::ifstream& stream, std::map<unsigned long, City *> cities, bool optional);
    static Road* readRoad(std::ifstream& stream, bool optional, long unsigned numCities);
    static std::map<unsigned long, City*> readCities(std::ifstream& stream);
    static int readInt(std::ifstream &stream, bool newline);
    
public:
    static InputReaderResult *read(std::string path);

};

#endif /* FileReader_hpp */
