//
//  FileReader.cpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FileReader.hpp"

/*
 FileReaderResult
 */

FileReaderResult::FileReaderResult(int to, int from, std::map<int, City *> cities){
    this->to= to;
    this->from = from;
    this->cities = cities;
}

/*
 End FileReaderResult
 */

/*
 Public
 */

FileReaderResult *FileReader::read(std::string path){
    std::ifstream stream;
    int from, to;
    
    stream.open(path);
    
    if(!stream.is_open()){
        char buff[1024];
        sprintf(buff, "Problem opening file at %s", path.c_str());
        throw std::invalid_argument(buff);
    }
    
    std::map<int, City *>cities = readCities(stream);
    printf("\n");
    
    readExistingRoads(stream, cities);
    printf("\n");
    
    readPotentialRoads(stream, cities);
    printf("\n");
    
    stream >> from;
    printf("Starting city: %d\n", from);
    
    stream >> to;
    printf("Ending city: %d\n", to);
    
    stream.close();
    
    return new FileReaderResult(to, from, cities);
}

/*
 Private 
 */

static Road* readRoad(std::ifstream& stream, bool optional){
    int toId, fromId, length;
    
    stream >> fromId;
    stream.get();
    stream >> toId;
    stream.get();
    stream >>length;
    
    return new Road(fromId, toId, length, optional);
}

std::map<int, City*> FileReader::readCities(std::ifstream& stream){
    int numCities;
    std::map<int, City*> cities;
    
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

void FileReader::readExistingRoads(std::ifstream& stream, std::map<int, City*> cities){
    int numRoads;
    stream >> numRoads;
    printf("Reading %d uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        Road* tempRoad = readRoad(stream, false);
        cities[tempRoad->from]->roads.push_back(tempRoad);
        
        printf("\tReading existing road from city %d to city %d with length of %d\n", tempRoad->from, tempRoad->to, tempRoad->length);
    }
    
    printf("Done reading uni-directional roads.\n");
}

void FileReader::readPotentialRoads(std::ifstream& stream, std::map<int, City*> cities){
    int numRoads;
    stream >> numRoads;
    printf("Reading %d potential uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        Road* tempRoad = readRoad(stream, true);
        cities[tempRoad->from]->roads.push_back(tempRoad);
        
        printf("\tReading potential road from city %d to city %d with length of %d\n", tempRoad->from, tempRoad->to, tempRoad->length);
    }
    
    printf("Done reading potential uni-directional roads.\n");
}