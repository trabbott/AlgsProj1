//
//  FibHeap.hpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#ifndef FibHeap_hpp
#define FibHeap_hpp

#include <climits>
#include <map>
#include <vector>

#include "City.hpp"
#include "Node.hpp"

//============================================================================================
// FibHeap
//
// A class representing a Fibonacci Heap with all of the corresponding attributes and methods.
// A fibonacci heap is used as the priority queue in Dijkstra's Algorithm in order to achieve
// the desired O(m + nlg(n)) complexity, where n is the number of nodes in a graph and m is the
// number of edges in that graph.
//
// Details for its implementation were found at these linkts:
//
// 1. http://www.cse.yorku.ca/~aaw/Jason/FibonacciHeapAlgorithm.html
// 2. http://www.computer.org/csdl/proceedings/focs/1984/0591/00/0715934.pdf
//============================================================================================
class FibHeap{
private:
    static FibHeap *_meld(FibHeap *first, FibHeap *second);
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
