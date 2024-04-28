//
// Created by Loïc Bermudez on 28/04/2024.
//

#include "../../algorithms.h"


Population rankSelection(Instance& instance, Population population, int populationSize){
    Population selected;

    vector<pair<long long int, Candidate>> costNCandidates;
    for(auto& candidate : population){
        long long int cost = instance.computeCost(candidate);
        costNCandidates.emplace_back(cost, candidate);
    }

    sort(costNCandidates.begin(), costNCandidates.end(),
         [](const auto& a, const auto& b) {return a.first > b.first;
    });

    for(int i = 0; i<populationSize; i++){
        selected.push_back(costNCandidates[i].second);
    }

    return selected;
}