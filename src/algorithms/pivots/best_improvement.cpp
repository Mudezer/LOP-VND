//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"

vector<long int> bestImprovement(Instance &instance,
                                 vector<long int> s,
                                 vector<long int> (*computeModification) (vector<long int>, int, int),
                                 long long int (*computeDelta) (Matrix, vector<long int>, int, int)){

    Matrix matrix = instance.getCostMat();
    vector<long int> bestS = s;
    long long int initialCost = instance.computeCost(s);
    long long int bestCost = instance.computeCost(s);
    long long int actualCost;
    int k=0,l=0;

    cout << "improvement in " << endl;
    cout << "S.size: " << s.size() << endl;

    for(int i=0;i<s.size(); i++){
        for(int j=i+1; j<s.size(); j++){
//            vector<long int> candidateS = computeModification(bestS, i,j);
            if((actualCost = initialCost+computeDelta(matrix, bestS, i, j))>bestCost){
                l = i, k= j;
                bestCost = actualCost;
            }
        }
    }

    cout << "improvement out " << endl;
    cout << "l: " << l << " k: " << k << endl;
    bestS = computeModification(bestS, l, k);


    return bestS;
}
