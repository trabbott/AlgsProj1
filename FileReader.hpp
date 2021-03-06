//
//  FileReader.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "City.hpp"
#include "InputReader.hpp"
#include "Road.hpp"


//============================================================================================
// FileReader
//
// A simple class used for file input if the user chooses to insert information
// about their graph from a file.
//============================================================================================
class FileReader : InputReader{
private:
    static unsigned long lineNo;
    
    static std::vector<Road *> readRoads(std::ifstream& stream, std::map<unsigned long, City *> cities, bool optional);
    static Road* readRoad(std::ifstream& stream, bool optional, long unsigned numCities);
    static std::map<unsigned long, City*> readCities(std::ifstream& stream);
    static unsigned long readUL(std::ifstream &stream, bool newline);
    
public:
    static InputReaderResult *read(std::string path);

};

#endif /* FileReader_hpp */
