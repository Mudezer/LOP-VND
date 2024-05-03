//
// Created by Loïc Bermudez on 25/03/2024.
//

#ifndef LOP_VND_OUTPUT_H
#define LOP_VND_OUTPUT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Output{
private:
    // generic
    string instanceName;
    long int instanceSize;
    string algoClass;
    // II and piped VND
    string pivot;
    string neighborhood;
    string init;
    // ILS
    string vndSequence;
    string localSearch;
    string perturbation;
    int moves;

    // memetic;
    string popInit;
    int populationSize;
    float mutationRate;
    string mutation;

    string configuration;
    string bestKnown;
    long long int bestKnowed;
    long long int bestCost;
    double elapsedTime;
    long long int relativeDeviation;

    // find the best known solution for the instance in the best knowns file
    void findBestKnown(string instance_name);
    // split a string with a delimiter
    vector<string> split(const string &s, char delimiter);
    //parse the configuration string
    void parseConfiguration(string config);
    void printOut();
public:
    Output();
    ~Output();

    // sets ups the output object with the different elements to be printed in the output file
    void setUp(string instanceName,
               long int instanceSize,
               string algoClass,
               string configuration,
               long long int bestCost,
               double elaspedTime);

    // prints the output in the output file
    void printOutput();



};

#endif //LOP_VND_OUTPUT_H
