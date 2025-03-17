#include "dijkstras.h"
#include <algorithm>

// Compute the shortest paths using Dijkstra's algorithm.
// 'graph' is the input graph, 'startNode' is the source vertex, and 'prevNodes' will store each node's predecessor.
vector<int> compute_dijkstra_shortest_path(const Graph& graph, int startNode, vector<int>& prevNodes) {
    int numNodes = graph.numVertices;
    vector<int> distanceVector(numNodes, INF);  // Initialize distances to INF.
    prevNodes.assign(numNodes, -1);              // Initialize all predecessors to -1.
    vector<bool> processed(numNodes, false);     // Track whether a node has been finalized.
    
    // Min-heap (priority queue) storing pairs of (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    
    distanceVector[startNode] = 0;
    minHeap.push({0, startNode});

    while (!minHeap.empty()) {
        int currentNode = minHeap.top().second;
        minHeap.pop();
        
        // Skip if the node has already been processed.
        if (processed[currentNode])
            continue;
        processed[currentNode] = true;
        
        // Relaxation step for all adjacent edges.
        for (const Edge& edge : graph[currentNode]) {
            int neighborNode = edge.dst;
            int edgeWeight = edge.weight;
            if (!processed[neighborNode] && distanceVector[currentNode] + edgeWeight < distanceVector[neighborNode]) {
                distanceVector[neighborNode] = distanceVector[currentNode] + edgeWeight;
                prevNodes[neighborNode] = currentNode;
                minHeap.push({distanceVector[neighborNode], neighborNode});
            }
        }
    }
    return distanceVector;
}

// Reconstruct the shortest path from the source to 'targetNode' using the 'prevNodes' array.
vector<int> reconstruct_shortest_path(const vector<int>& distanceVector, const vector<int>& prevNodes, int targetNode) {
    vector<int> path;
    for (int node = targetNode; node != -1; node = prevNodes[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}

// Display the path and its total cost.
void display_path(const vector<int>& path, int totalCost) {
    if (path.size() == 1) {
        cout << "Path not found" << endl;
        return;
    }
    
    for (size_t idx = 0; idx < path.size(); ++idx) {
        cout << path[idx];
        if (idx < path.size() - 1)  // Print space between nodes, but not after the last one.
            cout << " ";
    }
    
    cout << "\nTotal cost is " << totalCost << "\n"; 
}
