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

    string output_path = "results/iter/res.csv";
    ofstream file;
    file.open(output_path, ios::app);
    file << "TESTING\n";
    file.close();


    return 0;
}