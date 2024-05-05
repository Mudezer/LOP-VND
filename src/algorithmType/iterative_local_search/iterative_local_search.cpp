//
// Created by Loïc Bermudez on 21/04/2024.
//

#include "iterative_local_search.h"

/**
 * Constructor: Configure the different parameters of the iterated local search algorithm
 * @param maxTime
 * @param perturbNbr
 * @param computeInitialSolution
 * @param perturbation
 * @param neighbourOperations
 * @param computeDeltas
 */
void IterativeLocalSearch::configure(
        double maxTime,
        int perturbNbr,
        Candidate (*computeInitialSolution)(Instance &),
        Candidate (*perturbation)(Candidate &, int, int),
        vector<Candidate (*) (Candidate&, int, int)> neighbourOperations,
        vector<long long int (*) (Matrix&, Candidate&, int, int)> computeDeltas
        ) {
    this->maxTime = maxTime;
    this->perturbNbr = perturbNbr;
    this->computeInitialSolution = computeInitialSolution;
    this->perturbation = perturbation;
    this->neighbourOperations = neighbourOperations;
    this->computeDeltas = computeDeltas;

    localSearch.configure(createRandomSolution,
                          firstImprovement,
                          neighbourOperations,
                          computeDeltas
                          );

}

/**
 * Apply a random perturbation to a candidate
 * @param candidate
 * @param nbrOfMoves
 * @return the perturbed candidate
 */
Candidate IterativeLocalSearch::randomPerturbation(Candidate candidate, int nbrOfMoves) {
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

/**
 * Check if the termination condition is met
 * @param starting time
 * @param actual time
 * @return true if the termination condition is met, false otherwise
 */
bool IterativeLocalSearch::termination(Time start, Time actual){
    auto duration = chrono::duration_cast<chrono::microseconds>(actual - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}

/**
 * Apply the acceptance criterion to two candidates
 * @param instance
 * @param candidate1
 * @param candidate2
 * @return the best candidate
 */
Candidate IterativeLocalSearch::acceptanceCriterion(Instance& instance, Candidate candidate1, Candidate candidate2 ){
    long long int cost1 = instance.computeCost(candidate1);
    long long int cost2 = instance.computeCost(candidate2);

    if (cost2 > cost1)
        return candidate2;
    else
        return candidate1;
}

/**
 * Apply the local search to all the individuals in the population
 *
 * @param instance
 * @param population
 * @return the optimized population
 */
Candidate IterativeLocalSearch::subsidiaryLocalSearch(Instance& instance, Candidate candidate){
    return localSearch.runVND(instance, candidate);
}


/**
 * Run the iterated local search algorithm
 *
 * @param instance
 * @return the best candidate found
 */
Candidate IterativeLocalSearch::runILS(Instance& instance){
    Time start = Clock::now();
    Candidate solution = computeInitialSolution(instance);
    Candidate bestSolution = subsidiaryLocalSearch(instance, solution);
    long long int bestCost = instance.computeCost(bestSolution);
    cout << "Initial solution: " << endl;
    for (long i : bestSolution)
        cout << i << " ";
    cout << endl;
    cout << "Initial solution cost: " << bestCost << endl;

    int iteration = 0;
    Candidate newSolution = vector<long int>(instance.getPSize());

    do{
        newSolution = randomPerturbation(bestSolution, perturbNbr);
        newSolution = subsidiaryLocalSearch(instance, newSolution);


        bestSolution = acceptanceCriterion(instance, bestSolution, newSolution);

    }while(!termination(start, Clock::now()));

    cout << "Number of iterations: " << iteration << endl<< endl;

    cout << "Best solution: " << endl;
    for (long i : bestSolution)
        cout << i << " ";
    cout << endl;
    cout << "Best solution cost: " << instance.computeCost(bestSolution) << endl;


    return bestSolution;
}

