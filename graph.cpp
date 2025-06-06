#include "Graph.h"
#include <queue>
#include <algorithm>

Graph::Graph(int numCities) : adjacencyMatrix(numCities, vector<int>(numCities, 0)) {}

void Graph::addCity(const string& city) {
    cities.push_back(city);
}

void Graph::addRoute(int from, int to) {
    if (from >= 0 && from < cities.size() && to >= 0 && to < cities.size()) {
        adjacencyMatrix[from][to] = 1;
        adjacencyMatrix[to][from] = 1;
    }
    else {
        cout << "Invalid city indices!" << endl;
    }
}

void Graph::displayConnections() const {
    cout << "City Connections:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        cout << cities[i] << ": ";
        for (size_t j = 0; j < cities.size(); ++j) {
            if (adjacencyMatrix[i][j] == 1)
                cout << cities[j] << " ";
        }
        cout << endl;
    }
}

int Graph::findCityIndex(const string& city) const {
    for (size_t i = 0; i < cities.size(); ++i) {
        if (cities[i] == city)
            return i;
    }
    return -1; // City not found
}

vector<string> Graph::findRoute(const string& start, const string& end) const {
    int startIdx = findCityIndex(start);
    int endIdx = findCityIndex(end);

    if (startIdx == -1 || endIdx == -1) {
        return vector<string>();
    }

    // Keep track of visited cities and their parents
    vector<bool> visited(cities.size(), false);
    vector<int> parent(cities.size(), -1);
    queue<int> q;

    // Start BFS
    q.push(startIdx);
    visited[startIdx] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == endIdx) {
            // Reconstruct path
            vector<string> path;
            int at = endIdx;
            while (at != -1) {
                path.push_back(cities[at]);
                at = parent[at];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Check all adjacent cities
        for (size_t i = 0; i < cities.size(); i++) {
            if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = current;
                q.push(i);
            }
        }
    }

    return vector<string>(); // No path found
}
