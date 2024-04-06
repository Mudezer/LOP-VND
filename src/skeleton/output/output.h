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

    string instanceName;
    long int instanceSize;
    string algoClass;
    string pivot;
    string neighborhood;
    string init;
    string configuration;
    string bestKnown;
    long long int bestKnowed;
    long long int bestCost;
    double elapsedTime;
    long long int relativeDeviation;

    void findBestKnown(string instance_name);
    vector<string> split(const string &s, char delimiter);
    void parseConfiguration(string config);
public:
    Output();
    ~Output();

    void setUp(string instanceName,
               long int instanceSize,
               string algoClass,
               string configuration,
               long long int bestCost,
               double elaspedTime);
    void printOutput();



};

#endif //LOP_VND_OUTPUT_H
