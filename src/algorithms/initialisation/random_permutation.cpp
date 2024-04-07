//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"
#include <algorithm>   // std::shuffle => to shuffle the initial solution
#include <random>      // std::default_random_engine => using the instance seed

/***
 *
 * @param instance
 * @return a random solution
 */
vector<long int> createRandomSolution(Instance &instance){

    vector<long int> s(instance.getPSize());

    for(int i=0; i<instance.getPSize();i++){
        s[i] = i;
    }

    shuffle(s.begin(), s.end(), default_random_engine(instance.getSeed()));

    return s;

}