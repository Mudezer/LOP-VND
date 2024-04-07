//
// Created by Loïc Bermudez on 18/03/2024.
//


#include "../algorithms.h"


/***
 * Proceed to the insertion of an element in the solution s
 * @param s
 * @param i
 * @param j
 * @return the solution s with the element i inserted at the position j
 */
vector<long int> insert(vector<long int> &s, int i, int j){

    long int temp = s[i];
    s.erase(s.begin()+i);
    s.insert(s.begin()+j, temp);

    return s;

}