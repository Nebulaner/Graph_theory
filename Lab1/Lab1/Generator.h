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

public:
    void generateGraph(int n);
    void print();
    void eccentricities();
};

class matrix
{
private:
    int vertices;
    vector<vector<int>> weightMatrix;

public:
    void genWeightMatrix(int numEdges);
    void printWM();
    void shimbel();

    void findRoutes(int start, int end);
};