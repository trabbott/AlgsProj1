//
//  Road.cpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "Road.hpp"

Road::Road(int to, int from, int length, int optional){
    this->to = to;
    this->from = from;
    this->length = length;
    this->optional = optional;
}