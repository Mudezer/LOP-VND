//
// Created by Loïc Bermudez on 23/04/2024.
//


#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef vector<long int> Candidate;
typedef vector<Candidate> Population;

Population twoPointCrossover(Candidate parent1, Candidate parent2){
    Population childs;
    Candidate child1;
    Candidate child2;

    int pivot1 = rand() % parent1.size()+1;
    int pivot2 = rand() % parent1.size()+1;

    if(pivot1 > pivot2){
        swap(pivot1, pivot2);
    }

    for(int i = 0; i<pivot1; i++){
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
    }

    for(int i = pivot1; i<pivot2; i++){
        child1.push_back(parent2[i]);
        child2.push_back(parent1[i]);
    }

    for(int i = pivot2; i<parent1.size(); i++){
        child1.push_back(parent1[i]);
        child2.push_back(parent2[i]);
    }

    childs.push_back(child1);
    childs.push_back(child2);


    return childs;
}

Candidate reparefilsdepute(Candidate candidate){

    vector<bool> used(candidate.size(), false);
    vector<long int> duplicates_idx;
    vector<long int> missing;

    for(int i=0; i<candidate.size(); i++){
        if(used[candidate[i]]){
            duplicates_idx.push_back(i);
        }else{
            used[candidate[i]] = true;
        }
    }

    for(int i=0; i<used.size(); i++){
        if(!used[i]){
            missing.push_back(i);
        }
    }



    random_device rd;
    mt19937 g(rd());

    // Shuffle the data vector
    std::shuffle(missing.begin(), missing.end(), g);



    for(int i = 0; i<duplicates_idx.size(); i++){
        candidate[duplicates_idx[i]] = missing[i];
    }

    return candidate;
}




int main(int argc, char **argv) {

//    srand(10);


    Candidate parent1 = vector<long int> (150);
    Candidate parent2 = vector<long int> (150);

    // Create a vector to store the numbers


    // Fill the vector with integers from 0 to 149
    std::iota(parent1.begin(), parent1.end(), 0);
    std::iota(parent2.begin(), parent2.end(), 0);


    // Obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    mt19937 generator(seed);


    // Shuffle the vector using the default random engine
    std::shuffle(parent1.begin(), parent1.end(), generator);
    std::shuffle(parent2.begin(), parent2.end(), generator);
    std::shuffle(parent2.begin(), parent2.end(), generator);

    cout << "Parent 1: ";
    for(int i = 0; i<parent1.size(); i++){
        cout << parent1[i] << " ";
    }
    cout << endl;

    cout << "Parent 2: ";
    for(int i = 0; i<parent2.size(); i++){
        cout << parent2[i] << " ";
    }
    cout << endl;

    Population childs = twoPointCrossover(parent1, parent2);

    Candidate child1 = childs[0];

    cout << "Child 1: ";
    for(int i = 0; i<child1.size(); i++){
        cout << child1[i] << " ";
    }
    cout << endl;

    child1 = reparefilsdepute(child1);

    cout << "Child 1: ";
    for(int i = 0; i<child1.size(); i++){
        cout << child1[i] << " ";
    }
    cout << endl;



    return 0;
}