//
// Created by Loïc Bermudez on 25/03/2024.
//

#ifndef LOP_VND_OUTPUT_H
#define LOP_VND_OUTPUT_H

#include <string>
using namespace std;

class Output{
private:
    char *instanceName;
    char *configuration;
    long long int bestKnown;
    long long int bestCost;
    double elapsedTime;
    long long int relative_deviation;
public:

    Output();
    ~Output();

    void setInstanceName(char *instanceName);
    void setBestKnown(long long int bestKnown);
    void setBestCost(long long int bestCost);
    void setElapsedTime(double elapsedTime);
    void setRelativeDeviation(long long int relative_deviation);

    char *getInstanceName();
    long long int getBestKnown();
    long long int getBestCost();
    double getElapsedTime();
    long long int getRelativeDeviation();

    void writeOutput();

};

#endif //LOP_VND_OUTPUT_H
