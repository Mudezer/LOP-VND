//
// Created by Loïc Bermudez on 24/04/2024.
//

#include "memetic.h"

/**
 * Constructor: Configure the different parameters of the memetic algorithm
 *
 * @param populationSize
 * @param mutationRate
 * @param maxTime
 * @param computeInitialPopulation
 * @param recombination
 * @param mutation
 * @param selection
 * @param neighbourOperation
 * @param computeDelta
 */
void Memetic::configure(
        int populationSize,
        float mutationRate,
        double maxTime,
        Population (*computeInitialPopulation) (Instance& , int),
        Population (*recombination) (Instance&, Population, int),
        Population (*mutation) (Instance&, Population, float),
        Population (*selection) (Instance&, Population, int),
        Candidate (*neighbourOperation) (Candidate&, int, int),
        long long int(*computeDelta) (Matrix&, Candidate&, int, int)

        ){

    cout << "Configuring Memetic Algorithm\n" << endl;
    this->populationSize = populationSize;
    this->mutationRate = mutationRate;
    this->maxTime = maxTime;
    this->computeInitialPopulation = computeInitialPopulation;
    this->recombination = recombination;
    this->mutation = mutation;
    this->selection = selection;

    this->localSearch.configure(
            createRandomSolution,
            neighbourOperation,
            computeDelta,
            firstImprovement // maybe change for first improvement
            );
}

/**
 * Apply the local search to all the individuals in the population
 *
 * @param instance
 * @param population
 * @return the optimized population
 */
Population Memetic::subsidiaryLocalSearch(Instance &instance, Population population) {
    Population newPop = vector<Candidate> (population.size());

    for(int i = 0; i<population.size(); i++){
        newPop[i] = (localSearch.runIterative(instance, population[i]));
    }

    return newPop;
}

/**
 * Check if the termination condition is met
 *
 * @param starting time
 * @param actual time
 * @return true if the termination condition is met, false otherwise
 */
bool Memetic::termination(Time start, Time actual){
    auto duration = chrono::duration_cast<chrono::microseconds>(actual - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}

/**
 * Run the memetic algorithm
 *
 * @param instance
 * @return the best candidate found
 */
Candidate Memetic::runMemetic(Instance& instance){



    Population parents = computeInitialPopulation(instance, populationSize); // SP
    parents = subsidiaryLocalSearch(instance, parents);

    Population children;
    Population family;
    Population mutated;
    int iteration = 0;

    Time start = Clock::now();
    do {
        children = recombination(instance, parents, populationSize); // SPR
        children = subsidiaryLocalSearch(instance, children);

        family = parents;
        family.insert(family.end(), children.begin(), children.end());

        mutated = mutation(instance, family, mutationRate);
        mutated = subsidiaryLocalSearch(instance, mutated);

        family.insert(family.end(), mutated.begin(), mutated.end());
        parents = selection(instance, family, populationSize);
        iteration++;
    }while(!termination(start, Clock::now()));

    cout << "Iteration: " << iteration << endl;
    return parents[0];

}



