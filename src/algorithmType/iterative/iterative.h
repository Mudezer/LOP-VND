//
// Created by Loïc Bermudez on 20/03/2024.
//

#ifndef LOP_VND_ITERATIVE_H
#define LOP_VND_ITERATIVE_H

#include "../../skeleton/skeleton.h"



class Iterative{
private:
    //pass a function as argument
    // first compute the initial solution (either random or CW)
    vector<long int> (*computeInitialSolution)(Instance&);
    // second consider the neighbour modification
    vector<long int> (*neighbourModif)(vector<long int>, int, int);
    // third consider the pivot algorithm
    vector<long int> (*pivotImprove)(Instance&,
                                        vector<long int>,
                                        vector<long int> (*) (vector<long int>, int, int));
public:
    void configure(
            vector<long int> (*computeInitialSolution) (Instance&),
            vector<long int> (*neighbourModif) (vector<long int>, int ,int),
            vector<long int> (*pivotImprove) (Instance&, vector<long int>,
                                                    vector<long int> (*) (vector<long int>, int, int))
    );
    vector<long int> runIterative(Instance &instance, vector<long int> s);
    vector<long int> runIterative(Instance &instance);
};


#endif //LOP_VND_ITERATIVE_H
