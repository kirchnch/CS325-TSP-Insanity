//
//  tspGreedy.cpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/10/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#include "tspGreedy.h"

void nearestNeighborTSP(tour *t, int starting_vertex){
    
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
        t->tour_length += (int) round(sqrt(nearest_distance));
    }
    t->tour_length += (int) round(sqrt(pow(( t->vertices[0].x - t->vertices[t->count-1].x),2) \
            + pow(( t->vertices[0].y -  t->vertices[t->count-1].y),2)));
    
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
        nearestNeighborTSP(&tmp_tour, i);
        if (min_tour_length > tmp_tour.tour_length){
            min_tour_length = tmp_tour.tour_length;
            copyTour(&min_tour, &tmp_tour);
        }
    }
    
    return min_tour;
}

//get nearest neighbor to target
struct node *searchNN(struct node *cur, struct node *target,
              struct node **best, double *best_distance, int axis){
    if (cur == NULL){
        return 0;
    }

    //find distance between current node and target
    double distance = getDistance(cur, target);

    //set new best distance if found or does not exist
    if (distance < *best_distance){
        *best_distance = distance;
        *best = cur;
    }

    //get distance between current node and target
    //switch dimension between x and y as you recurse
    axis = (axis+1) % 2;

    if (target->point[axis] < cur->point[axis]){
        cur = searchNN(cur->left, target, best, best_distance, axis);
    }
    else {
        cur = searchNN(cur->right, target, best, best_distance, axis);
    }
}

//get distance between two nodes
double getDistance(struct node *cur, struct node *target){
    return pow((cur->point[0]-target->point[0]), 2) +
           pow((cur->point[1]-target->point[1]), 2);
}