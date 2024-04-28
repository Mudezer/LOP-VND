//
// Created by Loïc Bermudez on 24/04/2024.
//

#ifndef LOP_VND_MEMETIC_H
#define LOP_VND_MEMETIC_H

#include "../../skeleton/skeleton.h"


class Memetic{
private:
    Population (*computeInitialPopulation) (Instance&);
    Population (*recombination) (Instance&, Population, int);
    Population (*mutation) (Instance&, Population, float);
    Population (*selection) (Instance&, Population, int);
    Iterative localSearch;
    bool termination(int actualGeneration);

    int populationSize;
    float mutationRate;
    int maxGeneration;

    Population subsidiaryLocalSearch(Instance& instance, Population population);


public:
//    Memetic();
//    ~Memetic();

    void configure(
            int populationSize,
            float mutationRate,
            int maxGeneration,
            Population (*computeInitialPopulation) (Instance&),
            Population (*recombination) (Instance&, Population, int),
            Population (*mutation) (Instance&, Population, float),
            Population (*selection) (Instance&, Population, int),
            Candidate (*neighbourOperation) (Candidate&, int, int),
            long long int(*computeDelta) (Matrix&, Candidate&, int, int)
    );

    Candidate run(Instance& instance);
};

#endif //LOP_VND_MEMETIC_H
