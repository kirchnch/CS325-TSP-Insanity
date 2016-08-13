//
//  tspGreedy.hpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/10/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#ifndef tspGreedy_hpp
#define tspGreedy_hpp

#include <stdio.h>
#include "inputOutputConversion.h"

struct node {
    int point[2];
    struct node *left, *right;
};

void nearestNeighborTSP(tour*, int);
tour loopNN(tour*,int);
struct node *searchNN(struct node *, struct node *,
                      struct node **, double *, int );
double getDistance(struct node *a, struct node *b);

#endif /* tspGreedy_hpp */
