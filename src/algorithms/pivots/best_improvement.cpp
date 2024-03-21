//
// Created by Loïc Bermudez on 18/03/2024.
//




#include "../algorithms.h"

vector<long int> runNeighboorModifications(Instance &instance, Configuration &configuration, vector<long int> s);
vector<long int> bestTranspose(Instance &instance, vector<long int> s);
vector<long int> bestExchange(Instance &instance, vector<long int> s);
vector<long int> bestInsert(Instance &instance, vector<long int> s);


vector<long int> bestImprovement(Instance &instance, Configuration &configuration){

//    cout << "I made it MF\n" << endl;

    vector<long int> s;
    vector<long int> bestS;

    s = computeInitialSolution(instance, configuration.getInitializationType());

    /* print the initial solution */
    cout << "Initial solution: " << endl;
    for(int i=0; i<instance.getPSize(); i++){
        cout << s[i] << " ";
    }
    cout << endl;

    /* compute intial cost */
    long long int cost = instance.computeCost(s);
    cout << "Initial cost: " << cost << endl;

    /* search the best improvement */

    bestS = runNeighboorModifications(instance, configuration, s);

    switch(configuration.getNeighborhoodModification()){
        case TRANSPOSE:
            cout << "Transpose Modification Based\n" << endl;
            bestS = bestTranspose(instance, s);
            break;
        case EXCHANGE:
            cout << "Exchange Modification Based\n" << endl;
            bestS = bestExchange(instance, s);
            break;
        case INSERT:
            cout << "Insert Modification Based\n" << endl;
            bestS = bestInsert(instance, s);
            break;
        default:
            cout << "Transpose Modification Based\n" << endl;
            bestS = bestTranspose(instance, s);
            break;
    }

    return s;
}

vector<long int> runNeighboorModificationst(Instance &instance, Configuration &config, vector<long int> initS){


    return initS;
}

