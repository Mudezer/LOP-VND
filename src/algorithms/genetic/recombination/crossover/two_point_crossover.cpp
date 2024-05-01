//
// Created by Loïc Bermudez on 23/04/2024.
//

#include "../../../algorithms.h"
#include <random>
#include <algorithm>

typedef vector<int> Index;



Candidate makeValid(Candidate child){
    vector<bool> used(child.size(), false);
    Index duplicates_idx;
    Candidate missing;

    for(int i=0; i<child.size(); i++){
        if(used[child[i]]){
            duplicates_idx.insert(duplicates_idx.end(),i);
        }else{
            used[child[i]] = true;
        }
    }

    for(int i=0; i<used.size(); i++){
        if(!used[i]){
            missing.push_back(i);
        }
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(missing.begin(), missing.end(), g);

    for(int i = 0; i<duplicates_idx.size(); i++){
        child[duplicates_idx[i]] = missing[i];
    }

    return child;

}

Population twoPointCrossover(Instance& instance, Candidate parent1, Candidate parent2){
    Population childs;
    Candidate child1;
    Candidate child2;



    int pivot1 = rand() % parent1.size();
    int pivot2 = rand() % parent1.size();

    while(pivot1 == pivot2){
        pivot2 = rand() % parent1.size();
    }

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

    child1 = makeValid(child1);
    child2 = makeValid(child2);

    childs.push_back(child1);
    childs.push_back(child2);

    return childs;
}