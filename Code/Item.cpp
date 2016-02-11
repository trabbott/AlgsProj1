//
//  Item.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "Item.hpp"

#define INFINITE 1000000000
#define NOT_DEFINED 0

Item::Item(unsigned long key){
    this->key = key;

    visited = false;  
    distance = INFINITE;
    previousCity = NOT_DEFINED;
}

