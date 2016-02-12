//
//  FibHeap.hpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef FibHeap_hpp
#define FibHeap_hpp

#include <climits>
#include <map>
#include <vector>

#include "City.hpp"
#include "Node.hpp"


class FibHeap{
private:
    static FibHeap *_meld(FibHeap *first, FibHeap *second);
    //static void _cut(Node *node, FibHeap *heap);
    static void _cascadingCut(FibHeap *heap, Node *node);
    static void _cut(FibHeap *heap, Node *node);

    
public:
    void _linkRoots();
    
    Node *min;
    
    FibHeap();
    FibHeap(Node *min);
    
    static void decreaseKey(unsigned long delta, Node *node, FibHeap *heap);
    static Node *findMin(FibHeap *heap);
    static Node *insert(Node *node, FibHeap *heap);
    static Node *insert(City *City, FibHeap *heap);
    static City *deleteMin(FibHeap *heap);
};

#endif /* FibHeap_hpp */
