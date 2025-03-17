#include "dijkstras.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// Computes the shortest paths from a source vertex to all other vertices in the graph
// using Dijkstra's algorithm. 'previous' will store the predecessor of each vertex in the shortest path tree.
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    // Number of vertices in the graph.
    int vertices = G.numVertices;
    // Initialize distances to each vertex as INF (a defined constant) and set predecessors to -1.
    vector<int> dist_list(vertices, INF);
    previous.assign(vertices, -1);
    // Create a vector to track whether a vertex's minimum distance is finalized.
    vector<bool> visited(vertices, false);
    // Priority queue (min-heap) to efficiently extract the vertex with the minimum tentative distance.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // The distance from the source to itself is always 0.
    dist_list[source] = 0;
    // Insert the source vertex into the queue with a distance of 0.
    pq.push({0, source});
    
    // Process the queue until it's empty.
    while (!pq.empty()) {
        // Extract the vertex with the smallest tentative distance.
        int u = pq.top().second;
        pq.pop();
        // If this vertex has already been finalized, skip it.
        if (visited[u])
            continue;
        // Mark vertex u as visited.
        visited[u] = true;
        
        // Iterate over all the edges outgoing from vertex u.
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;      // Destination vertex of the edge.
            int weight = neighbor.weight; // Weight of the edge.
            // If vertex v hasn't been processed and we find a shorter path to it through u:
            if (!visited[v] && dist_list[u] + weight < dist_list[v]) {
                // Update the shortest known distance to vertex v.
                dist_list[v] = dist_list[u] + weight;
                // Record u as the predecessor of v.
                previous[v] = u;
                // Insert the updated distance and vertex into the priority queue.
                pq.push({dist_list[v], v});
            }
        }
    }
    // Return the list of shortest distances from the source.
    return dist_list;
}

// Reconstructs the shortest path from the source to the specified destination using the 'previous' vector.
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    // Start from the destination and follow the predecessors back to the source.
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    // Reverse the path so that it starts at the source and ends at the destination.
    reverse(path.begin(), path.end());
    return path;
}

// Prints the shortest path and its total cost.
void print_path(const vector<int>& path, int total) {
    // If the path contains only one vertex, it's likely that no path was found.
    if (path.size() == 1) {
        cout << "Path not found" << endl;
        return;
    }
    
    // Print each vertex in the path.
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        // Print a space after each vertex except for the last one.
        if (i < path.size() - 1)
            cout << " ";
    }
    
    // Print the total cost of the path.
    cout << "\nTotal cost is " << total << "\n";
}
