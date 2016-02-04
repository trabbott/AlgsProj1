//
//  main.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include "FibHeap.hpp"
#include "FileReader.hpp"

int main(int argc, char *argv[]){
    /* FibHeap Tests
     
    FibHeap *heap1 = new FibHeap();
    
    FibHeap::insert(new Item(10), heap1);
    FibHeap::insert(new Item(11), heap1);
    FibHeap::insert(new Item(12), heap1);
    FibHeap::insert(new Item(100), heap1);
    
    for(int i = 0; i < 17; i++){
        FibHeap::insert(new Item(i), heap1);
    }
    
    Item *i;
    while (heap1->min != nullptr) {
        i = FibHeap::deleteMin(heap1);
        
        printf("%d\n", i->key);
    }
     */
    
    /*
     Input File Reading Tests
     */
    std::string filename = "/Volumes/Files/gregorymoon/Google Drive/School/2015-2016/Spring 2016/CSE 591 - Foundations of Algorithms/programming assignment/1/dijkstra/dijkstra/inputs/input-1.txt";
    FileReaderResult *result = FileReader::read(filename);
}
