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
    readRoads(stream, cities, true);
    printf("\n");
    
    from = FileReader::readUL(stream, true);
    printf("Starting city: %lu\n", from);
    
    to = FileReader::readUL(stream, true);
    printf("Ending city: %lu\n", to);
    
    stream.close();
    
    return new InputReaderResult(to, from, cities);
}

/*
 Private 
 */


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
        return new Road(from, to, length, optional);
    }
    catch(std::invalid_argument& e){
        InputReader::logError("Invalid input on line: %lu", FileReader::lineNo - 1);
        throw e;
    }
}

std::map<unsigned long, City*> FileReader::readCities(std::ifstream& stream){
    unsigned long numCities;
    std::map<unsigned long, City*> cities;
    
    numCities = FileReader::readUL(stream, true);
    
    printf("Reading %lu cities.\n", numCities);
    
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
    unsigned long numRoads;
    const char* optionalText = FileReader::getOptionalText(optional);
    numRoads = FileReader::readUL(stream, true);
    printf("Reading %lu uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        temp = readRoad(stream, false, cities.size());
        cities[temp->from]->roads.push_back(temp);
        
        printf("\tReading %s road from city %lu to city %lu with length of %lu\n", optionalText, temp->from, temp->to, temp->length);
    }
    
    printf("Done reading %s uni-directional roads.\n", optionalText);
}

unsigned long FileReader::readUL(std::ifstream &stream, bool newline){
    unsigned long output;
    stream >> output;
    
    if (newline) {
        FileReader::lineNo++;
    }
    
    return output;
}