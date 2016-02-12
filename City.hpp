//
//  City.hpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef City_hpp
#define City_hpp

#include <climits>
#include <vector>

#include "Road.hpp"

class City{
public:
    std::vector<Road *> toRoads, fromRoads;
    unsigned long key;
    bool visited;
    unsigned long distance;


    City(unsigned long key);
};

#endif /* Item_hpp */