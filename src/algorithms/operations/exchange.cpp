//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"

vector<long int> exchange(vector<long int> s, int i, int j){

    cout << "exchange in " << endl;
    cout << "i: " << i << " j: " << j << endl;
    long int temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    cout << "exchange out " << endl;
    return s;
}