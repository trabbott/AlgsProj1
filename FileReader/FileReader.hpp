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

#include "Edge.hpp"
#include "City.hpp"

class FileReaderResult{
public:
    int to, from;
    std::map<int, City *> cities;
    
    FileReaderResult(int to, int from, std::map<int, City *> cities);
};

class FileReader{
private:
    static void readPotentialRoads(std::ifstream& stream, std::map<int, City *> cities);
    static void readExistingRoads(std::ifstream& stream, std::map<int, City *> cities);
    static std::map<int, City*> readCities(std::ifstream& stream);
    
public:
    static FileReaderResult *read(std::string path);

};

#endif /* FileReader_hpp */
