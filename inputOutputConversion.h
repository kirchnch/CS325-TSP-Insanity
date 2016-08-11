//
//  inputOutputConversion.hpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/10/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#ifndef inputOutputConversion_hpp
#define inputOutputConversion_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <limits>
#include <cstring>
#include <stdio.h>

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
void copyTour(tour*, tour*);
void initTour(tour*, int);
void swapVertex(tour*, int, int);

#endif /* inputOutputConversion_hpp */
