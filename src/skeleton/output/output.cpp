//
// Created by Loïc Bermudez on 25/03/2024.
//

#include "output.h"

Output::Output(){}

Output::~Output(){}

void Output::setInstanceName(char *instanceName) {
    this->instanceName = instanceName;
}

void Output::setBestKnown(long long int bestKnown) {
    this->bestKnown = bestKnown;
}

void Output::setBestCost(long long int bestCost) {
    this->bestCost = bestCost;
}

void Output::setElapsedTime(double elapsedTime) {
    this->elapsedTime = elapsedTime;
}

void Output::setRelativeDeviation(long long int relative_deviation) {
    this->relative_deviation = relative_deviation;
}

char *Output::getInstanceName() {
    return this->instanceName;
}

long long int Output::getBestKnown() {
    return this->bestKnown;
}

long long int Output::getBestCost() {
    return this->bestCost;
}

double Output::getElapsedTime() {
    return this->elapsedTime;
}

long long int Output::getRelativeDeviation() {
    return this->relative_deviation;
}

void Output::writeOutput(){


}
