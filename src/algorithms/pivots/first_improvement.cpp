//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"


vector<long int> firstImprovement(Instance &instance, vector<long int> s,
                                 vector<long int> (*computeModification) (vector<long int>, int, int)){
    vector<long int> bestS = s;
    long long int bestCost = instance.computeCost(s);
    for(int i=0; i<s.size(); i++){
        for(int j=i+1; j<s.size(); j++){
            vector<long int> candidateS = computeModification(bestS, i, j);
            if(instance.computeCost(candidateS) > bestCost){
                return candidateS;
            }
        }
    }

    return s;
}