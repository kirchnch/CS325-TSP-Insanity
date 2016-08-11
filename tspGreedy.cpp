//
//  tspGreedy.cpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/10/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#include "tspGreedy.h"

void nearestNeighbor(tour *t, int starting_vertex){
    
    swapVertex(t, 0, starting_vertex);
    for (int i=0; i< t->count-1; i++) {
        double tmp_distance = 0;
        int nearest;
        double nearest_distance = std::numeric_limits<double>::infinity();
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
