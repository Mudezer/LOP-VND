//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "configuration.h"


Configuration::Configuration(){}

Configuration::~Configuration(){}

void Configuration::parseArguments(int argc, char **argv){
    // instance:all:iter:vnd:pivot:neighbour:init"i:a:t:v:p:n:g"
    const char* const short_opts = "i:a:t:v:e:s:r:p:n:g:h";
    const option long_opts[] = {
            {"-i", required_argument, nullptr, 'i'},
            {"iter", no_argument, nullptr, 't'},
            {"vnd", required_argument, nullptr, 'v'},
            {"first", no_argument, nullptr, 'f'},
            {"best", no_argument, nullptr, 'b'},
            {"exchange", no_argument, nullptr, 'e'},
            {"insert", no_argument, nullptr, 's'},
            {"transpose", no_argument, nullptr, 'r'},
            {"cw", no_argument, nullptr, 'c'},
            {"random", no_argument, nullptr, 'g'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}

    };

    while(true){
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if(-1 == opt)
            break;

        switch(opt){
            case 'i':
                this->FileName = optarg;
                cout << "Instance file: " << this->FileName << "\n" << endl;
                break;
            case 't':
                this->algorithmType = ITERATIVE;
                this->algoClass = "iter";
                this->configuration += "iter_";
                cout << "Running Iterative algorithm\n" << endl;
                break;
            case 'v':
                this->algorithmType = VND;
                this->algoClass = "vnd";
                this->configuration += "vnd_";
                setUpVND( optarg);
                cout << "Running VND algorithm\n" << endl;
                break;
            case 'f':
                this->pivotAlgorithm = FIRST;
                this->configuration += "first_";
                this->computePivot = firstImprovement;
                cout << "First pivot algorithm\n" << endl;
                break;
            case 'b':
                this->pivotAlgorithm = BEST;
                this->configuration += "best_";
                this->computePivot = bestImprovement;
                cout << "Best pivot algorithm\n" << endl;
                break;
            case 'e':
                this->neighborhoodModification = EXCHANGE;
                this->configuration += "exchange_";
                this->computeNeighborhood = exchange;
                this->computeDelta = computeDeltaExchange;
                cout << "Exchange neighborhood\n" << endl;
                break;
            case 's':
                this->neighborhoodModification = INSERT;
                this->configuration += "insert_";
                this->computeNeighborhood = insert;
                this->computeDelta = computeDeltaInsert;
                cout << "Insert neighborhood\n" << endl;
                break;
            case 'r':
                this->neighborhoodModification = TRANSPOSE;
                this->configuration += "transpose_";
                this->computeNeighborhood = transpose;
                this->computeDelta = computeDeltaTranspose;
                cout << "Transpose neighborhood\n" << endl;
                break;
            case 'c':
                this->initializationType = CW;
                this->configuration += "cw";
                this->computeInit = createCWHeuristicSolution;
                cout << "CW initialization\n" << endl;
                break;
            case 'g':
                this->initializationType = RANDOM;
                this->configuration += "random";
                this->computeInit = createRandomSolution;
                cout << "Random initialization\n" << endl;
                break;
            case 'h':
            case '?':
            default:
                cout << "Usage: ./lop -i <instance_file> --all --iter\n"
                        "Usage: ./lop -i <instance_file> --all --vnd\n"
                        "Usage: ./lop -i <instance_file> --iter --exchange --insert --transpose --cw --random\n"
                        "Usage: ./lop -i <instance_file> --vnd --TIE\n";
                exit(1);
                break;
        }
    }
}

int Configuration::getAlgorithmType(){
    return algorithmType;
}

string Configuration::getFileName(){
    return FileName;
}



string Configuration::getConfiguration(){
    return configuration;
}

string Configuration::getAlgoClass(){
    return algoClass;
}


void Configuration::setUpVND(string opt) {
    this->pivotAlgorithm = FIRST;
    this->computePivot = firstImprovement;
    this->configuration += "first_";
    this->initializationType = CW;
    this->computeInit = createCWHeuristicSolution;
    this->configuration += "cw_";

    if(opt == "TIE"){
        this -> computeNeighborhoods = {transpose, insert, exchange};
        this -> computeDeltas = {computeDeltaTranspose, computeDeltaInsert, computeDeltaExchange};
        this -> configuration += "TIE";
    }
    else if(opt == "TEI"){
        this -> computeNeighborhoods = {transpose, exchange, insert};
        this -> computeDeltas = {computeDeltaTranspose, computeDeltaExchange, computeDeltaInsert};
        this -> configuration += "TEI";
    }
}