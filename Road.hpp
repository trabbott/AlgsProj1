//
//  Road.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include <stdexcept>

//============================================================================================
// Road
//
// A simple class that contains details about an edge in a graph, including what city it leads to, what city
// it comes from, its length, and whether or not it is an optional road.
//============================================================================================
class Road{
public:
    unsigned long to, from, length;
    bool optional;
    
    Road(unsigned long to, unsigned long from, unsigned long length, unsigned long optional);
};

#endif /* Road_hpp */
