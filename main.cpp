//
//  main.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FibHeap.hpp"

int main(int argc, char *argv[]){
    FibHeap *heap1 = new FibHeap();
    
    /*
    FibHeap::insert(new Item(10), heap1);
    FibHeap::insert(new Item(11), heap1);
    FibHeap::insert(new Item(12), heap1);
    FibHeap::insert(new Item(100), heap1);
     */
    
    for(int i = 0; i < 17; i++){
        FibHeap::insert(new Item(i), heap1);
    }
    
    Item *i;
    while (heap1->min != nullptr) {
        i = FibHeap::deleteMin(heap1);
        
        printf("%d\n", i->key);
    }
    
    
    
    printf("Done\n");
}