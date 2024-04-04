//
// Created by Loïc Bermudez on 03/04/2024.
//

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

//    string output_path = "results/iter/res.csv";
//    ofstream file;
//    file.open(output_path, ios::app);
//    file << "TESTING\n";
//    file.close();

    int a = 3494;
    int bestcost = 3494;
    int delta = -40;

    if((a+delta) > bestcost){
        cout << "YES\n";
    }else
    {
        cout << "NO\n";
    }


    return 0;
}