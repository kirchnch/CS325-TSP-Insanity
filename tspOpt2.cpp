//
//  tspOpt2.cpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/11/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#include "tspOpt2.h"

//find the initial tour using NN algorithm
tour getNNtour(struct tour tsp) {
    tour NNtour = loopNN(&tsp, 1);
    return NNtour;
}

//improve the initial tour that was found by NN algorithm
void opt2(struct tour *initialTour) {
    int vertexCount = initialTour->count;
    
    //Try swapping each vertex with all other vertices to see if the tour is improved
    int unimprove = 0;
    int best_dist = initialTour->tour_length;
    
    for (int i = 0; i < vertexCount-1; i++) {
        for (int j = i+1; j < vertexCount; j++) {
            
            tour tmp = opt2swap(initialTour, i, j, vertexCount);
            int new_dist = getTourLength(&tmp);
            tmp.tour_length = new_dist;
            //cout << new_dist << endl; //debug
            
            //if found a better route
            if (new_dist < best_dist) {
                //opt2swap(initialTour, i, j, new_dist, vertexCount);
                copyTour(initialTour, &tmp);
                best_dist = new_dist;
                unimprove = 0; //reset unimproved count
                cout << best_dist << endl;
            }
            else {
                unimprove++;
            }
        }
    }

}

tour opt2swap(struct tour *initialTour, int i, int j, int vertexCount) {
    struct tour tmp;
    //int vertexCount = initialTour->count;
    initTour(&tmp, vertexCount);
    //tmp.tour_length = new_dist;
    
    //add route[0] to route[i-1] in order to tmp
    for (int c = 0; c < i; c++){
        tmp.vertices[c] = initialTour->vertices[c];
        tmp.count++;
    }
    
    //add route[i] to route[j] in reverse order to tmp
    int dec = 0;
    for (int c = i; c <= j; c++) {
        tmp.vertices[c] = initialTour->vertices[j-dec];
        dec++;
        tmp.count++;
    }
    
    //add route[j+1] to end of route in order to tmp
    for (int c = j+1; c < vertexCount; c++) {
        tmp.vertices[c] = initialTour->vertices[c];
        tmp.count++;
    }
    
    return tmp;
    //copy the new tour to initialTour
    //copyTour(initialTour, &tmp);
}