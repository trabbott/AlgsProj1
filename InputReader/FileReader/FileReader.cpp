//
//  FileReader.cpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FileReader.hpp"

/*
 Public
 */

unsigned long FileReader::lineNo = 0;

InputReaderResult *FileReader::read(std::string path){
    FileReader::lineNo = 0;
    std::ifstream stream;
    int from, to;
    
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
    readRoads(stream, cities, true);
    printf("\n");
    
    stream >> from;
    printf("Starting city: %d\n", from);
    
    stream >> to;
    printf("Ending city: %d\n", to);
    
    stream.close();
    
    return new InputReaderResult(to, from, cities);
}

/*
 Private 
 */


Road* FileReader::readRoad(std::ifstream& stream, bool optional, long unsigned numCities){
    unsigned long to, from, length, cityLimit = numCities - 1;
    
    from = FileReader::readInt(stream, false);
    stream.get();
    to = FileReader::readInt(stream, false);
    stream.get();
    length = FileReader::readInt(stream, true);
    
    if (from > cityLimit || to > cityLimit) {
        InputReader::throwException("Values for 'fromCity' and 'toCity' must be unique integers between 0 and %lu inclusive.", cityLimit);
    }
    
    try{
        return new Road(from, to, length, optional);
    }
    catch(std::invalid_argument& e){
        InputReader::logError("Invalid input on line: %lu", FileReader::lineNo - 1);
        throw e;
    }
}

std::map<unsigned long, City*> FileReader::readCities(std::ifstream& stream){
    int numCities;
    std::map<unsigned long, City*> cities;
    
    stream >> numCities;
    
    printf("Reading %d cities.\n", numCities);
    
    for (int i = 0; i < numCities; i++) {
        City* tempCity = new City(i);
        cities.insert(std::pair<int, City *>(i, tempCity));
        printf("\tReading city %d.\n", i);
    }
    
    printf("Done reading cities.\n");
    
    return cities;
}

void FileReader::readRoads(std::ifstream& stream, std::map<unsigned long, City*> cities, bool optional){
    Road *temp;
    int numRoads;
    const char* optionalText = FileReader::getOptionalText(optional);
    stream >> numRoads;
    printf("Reading %d uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        temp = readRoad(stream, false, cities.size());
        cities[temp->from]->roads.push_back(temp);
        
        printf("\tReading %s road from city %lu to city %lu with length of %lu\n", optionalText, temp->from, temp->to, temp->length);
    }
    
    printf("Done reading %s uni-directional roads.\n", optionalText);
}

int FileReader::readInt(std::ifstream &stream, bool newline){
    int output;
    stream >> output;
    
    if (newline) {
        FileReader::lineNo++;
    }
    
    return output;
}