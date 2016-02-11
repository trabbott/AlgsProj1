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

#include "Item.hpp"
#include "Node.hpp"


class FibHeap{
private:
    void _linkRoots();
    static FibHeap *_meld(FibHeap *first, FibHeap *second);
    //Node *FibHeap::_find(Item *item);
    void FibHeap::_cut(Node *node, FibHeap *heap);
    
public:
    Node *min;
    
    FibHeap();
    FibHeap(Node *min);
    
    static void decreaseKey(int delta, Item *item, FibHeap *heap);
    static void decreaseKey(int delta, Node *node, FibHeap *heap);

    static Node *findMin(FibHeap *heap);
    static void insert(Node *node, FibHeap *heap);
    static void insert(Item *item, FibHeap *heap);
    static Item *deleteMin(FibHeap *heap);
};

#endif /* FibHeap_hpp */
