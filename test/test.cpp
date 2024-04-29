//
// Created by Loïc Bermudez on 23/04/2024.
//


#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef vector<long int> Candidate;


// Hash function
struct hashFunction
{
    size_t operator()(const vector<long int>
                      &myVector) const
    {
        std::hash<int> hasher;
        size_t answer = 0;

        for (int i : myVector)
        {
            answer ^= hasher(i) + 0x9e3779b9 +
                      (answer << 6) + (answer >> 2);
        }
        return answer;
    }
};

typedef unordered_set<Candidate,hashFunction> History;


History updateHistory(Candidate candidate, History history){
    if(history.find(candidate) == history.end()){
        history.insert(candidate);
        cout << "Inserted" << endl;
    }else {
        cout << "Already in history" << endl;
    }

    return history;
}

bool isInHistory(Candidate candidate, History history) {
    return history.find(candidate) == history.end();
}




int main(int argc, char **argv) {

    Candidate candidate1 = {1, 2, 3, 4, 5};
    Candidate candidate2 = {1, 2, 3, 4, 5};
    Candidate candidate3 = {5, 3, 2, 1, 4};

    History history;

    history = updateHistory(candidate1, history);
    history = updateHistory(candidate3, history);
    history = updateHistory(candidate2, history);

    cout << "Is candidate1 in history: " << isInHistory(candidate1, history) << endl;
    cout << "Is candidate2 in history: " << isInHistory(candidate2, history) << endl;
    cout << "Is candidate3 in history: " << isInHistory(candidate3, history) << endl;


    return 0;
}