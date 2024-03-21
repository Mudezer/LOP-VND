//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "skeleton/instance/instance.h"
#include "algorithms/algorithms.h"
#include <chrono>


void run(Instance &instance, Configuration &configuration);
void runInstance(Instance &instance, Configuration &configuration);
void runIterative(Instance &instance, Configuration &configuration);
void runVND(Instance &instance, Configuration &configuration);



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

    if(configuration.getAlgorithmType() == ITERATIVE){
        runIterative(instance, configuration);
    }
    else if(configuration.getAlgorithmType() == VND){
        runVND(instance, configuration);
    }
    else{
        cerr << "Algorithm type not recognized." << endl;
        exit(1);
    }

}

void runIterative(Instance &instance, Configuration &configuration){

    vector<long int> s;

    switch(configuration.getPivotAlgorithm()){
        case FIRST:
            cout << "First pivot algorithm" << endl;
            s = firstImprovement(instance);
            break;
        case BEST:
            cout << "Best pivot algorithm" << endl;
            s = bestImprovement(instance, configuration);
            break;
        default:
            cerr << "Pivot algorithm not recognized." << endl;
            exit(1);

    }








}

void runVND(Instance &instance, Configuration &configuration){


}
