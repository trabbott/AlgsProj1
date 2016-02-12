//
//  Node.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <map>

#include "City.hpp"

//============================================================================================
// Node
//
// A simple class that acts as a node in a FibHeap as well as methods to help the FibHeap
// stay organized properly. It contains pointers to its parent, child, left neightbor, and right
// neighbor to facilitate the creation of doubly-linked lists which allow the formation of
// circular lists which let FibHeap operations run with the desired time complexities. It also
// keeps track of its rank (# of children) and whether or not it has been marked (cut from its
// parent).
//============================================================================================
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
