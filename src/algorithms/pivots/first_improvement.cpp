//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"

/***
 * This function is used to find the first improvement in a given solution
 * @param instance
 * @param s
 * @param computeModification
 * @param computeDelta
 * @return the first solution found
 */
vector<long int> firstImprovement(Instance &instance, vector<long int> s,
                                 vector<long int> (*computeModification) (vector<long int>&, int, int),
                                 long long int (*computeDelta) (Matrix&, vector<long int>&, int, int)){


    Matrix matrix = instance.getCostMat();
    vector<long int> bestS = s;
    long long int bestCost = instance.computeCost(s);



    for(int i=0; i<s.size(); i++){
        for(int j=i+1; j<s.size(); j++){
            if((bestCost + computeDelta(matrix, bestS, i, j )) > bestCost){
                return computeModification(bestS, i, j);
            }
        }
    }

    return s;
}