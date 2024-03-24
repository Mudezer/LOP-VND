//
// Created by Loïc Bermudez on 23/03/2024.
//

#ifndef LOP_VND_VARIABLENEIGHBOORDESCEND_H
#define LOP_VND_VARIABLENEIGHBOORDESCEND_H

#include "../../skeleton/skeleton.h"

class VariableNeighbourDescent{
private:
    vector<long int> (*computeInitialSolution)(Instance&);
    vector<long int> (*pivotImprove)(Instance&,
                                 vector<long int>,
                                 vector<long int> (*) (vector<long int>, int, int));
    // we create a vector of function pointers => we need 3 methods to be used in the VND
    vector<vector<long int> (*) (vector<long int>, int, int)> neighbourOperations;


public:
    void configure(
            vector<long int> (*computeInitialSolution) (Instance&),
            vector<long int> (*pivotImprove) (Instance&, vector<long int>,
                                                    vector<long int> (*) (vector<long int>, int, int)),
            vector<vector<long int> (*) (vector<long int>, int, int)> neighbourOperations
    );
//    vector<long int> runVND(Instance &instance, vector<long int> s);
    vector<long int> runVND(Instance &instance);

};

#endif //LOP_VND_VARIABLENEIGHBOORDESCEND_H


