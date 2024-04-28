//
// Created by Loïc Bermudez on 23/04/2024.
//

#include "../../algorithms.h"


Population recombination(Instance& instance, Population population, int populationSize){
    Population newPop;
    // TODO: change this to random selection of parents to recombinate
    for(int i =0; i<populationSize; i++){
        Population newChilds = twoPointCrossover(
                        instance,
                        population[rand() % (populationSize/4)],
                        population[rand() % (populationSize)]
        );

        newPop.push_back(newChilds[0]);
        newPop.push_back(newChilds[1]);

    }

    return newPop;
}

