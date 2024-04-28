//
// Created by Loïc Bermudez on 23/04/2024.
//


#include "../../algorithms.h"

Population randomPopulationInitialisation(Instance& instance, int populationSize){

    Population population = vector<Candidate> (populationSize);

    for(int i = 0; i< populationSize; i++){
        population[i] = createRandomSolution(instance);
    }

    return population;
}