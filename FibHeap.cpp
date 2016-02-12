//
//  FibHeap.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FibHeap.hpp"

//============================================================================================
// FibHeap::FibHeap
//
// Inputs:
//
// Outputs:
//
// A FibHeap constructor. Initializes the minimum node of the heap to null.
//============================================================================================
FibHeap::FibHeap(){
    this->min = nullptr;
}

//============================================================================================
// FibHeap::FibHeap
//
// Inputs:
//  min: A pointer to a Node object.
//
// Outputs:
//
// A FibHeap constructor. Initializes the minimum node of the heap to the node passed to it.
//============================================================================================
FibHeap::FibHeap(Node *min)
{
    this->min = min;
}

//============================================================================================
// FibHeap::findMin
//
// Inputs:
//  heap: A pointer to a FibHeap object.
//
// Outputs:
//  The Node object containing the City object with the smallest distance attribute.
//
// Return the node with the minimum key (in this case the key will be the distance from the starting
// city in Dijkstra's algorithm to the city containd within a Node).
//============================================================================================
Node *FibHeap::findMin(FibHeap *heap)
{
    return heap->min;
}

//============================================================================================
// FibHeap::insert
//
// Inputs:
//  city: A City object to be inserted into the node which is inserted into the heap.
//  heap: A FibHeap object.
//
// Outputs:
//  The just-inserted node.
//
// Insert a new node into the heap.
//============================================================================================
Node *FibHeap::insert(City *city, FibHeap *heap)
{
    return FibHeap::insert(new Node(city), heap);
}

//============================================================================================
// FibHeap::
//
// Inputs:
//  node: The node which to be inserted into the heap.
//  heap: A FibHeap object.
//
// Outputs:
//  The just-inserted node.
//
// Insert a new node into the heap.
//============================================================================================
Node *FibHeap::insert(Node *node, FibHeap *heap)
{
    node->rank = 0;
    node->parent = nullptr;
    node->child = nullptr;
    node->left = node;
    node->right = node;
    node->mark = false;
    
    
    if(heap->min != nullptr){
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        
    }
    else{
        heap->min = node;
    }
    
    if(heap->min == nullptr || node->distance() < heap->min->distance()){
        heap->min = node;
    }
    
    return node;
}

//============================================================================================
// FibHeap::deleteMin
//
// Inputs:
//  heap: The FibHeap object to have the minimum node removed from.
//
// Outputs:
//  The City object that was contained within the minimum node before it was deleted.
//
// Remove the current minimum node from the heap and reorganize the heap.
//============================================================================================
City *FibHeap::deleteMin(FibHeap *heap)
{
    std::vector<Node *> children;
    City *ret = heap->min->item;
    Node *currChild, *temp;
    
    if(heap->min != nullptr){
        children = heap->min->getChildren();
        heap->min->child = nullptr;
        
        for(auto it = children.begin(); it != children.end(); it++){
            currChild = *it;
            
            currChild->parent = nullptr;
            currChild->left = currChild;
            currChild->right = currChild;
            
            FibHeap::insert(currChild, heap);
        }
        
        if(heap->min == heap->min->right){
            heap->min = nullptr;
        }
        else{
            heap->min->left->right = heap->min->right;
            heap->min->right->left = heap->min->left;
            temp = heap->min->right;
            heap->min->right = heap->min;
            heap->min->left = heap->min;
            
            heap->min = temp;
            heap->_linkRoots();
        }
    }
    
    return ret;
}

//============================================================================================
// FibHeap::decreaseKey
//
// Inputs:
//  delta:  The desired amount to decrease the node's key by.
//  node:   The Node object whose key is to be decreased.
//  heap:   The FibHeap object that contains node
//
// Outputs:
//
// Decrease the key (distance of the city contained within a node) of the specified node by the
// specified delta value and reorganize the heap accordingly.
//============================================================================================
void FibHeap::decreaseKey(unsigned long delta, Node *node, FibHeap *heap)
{
    Node *parent = node->parent;
    node->item->distance -= delta;
    
    if(node->parent != nullptr && node->distance() < node->parent->distance()){
        FibHeap::_cut(heap, node);
        FibHeap::_cascadingCut(heap, parent);
    }
    
    if (heap->min == nullptr || node->distance() < heap->min->distance()) {
        heap->min = node;
    }
}

