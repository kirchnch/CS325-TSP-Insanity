//
//  tspOpt2.hpp
//  Proj4-TSP
//
//  Created by Linh Dao on 8/11/16.
//  Copyright © 2016 Linh Dao. All rights reserved.
//

#ifndef tspOpt2_hpp
#define tspOpt2_hpp

#include <stdio.h>
#include "tspGreedy.h"

void opt2(struct tour*); //improve the initial tour
tour opt2swap(struct tour*, int, int, int);

#endif /* tspOpt2_hpp */
