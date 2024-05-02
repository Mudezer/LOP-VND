//
// Created by Loïc Bermudez on 18/03/2024.
//

#ifndef LOP_VND_CONFIGURATION_H
#define LOP_VND_CONFIGURATION_H

//#include "../algorithms.h"
#include "../../algorithmType/algorithm_type.h"
#include "../../algorithms/algorithms.h"
#include "../utilities/utilities.h"
#include <iostream>
#include <string>
#include <getopt.h>

typedef vector<long int> Candidate;
typedef vector<Candidate> Population;
typedef vector<vector<long int>> Matrix;
using namespace std;

/* algorithmType */
#define ITERATIVE 1
#define VND 2
#define ILS 3
#define MEMETIC 4

/* Initialisation Type */
#define RANDOM 1
#define CW 2

/* Pivot Algorithms */
#define FIRST 1
#define BEST 2

/* Neighborhood Modification */
#define NONE 0
#define TRANSPOSE 1
#define EXCHANGE 2
#define INSERT 3

/* VND Neighborhood*/
#define NONE 0
#define TRANS_EXCH_INS 1
#define TRANS_INS_EXCH 2



/* ILS */


/* Memetic Algorithm */


class Configuration{
private:
    string FileName;
    string algoClass;
    string configuration;

    int algorithmType;
    int pivotAlgorithm;
    int neighborhoodModification;
    int initializationType;

    //ILS
    double maxTime;
    int perturbNbr;

    //Memetic

    int populationSize;
    float mutationRate;
    int maxGeneration;


public:
    Configuration();
    ~Configuration();

    //Initialisation Method pointer
    vector<long int> (*computeInit) (Instance&);

    //Pivot Method pointer
    vector<long int> (*computePivot) (Instance&,
                                        vector<long int>,
                                        vector<long int> (*) (vector<long int>&, int, int),
                                        long long int (*) (Matrix&, vector<long int>&, int, int));
    //Neighborhood Modification Method pointer
    vector<long int> (*computeNeighborhood) (vector<long int>&, int, int);

    //Speed up the computation of the neighborhood modifications on the cost pointer
    long long int (*computeDelta) (Matrix&, vector<long int>&, int, int);

    //VND Neighborhoods sequence
    vector<vector<long int> (*) (vector<long int>&, int, int)> computeNeighborhoods;
    // VND Delta sequence
    vector<long long int (*) (Matrix&, vector<long int>&, int, int)> computeDeltas;


    //Parse the command line argument when running the program
    void parseArguments(int argc, char **argv);

    // VND Configuration
    void setPivotAlgorithm(string opt);
    void setNeighbourModification(string opt);
    void setInitialisation(string opt);

    // sets up the piped vnd algorithm
    void setUpVND(string opt);

    // sets up the piped ils algorithm
    void setUpILSSequence(string opt);
    void setPerturbation(string opt);
    Candidate (*perturbation) (Candidate&, int, int);

    //Memetic Algorithm
    Population (*initPopulation) (Instance&, int);
    Population (*recombine) (Instance&, Population, int);
    Population (*mutate) (Instance&, Population, float);
    Population (*select) (Instance&, Population, int);

    //getters
    int getAlgorithmType();
    string getFileName();
    string getAlgoClass();
    string getConfiguration();

    int getPopulationSize();
    float getMutationRate();
    int getMaxGeneration();

    double getMaxTime();
    int getPerturbNbr();


};

#endif //LOP_VND_CONFIGURATION_H
