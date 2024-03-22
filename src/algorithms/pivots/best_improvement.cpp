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

    /* print the best solution */
    cout << "Best solution: \n" << endl;
    for(int i=0; i<instance.getPSize(); i++){
        cout << bestS[i] << " ";
    }
    cout << endl;

    /* compute the best cost */
    long long int bestCost = instance.computeCost(bestS);
    cout << "Best cost: " << bestCost << endl;



    return s;
}

vector<long int> runNeighboorModifications(Instance &instance, Configuration &config, vector<long int> initS){

    switch(config.getNeighborhoodModification()){
        case TRANSPOSE:
            cout << "Transpose Modification Based\n" << endl;
            return bestTranspose(instance, initS);
        case EXCHANGE:
            cout << "Exchange Modification Based\n" << endl;
            return bestExchange(instance, initS);
        case INSERT:
            cout << "Insert Modification Based\n" << endl;
            return bestInsert(instance, initS);
        default:
            cout << "Default: Transpose Modification Based\n" << endl;
            return bestTranspose(instance, initS);
    }

}

vector<long int> bestTranspose(Instance &instance, vector<long int> s){
    // final list we will return
    vector<long int> bestS = s;
    // best candidate list which will update the bestSolution list
    vector<long int> bestCandidate = s;
    // candidate list which will be used to test the cost
    vector<long int> candidateS(instance.getPSize());
    

    long long int bestCost = instance.computeCost(s);
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size();i++){
            for(int j = i; j<s.size();j++ ){
                candidateS = transpose(bestS, j,i);
                if(instance.computeCost(candidateS) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = instance.computeCost(candidateS);
                    improvement = true;
                }
            }
        }
        bestS = bestCandidate;
    }


//    for(int i = 0; i<instance.getPSize(); i++){
//        candidateS = transpose(bestS, i, i+1);
//        actualCost = instance.computeCost(candidateS);
//
//        if(actualCost > bestCost){
//            bestS = candidateS;
//            bestCost = actualCost;
//        }
//    }


    return bestS;
}

vector<long int> bestInsert(Instance &instance, vector<long int> s) {
    vector<long int> bestS = s;
    vector<long int> bestCandidate = s;
    vector<long int> candidateS(instance.getPSize());
    long long int bestCost = instance.computeCost(s);
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size();i++){
            for(int j = i+1; j<s.size(); j++){
                candidateS = insert(bestCandidate, i, j);
                if(instance.computeCost(candidateS) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = instance.computeCost(candidateS);
                    improvement = true;
                }

            }
        }
        bestS = bestCandidate;
    }

    return bestS;

}

vector<long int> bestExchange(Instance &instance, vector<long int> s) {
    vector<long int> bestS = s;
    vector<long int> bestCandidate = s;
    vector<long int> candidateS(instance.getPSize());
    long long int bestCost = instance.computeCost(s);
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size(); i++){
            for(int j = i+1; j<s.size(); j++){
                candidateS = exchange(bestCandidate, i, j);
                if(instance.computeCost(candidateS) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = instance.computeCost(candidateS);
                    improvement = true;
                }
            }
        }
        bestS = bestCandidate;
    }

    return bestS;

}

