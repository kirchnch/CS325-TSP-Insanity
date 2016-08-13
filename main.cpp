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
#include <unistd.h>
#include "inputOutputConversion.h"
#include "tspGreedy.h"
#include "tspOpt2.h"

using namespace std;

//use globals for alarm
struct tour best_tsp;
string output_filename;

//setup signal alarm
void sigalrm_handler(int sig){
    tourToFile(&best_tsp, output_filename);
    exit(0);
}

int main(int argc, const char * argv[]) {
    //first argument is intput filename
    string input_filename = argv[1];
    //assign output filename
    output_filename = input_filename + ".tour";
    
    //get list of tour from parsed file
    struct tour tsp;

    initTour(&tsp, 0);
    fileToTour(input_filename, &tsp);
    initTour(&best_tsp, tsp.count);


    //setup alarm
    signal(SIGALRM, &sigalrm_handler);
    //run for 2:59 min (179 s) with one second for write (?)
    alarm(179);

    //do multiple iterations of greedy TSP algorithm with different starting vertices
    double best_distance = std::numeric_limits<double>::infinity();
    int start_vertex = 0;
    int num_vertices = tsp.count;

    struct tour tmp;
    initTour(&tmp, tsp.count);
    while (start_vertex < num_vertices){
        copyTour(&tmp, &tsp);
        nearestNeighborTSP(&tmp, start_vertex);
        start_vertex++;
        cout << "NN: " << tmp.tour_length << endl; //debug


        if (best_distance > tmp.tour_length){
            best_distance = tmp.tour_length;
            copyTour(&best_tsp, &tmp);
            tourToFile(&best_tsp, output_filename);
        }

        //improve tsp by opt_2
        opt2(&tmp);

        cout << "OPT: " << tmp.tour_length << endl;

        if (best_distance > tmp.tour_length){
            best_distance = tmp.tour_length;
            copyTour(&best_tsp, &tmp);
            tourToFile(&best_tsp, output_filename);
        }
    }
    tourToFile(&best_tsp, output_filename);
}







