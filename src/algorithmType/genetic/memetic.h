//
// Created by Loïc Bermudez on 24/04/2024.
//

#ifndef LOP_VND_MEMETIC_H
#define LOP_VND_MEMETIC_H

#include "../iterative/iterative.h"
#include "../../skeleton/instance/instance.h"
#include "../../algorithms/algorithms.h"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> Time;
typedef vector<vector<long int>> Population;
typedef vector<long int> Candidate;


class Memetic{
private:
    Population (*computeInitialPopulation) (Instance&,int);
    Population (*recombination) (Instance&, Population, int);
    Population (*mutation) (Instance&, Population, float);
    Population (*selection) (Instance&, Population, int);
    Iterative localSearch;
    bool termination(Time start, Time actual);

    int populationSize;
    float mutationRate;
    double maxTime;

    Population subsidiaryLocalSearch(Instance& instance,
                                     Population population);


public:
//    Memetic();
//    ~Memetic();

    void configure(
            int populationSize,
            float mutationRate,
            double maxTime,
            Population (*computeInitialPopulation) (Instance&,int),
            Population (*recombination) (Instance&, Population, int),
            Population (*mutation) (Instance&, Population, float),
            Population (*selection) (Instance&, Population, int),
            Candidate (*neighbourOperation) (Candidate&, int, int),
            long long int(*computeDelta) (Matrix&, Candidate&, int, int)
    );

    Candidate runMemetic(Instance& instance);
};

#endif //LOP_VND_MEMETIC_H
