//
//  FibHeap.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FibHeap.hpp"

//int nullptr = 0;

/*
 Public
 */

// Constructor
FibHeap::FibHeap(){
    this->min = nullptr;
}

FibHeap::FibHeap(Node *min)
{
    this->min = min;
}


Node *FibHeap::findMin(FibHeap *heap)
{
    return heap->min;
}


Node *FibHeap::insert(City *city, FibHeap *heap)
{
    return FibHeap::insert(new Node(city), heap);
}

Node *FibHeap::insert(Node *node, FibHeap *heap)
{
    if (heap->min == nullptr) 
    {
        heap->min = node;
    }
    else
    {
        *heap = *FibHeap::_meld(heap, new FibHeap(node));
    }
    return node;
}

City *FibHeap::deleteMin(FibHeap *heap)
{
    Node *currChild = heap->min->child;
    City *ret = heap->min->item;
    
    if(heap->min->right == heap->min)
    {
        heap->min = nullptr;
    }
    else
    {
        heap->min->right->left = heap->min->left;
        heap->min->left->right = heap->min->right;
        heap->min = heap->min->right;
    }
    
    Node *firstChild = currChild;
    
    if (currChild != nullptr) 
    {
        do
        {
            currChild->parent = nullptr;
            FibHeap::insert(currChild, heap);
            currChild = currChild->right;
        } while (currChild != firstChild);
    }
    
    heap->_linkRoots();
    
    return ret;
}

/*
We implement decrease key and delete as follows:
To cary out decrease key (A, i, h), 
we subtract A from the key of i, 
find the node x containing i, 
and cut the edge joining x to its parent p(x). 

This requires removing x from the list of children of p(x) 
and making the parent pointer of x null. 
The effect of the cut is to make the subtree rooted at x into a new tree of h, 
and requires decreasing the rank of p(x) 
and adding x to the list of roots of h. 

(If x is originally a root, 
    we carry out decrease key (A, i, h) merely by subtracting A from the key of i.) 
If the new key of i is smaller than the key of the minimum node, 
    we redefine the minimum node to be x. 

This method works because A is nonnegative; decreasing the key of i preserves heap order within the subtree rooted at x, though it may violate heap order between x and its parent. A decrease key operation takes 0( 1) actual time.
*/
/*
void FibHeap::decreaseKey(int delta, Node *node, FibHeap *heap)
{
    node->item->key -= delta;
    
    if(node->parent != nullptr){
        if(node->parent->child == node){
            if(node->right != node){
                node->parent->child = node->right;
            }
            else{
                node->parent->child = nullptr;
            }
        }
        
        node->parent->rank--;

        node->left->right = node->right;
        node->right->left = node->left;
        
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        
        FibHeap::insert(node, heap);
    }
}
 */
void FibHeap::decreaseKey(unsigned long delta, Node *node, FibHeap *heap)
{
    Node* parent = node->parent;
    
    node->item->distance = node->item->distance - delta;       // Might want to trap an error where (key - delta) < 0
    
    if (parent == nullptr)
    {
        if(heap->min->distance() > node->distance()){
            heap->min = node;
        }
        
        return;
    }
    else if (parent->item->distance <= node->item->distance){
        return;
    }
    
    FibHeap::_cut(node, heap);
}


void FibHeap::_cut(Node *node, FibHeap *heap)
{
    Node *originalParent = node->parent;
    
    if (originalParent != nullptr)
    {
        originalParent->rank--;
        
        /* Cut off pointers to node. */
        // Left
        Node* originalLeft = node->left;
        originalLeft->right = node->right;
        
        // Right
        Node* originalRight = node->right;
        originalRight->left = node->left;
        
        // Parent
        if(originalLeft == node)     // IE node is an only child
        {
            originalParent->child = nullptr;
        }
        else if (originalParent->child == node)      // IE parent points to child we are removing
        {
            originalParent->child = node->right;
        }
        
        /* Hoist node to root */ //I'm using the sibling pointers of min to track all root Citys.
        
        node->parent = nullptr;  // Is null how we denote root level?
        
        Node *min = heap->min;
        Node* rMin = min->right;
        
        min->right = node;
        node->right = rMin;
        
        rMin->left = node;
        node->left = min;
        
        
        if (min->item->distance > node->item->distance)
        {
            heap->min = node;
        }
        // Is there a data structure that keeps track of what is in root?
        // If so, add this node to root.
        
        // Cascade markings of original parent and _cut if needed.
        if(originalParent->mark == false)
        {
            originalParent->mark = true;
        }
        else
        {
            originalParent->mark = false;
            originalParent->rank -= 1;
            FibHeap::_cut(originalParent, heap);
            
            // Set parent->mark to false
            // Null child pointer
            // Move parent to root
            // Recursivly act on its parent node in same fassion
        }
    }
}

void FibHeap::deleteNode(Node *node, FibHeap *heap)
{
    if(node == heap->min){
        FibHeap::deleteMin(heap);
        return;
    }
    
    node->left->right = node->right;
    node->right->left = node->left;
    
    if (node->parent != nullptr)
    {
        node->parent->rank--;

        if(node->left == node)     // IE node is an only child
        {       
            node->parent->child = nullptr;
        }
        else if (node->parent->child == node)
        {
            node->parent->child = node->right;
        }
    }
    
    if(node->child != nullptr){
        node->child->right = heap->min->right;
        node->child->left = heap->min;
        node->child->parent = nullptr;
    }
    
    heap->_linkRoots();
}

void FibHeap::_linkRoots()
{
    unsigned long minValue = ULONG_MAX;
    bool update;
    std::map<unsigned long, Node *> rankMap;
    Node *currNode = this->min;
    
    if(currNode != nullptr)
    {
        do
        {
            update = false;
            
            if (minValue > currNode->distance())
            {
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

