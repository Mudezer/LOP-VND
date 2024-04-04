//
// Created by Loïc Bermudez on 28/03/2024.
//

#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>

using namespace std;
typedef vector<vector<int>> Matrix;
typedef vector<int> state;

/* algorithmType */
#define ITERATIVE 1
#define VND 2

/* Initialisation Type */
#define RANDOM 1
#define CW 2

/* Pivot Algorithms */
#define FIRST 1
#define BEST 2

/* Neighborhood Modification */
#define NONE 0
#define TRANSPOSE 1
#define EXCHANGE 2
#define INSERT 3

/* VND Neighborhood*/
#define NONE 0
#define TRANS_EXCH_INS 1
#define TRANS_INS_EXCH 2

/*
    ./lop -i <instance_file> --all --iter
    ./lop -i <instance_file> --all --vnd
    ./lop -i <instance_file> --iter --pivot --neighbour --init
    ./lop -i <instance_file> --iter --pivot


 */

class Config{
private:
    string instance;
    string configuration;
    string algoClass;

    bool all;
    string all_algo;
    int algorithmType;
    int neighborhoodModification;
//    int vndNeighborhood;
    int initializationType;
public:
    Config();
    ~Config();
    void processArgs(int argc, char **argv);
    string getConfiguration(){return this->configuration;}
    string getInstance(){return this->instance;}
    string getAlgoClass(){return this->algoClass;}



};

Config::Config(){}
Config::~Config(){}

void Config::processArgs(int argc, char **argv){
    this->all = false;
    // instance:all:iter:vnd:pivot:neighbour:init"i:a:t:v:p:n:g"
    const char* const short_opts = "i:a:t:v:e:s:r:p:n:g:h";
    const option long_opts[] = {
            {"-i", required_argument, nullptr, 'i'},
            {"all", required_argument, nullptr, 'a'},
            {"iter", no_argument, nullptr, 't'},
            {"vnd", no_argument, nullptr, 'v'},
            {"first", no_argument, nullptr, 'f'},
            {"best", no_argument, nullptr, 'b'},
            {"exchange", no_argument, nullptr, 'e'},
            {"insert", no_argument, nullptr, 's'},
            {"transpose", no_argument, nullptr, 'r'},
//            {"pivot", no_argument, nullptr, 'p'},
//            {"neighbour", no_argument, nullptr, 'n'},
//            {"init", no_argument, nullptr, 'g'},
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
                this->instance = optarg;
                cout << "Instance file: " << this->instance << "\n" << endl;
                break;
            case 'a':
                this->all = true;
                this->all_algo = optarg;
                cout << "Running all algorithms based on " << this->all_algo << "\n" << endl;
                break;
            case 't':
                this->all = false;
                this->algorithmType = ITERATIVE;
                this->algoClass = "iter";
                this->configuration += "iter_";
                cout << "Running Iterative algorithm\n" << endl;
                break;
            case 'v':
                this->all = false;
                this->algorithmType = VND;
                cout << "Running VND algorithm\n" << endl;
                break;
            case 'f':
                this->initializationType = FIRST;
                this->configuration += "first_";
                cout << "First pivot algorithm\n" << endl;
                break;
            case 'b':
                this->initializationType = BEST;
                cout << "Best pivot algorithm\n" << endl;
                break;
            case 'e':
                this->neighborhoodModification = EXCHANGE;
                this->configuration += "exchange_";
                cout << "Exchange neighborhood\n" << endl;
                break;
            case 's':
                this->neighborhoodModification = INSERT;
                cout << "Insert neighborhood\n" << endl;
                break;
            case 'r':
                this->neighborhoodModification = TRANSPOSE;
                cout << "Transpose neighborhood\n" << endl;
                break;
            case 'c':
                this->initializationType = CW;
                this->configuration += "cw";
                cout << "CW initialization\n" << endl;
                break;
            case 'g':
                this->initializationType = RANDOM;
                cout << "Random initialization\n" << endl;
                break;
            case 'h':
            case '?':
            default:
                cout << "Usage: ./lop -i <instance_file> --all --iter\n"
                        "Usage: ./lop -i <instance_file> --all --vnd\n"
                        "Usage: ./lop -i <instance_file> --iter --exchange --insert --transpose --cw --random\n"
                        "Usage: ./lop -i <instance_file> --vnd --exchange --insert --transpose --cw --random\n";
                break;
        }
    }
}

int main(int argc, char **argv){
    Config config;
    config.processArgs(argc, argv);

    cout << "Configuration: " << config.getConfiguration() << endl;
    cout << "Algorithm Class: " << config.getAlgoClass() << endl;

    return 0;
}

