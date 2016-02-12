//  Node.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "Node.hpp"

//============================================================================================
// Node::Node
//
// Inputs:
//  city: The City object to be contained within the node.s
//
// Outputs:
//
// The node constructor which initializes all attributes to their apropriate values.
//============================================================================================
Node::Node(City *city){
    this->item = city;
    this->rank = 0;

    this->child = nullptr;
    this->left = this;
    this->right = this;
    this->parent = nullptr;
    
}

//============================================================================================
// Node::getChildren
//
// Inputs:
//
// Outputs:
//  A vector of Node objects corresponding to the children of a node
//
//  A utility method that makes it easier to traverse through the children of a node without having
//  to keep track of any pointers by using a vector.
//============================================================================================
std::vector<Node *> Node::getChildren(){
    std::vector<Node *> ret;
    Node *currNode;
    
    if((currNode = this->child) != nullptr){
        Node *firstNode = currNode;
        
        do{
            ret.push_back(currNode);
            currNode = currNode->right;
        }while(currNode != firstNode);
    }
    
    return ret;
}

//============================================================================================
// Node::link
//
// Inputs:
//  first:  The first of the Node objects to be linked.
//  second: The other Node object to be linked.
//
// Outputs:
//  The Node with the smaller distance of the two that were input.
//
// This methos is analagous to the FibHeap _meld method. Two nodes are combined so that the one
// whose distance is larger becomes a child of the one whose distance is smaller. The combindation
// is done in such a way that the mean heap property of each node is maintained.
//============================================================================================
Node *Node::link(Node *first, Node *second){
    Node *a, *b;
    
    if (first->distance() < second->distance()) {
        a = first;
        b = second;
    }
    else{
        a = second;
        b = first;
    }
    
    if(b->parent == nullptr){
        a->parent = nullptr;
    }
    else if(a->parent == nullptr){
        b->parent = nullptr;
    }
    
    b->left->right = b->right;
    b->right->left = b->left;
    a->addChild(b);
    
    return a;
}

//============================================================================================
// Node::addChild
//
// Inputs:
//  newChild: The Node object to be added as a child to the current Node.
//
// Outputs:
//
// Add a child to the current node. After the new node is added, the _linkChildren method is called
// which ensures that the min heap properties are maintained by every node.
//============================================================================================
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
        newChild->right = this->child->right;
        this->child->right->left = newChild;
    }
    
    this->child->right = newChild;
    newChild->left = this->child;
    newChild->parent = this;
    
    this->rank++;
    this->_linkChildren();
}

//============================================================================================
// Node::_linkChildren
//
// Inputs:
//
// Outputs:
//
// Analagous to the link method of the FibHeap class. All of the children with the same # of
// children are combined to maintain the required min heap properties of each node.
//============================================================================================
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

//============================================================================================
// Node::distance
//
// Inputs:
//
// Outputs:
//  The distance attribute of the City object contained within the node.
//============================================================================================
unsigned long Node::distance(){
   // return std::max(this->item->opt->value, this->item->mand->value);
    
    return this->item->distance;
}

//============================================================================================
// Node::key
//
// Inputs:
//
// Outputs:
//  The id attribute of the City object contained within the node.
//============================================================================================
unsigned long Node::key(){
    return this->item->key;
}
