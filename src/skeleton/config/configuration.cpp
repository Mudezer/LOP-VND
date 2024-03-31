//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "configuration.h"


Configuration::Configuration(){}

Configuration::~Configuration(){}

void Configuration::parseArguments(int argc, char **argv){
    if(argc < 3){
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


    if(!(((string)argv[3]).compare("--iter"))){
        cout << "Running Iterative algorithm\n" << endl;
        algorithmType = ITERATIVE;

        setNeighborhoodModification(argv[5]);
        setInitializationType(argv[6]);
        vndNeighborhood = NONE;
        setPivotAlgorithm(argv[4]);

    }
    else if(!(((string)argv[3]).compare("--vnd"))){
        cout << "Running VND algorithm\n" << endl;
        algorithmType = VND;

        neighborhoodModification = NONE;
        char init[] = "--cw";
        setInitializationType(init);
        setVNDNeighborhood(argv[4]);
        setPivotAlgorithmVND();



    }
    else if(!(((string)argv[3]).compare("--all"))){

    }
}

void Configuration::setFileName(char *filename){
    this->FileName = filename;
}

void Configuration::setPivotAlgorithmVND() {
    this->pivotAlgorithm = FIRST;
    this->computePivot = firstImprovement;

}

void Configuration::setPivotAlgorithm(char *pivot){
    if(!(((string)pivot).compare("--first"))){
        cout << "First improvement selected\n" << endl;
        this->pivotAlgorithm = FIRST;
        this->computePivot = firstImprovement;

    }
    else if(!(((string)pivot).compare("--best"))){
        cout << "Best improvement selected\n" << endl;
        this->pivotAlgorithm = BEST;
        this->computePivot = bestImprovement;
    }
}

void Configuration::setNeighborhoodModification(char *operation) {
    if (!(((string) operation).compare("--transpose"))) {
        cout << "Transpose selected\n" << endl;
        this->neighborhoodModification = TRANSPOSE;
        this->computeNeighborhood = transpose;
        this->computeDelta = computeDeltaTranspose;

    } else if (!(((string) operation).compare("--exchange"))) {
        cout << "Exchange selected\n" << endl;
        this->neighborhoodModification = EXCHANGE;
        this->computeNeighborhood = exchange;
        this->computeDelta = computeDeltaExchange;

    } else if (!(((string) operation).compare("--insert"))){
        cout << "Insert selected\n" << endl;
        this->neighborhoodModification = INSERT;
        this->computeNeighborhood = insert;
        this->computeDelta = computeDeltaInsert;
    }
}

void Configuration::setInitializationType(char *initialization){
    if(!(((string)initialization).compare("--random"))){
        cout << "Random initialization selected\n" << endl;
        this->initializationType = RANDOM;
        this->computeInit = createRandomSolution;
    }

    else if(!(((string)initialization).compare("--cw"))){
        cout << "Cheneby x Watanabe heuristic initialization selected\n" << endl;
        this->initializationType = CW;
        this->computeInit = createCWHeuristicSolution;
    }
}

void Configuration::setVNDNeighborhood(char *vnd) {
    if (!(((string) vnd).compare("--TEI"))) {
        cout << "Transpose - Exchange - Insert VND sequence selected\n" << endl;
        this->vndNeighborhood = TRANS_EXCH_INS;

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), transpose);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaTranspose);

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), exchange);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaExchange);

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), insert);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaInsert);

    }
    else if (!(((string) vnd).compare("--TIE"))) {
        cout << "Transpose - Insert - Exchange VND sequence selected\n" << endl;
        this->vndNeighborhood = TRANS_INS_EXCH;

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), transpose);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaTranspose);

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), insert);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaInsert);

        this->computeVNDNeighborhoods.insert(computeVNDNeighborhoods.end(), exchange);
        this->computeDeltas.insert(computeDeltas.end(), computeDeltaExchange);
    }
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


