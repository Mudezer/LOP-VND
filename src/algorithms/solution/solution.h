//
// Created by Loïc Bermudez on 19/03/2024.
//

#ifndef LOP_VND_SOLUTION_H
#define LOP_VND_SOLUTION_H

#include "../algorithms.h"
#include <vector>
#include <string>

using namespace std;

class Solution{
private:
    string instanceName;
    long int instanceSize;
    long long int cost;
    vector< long int > bestSolution;

public:
    Solution(string Name, long int instanceSize, long long int cost);
    ~Solution();

    string getInstanceName();
    long int getInstanceSize();
    long long int getCost();
    vector< long int > getBestSolution();



};

#endif //LOP_VND_SOLUTION_H
