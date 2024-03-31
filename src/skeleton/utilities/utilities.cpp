//
// Created by Loïc Bermudez on 23/03/2024.
//

#include "utilities.h"



long long int computeDeltaInsert(Matrix CostMat, vector<long int> s, int i, int j){
    long long int delta = 0;
    long int k;
    if(i<j){
        for(k = i+1; k<=j; k++){
            delta += CostMat[s[k]][s[i]] - CostMat[s[i]][s[k]];
        }
    }else if(i>j){
        for(k=j;k<i;k++){
            delta += CostMat[s[i]][s[k]] - CostMat[s[k]][s[i]];
        }
    }

    return delta;
}

long long int computeDeltaTranspose(Matrix CostMat, vector<long int> s, int i, int j) {
    long long int delta = 0;

    // i is always smaller than j as we transpose i and i+1
    // no use to do it in the reverse order as candidate is the same
    delta = CostMat[s[i+1]][s[i]] - CostMat[s[i]][s[i+1]];

    return delta;

}

long long int computeDeltaExchange(Matrix CostMat, vector<long int> s, int i, int j){

    long long int delta = 0;

    for(int k = i; k<j; k++){
        delta += CostMat[s[j]][s[k]] - CostMat[s[k]][s[j]];
    }
    for(int l = i+1; l<j; l++){
        delta += CostMat[s[l]][s[i]] - CostMat[s[i]][s[l]];
    }

    return delta;
}