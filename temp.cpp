//
//  main.cpp
//  program
//
//  readd by Gregory Moon on 1/29/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//
/*
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>

struct Road{
    int fromId, toId, length;
    bool optional;
    
    Road(int fromId, int toId, int length, bool optional){
        this->fromId = fromId;
        this->toId = toId;
        this->length = length;
        this->optional = optional;
    }
};

struct City{
    int id;
    std::vector<Road*> roads;
    
    City(int id){
        this->id = id;
    }
};

struct PathInfo{
    static int currPath;
    
    int length, id, start;
    bool builtOptional;
    std::vector<int> cityIds;
    
    PathInfo(int start){
        this->id = PathInfo::currPath;
        this->length = 0;
        this->builtOptional = false;
        this->cityIds.push_back(start);
        
        currPath++;
    }
    
    PathInfo* clone(){
        PathInfo* newInfo = new PathInfo(this->cityIds[0]);
        std::vector<int> newIds;
        
        for(int i = 0; i < this->cityIds.size(); i++){
            newIds.push_back(this->cityIds[i]);
        }
        
        newInfo->length = this->length;
        newInfo->builtOptional = this->builtOptional;
        newInfo->cityIds = newIds;
        
        return newInfo;
    }
    
    bool add(Road* road){
        if(std::find(this->cityIds.begin(), this->cityIds.end(), road->toId) != this->cityIds.end()){
            return false;
        }
        
        this->cityIds.push_back(road->toId);
        this->length += road->length;
        return true;
    }
};

int PathInfo::currPath = 0;


static void showUsage(std::string name);
static Road* readRoad(std::ifstream& stream, bool optional);
static void readExistingRoads(std::ifstream& stream, std::map<int, City*> cities);
static void readPotentialRoads(std::ifstream& stream, std::map<int, City*> cities);
static std::map<int, City*> readCities(std::ifstream& stream);
static void findPath(City* from, City* to, PathInfo* pathInfo);

//Temporary
const std::string INPUT_FILENAME = "/Volumes/Files/gregorymoon/Google\ Drive/School/2015-2016/Spring\ 2016/CSE\ 591\ -\ Foundations\ of\ Algorithms/programming\ assignment/1/program/program/input-4.txt";

static std::map<int, City*> cities;
static std::map<int, int> successes;

static std::vector<PathInfo*> paths;
static std::vector<int> failures;


int main(int argc, const char * argv[]) {
    //Initialize number of paths to 0. Can't do this in struct, may think about moving PathInfo & other structs to classes instead
    
    std::ifstream stream;
    int to, from;
    
    stream.open(INPUT_FILENAME);
    
    if(!stream.is_open()){
        printf("Problem opening file at %s\n", INPUT_FILENAME.c_str());
        return -1;
    }
    
    cities = readCities(stream);
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
    
    findPath(cities[from], cities[to], new PathInfo(from));
    
    return 0;
}

static void findPath(City* from, City* to, PathInfo* pathInfo){
    City* nextCity;
    Road* currRoad;
    
    for(int i = 0; i < from->roads.size(); i++){
        PathInfo* newInfo = pathInfo->clone();
        currRoad = from->roads[i];
        
        if(!newInfo->add(currRoad)){
            //avoid infinite loop
            continue;
        }
        
        if(currRoad->optional){
            if(newInfo->builtOptional){
                continue;
            }
            else{
                newInfo->builtOptional = true;
            }
        }
        
        if(currRoad->toId == to->id){
            paths.push_back(newInfo);
            return;
        }
        
        nextCity = cities[currRoad->toId];
        findPath(nextCity, to, newInfo);
    }
}

 Methods for reading from input file

static Road* readRoad(std::ifstream& stream, bool optional){
    int toId, fromId, length;
    
    stream >> fromId;
    stream.get();
    stream >> toId;
    stream.get();
    stream >>length;
    
    return new Road(fromId, toId, length, optional);
}

static void readExistingRoads(std::ifstream& stream, std::map<int, City*> cities){
    int numRoads;
    stream >> numRoads;
    printf("Reading %d uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        Road* tempRoad = readRoad(stream, false);
        cities[tempRoad->fromId]->roads.push_back(tempRoad);
        
        printf("\tReading existing road from city %d to city %d with length of %d\n", tempRoad->fromId, tempRoad->toId, tempRoad->length);
    }
    
    printf("Done reading uni-directional roads.\n");
}

static void readPotentialRoads(std::ifstream& stream, std::map<int, City*> cities){
    int numRoads;
    stream >> numRoads;
    printf("Reading %d potential uni-directional roads.\n", numRoads);
    
    for(int i = 0; i < numRoads; i++){
        Road* tempRoad = readRoad(stream, true);
        cities[tempRoad->fromId]->roads.push_back(tempRoad);
        
        printf("\tReading potential road from city %d to city %d with length of %d\n", tempRoad->fromId, tempRoad->toId, tempRoad->length);
    }
    
    printf("Done reading potential uni-directional roads.\n");
}


static std::map<int, City*> readCities(std::ifstream& stream){
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

 See command line parsing code at http://www.cplusplus.com/articles/DEN36Up4/
static void showUsage(std::string name)
{
     std::cerr << "Usage: " << name << " <option(s)> SOURCES "
     << "Options:\n"
     << "\t-h,--help\t\tShow this help message\n"
     << "\t-d,--destination DESTINATION\tSpecify the destination path"
     << std::endl;
}
*/
