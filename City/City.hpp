//
//  City.hpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef City_hpp
#define City_hpp

#include <vector>

#include "Edge.hpp"
#include "Item.hpp"

class City : Item{
public:
    std::vector<Edge *> roads;
    
    City(int key);
};

#endif /* City_hpp */
