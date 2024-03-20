//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "../algorithms.h"
#include <algorithm>   // std::shuffle => to shuffle the initial solution
#include <random>      // std::default_random_engine => using the instance seed


vector<long int> createRandomSolution(Instance &instance){

    vector<long int> s(instance.getPSize());

//    srand(instance.getSeed());

    for(int i=0; i<instance.getPSize();i++){
        s[i] = i;
    }

    shuffle(s.begin(), s.end(), default_random_engine(instance.getSeed()));

    cout<< "Random solution: ";
    for(int i=0; i<instance.getPSize();i++){
        cout<< s[i] << " ";
    }
    cout<<endl;
    return s;

}