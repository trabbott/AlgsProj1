//
//  City.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef City_hpp
#define City_hpp

#include <climits>
#include <vector>

#include "Road.hpp"

//============================================================================================
// City
//
// A simple class that contains details about a City, including the roads leading to and from that city,
// the distance from the starting City in Dijkstra's Algorithm to itself, whether or not it has been
// visited by an instance of Dijkstra's algorithm yet, and its id (key).
//============================================================================================
class City{
public:
    std::vector<Road *> toRoads, fromRoads;
    unsigned long key;
    bool visited;
    unsigned long distance;


    City(unsigned long key);
};

#endif /* Item_hpp */
