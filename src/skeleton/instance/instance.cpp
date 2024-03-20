//
// Created by Loïc Bermudez on 18/03/2024.
//

#include "instance.h"


Instance::Instance(){}

Instance::~Instance(){}

long int Instance::getPSize(){
    return PSize;
}

long int Instance::getSeed(){
    return Seed;
}

void Instance::allocateMatrix(){
    // resize the columns length
    CostMat.resize(PSize);

    // resize the rows length
    for(int i = 0; i<PSize; i++){
        CostMat[i].resize(PSize);
    }
}



long long int Instance::computeCost(vector<long> &s) {
    int h, k;
    long long int sum = 0;

    for(sum=0,h=0; h<PSize;h++)
    for(k=h+1; k<PSize; k++)
        sum += CostMat[s[h]][s[k]];
    return (sum);
}

long long int Instance::computeAttractiveness(long step, long row) {
    long int i;
    long long int sum;

    for(sum=0,i=step+1; i<PSize; i++)
        sum += CostMat[row][i];

    return sum;
}


void Instance::readInstance(const char *filename){

    ifstream file;
    long int i, j;
    string str;
    long int val;

    file.open(filename);

    if(!file.is_open()){
        perror("readInstance");
        cerr << "readInstance: Error on reading instance." << endl;
        exit(1);
    }

    file >> PSize;
    allocateMatrix();

    for(i=0; i<PSize; ++i){
        for(j=0; j<PSize; ++j){
            file >> val;


            CostMat[i][j] = val;
        }
    }

    file.close();

    Seed = (long int) 0;
    for (i=0; i < PSize; ++i)
        for (j=0; j < PSize; ++j)
            Seed += (long int) CostMat[i][j];

    cout << "Seed used to initialize RNG: " << Seed << endl;
    cout << endl;
    cout << endl;

}









