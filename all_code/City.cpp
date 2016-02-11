//
//  City.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

 #include "City.hpp"

City::City(unsigned long key){
    this->key = key;

    this->visited = false;
    this->distance = ULONG_MAX;
}

