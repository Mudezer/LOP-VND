//
// Created by Loïc Bermudez on 21/03/2024.
//


#include "../algorithms.h"

vector<long int> computeInitialSolution(Instance &instance, int initializationType){



    switch(initializationType){
        case RANDOM:
            cout << "Random Permutation Initialization\n" << endl;
            return createRandomSolution(instance);
        case CW:
            cout << "Chenery x Watanabe Initialization\n" << endl;
            return createCWHeuristicSolution(instance);
        default:
            return createRandomSolution(instance);
    }
}