//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"


vector<long int> createCWHeuristicSolution(Instance &instance){

    vector<long int> s(instance.getPSize());
    vector<bool> usedRow(instance.getPSize(), false);
    long int actualRow, bestRow;
    long long int attractiveness, maxAttractiveness=0;
    int step;

    for(step = 0; step <= instance.getPSize(); step++){
        maxAttractiveness = -1;
        for(actualRow = 0; actualRow < instance.getPSize(); actualRow++){
            if(!usedRow[actualRow]){
                attractiveness = instance.computeAttractiveness(step, actualRow);
                if(attractiveness > maxAttractiveness){
                    maxAttractiveness = attractiveness;
                    bestRow = actualRow;
                }
            }
        }
        s[step] = bestRow;
        usedRow[bestRow] = true;
    }

    cout<< "CW Heuristic solution: ";
    for(int i=0; i<instance.getPSize();i++){
        cout<< s[i] << " ";
    }
    cout<<endl;

    return s;

}


