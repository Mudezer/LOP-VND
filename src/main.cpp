//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "skeleton/skeleton.h"
#include "algorithms/algorithms.h"
#include "algorithmType/algorithm_type.h"
#include <chrono>


void run(Instance &instance, Configuration &configuration);
void runInstance(Instance &instance, Configuration &configuration);
vector<long int> setIterative(Instance &instance, Configuration &config);




int main(int argc, char **argv){

    // parsing command line arguments
    Configuration config;
    config.parseArguments(argc, argv);

    // reading instance from file
    Instance instance;
    instance.readInstance(config.getFileName());

    cout << "Data have been read from instance file. Size of instance : " << instance.getPSize() << "\n\n";


    //setting a random seed for all random operations
    cout << "Seed used to intialize RNG: " << instance.getSeed() << "\n";
    srand(instance.getSeed());


    // running the algorithm
    run(instance, config);
    return 0;
}

void run(Instance &instance, Configuration &configuration){


    switch(configuration.getAlgorithmType()) {
        case ITERATIVE:
        case VND: {


            auto start = std::chrono::high_resolution_clock::now();

            runInstance(instance, configuration);

            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            double time = ((double) duration.count()) / 1000000.0;

            cout << "Time taken: " << time << setprecision(9) << "s\n" << endl;

//            // compute the number of element in the solution
//            cout << "Number of elements in the solution: " << s.size() << endl;
            }
            break;
        default:
            cerr << "Algorithm type not recognized." << endl;
            exit(1);
            break;
    }

}

void runInstance(Instance &instance, Configuration &configuration){

    vector<long int> s;
    if(configuration.getAlgorithmType() == ITERATIVE){
        s = setIterative(instance, configuration);
    }
    else if(configuration.getAlgorithmType() == VND){
//        runVND(instance, configuration);
    }
    else{
        cerr << "Algorithm type not recognized." << endl;
        exit(1);
    }

}

vector<long int> setIterative(Instance &instance, Configuration &config){

    cout << "Running Iterative algorithm" << endl;

    Iterative iterative;
    iterative.configure(
            config.computeInit,
            config.computeNeighborhood,
            config.computePivot
            );

    vector<long int> s = iterative.runIterative(instance);
    return s;
}



