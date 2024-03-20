//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "skeleton/instance/instance.h"
#include "algorithms/algorithms.h"
#include <chrono>



int main(int argc, char **argv){

    // parsing command line arguments
    Configuration config;
    config.parseArguments(argc, argv);

    // reading instance from file
    Instance instance;
    instance.readInstance(config.getFileName());

    cout << "Data have been read from instance file. Size of instance : " << instance.getPSize() << "\n\n";


    //setting a random seed for all random operations
    cout << "Seed used to intialize RNG: " << instance.getSeed() << "\n\n";
    srand(instance.getSeed());

    auto start = std::chrono::high_resolution_clock::now();

    vector<long int> s = createRandomSolution(instance);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    double time = ((double)duration.count())/1000000.0;

    cout << "Time taken: " << time << setprecision(9) << "s\n" << endl;;

    return 0;
}