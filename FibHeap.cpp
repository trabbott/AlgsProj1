//
//  FibHeap.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
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
    /*
    if (heap->min == nullptr) 
    {
        heap->min = node;
    }
    else
    {
        *heap = *FibHeap::_meld(heap, new FibHeap(node));
    }
    return node;
     */
    
    /*
     degree[x] := 0
     p[x] := NIL
     child[x] := NIL
     left[x] := x
     right[x] := x
     mark[x] := FALSE
     concatenate the root list containing x with root list H
     if min[H] = NIL or key[x]<key[min[H]]
     then min[H] := x
     n[H]:= n[H]+1
     */
    
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

City *FibHeap::deleteMin(FibHeap *heap)
{
    /*
    std::vector<Node *> children = heap->min->getChildren();
    City *ret = heap->min->item;
    
    if(heap->min->right != heap->min){
        heap->min->right->left = heap->min->left;
        heap->min->left->right = heap->min->right;
        heap->min = heap->min->right;
    }
    else{
        heap->min = nullptr;
    }
    
    Node *temp;
    
    for(auto it = children.begin(); it != children.end(); it++){
        temp = *it;
        temp->parent = nullptr;
        FibHeap::insert(temp, heap);
    }
    
    heap->_linkRoots();
    
    return ret;
     */
    
    /*
     z:= min[H]
     if z <> NIL
        then for each child x of z
            do add x to the root list of H
                p[x]:= NIL
            remove z from the root list of H
            if z = right[z]
                then min[H]:=NIL
                else min[H]:=right[z]
                    CONSOLIDATE(H)
                n[H] := n[H]-1
     return z
     
     */
    
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
void FibHeap::decreaseKey(unsigned long delta, Node *node, FibHeap *heap)
{
    /*
    node->item->distance = node->item->distance - delta;       // Might want to trap an error where (key - delta) < 0
    
    if(node->parent != nullptr){
        if(node->parent->child == node){
            if(node->right == node){
                node->parent->child = nullptr;
            }
            else{
                node->parent->child = node->right;
            }
        }
    }
    
    if(node->right != node){
        node->right->left = node->left;
        node->left->right = node->right;
    }
    
    node->parent = nullptr;
    node->left = node;
    node->right = node;
    
    FibHeap::insert(node, heap);
    */
    /*
    Node* parent = node->parent;
    if (parent == nullptr)
    {
        if(heap->min != nullptr && heap->min->distance() > node->distance()){
            heap->min = node;
        }
        
        return;
    }
    else if (parent->item->distance <= node->item->distance){
        return;
    }
     */
    
    /*
     if k > key[x]
        then error "new key is greater than current key"
     key[x] := k
     y := p[x]
     if y <> NIL and key[x]<key[y]
        then CUT(H, x, y)
            CASCADING-CUT(H,y)
     if key[x]<key[min[H]]
        then min[H] := x
     */
    
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

/*
 CUT(H,x,y)
 Remove x from the child list of y, decrementing degree[y]
 Add x to the root list of H
 p[x]:= NIL
 mark[x]:= FALSE
 
*/

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

/*
CASCADING-CUT(H,y)
z:= p[y]
if z <> NIL
then if mark[y] = FALSE
then mark[y]:= TRUE
else CUT(H, y, z)
CASCADING-CUT(H, z)
*/
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

