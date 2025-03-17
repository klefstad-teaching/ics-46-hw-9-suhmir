#include "dijkstras.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int vertices = G.numVertices;
    vector<int> dist_list(vertices, INF);
    previous.assign(vertices, -1);
    vector<bool> visited(vertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist_list[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && dist_list[u] + weight < dist_list[v]) {
                dist_list[v] = dist_list[u] + weight;
                previous[v] = u;
                pq.push({dist_list[v], v});
            }
        }
    }
    return dist_list;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

// Modified print_path: now prints a trailing space after every element.
void print_path(const vector<int>& path, int total) {
    if (path.size() == 1) {
        cout << "Path not found" << endl;
        return;
    }
    
    // Print each number followed by a space (even after the last element).
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    
    cout << "\nTotal cost is " << total << "\n"; 
}
