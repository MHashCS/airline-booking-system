#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    vector<string> cities;

public:
    Graph(int numCities);
    void addCity(const string& city);
    void addRoute(int from, int to);
    void displayConnections() const;
    int findCityIndex(const string& city) const;
    vector<string> findRoute(const string& start, const string& end) const;
};

#endif
