//
// Created by Loïc Bermudez on 21/04/2024.
//

#include "iterative_local_search.h"


void IterativeLocalSearch::configure(
        double maxTime,
        int perturbNbr,
        Candidate (*computeInitialSolution)(Instance &),
        Candidate (*perturbation)(Candidate &, int, int),
        Candidate (*neighbourOperation)(Candidate &, int, int),
        long long int (*computeDelta)(Matrix &, Candidate &, int, int)
        ) {
    this->maxTime = maxTime;
    this->perturbNbr = perturbNbr;
    this->computeInitialSolution = computeInitialSolution;
    this->perturbation = perturbation;
    this->computeModification = neighbourOperation;
    this->computeDelta = computeDelta;
}


void IterativeLocalSearch::updateHistory(Candidate candidate) {
    if(history.find(candidate) == history.end()){
        history.insert(candidate);
    }

}

bool IterativeLocalSearch::isInHistory(Candidate candidate) {
    if(history.find(candidate) == history.end()) {
        return false; // not in history
    }else{
        return true; // in history
    }
}


Candidate IterativeLocalSearch::randomPerturbation(Candidate &candidate, int nbrOfMoves) {
    Candidate backUp = candidate;
    Candidate newCandidate;

    for(int k = 1; k <= nbrOfMoves; k++) {
        int i = rand() % candidate.size();
        int j = rand() % candidate.size();
        while (i == j) {
            j = rand() % candidate.size();
        }

        newCandidate = perturbation(candidate, i, j);
    }

    return newCandidate;
}

bool IterativeLocalSearch::termination(Time start, Time actual){
    auto duration = chrono::duration_cast<chrono::microseconds>(actual - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}


Candidate IterativeLocalSearch::subsidiaryLocalSearch(Instance& instance, Candidate candidate){
    Matrix matrix = instance.getCostMat();
    Candidate backUp = candidate;
    long long int bestCost = instance.computeCost(candidate);
    long long int maxTemp=0;
    int r=0;

    for(int i = 0; i<candidate.size();i++){
        /* r = arg max j.j≠i f(neighbour(candidate,i,j)*/
        for(int j = i+1; j<candidate.size();j++){
            long long int temp = computeDelta(matrix, candidate, i, j);
            if(temp > maxTemp){
                maxTemp = temp;
                r = j;
            }
        }
        if((bestCost + computeDelta(matrix, candidate, i, r)) > bestCost){
            return computeModification(candidate, i, r);
        }
    }

    return backUp;
}



Candidate IterativeLocalSearch::runILS(Instance& instance){
    Time start = Clock::now();
    Candidate solution = computeInitialSolution(instance);

    cout << "Initial solution: " << endl;
    for (int i = 0; i < solution.size(); i++) {
        cout << solution[i] << " ";
    }
    cout << endl;

    cout <<"Initial solution cost: " << instance.computeCost(solution) << endl;

    Candidate bestSolution = subsidiaryLocalSearch(instance, solution);

    updateHistory(bestSolution);
    long long int bestCost = instance.computeCost(bestSolution);
    cout << "Initial best cost: " << bestCost << endl;
    long long int newCost;
    do{
        solution = randomPerturbation(bestSolution, perturbNbr);
        solution = subsidiaryLocalSearch(instance, bestSolution);
        updateHistory(solution);
//        cout << "new cost: " << instance.computeCost(solution) << endl;
        if(((newCost = instance.computeCost(solution)) > bestCost) && !isInHistory(solution)){
            bestCost = newCost;
            bestSolution = solution;
            updateHistory(bestSolution);
            cout << "new best cost: " << bestCost << endl;
        }

    }while(!termination(start, Clock::now()));


    return bestSolution;
}

