//
// Created by Loïc Bermudez on 23/04/2024.
//


#include "../../algorithms.h"

/**
 * Create a random population for the memetic algorithm
 * @param instance
 * @param populationSize
 * @return a population of random solutions
 */
Population randomPopulationInitialisation(Instance& instance, int populationSize){

    Population population = vector<Candidate> (populationSize);

    for(int i = 0; i< populationSize; i++){
        population[i] = createRandomSolution(instance);
    }

    return population;
}