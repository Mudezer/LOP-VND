//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"

/*vector<long int> runNeighboorModifications(Instance &instance,
                                           Configuration &configuration,
                                           vector<long int> s);

vector<long int> bestTranspose(Instance &instance, vector<long int> s);
vector<long int> bestExchange(Instance &instance, vector<long int> s);
vector<long int> bestInsert(Instance &instance, vector<long int> s);*/

vector<long int> bestImprovement(Instance &instance, vector<long int> s,
                                 vector<long int> (*computeModification) (vector<long int>, int, int)){

    vector<long int> bestS = s;
    long long int bestCost = instance.computeCost(s);
    long long int actualCost;

    for(int i=0;i<s.size(); i++){
        for(int j=i+1; j<s.size(); j++){
            vector<long int> candidateS = computeModification(bestS, i,j);
            if((actualCost = instance.computeCost(candidateS))>bestCost){
                bestS = candidateS;
                bestCost = actualCost;
            }
        }
    }

    return bestS;
}




/*vector<long int> bestImprovement(Instance &instance, Configuration &configuration){

//    cout << "I made it MF\n" << endl;

    vector<long int> s;
    vector<long int> bestS;

    s = computeInitialSolution(instance, configuration.getInitializationType());


    cout << "Initial solution: " << endl;
    for(int i=0; i<instance.getPSize(); i++){
        cout << s[i] << " ";
    }
    cout << endl;


    long long int cost = instance.computeCost(s);
    cout << "Initial cost: " << cost << endl;



    bestS = runNeighboorModifications(instance, configuration, s);


    cout << "Best solution: \n" << endl;
    for(int i=0; i<instance.getPSize(); i++){
        cout << bestS[i] << " ";
    }
    cout << endl;


    long long int bestCost = instance.computeCost(bestS);
    cout << "Best cost: " << bestCost << endl;



    return bestS;
}

vector<long int> runNeighboorModifications(Instance &instance,
                                           Configuration &config,
                                           vector<long int> initS){

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

}*/



/*vector<long int> bestTranspose(Instance &instance, vector<long int> s){
    vector<long int> bestS = s;
    vector<long int> bestCandidate = s;
    long long int bestCost = instance.computeCost(s);
    long long int actualCost;
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size()-1;i++){
                vector<long int> candidateS = transpose(bestS, i, i+1);
                if((actualCost = instance.computeCost(candidateS)) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = actualCost;
                    improvement = true;
                }

        }
        bestS = bestCandidate;
    }

    return bestS;
}

vector<long int> bestInsert(Instance &instance, vector<long int> s) {
    vector<long int> bestS = s;
    vector<long int> bestCandidate = s;
    long long int bestCost = instance.computeCost(s);
    long long int actualCost;
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size();i++){
            for(int j = i+1; j<s.size(); j++){
                vector<long int> candidateS = insert(bestS, i, j);
                if((actualCost = instance.computeCost(candidateS)) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = actualCost;
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
    long long int bestCost = instance.computeCost(s);
    long long int actualCost;
    bool improvement = true;

    while(improvement){
        improvement = false;
        for(int i = 0; i<s.size(); i++){
            for(int j = i+1; j<s.size(); j++){
                vector<long int> candidateS = exchange(bestS, i, j);
                if((actualCost = instance.computeCost(candidateS)) > bestCost){
                    bestCandidate = candidateS;
                    bestCost = actualCost;
                    improvement = true;
                }
            }
        }
        bestS = bestCandidate;
    }

    return bestS;

}*/

