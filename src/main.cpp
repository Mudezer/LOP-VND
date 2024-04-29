//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "skeleton/skeleton.h"
#include "algorithms/algorithms.h"
#include "algorithmType/algorithm_type.h"
#include <chrono>


void run(Instance &instance, Configuration &configuration);
vector<long int> runInstance(Instance &instance, Configuration &configuration);
Iterative setIterative(Instance &instance, Configuration &config);
VariableNeighbourDescent setVND(Instance &instance, Configuration &config);
IterativeLocalSearch setILS(Instance &instance, Configuration &config);
Memetic setMemetic(Instance &instance, Configuration &config);


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

    vector<long int> finalSolution;
    double time = 0.0;

    switch(configuration.getAlgorithmType()) {
        case ITERATIVE:
        case VND:
        case ILS:
        case MEMETIC:{


            auto start = std::chrono::high_resolution_clock::now();

            finalSolution = runInstance(instance, configuration);

            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            time = ((double) duration.count()) / 1000000.0;

            cout << "Time taken: " << time << setprecision(9) << "s\n" << endl;

            }
            break;
        default:
            cerr << "Algorithm type not recognized." << endl;
            exit(1);
            break;
    }

    cout << "Final solution: " << endl;
    for (long i : finalSolution)
        cout << i << " ";
    cout << endl;

    cout << "Final solution cost: " << instance.computeCost(finalSolution) << endl;


    /*Output output;
    output.setUp(instance.getInstanceName(),
                  instance.getPSize(),
                  configuration.getAlgoClass(),
                  configuration.getConfiguration(),
                  instance.computeCost(finalSolution),
                  time);

    output.printOutput();*/



}

vector<long int> runInstance(Instance &instance, Configuration &configuration){

    vector<long int> s;
    if(configuration.getAlgorithmType() == ITERATIVE){
        Iterative iterative = setIterative(instance, configuration);
        return s = iterative.runIterative(instance);
    }
    else if(configuration.getAlgorithmType() == VND){
        VariableNeighbourDescent vnd = setVND(instance, configuration);
        return s = vnd.runVND(instance);
    }
    else if(configuration.getAlgorithmType() == ILS){
        IterativeLocalSearch ils = setILS(instance, configuration);
        return s = ils.runILS(instance);
    }
    else if(configuration.getAlgorithmType() == MEMETIC){
        Memetic memetic = setMemetic(instance, configuration);
        return s = memetic.runMemetic(instance);
    }
    else{
        cerr << "Algorithm type not recognized." << endl;
        exit(1);
    }


}

Iterative setIterative(Instance &instance, Configuration &config){

    cout << "Running Iterative algorithm" << endl;

    Iterative iterative;
    iterative.configure(
            config.computeInit,
            config.computeNeighborhood,
            config.computeDelta,
            config.computePivot

            );

    return iterative;
}

VariableNeighbourDescent setVND(Instance &instance, Configuration &config){

    cout << "Running VND algorithm" << endl;
    VariableNeighbourDescent vnd;
    vnd.configure(config.computeInit,
                  config.computePivot,
                  config.computeNeighborhoods,
                  config.computeDeltas
                  );
    return vnd;
}

IterativeLocalSearch setILS(Instance &instance, Configuration &config){

    cout << "Running ILS algorithm" << endl;
    IterativeLocalSearch ils;
    ils.configure(config.getMaxTime(),
                    config.getPerturbNbr(),
                    config.computeInit,
                    config.perturbation,
                    config.computeNeighborhood,
                    config.computeDelta
                  );
    return ils;

}

Memetic setMemetic(Instance &instance, Configuration &config){

    cout << "Running Memetic algorithm" << endl;
    Memetic memetic;
    memetic.configure(config.getPopulationSize(),
                      config.getMutationRate(),
                      config.getMaxGeneration(),
                      config.initPopulation,
                      config.recombine,
                      config.mutate,
                      config.select,
                      config.computeNeighborhood,
                      config.computeDelta
                      );
    return memetic;

}


