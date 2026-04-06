#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <set>
#include <queue>

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
    graph(int t);

    void print();
    
    void eccentricities();
};

