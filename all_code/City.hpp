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
struct BackPointer;

class City{
public:
    BackPointer *mand, *opt;
    std::vector<Road *> roads;
    unsigned long key;
    bool visited;
    unsigned long distance;


    City(unsigned long key);
};

struct BackPointer{
    unsigned long value;
    City *prev;
    
    BackPointer(){
        value = ULONG_MAX;
        prev = nullptr;
    }
};

#endif /* Item_hpp */