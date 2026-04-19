#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include <string>

using namespace std;
int Distribution(int max);

class graph
{
private:
    int vertices;
    vector<pair<int, int>> edges;
    vector<int> degrees;
    vector<vector<int>> adj;

    vector<vector<int>> weightMatrix;

public:
    graph(int t);
    void print();

    void eccentricities();

    void genWeightMatrix(int minWeight, int maxWeight);
    void shimbel();

    void findRoutes();
};

