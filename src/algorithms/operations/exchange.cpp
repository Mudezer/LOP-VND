//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"

/**
 * Proceed to the exchange of two elements in the solution s
 * @param s
 * @param i
 * @param j
 * @return return the solution s with the elements i and j exchanged
 */

vector<long int> exchange(vector<long int> &s, int i, int j){

    long int temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    return s;
}