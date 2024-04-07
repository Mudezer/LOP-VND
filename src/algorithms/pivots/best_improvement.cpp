//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"

/***
 * This function is used to find the best improvement in a given solution
 * @param instance
 * @param s
 * @param computeModification
 * @param computeDelta
 * @return the best solution found
 */
vector<long int> bestImprovement(Instance &instance,
                                 vector<long int> s,
                                 vector<long int> (*computeModification) (vector<long int>&, int, int),
                                 long long int (*computeDelta) (Matrix&, vector<long int>&, int, int)){

    Matrix matrix = instance.getCostMat();
    vector<long int> bestS = s;
    long long int initialCost = instance.computeCost(s);
    long long int bestCost = instance.computeCost(s);
    int k=0,l=0;

    for(int i=0;i<s.size(); i++){
        for(int j=i+1; j<s.size(); j++){
            if((initialCost + computeDelta(matrix, bestS, i, j)) > bestCost){
                l = i, k= j;
                bestCost = initialCost + computeDelta(matrix, bestS, i, j);
            }
        }
    }

    // following condition absolutely necessary if want to avoid transpose to loop forever
    if( computeDelta(matrix, bestS, l, k) > 0){
        bestS = computeModification(bestS, l, k);
    }

//    bestS = computeModification(bestS, l, k);

    return bestS;
}
