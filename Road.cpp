//
//  Road.cpp
//  dijkstra
//
//  Created by Gregory Moon on & Tim Abbott 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "Road.hpp"

//============================================================================================
// Road::Road
//
// Input:
//  to:         The city id of the city that the road leads to.
//  from:       The city id of the city that the road comes from.
//  length:     The distance from 'to' to 'from'.
//  optional:   A boolean flag indicating whether or not the road is optional.
//
// Output:
//
// The constructor for a Road object. Initializes all relevant attributes.
//============================================================================================
Road::Road(unsigned long to, unsigned long from, unsigned long length, unsigned long optional){
    
    if (to == from) {
        throw std::invalid_argument("'to' and 'from' parameters must be different.");
    }
    else if(length < 1){
        throw std::invalid_argument("'length' parameter must be greater than 0");
    }
    
    this->to = to;
    this->from = from;
    this->length = length;
    this->optional = optional;
}
