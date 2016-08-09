#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

tour fileToTour(string);
void printTour(tour);
void tourToFile(tour, string);
tour nearestNeighbor(tour);

int main(int argc, const char * argv[]) {
    //first argument is intput filename
    string input_filename = argv[1];
    //assign output filename
    string output_filename = input_filename + ".tour";

    //get list of tour from parsed file
    tour tsp;
    tsp = fileToTour(input_filename);
    nearestNeighbor(tsp);

    //convert TSP tour sorted by index to output file
    tourToFile(tsp, output_filename);
}

tour nearestNeighbor(tour vs){
    //tsp answer data type
    tour tsp;
    cout << "blah";
    tsp.vertices = (vertex*) malloc(sizeof(vertex)*vs.count);
    tsp.vertices[0] = vs.vertices[0];
    for (int i=0; i<vs.count-1; i++){
        vertex nearest;
        double nearest_distance = INFINITY;
        for (int j=i+1; j<vs.count; i++){
            //calculate sum of squares instead of sqrt(x^2+y^2) for speed
            //convert later to kd-tree?
            double tmp_distance = sqrt(vs.vertices[i].x-vs.vertices[j].x) + sqrt(vs.vertices[i].y-vs.vertices[j].y);
            if (nearest_distance > tmp_distance){
                nearest_distance = tmp_distance;
                nearest = vs.vertices[j];
            }
        }
        tsp.vertices[i+1] = nearest;
    }
    printTour(vs);
}

tour fileToTour(string filename){
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
    tour vs;
    vs.vertices = (vertex *) malloc(sizeof(vertex)*lineCount);
    vs.count = lineCount;
    for (int i=0; i<vs.count; i++){
        vertex v;
        getline(inputFile, line);
        stringstream ss(line);

        //parse each line into vertex
        ss >> ws >> v.index >> ws >> v.x >> ws >> v.y;
        vs.vertices[i] = v;
    }

    inputFile.close();
    return vs;
}

void tourToFile(tour vs, string filename){
    ofstream outputFile(filename);
    if (!outputFile.is_open()){
        cout << "Cannot open output file" << endl;
    }

    //output length of tour
    outputFile << vs.tour_length;
    for (int i=0; i<vs.count; i++){
        outputFile << vs.vertices[i].index  << endl;
    }

    outputFile.close();
}

void printTour(tour vs){
    for(int i=0; i<vs.count; i++){
        cout << vs.vertices[i].index << " " << vs.vertices[i].x << " " << vs.vertices[i].y << " " << endl;
    }
}
