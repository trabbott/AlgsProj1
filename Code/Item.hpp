//
//  Item.hpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include "Node.hpp"

class Item
{
public:
    unsigned long key;
    bool visited;  
    int distance;
    Node* previousCity;


    Item(unsigned long key);
};

#endif /* Item_hpp */
