//
// Created by Loïc Bermudez on 23/03/2024.
//

#include "vnd.h"

void VariableNeighbourDescent::configure(
        vector<long int> (*computeInitialSolution)(Instance&),
        vector<long int> (*pivotImprove)(Instance&,
                                         vector<long int>,
                                         vector<long int> (*) (vector<long int>&, int, int),
                                         long long int (*) (Matrix&, vector<long int>&, int, int)),
        vector<vector<long int> (*) (vector<long int>&, int, int)> neighbourOperations,
        vector<long long int (*) (Matrix&, vector<long int>&, int, int)> computeDeltas
        ){
    this->computeInitialSolution = computeInitialSolution;
    this->pivotImprove = pivotImprove;
    this->neighbourOperations = neighbourOperations;
    this->computeDeltas = computeDeltas;
}

vector<long int> VariableNeighbourDescent::runVND(Instance &instance){
    vector<long int> s = computeInitialSolution(instance);
    cout << "Initial solution: " << endl;
    for (long i : s)
        cout << i << " ";

    cout << endl;

    cout << "Initial solution cost: " << instance.computeCost(s) << endl;

    vector<long int> bestS = s;
    int k = neighbourOperations.size(); // number of neighbourhoods
    int i = 0; // current neighbourhood


    while(i < k){
        vector<long int> candidateS = pivotImprove(instance, bestS, neighbourOperations[i], computeDeltas[i]);
        if(bestS == candidateS) {
            i++;
        }else{
            bestS = candidateS;
            i = 0;
        }
    }

    cout << "Best solution: " << endl;
    for (long i : bestS)
        cout << i << " ";
    cout << endl;

    cout << "Best solution cost: " << instance.computeCost(bestS) << endl;

    return bestS;

}




