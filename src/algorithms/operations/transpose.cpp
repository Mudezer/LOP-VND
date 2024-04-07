//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"


/***
 * Proceed to the transpose of two elements in the solution s
 * @param s
 * @param i
 * @param j
 * @return the solution s with the elements i and i+1 transposed
 */
vector<long int> transpose(vector<long int> &s, int i, int j){

    long int temp = s[i];
    s[i] = s[i+1];
    s[i+1] = temp;

    return s;
}