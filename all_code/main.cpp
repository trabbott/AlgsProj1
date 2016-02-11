//
//  main.cpp
//  dijkstra
//
//  Created by Gregory Moon on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include <string>
#include <map>

#include "CommandLineReader.hpp"
#include "Dijkstra.hpp"
#include "FibHeap.hpp"
#include "FileReader.hpp"
#include "InputReader.hpp"

static void showUsage();
static std::map<std::string, std::string> getParameters(int argc, char *argv[]);

int main(int argc, char *argv[]){
    /*
     Command Line Parsing
     
     Would like to use getopt but it's not necessarily as cross-platform friendly as doing it a simpler/less effective way. The getParameters/showUsage functions should be fine for our purposes though.
    */
    /*
    InputReaderResult *input;
    
    if(argc < 2){
        input = CommandLineReader::read();
    }
    else{
        std::map<std::string, std::string> params = getParameters(argc, argv);
        
        if(params["help"] == "t"){
            showUsage();
            return 0;
        }
        
        input = FileReader::read(params["filepath"]);
    }
     */
    
    /*
     FibHeap Tests
     */
    
    /*
    FibHeap *heap1 = new FibHeap();
    
    Node *n3 = FibHeap::insert(new City(3), heap1);
    Node *n4 = FibHeap::insert(new City(4), heap1);
    Node *n5 = FibHeap::insert(new City(5), heap1);
   Node *n7=  FibHeap::insert(new City(7), heap1);
    Node *n8 = FibHeap::insert(new City(8), heap1);
    Node *n14= FibHeap::insert(new City(14), heap1);
    Node *n12 = FibHeap::insert(new City(12), heap1);
   Node *n10 =  FibHeap::insert(new City(10), heap1);
   Node *n9 =  FibHeap::insert(new City(9), heap1);
   Node *n15 =  FibHeap::insert(new City(15), heap1);
    
    heap1->_linkRoots();
    
    FibHeap::decreaseKey(4, n10, heap1);
     */
    
    /*
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
    std::string filename = "/Volumes/Files/gregorymoon/Google Drive/School/2015-2016/Spring 2016/CSE 591 - Foundations of Algorithms/programming assignment/1/dijkstra/dijkstra/inputs/input-2.txt";
    InputReaderResult *result = FileReader::read(filename);
    
    std::map<unsigned long, City *> path = Dijkstra::run(result);
    std::vector<unsigned long> output;
    unsigned long currKey = path[result->to]->key;
    output.push_back(result->to);
    
    do{
        output.push_back(currKey);
        currKey = path[currKey]->key;
    }while(currKey != result->from);
    
    output.push_back(result->from);
    
    while(output.size() > 0){
        if(output.size() > 1){
            printf("%lu -> ", output.back());
        }
        else{
            printf("%lu\n", output.back());
        }
        
        output.pop_back();
    }
    
    
    /*
     Command Line Reading Tests
     */
    /*
    CommandLineReader::read();
     */
}

static std::map<std::string, std::string> getParameters(int argc, char *argv[]){
    std::map<std::string, std::string> options;
    options["help"] = "f";
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if ((arg == "-h") || (arg == "--help")) {
            options["help"] = "t";
        }
        else if ((arg == "-f") || (arg == "--file")) {
            if (i + 1 < argc) {
                options["filepath"] = argv[++i];
            }
            else{
                fprintf(stderr,"--file option requires one argument.\n");
                options["help"] = "t";
            }
        }
        else{
            fprintf(stderr,"Unknown argument '%s'.\n", arg.c_str());
            options["help"] = "t";
        }
        
        if(options["help"] == "t"){
            break;
        }
    }
    
    return options;
}

static void showUsage()
{
    fprintf(stderr,
        "Usage: dijkstra <option(s)> INPUT\n"
        "Options:\n"
            "\t-h,--help\t\t\t\tShow this help message\n"
            "\t-f,--file FILE_PATH\t\tRead input from a file\n\n"
        "If no option is included, you will be prompted for inputs from the command line.\n\n"
    );
}
