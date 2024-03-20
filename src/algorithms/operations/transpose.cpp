//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"

vector<long int> transpose(vector<long int> s, int i, int j){

    long int temp = s[i];
    s[i] = s[i+1];
    s[i+1] = temp;

    return s;
}