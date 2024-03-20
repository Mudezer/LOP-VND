//
// Created by Loïc Bermudez on 18/03/2024.
//

#ifndef LOP_VND_INSTANCE_H
#define LOP_VND_INSTANCE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Instance{
    private:
        long int PSize;
        long int Seed;
        std::vector< std::vector <long int> > CostMat;

    public:
        Instance();
        ~Instance();

        long int getPSize();

        long int getSeed();

        void allocateMatrix();

        void readInstance(const char *filename);

        long long int computeCost(vector<long int> &s);
        long long int computeAttractiveness(long int step, long int row);


};


#endif //LOP_VND_INSTANCE_H
