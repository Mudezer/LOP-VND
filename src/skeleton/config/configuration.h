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

typedef vector<vector<long int>> Matrix;
using namespace std;

/* algorithmType */
#define ITERATIVE 1
#define VND 2

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

class Configuration{
private:
    string FileName;
    string algoClass;
    string configuration;

    // all flag
    bool all;
    string all_algo;

    int algorithmType;
    int pivotAlgorithm;
    int neighborhoodModification;
    int vndNeighborhood;
    int initializationType;

public:
    Configuration();
    ~Configuration();

    vector<long int> (*computeInit) (Instance&);
    vector<long int> (*computePivot) (Instance&,
                                        vector<long int>,
                                        vector<long int> (*) (vector<long int>&, int, int),
                                        long long int (*) (Matrix&, vector<long int>&, int, int));
    vector<long int> (*computeNeighborhood) (vector<long int>&, int, int);
    long long int (*computeDelta) (Matrix&, vector<long int>&, int, int);
    vector<vector<long int> (*) (vector<long int>&, int, int)> computeNeighborhoods;
    vector<long long int (*) (Matrix&, vector<long int>&, int, int)> computeDeltas;
//    vector<vector<long int> (*) (Instance&)> computeInitializations;
//    vector<vector<long int> (*) (Instance&,
//                                vector<long int>,
//                                vector<long int> (*) (vector<long int>&, int, int),
//                                long long int (*) (Matrix&, vector<long int>&, int, int))> computePivots;


    //setters
    void parseArguments(int argc, char **argv);

    //getters
    int getAlgorithmType();
    string getFileName();

    // running all kind of algorithm type
    bool isAll();
    string getAllAlgo();

    string getAlgoClass();
    string getConfiguration();
    void setUpVND(string opt);


};

#endif //LOP_VND_CONFIGURATION_H