//============================================================================================
// FibHeap::_cut
//
// Inputs:
//  heap: The FibHeap containing node.
//  node: The Node object to cut from its parent.
//
// Outputs:
//
// Remove a node from its parent and reorganize the FibHeap that contains that node accordingly.
//============================================================================================
void FibHeap::_cut(FibHeap *heap, Node *node){
    Node *parent = node->parent;
    
    if(parent != nullptr){
        if(parent->child == node){
            if(node->right == node){
                parent->child = nullptr;
            }
            else{
                parent->child = node->right;
                node->right->left = node->left;
                node->left->right = node->right;
                
                node->left = node;
                node->right = node;
            }
        }
        
        parent->rank--;
    }
    
    node->mark = true;
    FibHeap::insert(node, heap);
}

//============================================================================================
// FibHeap::_cascadingCut
//
// Inputs:
//  heap: The FibHeap object containing node.
//  node: The Node object to be cut from its parent.
//
// Outputs:
//
// A recursive version of the _cut method that keeps track of which nodes have been cut from their
// parent as it cuts nodes from some arbitrary depth to the root in order to reorganize heap. This
// is done when a key is decreased for some node as the effects of this decrease could potentially
// cascade throughout the tree.
//============================================================================================
void FibHeap::_cascadingCut(FibHeap *heap, Node *node){
    Node *parent = node->parent;
    
    if(parent != nullptr){
        if(!parent->mark){
            parent->mark = true;
        }
        else{
            FibHeap::_cut(heap, node);
            FibHeap::_cascadingCut(heap, parent);
        }
    }
}

//============================================================================================
// FibHeap::_linkRoots
//
// Inputs:
//
// Outputs:
//
// FibHeap objects can contain multiple root nodes. Linking the root nodes structures the heap
// so that nodes with the same arnk (# of children) are combined into one tree. This is done
// recursively so that each tree in the reorganized FibHeap is a valid Min-Heap.
//============================================================================================
void FibHeap::_linkRoots(){
    std::map<unsigned long, Node *> rankMap;
    Node *currNode = this->min;
    
    unsigned long minValue = ULONG_MAX;
    bool update;
    
    if(currNode != nullptr){
        do{
            update = false;
            
            if (minValue > currNode->distance()){
                minValue = currNode->distance();
                this->min = currNode;
            }
            
            if (rankMap[currNode->rank] == nullptr) 
            {
                update = true;
                rankMap[currNode->rank] = currNode;
            }
            else if(rankMap[currNode->rank] != currNode)
            {
                update = true;
                
                while(rankMap[currNode->rank] != nullptr && rankMap[currNode->rank] != currNode)
                {
                    currNode = Node::link(rankMap[currNode->rank], currNode);
                    rankMap[currNode->rank - 1] = nullptr;
                }
                
                rankMap[currNode->rank] = currNode;
            }
            currNode = currNode->right;
        } while ( update );
    }
}

//============================================================================================
// FibHeap::
//
// Inputs:
//  first:  A FibHeap object
//  second: A FibHeap object
//
// Outputs:
//  A new FibHeap object that is a combination of the first and second FIbHeap inputs.
//
// Combine two FibHeap objects, making sure that the smallest minimum node of the first and
// second inputs is the minimum node of the new heap.
//============================================================================================
FibHeap *FibHeap::_meld(FibHeap *first, FibHeap *second)
{
    FibHeap *a, *b;
    
    if (first->min->distance() < second->min->distance())
    {
        a = first;
        b = second;
    }
    else
    {
        a = second;
        b = first;
    }
    
    Node *temp = b->min->left;
    
    a->min->left->right = b->min;
    b->min->left = a->min->left;
    
    temp->right = a->min;
    a->min->left = temp;
    
    return a;
}

