//
//  FileReader.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FileReader.hpp"

unsigned long FileReader::lineNo = 0;

//============================================================================================
// FileReader::read
//
// Input:
//  path: path to the file containing details about the graph to be used with Dijkstra's Algorithm.
//
// Output:
//  InputReaderResult object.
//
// Read the details about the graph that will be used with Dijkstra's Algorithm from the specified
// file.
//============================================================================================
InputReaderResult *FileReader::read(std::string path){
    FileReader::lineNo = 0;
    std::ifstream stream;
    unsigned long from, to;
    
    stream.open(path);
    
    if(!stream.is_open()){
        InputReader::throwException("Problem opening file at %s", path.c_str());
    }
    
    std::map<unsigned long, City *>cities = FileReader::readCities(stream);
    printf("\n");
    
    //read existing roads
    readRoads(stream, cities, false);
    printf("\n");
    
    //read potential roads
    std::vector<Road *> optRoads = readRoads(stream, cities, true);
    printf("\n");
    
    from = FileReader::readUL(stream, true);
    printf("Starting city: %lu\n", from);
    
    to = FileReader::readUL(stream, true);
    printf("Ending city: %lu\n", to);
    
    stream.close();
    
    return new InputReaderResult(to, from, cities, optRoads);
}

//============================================================================================
// FileReader::readRoad
//
// Input:
//  stream:     A reference to the currenly open file.
//  optional:   A boolean flag indicating whether or not the road being read is an optional road
//              or not.
//  numCities:  The total number of cities in the graph.
//
// Output:
//  A Road object initialized using the information read from the file.
//
// Read in the details about a road from the a the file specified by stream.
//============================================================================================
Road* FileReader::readRoad(std::ifstream& stream, bool optional, long unsigned numCities){
    unsigned long to, from, length, cityLimit = numCities - 1;
    
    from = FileReader::readUL(stream, false);
    stream.get();
    to = FileReader::readUL(stream, false);
    stream.get();
    length = FileReader::readUL(stream, true);
    
    if (from > cityLimit || to > cityLimit) {
        InputReader::throwException("Values for 'fromCity' and 'toCity' must be unique integers between 0 and %lu inclusive.", cityLimit);
    }
    
    try{
        return new Road(to, from, length, optional);
    }
    catch(std::invalid_argument& e){
        InputReader::logError("Invalid input on line: %lu", FileReader::lineNo - 1);
        throw e;
    }
}

//============================================================================================
// FileReader::readCities
//
// Input:
//  stream: A reference to the currenly open file.
//
// Output:
//  A map with city ids as keys and City objects as values.
//
// Read the number of cities in the graph from a file and create that many cities, using an
// incrementing index starting at 0 as ids for the cities.
//============================================================================================
std::map<unsigned long, City*> FileReader::readCities(std::ifstream& stream){
    unsigned long numCities;
    std::map<unsigned long, City*> cities;
    
    numCities = FileReader::readUL(stream, true);
    
    printf("Reading %lu cities.\n", numCities);
    
    for (int i = 0; i < numCities; i++) {
        City* tempCity = new City(i);
        cities.insert(std::pair<int, City *>(i, tempCity));
        printf("  Reading city %d.\n", i);
    }
    
    printf("Done reading cities.\n");
    
    return cities;
}

//============================================================================================
// FileReader::readRoads
//
// Input:
//  stream:     A reference to the currenly open file.
//  cities:     A map using city ids as keys and City objects as values.
//  optional:   A boolean flag indicating whether the roads being read in are optional or not.
//
// Output:
//  A vector of Road objects.
//
// Read in a set of multiple optional or mandatoryroads from a file, updating the 'toRoads'
// and 'fromRoads' attributes of each City object accordingly.
//============================================================================================
std::vector<Road *> FileReader::readRoads(std::ifstream& stream, std::map<unsigned long, City*> cities, bool optional){
    Road *temp;
    std::vector<Road *> roads;
    unsigned long numRoads;
    const char* optionalText = FileReader::getOptionalText(optional);
    numRoads = FileReader::readUL(stream, true);
    printf("Reading %lu uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        temp = readRoad(stream, optional, cities.size());
        
        if(!optional){
            cities[temp->from]->fromRoads.push_back(temp);
            cities[temp->to]->toRoads.push_back(temp);
        }
        else{
            roads.push_back(temp);
        }
        
        printf("  Reading %s road from city %lu to city %lu with length of %lu\n", optionalText, temp->from, temp->to, temp->length);
    }
    
    printf("Done reading %s uni-directional roads.\n", optionalText);
    
    return roads;
}

//============================================================================================
// FileReader::readUL
//
// Input:
//  stream:     A reference to the currenly open file.
//  newLine:    A boolean flag indicating whether a new line is expected or not so that the
//              static lineNo attribute can be incremented accordingly.
//
// Output:
//  An unsigned long.
//
// Read an unsigned long from the currently open file.
//============================================================================================
unsigned long FileReader::readUL(std::ifstream &stream, bool newline){
    unsigned long output;
    stream >> output;
    
    if (newline) {
        FileReader::lineNo++;
    }
    
    return output;
}