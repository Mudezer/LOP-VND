//
// Created by Loïc Bermudez on 23/03/2024.
//

#ifndef LOP_VND_UTILITIES_H
#define LOP_VND_UTILITIES_H

#include <vector>

using namespace std;
typedef vector<vector<long int>> Matrix;

// speed ups for the insert operation
long long int computeDeltaInsert(Matrix &CostMat,
                                 vector<long int> &s,
                                 int i,
                                 int j);

// speed ups for the transpose operation
long long int computeDeltaTranspose(Matrix &CostMat,
                                    vector<long int> &s,
                                    int i,
                                    int j);

// speed ups for the exchange operation
long long int computeDeltaExchange(Matrix &CostMat,
                                   vector<long int> &s,
                                   int i,
                                   int j);

#endif //LOP_VND_UTILITIES_H
