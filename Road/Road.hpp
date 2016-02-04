//
//  Road.hpp
//  dijkstra
//
//  Created by Gregory Moon on 2/3/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include <stdio.h>

class Road{
public:
    int to, from, length;
    bool optional;
    
    Road(int to, int from, int length, int optional);
};

#endif /* Road_hpp */
