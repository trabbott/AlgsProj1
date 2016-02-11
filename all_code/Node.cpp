//  Node.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "Node.hpp"

Node::Node(City *city){
    this->item = city;
    this->rank = 0;

    this->child = nullptr;
    this->left = this;
    this->right = this;
    this->parent = nullptr;
}

Node *Node::link(Node *first, Node *second){
    Node *a, *b;
    
    if (first->key() < second->key()) {
        a = first;
        b = second;
    }
    else{
        a = second;
        b = first;
    }
    
    b->left->right = b->right;
    b->right->left = b->left;
    a->addChild(b);
    
    return a;
}

void Node::addChild(Node *newChild){
    if (newChild == nullptr) {
        return;
    }
    else if (this->child == nullptr) {
        this->child = newChild;
    }
    else if(this->child->right == this->child){
        this->child->left = newChild;
        newChild->right = this->child;
    }
    else{
        Node *temp = this->child->right;
        
        newChild->right = temp;
        temp->left = newChild;
    }
    
    this->child->right = newChild;
    
    newChild->left = this->child;
    newChild->parent = this;
    this->rank++;
    this->_linkChildren();
}

void Node::_linkChildren(){
    bool update;
    std::map<int, Node *> rankMap;
    Node *currNode = this->child;
    
    if(currNode != nullptr){
        do{
            update = false;
            
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

unsigned long Node::distance(){
    return this->item->distance;
}

unsigned long Node::key(){
    return this->item->key;
}
