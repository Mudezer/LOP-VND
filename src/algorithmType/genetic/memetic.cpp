//
// Created by Loïc Bermudez on 24/04/2024.
//

#include "memetic.h"


void Memetic::configure(
        int populationSize,
        float mutationRate,
        int maxGeneration,
        Population (*computeInitialPopulation) (Instance& , int),
        Population (*recombination) (Instance&, Population, int),
        Population (*mutation) (Instance&, Population, float),
        Population (*selection) (Instance&, Population, int),
        Candidate (*neighbourOperation) (Candidate&, int, int),
        long long int(*computeDelta) (Matrix&, Candidate&, int, int)

        ){

    this->populationSize = populationSize;
    this->mutationRate = mutationRate;
    this->maxGeneration = maxGeneration;

    this->computeInitialPopulation = computeInitialPopulation;
    this->recombination = recombination;
    this->mutation = mutation;
    this->selection = selection;

    this->localSearch.configure(
            createRandomSolution,
            neighbourOperation,
            computeDelta,
            bestImprovement // maybe change for first improvement
            );



}

Population Memetic::subsidiaryLocalSearch(Instance &instance, Population population) {
    Population newPop;

    for(int i = 0; i<population.size(); i++){
        newPop.push_back(this->localSearch.runIterative(instance, population[i]));
    }

    return newPop;
}

bool Memetic::termination(int actualGeneration){
    return actualGeneration < this->maxGeneration;
}


Candidate Memetic::runMemetic(Instance& instance){

    Population parents = computeInitialPopulation(instance, populationSize); // SP
    parents = subsidiaryLocalSearch(instance, parents);

    int actualGen = 0;
    Population children;
    Population family;
    Population mutated;

    do {
        children = recombination(instance, parents, populationSize); // SPR
        children = subsidiaryLocalSearch(instance, children);

        family = parents;
        family.insert(family.end(), children.begin(), children.end());

        mutated = mutation(instance, family, mutationRate);
        mutated = subsidiaryLocalSearch(instance, mutated);

        family.insert(family.end(), mutated.begin(), mutated.end());
        parents = selection(instance, family, populationSize);
    }while(termination(actualGen++));


    return parents[0];

}



