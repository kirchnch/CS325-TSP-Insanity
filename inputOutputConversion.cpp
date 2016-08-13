//
//  inputOutputConversion.cpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/10/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#include "inputOutputConversion.h"

using namespace std;

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

void copyTour(tour *dest, tour *source){
    dest->tour_length = source->tour_length;
    dest->count = source->count;
    for (int i=0; i<source->count; i++){
        dest->vertices[i] = source->vertices[i];
    }
}

void initTour(tour *t, int num_vertices){
    t->count = 0;
    t->tour_length = 0;
    t->vertices = (vertex*) malloc(sizeof(vertex)*num_vertices);
}

int getTourLength(tour *t) {
    int tourLength = 0;
    int edgeLength;
    for (int i=0; i < t->count-1; i++) {
        edgeLength = (int) round(sqrt(pow((t->vertices[i].x - t->vertices[i+1].x),2)
                                + pow((t->vertices[i].y - t->vertices[i+1].y),2)));
        tourLength += edgeLength;
    }
    //need to calculate distance between last vertex and starting vertex
    tourLength += (int) round(sqrt(pow((t->vertices[0].x - t->vertices[t->count-1].x),2) \
                      + pow((t->vertices[0].y - t->vertices[t->count-1].y),2)));

    return tourLength;
}

void initEdgeList(edgeList* edgeList, int numOfEdges) {
    edgeList->count = 0;
    edgeList->edges = (edge*) malloc (sizeof(edge)*numOfEdges);
}

void swapVertex(tour *t, int x, int y){
    vertex tmp = t->vertices[x];
    t->vertices[x] = t->vertices[y];
    t->vertices[y] = tmp;
}

void swapEdge(edgeList* lst, int index1, int index2) {
    edge tmp = lst->edges[index1];
    lst->edges[index1] = lst->edges[index2];
    lst->edges[index2] = tmp;
}