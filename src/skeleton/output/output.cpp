//
// Created by Loïc Bermudez on 25/03/2024.
//

#include "output.h"

Output::Output(){}

Output::~Output(){}

void Output::setUp(string instanceNamed,
                   string algoClass,
                   string configuration,
                   long long int bestCost,
                   double elapsedTime) {
    this->instanceName = instanceNamed;
    this->algoClass = algoClass;
    this->configuration = configuration;
    this->bestCost = bestCost;
    this->elapsedTime = elapsedTime;

    findBestKnown(instanceNamed);
}

vector<string> Output::split(const string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void Output::findBestKnown(string instance_name){

    string path_to_bestKnowns = "assets/best_known/best_known.txt";

    ifstream file(path_to_bestKnowns);

    if(file.is_open()){
        string line;
        while(getline(file, line)){
            std::size_t found = line.find(instance_name);
            if (found != string::npos) {
                string afterKeyword = line.substr(found);
                vector<string> splitResults = split(afterKeyword, ' ');
                for (int i = 1; i < splitResults.size(); i++) {
                    if (!splitResults[i].empty()) {
                        this->bestKnown = splitResults[i];
                        break;
                    }
                }
                if (!bestKnown.empty()) {
                    break;
                }
            }
        }
    }
    else{
        this->bestCost = -1; // -1 means that the best known is not available
    }

}

void Output::printOutput(){

    cout << "Instance name: " << this->instanceName << endl;
    cout << "Algorithm class: " << this->algoClass << endl;
    cout << "Configuration: " << this->configuration << endl;
    cout << "Best known: " << this->bestKnown << endl;
    cout << "Best cost: " << this->bestCost << endl;
    cout << "Elapsed time: " << this->elapsedTime << endl;

    string path_to_output = "results/" + this->algoClass + "/" + "res_"+ this->algoClass + ".csv";
    cout << "Output file: " << path_to_output << endl;

//ios::out | ios::app
    ofstream file;
    file.open(path_to_output, ios::app);

    if(!file){
        cerr << "File could not be opened for writing." << endl;
    }


    file << this->instanceName << "," << this->configuration << "," << this->bestCost << "," << this->bestKnown << "," << this->elapsedTime << endl;

    file.close();


}