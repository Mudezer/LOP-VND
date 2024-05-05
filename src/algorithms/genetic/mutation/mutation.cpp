//
// Created by Loïc Bermudez on 24/04/2024.
//

#include "../../algorithms.h"

/**
 * Apply a random mutation to a candidate
 * @param instance
 * @param candidate
 * @return the mutated candidate
 */

Candidate randomExchange(Instance& instance, Candidate candidate){
    int i = rand() % candidate.size();
    int j = rand() % candidate.size();

    while(i == j)
        j = rand() % candidate.size();

    if(i > j)
        swap(i, j);

    exchange(candidate, i, j); // TODO: study the different operators

    return candidate;
}

/**
 * Apply a random mutation to the population
 * @param instance
 * @param population
 * @param mutationRate
 * @return the mutated population
 */
Population randomMutation(Instance& instance, Population population, float mutationRate){
    Population mutated = vector<Candidate> (population.size());

    for(int i =0; i<population.size(); i++){
        float mutation = (float) (rand() % 100) / (float) 100;
        if (mutation <= mutationRate){
            mutated[i] = randomExchange(instance, population[i]);
        }else{
            mutated[i]=population[i];
        }
    }


    return mutated;
}