#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <limits>
#include <cstring>
#include <time.h>
#include "inputOutputConversion.h"
#include "tspGreedy.h"
#include "tspOpt2.h"

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
    clock_t begin;
    begin = clock();
    tsp = loopNN(&tsp, 1);
    clock_t end1;
    end1 = clock();
    cout << tsp.tour_length << endl; //debug
    cout << getTourLength(&tsp)<< endl; //debug
    cout << (double)(end1 - begin)/CLOCKS_PER_SEC << endl;
    
    //improve tsp by opt_2
    opt2(&tsp);
    clock_t end2;
    end2 = clock();
    cout << getTourLength(&tsp)<< endl; //debug
    cout << (double)(end2 - begin)/CLOCKS_PER_SEC << endl;
    
    //convert TSP tour sorted by index to output file
    tourToFile(&tsp, output_filename);
}







