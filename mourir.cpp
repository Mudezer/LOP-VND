//
// Created by Loïc Bermudez on 28/03/2024.
//

#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<int>> Matrix;
typedef vector<int> state;

int computeCost(Matrix matrix,vector<int> &s) {
    int h, k;
     int sum = 0;

    for(h=0; h<s.size();h++)
        for(k=h+1; k<s.size(); k++)
            sum += matrix[s[h]][s[k]];
    return (sum);
}

state insert(state s, int i, int j){

    int temp = s[i];
    s.erase(s.begin()+i);
    s.insert(s.begin()+j, temp);

    return s;

}

state transpose(state s, int i, int j){

    int temp = s[i];
    s[i] = s[i+1];
    s[i+1] = temp;

    return s;
}

state exchange(state s, int i, int j){

    long int temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    return s;
}

int computeDelta(Matrix matrix,state s, int i, int j){
    int delta = 0;

    for(int k = i; k<j; k++){
        delta += matrix[s[j]][s[k]] - matrix[s[k]][s[j]];
    }
    for(int l = i+1; l<j; l++){
        delta += matrix[s[l]][s[i]] - matrix[s[i]][s[l]];
    }



    return delta;
}

int computeDeltaInsert(Matrix CostMat, vector<int> &s, int i, int j){
    int delta = 0;
    int k;
    if(i<j){
        for(k = i+1; k<=j; k++){
            delta += CostMat[s[k]][s[i]] - CostMat[s[i]][s[k]];
//            delta += CostMat[s[k]][s[j]] - CostMat[s[j]][s[k]];
        }
    }
    else if(i>j){
        for(k=j;k<i;k++){
            delta += CostMat[s[i]][s[k]] - CostMat[s[k]][s[i]];
        }
    }

    return delta;
}

int computeDeltaTranspose(Matrix CostMat, vector<int> &s, int i, int j) {
    int delta = 0;

    // i is always smaller than j as we transpose i and i+1
    // no use to do it in the reverse order as candidate is the same
    delta = CostMat[s[i+1]][s[i]] - CostMat[s[i]][s[i+1]];

    return delta;

}

void printMatrix(Matrix matrix, state s){

    cout << "State: ";
    for(int i=0; i<s.size(); i++){
        cout << s[i] << " ";
    }

    cout << endl;
    cout << "Matrix: " << endl;
    for(int i = 0; i <s.size(); i++){
        for(int j = 0; j<s.size(); j++){
            cout << matrix[s[i]][s[j]] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}


int main(){

    vector<vector<int>> matrix = {{1,2,3,4,5,6},
                                   {7,8,9,10,11,12},
                                   {13,14,15,16,17,18},
                                   {19,20,21,22,23,24},
                                   {25,26,27,28,29,30},
                                   {31,32,33,34,35,36}};

//    vector<int> s = {0,1,2,3,4,5};
//
//    int cost = computeCost(matrix, s);
//
//    cout << "Cost: " << cost << endl;

    //EXCHANGE

    /*state new_s = exchange(s, 0, 3);
    int cost1 = computeCost(matrix, new_s);
    int delta1 = computeDelta(matrix, s, 0, 3);

    cout << "first exchange " << endl;
    cout << "Cost 1 : " << cost1 << endl;
    cout << "Delta 1 : " << delta1 << endl;
    cout << " initial cost + delta1:" << cost + delta1 << endl;

    //second exchange
    state next_State = exchange(new_s, 1, 4);
    int cost2 = computeCost(matrix, next_State);
    int delta2 = computeDelta(matrix, new_s, 1, 4);

    cout << "second exchange " << endl;
    cout << "Cost 2 : " << cost2 << endl;
    cout << "Delta 2 : " << delta2 << endl;
    cout << " cost1 + delta2: " << cost1 + delta2 << endl;
    cout << "initial cost + delta2: " << cost + delta2 << endl;*/

    //INSERT

    /*state new_s = insert(s, 0, 3);
    int cost1 = computeCost(matrix, new_s);
    int delta1 = computeDeltaInsert(matrix, s, 0, 3);

//    printMatrix(matrix, new_s);

    cout << "first insert " << endl;
    cout << "Cost 1 : " << cost1 << endl;
    cout << "Delta 1 : " << delta1 << endl;
    cout << " initial cost + delta1:" << cost + delta1 << endl;

    //second insert
    state next_State = insert(new_s, 1, 4);
    int cost2 = computeCost(matrix, next_State);
    int delta2 = computeDeltaInsert(matrix, new_s, 1, 4);

    cout << "second insert " << endl;
    cout << "Cost 2 : " << cost2 << endl;
    cout << "Delta 2 : " << delta2 << endl;
    cout << " cost1 + delta2: " << cost1 + delta2 << endl;
    cout << "initial cost + delta2: " << cost + delta2 << endl;*/

    //TRANSPOSE

    vector<int> s = {0,1,2,3,4,5};

    int cost = computeCost(matrix, s);

    cout << "Cost: " << cost << endl;

    state new_s = transpose(s, 4, 3);
    int cost1 = computeCost(matrix, new_s);
    int delta1 = computeDeltaTranspose(matrix, s, 4, 3);

//    printMatrix(matrix, new_s);

    cout << "first transpose " << endl;
    cout << "Cost 1 : " << cost1 << endl;
    cout << "Delta 1 : " << delta1 << endl;
    cout << " initial cost + delta1:" << cost + delta1 << endl;



    return 0;
}