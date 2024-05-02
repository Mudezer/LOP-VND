//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "configuration.h"


Configuration::Configuration(){}

Configuration::~Configuration(){}

void Configuration::parseArguments(int argc, char **argv){

    const char* const short_opts = "i:t:v:l:m:f:c:e:q:w:z:p:n:o:r:s:k";
    const option long_opts[] = {
            {"-i", required_argument, nullptr, 'i'},
            // algo type
            {"iter", no_argument, nullptr, 't'},
            {"vnd", required_argument, nullptr, 'v'},
            {"ils", required_argument, nullptr, 'l'},
            {"memetic", no_argument, nullptr, 'm'},

            // Simple VND variables
            {"pivot", required_argument, nullptr, 'f'},
            {"init", required_argument, nullptr, 'c'},
            {"neighbour", required_argument, nullptr, 'e'},

            // ILS variables
            {"perturb", required_argument, nullptr, 'r'},
            {"time", required_argument, nullptr, 's'},
            {"moves", required_argument, nullptr, 'k'},

            // memetic variables
            {"rank-comb",no_argument, nullptr, 'q'},
            {"rank-select", no_argument, nullptr,'w'},
            {"rank-mut", no_argument, nullptr, 'z'},
            {"pop", required_argument, nullptr, 'p'},
            {"rate", required_argument, nullptr, 'n'},

            // help
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
            case 'l':
                this->algorithmType = ILS;
                this->algoClass = "ils";
                this->configuration += "ils_";
                setUpILSSequence(optarg);
                cout << "Running ILS algorithm\n" << endl;
                break;
            case 'm':
                this->algorithmType = MEMETIC;
                this->algoClass = "memetic";
                this->configuration += "memetic_";
                this->initPopulation = randomPopulationInitialisation;
                this->configuration += "random-init_";
                cout << "Running Memetic algorithm\n" << endl;
                break;
            case 'f':
                setPivotAlgorithm(optarg);
                break;
            case 'e':
                setNeighbourModification(optarg);
                break;
            case 'c':
                setInitialisation(optarg);
                break;
            case 'r':
                setPerturbation(optarg);
                break;
            case 's':
                this->maxTime = atof(optarg);
                this->configuration += "time_" + to_string(this->maxTime) + "_";
                break;
            case 'k':
                this->perturbNbr = atoi(optarg);
                this->configuration += "moves_" + to_string(this->perturbNbr) + "_";
                break;
            case 'q':
                this->recombine = recombination;
                this->configuration += "rank-comb_";
                cout << "Rank based recombination\n" << endl;
                break;
            case 'w':
                this->select = rankSelection;
                this->configuration += "rank-select_";
                cout << "Rank based selection\n" << endl;
                break;
            case 'z':
                this->mutate = randomMutation;
                this->configuration += "rank-mut_";
                cout << "Rank based mutation\n" << endl;
                break;
            case 'p':
                this->populationSize = atoi(optarg);
                this->configuration += "pop_" + to_string(this->populationSize) + "_";
                cout << "Population size: " << this->populationSize << "\n" << endl;
                break;
            case 'n':
                this->mutationRate = atof(optarg);
                this->configuration += "mut_" + to_string(this->mutationRate) + "_";
                cout << "Mutation rate: " << this->mutationRate << "\n" << endl;
                break;
            case 'h':
            case '?':
            default:
                // TODO: redo the help message
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

int Configuration::getPopulationSize(){
    return this->populationSize;
}

float Configuration::getMutationRate(){
    return this->mutationRate;
}

int Configuration::getMaxGeneration(){
    return this->maxGeneration;
}

double Configuration::getMaxTime(){
    return this->maxTime;
}

int Configuration::getPerturbNbr(){
    return this->perturbNbr;
}

void Configuration::setPivotAlgorithm(string opt){

    cout << "Pivot algorithm: " << opt << endl;

    if(opt == "first"){
        this->pivotAlgorithm = FIRST;
        this->configuration += "first_";
        this->computePivot = firstImprovement;
        cout << "First pivot algorithm\n" << endl;
    }
    else if(opt == "best"){
        this->pivotAlgorithm = BEST;
        this->configuration += "best_";
        this->computePivot = bestImprovement;
        cout << "Best pivot algorithm\n" << endl;
    }
    else{
        cerr << "Pivot algorithm not recognized." << endl;
        exit(1);
    }

}

void Configuration::setNeighbourModification(string opt){
    if(opt == "exchange"){
        this->neighborhoodModification = EXCHANGE;
        this->configuration += "exchange_";
        this->computeNeighborhood = exchange;
        this->computeDelta = computeDeltaExchange;
        cout << "Exchange neighborhood\n" << endl;
    }
    else if(opt == "insert"){
        this->neighborhoodModification = INSERT;
        this->configuration += "insert_";
        this->computeNeighborhood = insert;
        this->computeDelta = computeDeltaInsert;
        cout << "Insert neighborhood\n" << endl;
    }
    else if(opt == "transpose"){
        this->neighborhoodModification = TRANSPOSE;
        this->configuration += "transpose_";
        this->computeNeighborhood = transpose;
        this->computeDelta = computeDeltaTranspose;
        cout << "Transpose neighborhood\n" << endl;
    }else{
        cerr << "Neighborhood modification not recognized." << endl;
        exit(1);
    }

}

void Configuration::setInitialisation(string opt){

    if(opt == "cw"){
        this->initializationType = CW;
        this->configuration += "cw";
        this->computeInit = createCWHeuristicSolution;
        cout << "CW initialization\n" << endl;
    }
    else if(opt =="random"){
        this->initializationType = RANDOM;
        this->configuration += "random";
        this->computeInit = createRandomSolution;
        cout << "Random initialization\n" << endl;
    }
    else{
        cerr << "Initialization not recognized." << endl;
        exit(1);
    }

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

void Configuration::setUpILSSequence(string opt){
    if(opt == "TIE"){
        this -> computeNeighborhoods = {transpose, insert, exchange};
        this -> computeDeltas = {computeDeltaTranspose, computeDeltaInsert, computeDeltaExchange};
        this -> configuration += "TIE_";
    }
    else if(opt == "TEI"){
        this -> computeNeighborhoods = {transpose, exchange, insert};
        this -> computeDeltas = {computeDeltaTranspose, computeDeltaExchange, computeDeltaInsert};
        this -> configuration += "TEI_";
    }
}


void Configuration::setPerturbation(string opt){
    if(opt == "tranpose"){
        this->perturbation = transpose;
        this->configuration += "perturb-transpose_";
    }
    else if(opt == "exchange"){
        this->perturbation = exchange;
        this->configuration += "perturb-exchange_";
    }
    else if(opt == "insert"){
        this->perturbation = insert;
        this->configuration += "perturb-insert_";
    }
    else{
        cerr << "Perturbation not recognized." << endl;
        exit(1);
    }

}

