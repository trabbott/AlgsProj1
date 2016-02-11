//
//  CommandLineReader.cpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "CommandLineReader.hpp"

InputReaderResult *CommandLineReader::read(){
    std::map<unsigned long, City *> cities = CommandLineReader::promptCities();
    unsigned long numExistingRoads, from, to;
    
    //prompt for existing roads
    numExistingRoads = CommandLineReader::promptRoads(false);
    CommandLineReader::promptRoadDetails(numExistingRoads, cities, false);
    printf("\n");
    
    //prompt for optional roads
    numExistingRoads = CommandLineReader::promptRoads(true);
    CommandLineReader::promptRoadDetails(numExistingRoads, cities, true);
    printf("\n");
    
    from = CommandLineReader::promptLimit(cities.size(), true);
    printf("\n");
    
    to = CommandLineReader::promptLimit(cities.size(), false);
    printf("\n");
    
    return new InputReaderResult(to, from, cities);
}

void CommandLineReader::promptRoadDetails(unsigned long numRoads, std::map<unsigned long, City *> cities, bool optional){
    unsigned long cityLimit = cities.size() - 1;
    const char *optionalText = CommandLineReader::getOptionalText(optional);
    Road *temp;
    
    printf("\tEnter the details for each road (fromCity:toCity:length):\n");
    
    for (int i = 0; i < numRoads; i++) {
        printf("\t\tRoad %d: ", i);
        
        unsigned long from, to, length;
        CommandLineReader::cleanBuffer();
        scanf("%lu:%lu:%lu", &from, &to, &length);
        
        try{
            if(from > cityLimit || to > cityLimit){
                throw std::invalid_argument("");
            }
            
            temp = new Road(to, from, length, optional);
        }
        catch(std::invalid_argument& e){
            InputReader::logError("Values for 'fromCity' and 'toCity' must be unique integers between 0 and %lu inclusive and the value for 'length' must be a positive integer.", cityLimit);
            i--;
            continue;
        }
        cities[temp->from]->roads.push_back(temp);
        
        printf("\t\t\tNew %s road from %lu to %lu with length %lu.\n", optionalText, temp->from, temp->to, temp->length);
    }
}

std::map<unsigned long, City *> CommandLineReader::promptCities(){
    std::map<unsigned long, City *> cities;
    City *temp;
    int numCities;
    
    do{
        printf("How many cities are in your graph?: ");
        CommandLineReader::cleanBuffer();
        scanf("%d", &numCities);
        
        if(numCities < 2){
            InputReader::logError("There must be at least 2 cities in your graph.");
        }
    }while(numCities < 2);
    
    for (int i = 0; i < numCities; i++) {
        temp = new City(i);
        cities.insert(std::pair<int, City *>(i, temp));
    }
    
    printf("\t%d cities (0 - %d) have been added.\n\n", numCities, numCities - 1);
    
    return cities;
}

unsigned long CommandLineReader::promptRoads(bool optional){
    unsigned long numRoads;
    const char *optionalText = CommandLineReader::getOptionalText(optional);
    
    printf("How many %s roads are in your graph?: ", optionalText);
    CommandLineReader::cleanBuffer();
    scanf("%lu", &numRoads);
    printf("\t%lu %s roads (0 - %lu) are being added.\n\n", numRoads, optionalText, numRoads - 1);
    
    return numRoads;
}

unsigned long CommandLineReader::promptLimit(unsigned long numCities, bool start){
    unsigned long ret, cityLimit = numCities - 1;
    
    do{
        printf("What city do you want to %s in?: ", start ? "start" : "end");
        CommandLineReader::cleanBuffer();
        scanf("%lu", &ret);
        
        if(ret > cityLimit){
            InputReader::logError("The %s city must be an integer between 0 and %lu.", start ? "start" : "end", cityLimit);
        }
    }while(ret > cityLimit);
    
    printf("\t%sing city: %lu\n\n", start ? "Start" : "End", ret);
    return ret;
}

void CommandLineReader::cleanBuffer(){
    char garbage[4096];
    fgets(garbage, sizeof(garbage)/sizeof(char), stdin);
    
}