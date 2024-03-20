//
// Created by Loïc Bermudez on 18/03/2024.
//

#ifndef LOP_VND_ALGORITHMS_H
#define LOP_VND_ALGORITHMS_H

#include <vector>
#include <cstdlib>
#include <string>
#include "../skeleton/instance/instance.h"
#include "config/configuration.h"

/*  Initialisation */
vector<long int> createRandomSolution(Instance &instance);

vector<long int> createCWHeuristicSolution(Instance &instance);

/*  Pivot    */
vector<long int> firstImprovement(Instance &instance, vector<long int> s);
vector<long int> bestImprovement(Instance &instance, vector<long int> s);

/* Operations */
vector<long int> exchange(vector<long int> s, int i, int j);
vector<long int> insert(vector<long int> s, int i, int j);
vector<long int> transpose(vector<long int> s, int i, int j);

/* constants for a pseudo-random number generator, taken from
   Numerical Recipes in C book --- never trust the standard C random
   number generator */
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#endif //LOP_VND_ALGORITHMS_H