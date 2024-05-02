//
// Created by Loïc Bermudez on 21/04/2024.
//

#ifndef LOP_VND_ITERATIVE_LOCAL_SEARCH_H
#define LOP_VND_ITERATIVE_LOCAL_SEARCH_H

#include "../../skeleton/instance/instance.h"
#include "../../algorithms/algorithms.h"
#include "../vnd/vnd.h"
#include <chrono>
//#include <random>

typedef vector<vector<long int>> Matrix;
typedef vector<long int> Candidate;


typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> Time;


class IterativeLocalSearch{
private:
    double maxTime;
    int perturbNbr;

    VariableNeighbourDescent localSearch;
    Candidate (*computeInitialSolution) (Instance&);
    Candidate (*perturbation) (Candidate&, int, int);
    vector<Candidate (*) (Candidate&, int, int)> neighbourOperations;
    vector<long long int (*) (Matrix&, Candidate&, int, int)> computeDeltas;

    Candidate subsidiaryLocalSearch(Instance& instance, Candidate candidate);
    Candidate randomPerturbation(Candidate candidate, int nbrOfMoves);
    Candidate acceptanceCriterion(Instance&, Candidate, Candidate);
    bool termination(Time start, Time actual);

public:
    void configure(
            double maxTime,
            int perturbNbr,
            Candidate (*computeInitialSolution) (Instance&),
            Candidate (*perturbation) (Candidate&, int, int),
            vector<Candidate (*) (Candidate&, int, int)> neighbourOperations,
            vector<long long int (*) (Matrix&, Candidate&, int, int)> computeDeltas
    );
    Candidate runILS(Instance& instance);
};

#endif //LOP_VND_ITERATIVE_LOCAL_SEARCH_H
