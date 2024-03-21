//
// Created by Loïc Bermudez on 19/03/2024.
//

#include "solution.h"

Solution::Solution(string Name, long int instanceSize, long long int cost){
    this->instanceName = Name;
    this->instanceSize = instanceSize;
    this->cost = cost;
}

Solution::~Solution(){}

long int Solution::getInstanceSize(){
    return this->instanceSize;
}

long long int Solution::getCost(){
    return this->cost;
}

string Solution::getInstanceName(){
    return this->instanceName;
}

vector< long int > Solution::getBestSolution(){
    return this->bestSolution;
}


