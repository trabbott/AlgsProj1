//
//  Node.hpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <map>

#include "Item.hpp"




class Node{
public:
    Node *parent, *child, *left, *right;
    Item *item;
    int rank;


    Node(Item* item);
    
    void addChild(Node *child);
    unsigned long key();
    static Node *link(Node *first, Node *second);
    
private:
    void _linkChildren();
};

#endif /* Node_hpp */
