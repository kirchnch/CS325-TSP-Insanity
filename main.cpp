#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <limits>
#include <cstring>
#include "inputOutputConversion.h"
#include "tspGreedy.h"

using namespace std;


int main(int argc, const char * argv[]) {
    //first argument is intput filename
    string input_filename = argv[1];
    //assign output filename
    string output_filename = input_filename + ".tour";
    
    //get list of tour from parsed file
    struct tour tsp;
    initTour(&tsp, 0);
    fileToTour(input_filename, &tsp);
    
    //do multiple iterations of greedy TSP algorithm with different starting vertices
    tsp = loopNN(&tsp, 1);
    
    //convert TSP tour sorted by index to output file
    tourToFile(&tsp, output_filename);
}







