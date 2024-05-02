//
// Created by Loïc Bermudez on 23/04/2024.
//

#include "../../algorithms.h"


Population recombination(Instance& instance, Population population, int populationSize){
    Population newPop;
    while(newPop.size() < populationSize){

        Population newChilds = twoPointCrossover(
                        instance,
                        population[rand() % (populationSize/4)],
                        population[rand() % (populationSize)]
        );
        newPop.insert(newPop.end(),(newChilds[0]));
        newPop.insert(newPop.end(),(newChilds[1]));

    }
    return newPop;
}

