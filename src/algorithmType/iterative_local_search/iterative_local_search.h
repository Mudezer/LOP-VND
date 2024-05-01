//
// Created by Loïc Bermudez on 21/04/2024.
//

#ifndef LOP_VND_ITERATIVE_LOCAL_SEARCH_H
#define LOP_VND_ITERATIVE_LOCAL_SEARCH_H

#include "../../skeleton/instance/instance.h"
//#include "../../algorithms/algorithms.h"
#include <unordered_set>
#include <chrono>
#include <random>

typedef vector<vector<long int>> Matrix;
typedef vector<long int> Candidate;


typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> Time;

// Hash function
struct hashFunction
{
    size_t operator()(const vector<long int>
                      &myVector) const
    {
        std::hash<int> hasher;
        size_t answer = 0;

        for (int i : myVector)
        {
            answer ^= hasher(i) + 0x9e3779b9 +
                      (answer << 6) + (answer >> 2);
        }
        return answer;
    }
};

typedef unordered_set<Candidate,hashFunction> History;



class IterativeLocalSearch{
private:
    double maxTime;
    int perturbNbr;
    History history;

    Candidate (*computeInitialSolution) (Instance&);
    Candidate (*perturbation) (Candidate&, int, int);
    Candidate (*computeModification) (Candidate&, int, int);
    long long int (*computeDelta) (Matrix&, Candidate&, int, int);

    Candidate subsidiaryLocalSearch(Instance& instance, Candidate candidate);
    Candidate randomPerturbation(Candidate& candidate, int nbrOfMoves);
    void updateHistory(Candidate candidate);
    bool termination(Time start, Time actual);
    bool isInHistory(Candidate candidate);

public:
    void configure(
            double maxTime,
            int perturbNbr,
            Candidate (*computeInitialSolution) (Instance&),
            Candidate (*perturbation) (Candidate&, int, int),
            Candidate (*neighbourOperation) (Candidate&, int, int),
            long long int (*computeDelta) (Matrix&, Candidate&, int, int)
    );

    Candidate runILS(Instance& instance);
};

#endif //LOP_VND_ITERATIVE_LOCAL_SEARCH_H
