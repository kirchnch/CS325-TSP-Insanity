#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <limits>
#include <cstring>

using namespace std;

//single vertex
struct vertex {
    int x;
    int y;
    int index;
};

//list of tour
struct tour {
    vertex *vertices;
    int count;
    int tour_length;
};

void fileToTour(string, tour*);
void printTour(tour*);
void tourToFile(tour*, string);
void nearestNeighbor(tour*, int);
void initTour(tour*, int);
void swapVertex(tour*, int, int);
struct tour loopNN(tour*,int);
void copyTour(tour*, tour*);

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

void nearestNeighbor(tour *t, int starting_vertex){

    swapVertex(t, 0, starting_vertex);
    for (int i=0; i< t->count-1; i++) {
        double tmp_distance = 0;
        int nearest;
        double nearest_distance = infinity();
        for (int j = i + 1; j <  t->count; j++) {
            //calculate pseudo distance sum of squares instead of sqrt(x^2+y^2) for speed
            //convert later to kd-tree?
            tmp_distance = pow(( t->vertices[i].x -  t->vertices[j].x),2) \
                           + pow(( t->vertices[i].y -  t->vertices[j].y),2);
            if (nearest_distance > tmp_distance) {
                nearest_distance = tmp_distance;
                nearest = j;
            }
        }
        swapVertex(t, i + 1, nearest);
        t->tour_length += sqrt(nearest_distance);
    }

}

//loops over greedy algorithm for different starting points
struct tour loopNN(tour *t, int num_loops){
    struct tour min_tour;
    initTour(&min_tour, t->count);
    struct tour tmp_tour;
    initTour(&tmp_tour, t->count);

    int min_tour_length = numeric_limits<int>::max();
    for (int i=0; i<num_loops; i++){
        copyTour(&tmp_tour, t);
        nearestNeighbor(&tmp_tour, i);
        if (min_tour_length > tmp_tour.tour_length){
            min_tour_length = tmp_tour.tour_length;
            copyTour(&min_tour, &tmp_tour);
        }
    }

    return min_tour;
}

void copyTour(tour *dest, tour *source){
    dest->tour_length = source->tour_length;
    dest->count = source->count;
    for (int i=0; i<source->count; i++){
        dest->vertices[i] = source->vertices[i];
    }

}

void swapVertex(tour *t, int x, int y){
    vertex tmp = t->vertices[x];
    t->vertices[x] = t->vertices[y];
    t->vertices[y] = tmp;
}

void initTour(tour *t, int num_vertices){
    t->count = 0;
    t->tour_length = 0;
    t->vertices = (vertex*) malloc(sizeof(vertex)*num_vertices);
}

void fileToTour(string filename, tour *t){
    ifstream inputFile(filename);
    if (!inputFile.is_open()){
        cout << "Error opening input file \n";
    }

    //find the number of lines
    string line;
    int lineCount = 0;
    while (getline(inputFile, line) && line.size() > 1){
        lineCount++;
    }

    //go back to beginning
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    //parse lines to vertices of tour
    t->vertices = (vertex *) malloc(sizeof(vertex)*lineCount);
    t->count = lineCount;
    for (int i=0; i<t->count; i++){
        vertex v;
        getline(inputFile, line);
        stringstream ss(line);

        //parse each line into vertex
        ss >> ws >> v.index >> ws >> v.x >> ws >> v.y;
        t->vertices[i] = v;
    }

    inputFile.close();
}

void tourToFile(tour *t, string filename){
    ofstream outputFile(filename);
    if (!outputFile.is_open()){
        cout << "Cannot open output file" << endl;
    }

    //output length of tour
    outputFile << t->tour_length << endl;
    for (int i=0; i<t->count; i++){
        outputFile << t->vertices[i].index << endl;
    }

    outputFile.close();
}

void printTour(tour *t){

    for(int i=0; i<t->count; i++){
        cout << t->vertices[i].index << " " << t->vertices[i].x << " " << t->vertices[i].y << " " << endl;
    }
    cout << t->tour_length << endl;
}
