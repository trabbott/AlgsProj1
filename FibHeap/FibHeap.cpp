//
//  FibHeap.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FibHeap.hpp"

/*
 Public
 */

FibHeap::FibHeap(){
    this->min = nullptr;
}

FibHeap::FibHeap(Node *min){
    this->min = min;
}

Node *FibHeap::findMin(FibHeap *heap){
    return heap->min;
}

void FibHeap::insert(Item *item, FibHeap *heap){
    FibHeap::insert(new Node(item), heap);
}

void FibHeap::insert(Node *node, FibHeap *heap){
    if (heap->min == nullptr) {
        heap->min = node;
    }
    else{
        *heap = *FibHeap::_meld(heap, new FibHeap(node));
    }
}

Item *FibHeap::deleteMin(FibHeap *heap){
    Node *currChild = heap->min->child;
    Item *ret = heap->min->item;
    
    if(heap->min->right == heap->min){
        heap->min = nullptr;
    }
    else{
        heap->min->right->left = heap->min->left;
        heap->min->left->right = heap->min->right;
        heap->min = heap->min->right;
    }
    
    Node *firstChild = currChild;
    
    if (currChild != nullptr) {
        do{
            currChild->parent = nullptr;
            FibHeap::insert(currChild, heap);
            currChild = currChild->right;
        }while (currChild != firstChild);
    }
    
    heap->_linkRoots();
    
    return ret;
}

void FibHeap::decreaseKey(int delta, Item *item, FibHeap *heap){
}

/*
 Private
 */

void FibHeap::_linkRoots(){
    unsigned long minValue = INT_MAX;
    bool update;
    std::map<unsigned long, Node *> rankMap;
    Node *currNode = this->min;
    
    if(currNode != nullptr){
        do{
            update = false;
            
            if (minValue > currNode->key()) {
                minValue = currNode->key();
                this->min = currNode;
            }
            
            if (rankMap[currNode->rank] == nullptr) {
                update = true;
                rankMap[currNode->rank] = currNode;
            }
            else if(rankMap[currNode->rank] != currNode){
                update = true;
                
                while(rankMap[currNode->rank] != nullptr && rankMap[currNode->rank] != currNode){
                    currNode = Node::link(rankMap[currNode->rank], currNode);
                    rankMap[currNode->rank - 1] = nullptr;
                }
                
                rankMap[currNode->rank] = currNode;
            }
            currNode = currNode->right;
        } while ( update );
    }
}

FibHeap *FibHeap::_meld(FibHeap *first, FibHeap *second){
    FibHeap *a, *b;
    
    if (first->min->key() < second->min->key()) {
        a = first;
        b = second;
    }
    else{
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

