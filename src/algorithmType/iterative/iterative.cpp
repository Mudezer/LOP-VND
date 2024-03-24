//
// Created by Loïc Bermudez on 20/03/2024.
//

#include "iterative.h"


void Iterative::configure(
        vector<long int> (*computeInitialSolution)(Instance&),
        vector<long int> (*neighbourOperation)(vector<long int>, int, int),
        vector<long int> (*pivotImprove)(Instance&,
                                             vector<long int>,
                                             vector<long int> (*) (vector<long int>, int, int))
        ){
    this->computeInitialSolution = computeInitialSolution;
    this->neighbourOperation = neighbourOperation;
    this->pivotImprove = pivotImprove;
}

vector<long int> Iterative::runIterative(Instance &instance, vector<long int> s){
    vector<long int> bestS = s;
    vector<long int> improved;
    bool improvement = true;

    while(improvement){
        improvement = false;
        improved = pivotImprove(instance, bestS, neighbourOperation);
        if(!(bestS == improved)){
            bestS = improved;
            improvement = true;
        }
    }

    cout << "Best solution: " << endl;
    for (int i = 0; i < bestS.size(); i++) {
        cout << bestS[i] << " ";
    }
    cout << endl;

    cout << "Best solution cost: " << instance.computeCost(bestS) << endl;

    return bestS;

}

vector<long int> Iterative::runIterative(Instance &instance){
    vector<long int> s = computeInitialSolution(instance);
    cout << "Initial solution: " << endl;
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << " ";
    }
    cout << endl;

    cout << "Initial solution cost: " << instance.computeCost(s) << endl;
    return runIterative(instance, s);
}