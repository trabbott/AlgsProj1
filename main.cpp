//
//  main.cpp
//  dijkstra
//
//  Created by Gregory Moon & Tim Abbott on 1/31/16.
//  Copyright © 2016 Gregory Moon. All rights reserved.
//

#include <algorithm>
#include <climits>
#include <cstdarg>
#include <string>
#include <map>

#include "CommandLineReader.hpp"
#include "Dijkstra.hpp"
#include "FibHeap.hpp"
#include "FileReader.hpp"
#include "InputReader.hpp"

static void showUsage();
static void printMandatoryPath(InputReaderResult *input, DijkstraResult *forwardResult);
static void printOptionalPahts(InputReaderResult *input, DijkstraResult *forwardResult, DijkstraResult *backwardResult);
static std::map<std::string, std::string> getParameters(int argc, char *argv[]);

int main(int argc, char *argv[]){
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
    
    printf("\nCalculating Shortest Path...\n");
    DijkstraResult *forwardResult = Dijkstra::runForward(input), *backwardResult = Dijkstra::runBackward(input);
    
    printMandatoryPath(input, forwardResult);
    printOptionalPahts(input, forwardResult, backwardResult);
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

static void printOptionalPahts(InputReaderResult *input, DijkstraResult *forwardResult, DijkstraResult *backwardResult){
    std::vector<unsigned long> output;
    Road *temp;
    unsigned long optDist, idx = 1, minPath = 0, minPathValue = ULONG_MAX;
    unsigned long currKey = input->to, mandLength = forwardResult->distances[input->to];
    std::vector<unsigned long> shorterPaths;

    printf("\n\n============ PATHS MADE BY OPTIONAL ROADS BELOW =====================\n");
    
    printf("\nPaths using an optional road:\n");
    for(auto it = input->optionalRoads.begin(); it != input->optionalRoads.end(); it++){
        temp = *it;
        
        optDist = temp->length + forwardResult->distances[temp->from] + backwardResult->distances[temp->to];
        
        if(optDist < mandLength){
            shorterPaths.push_back(idx);
        }
        
        if(optDist < minPathValue){
            minPathValue = optDist;
            minPath = idx;
        }
        
        printf("  Path %lu: ", idx);
        
        currKey = temp->from;
        
        do{
            output.push_back(currKey);
            if ( forwardResult->previous.find(currKey) == forwardResult->previous.end() ) {
                break;
            } else {
                currKey = forwardResult->previous[currKey]->key;
            }
        }while(currKey != input->from);
        
        if(std::find(output.begin(), output.end(), currKey) == output.end()) {
            output.push_back(currKey);
        }
        
        currKey = temp->to;
        
        do{
            output.insert(output.begin(), currKey);
            if ( backwardResult->previous.find(currKey) == backwardResult->previous.end() ) {
                break;
            } else {
                currKey = backwardResult->previous[currKey]->key;
            }
        }while(currKey != input->to);
        
        if(std::find(output.begin(), output.end(), currKey) == output.end()) {
            output.insert(output.begin(), currKey);
        }
        
        while(output.size() > 0){
            if(output.size() > 1){
                printf("%lu -> ", output.back());
            }
            else{
                printf("%lu with length %lu\n", output.back(), optDist);
            }
            
            output.pop_back();
        }
        
        idx++;
    }
    
    
    printf("\n\n==================== SHORTEST PATH SUMMARY BELOW ==============================\n");
    
    switch(shorterPaths.size())
    {
        case 0:
            printf("\n0: No optional paths are shorter than the path using only existing roads.\n\n");
            break;
        case 1:
            printf("\n1: Optional path %lu is shorter than the path using only existing roads.\n", shorterPaths[0]);
            printf("\nOptional path %lu is the shortest possible path and has length %lu.\n\n", minPath, minPathValue);
            break;
        default:
            printf("\n2+: Optional paths ");
            int i;
            for (i = 0; i < shorterPaths.size() - 1; i++)
            {
                printf("%lu ", shorterPaths[i]);
            }
            printf("and %lu are shorter than the path using only existing roads.\n", shorterPaths[i]);
            printf("\nOptional path %lu is the shortest possible path and has length %lu.\n\n", minPath, minPathValue);
            break;
    }
}

static void printMandatoryPath(InputReaderResult *input, DijkstraResult *forwardResult){
    std::vector<unsigned long> output;
    unsigned long currKey = input->to, mandLength = forwardResult->distances[input->to];
    
    printf("\nShortest path using existing roads:\n");
    
    if(mandLength == ULONG_MAX){
        printf("\nThere is no path from %lu to %lu using only existing roads.\n", input->from, input->to);
        return;
    }
    
    do{
        output.push_back(currKey);
        
        if(forwardResult->previous.find(currKey) != forwardResult->previous.end()){
            currKey = forwardResult->previous[currKey]->key;
        }
        else{
            break;
        }
    }while(currKey != input->from);
    
    if(std::find(output.begin(), output.end(), currKey) == output.end()) {
        output.push_back(input->from);
    }
    
    while(output.size() > 0){
        if(output.size() > 1){
            printf("%lu -> ", output.back());
        }
        else{
            printf("%lu with length %lu\n", output.back(), mandLength);
        }
        
        output.pop_back();
    }
}

static void showUsage()
{
    fprintf(stderr,
            "Usage: dijkstra <option(s)> INPUT\n"
            "Options:\n"
            "   -h,--help             Show this help message\n"
            "   -f,--file FILE_PATH   Read input from a file\n\n"
            "   If no option is included, you will be prompted for inputs from the command line.\n\n"
            );
}

