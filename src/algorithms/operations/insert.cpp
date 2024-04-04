//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"

vector<long int> insert(vector<long int> &s, int i, int j){

    long int temp = s[i];
    s.erase(s.begin()+i);
    s.insert(s.begin()+j, temp);

    return s;

}