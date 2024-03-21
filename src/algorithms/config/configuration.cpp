//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "configuration.h"

Configuration::Configuration(){}

Configuration::~Configuration(){}

void Configuration::parseArguments(int argc, char **argv){
    if(argc < 4){
        cerr << "Incorrect number of arguments." << endl;
//        cerr << "Usage: ./lop -i <instance_name> --<algo_type> --<pivot_algorithm> --<neighborhood_modification> --<initialisation_type>  \n" << endl;
        cerr << "Usage : ./lop -i <instance_name> --<algo_type>  [--options] " << endl;
        exit(1);
    }

    if(!(((string)argv[1]).compare("-i"))){
        setFileName(argv[2]);
    }
    else{
        cerr << "Incorrect arguments." << endl;
        cerr << "Usage: ./lop -i <instance_name> --<algo_type> --<pivot_algorithm> --<neighborhood_modification> --<initialisation_type>  \n" << endl;
        exit(1);
    }


//    for(int i = 0; i < argc; i++){
//        cout << argv[i] << endl;
//    }

    if(!(((string)argv[3]).compare("--iter"))){
        algorithmType = ITERATIVE;
        setPivotAlgorithm(argv[4]);
        setNeighborhoodModification(argv[5]);
        setInitializationType(argv[6]);
        char *FileName = argv[2];
        vndNeighborhood = NONE;

    }
    else if(!(((string)argv[3]).compare("--vnd"))){
        algorithmType = VND;
        pivotAlgorithm = FIRST;
        neighborhoodModification = NONE;
        initializationType = CW;
        char *FileName = argv[2];
        setVNDNeighborhood(argv[4]);



    }
}

void Configuration::setFileName(char *filename){
    FileName = filename;
}

void Configuration::setPivotAlgorithm(char *pivot){
    if(!(((string)pivot).compare("--first"))){
        pivotAlgorithm = FIRST;
    }
    else if(!(((string)pivot).compare("--best"))){
        pivotAlgorithm = BEST;
    }
}

void Configuration::setNeighborhoodModification(char *operation){
    if(!(((string)operation).compare("--transpose")))
        neighborhoodModification = TRANSPOSE;

    else if(!(((string)operation).compare("--exchange")))
        neighborhoodModification = EXCHANGE;

    else if (!(((string) operation).compare("--insert")))
        neighborhoodModification = INSERT;

}

void Configuration::setInitializationType(char *initialization){
    if(!(((string)initialization).compare("--random")))
        initializationType = RANDOM;

    else if(!(((string)initialization).compare("--cw")))
        initializationType = CW;
}

void Configuration::setVNDNeighborhood(char *vnd) {
    if (!(((string) vnd).compare("TEI")))
        vndNeighborhood = TRANS_EXCH_INS;

    else if (!(((string) vnd).compare("TIE")))
        vndNeighborhood = TRANS_INS_EXCH;

}

int Configuration::getAlgorithmType(){
    return algorithmType;
}

int Configuration::getPivotAlgorithm(){
    return pivotAlgorithm;
}

int Configuration::getNeighborhoodModification(){
    return neighborhoodModification;
}

int Configuration::getVNDNeighborhood(){
    return vndNeighborhood;
}

int Configuration::getInitializationType(){
    return initializationType;
}

char *Configuration::getFileName(){
    return FileName;
}