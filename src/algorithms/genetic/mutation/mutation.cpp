//
// Created by Loïc Bermudez on 24/04/2024.
//

#include "../../algorithms.h"


Candidate randomExchange(Instance& instance, Candidate candidate){
    int i = rand() % candidate.size()+1;
    int j = rand() % candidate.size()+1;

    if(i > j)
        swap(i, j);

    exchange(candidate, i, j); // TODO: study the different operators

    return candidate;
}

Population randomMutation(Instance& instance, Population population, float mutationRate){
    Population mutated;

    for(int i =0; i<population.size(); i++){
        float mutation = (float) (rand() % 100) / (float) 100;
        if (mutation <= mutationRate){
            mutated.push_back(randomExchange(instance, population[i]));
        }else{
            mutated.push_back(population[i]);
        }
    }

    return mutated;
}