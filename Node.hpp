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

#include "City.hpp"


class Node{
public:
    Node *parent, *child, *left, *right;
    City *item;
    bool mark;
    int rank;


    Node(City* item);
    
    void addChild(Node *child);
    std::vector<Node *> getChildren();
    unsigned long key();
    unsigned long distance();
    static Node *link(Node *first, Node *second);
    
private:
    void _linkChildren();
};


#endif /* Node_hpp */
