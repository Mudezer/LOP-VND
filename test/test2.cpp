//
// Created by Loïc Bermudez on 28/04/2024.
//


#include <vector>
#include <algorithm>
#include <iostream>

class Instance {
public:
    long long computeCost(const std::vector<long int>& candidate) {
        // Dummy implementation: replace with actual cost computation
        long long cost = 0;
        for (auto val : candidate) {
            cost += val;
        }
        return cost;
    }
};

int main() {
    std::vector<std::vector<long int>> Population = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            {10, 11, 12}
    };
    int populationSize = 3;  // Select the top 3 candidates

    Instance instance;
    std::vector<std::pair<long long, std::vector<long int>>> scoredCandidates;

    // Compute the cost for each candidate
    for (auto& candidate : Population) {
        long long score = instance.computeCost(candidate);
        scoredCandidates.emplace_back(score, candidate);
    }

    // Sort candidates by score in descending order
    std::sort(scoredCandidates.begin(), scoredCandidates.end(),
              [](const auto& a, const auto& b) {
                  return a.first > b.first;
              });

    // Extract the top populationSize candidates
    std::vector<std::vector<long int>> selectedCandidates;
    for (int i = 0; i < populationSize; ++i) {
        selectedCandidates.push_back(scoredCandidates[i].second);
    }

    // Print selected candidates
    for (const auto& candidate : selectedCandidates) {
        for (auto value : candidate) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    return 0;
}