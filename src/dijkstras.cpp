#include "dijkstras.h"
#include <algorithm>

// Function to compute the shortest distances from the start node to all other nodes using Dijkstra's algorithm
vector<int> dijkstra_shortest_path(const Graph& graph, int start_node, vector<int>& predecessors) {
    int num_vertices = graph.numVertices;
    vector<int> distances(num_vertices, INF); // Initialize all distances to infinity
    predecessors.assign(num_vertices, -1); // Initialize all predecessors to -1
    vector<bool> is_visited(num_vertices, false); // Track visited nodes
    
    // Min-heap priority queue to select the node with the smallest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

    distances[start_node] = 0; // Distance to the start node is zero
    min_heap.push({0, start_node}); // Push the start node into the heap

    while (!min_heap.empty()) {
        int current_node = min_heap.top().second; // Select the node with the smallest distance
        min_heap.pop();

        if (is_visited[current_node]) // Skip if already visited
            continue;

        is_visited[current_node] = true; // Mark the current node as visited

        // Explore all adjacent edges
        for (const Edge& edge : graph[current_node]) {
            int neighbor = edge.dst; // Neighboring node
            int edge_weight = edge.weight; // Weight of the edge to the neighbor

            // Update the distance if a shorter path is found
            if (!is_visited[neighbor] && distances[current_node] + edge_weight < distances[neighbor]) {
                distances[neighbor] = distances[current_node] + edge_weight; // Update distance
                predecessors[neighbor] = current_node; // Update predecessor
                min_heap.push({distances[neighbor], neighbor}); // Push the updated node into the heap
            }
        }
    }

    return distances; // Return the computed shortest distances
}

// Function to extract the shortest path from the start node to the destination node
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& predecessors, int destination) {
    vector<int> path;
    
    // Trace the path from destination to start using the predecessors
    for (int current = destination; current != -1; current = predecessors[current]) {
        path.push_back(current);
    }

    reverse(path.begin(), path.end()); // Reverse to get the path from start to destination
    return path; // Return the extracted path
}

// Function to print the computed path and its total cost
void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) { // If no path exists
        cout << "No path available" << endl;
    } else if (path.size() == 1) { // If the path contains only one node, it's invalid
        cout << "Path not found" << endl;
    } else {
        // Print the path
        for (size_t index = 0; index < path.size(); ++index) {
            cout << path[index];
            if (index < path.size() - 1) // Avoid extra space at the end
                cout << " ";
        }
        // Print the total cost of the path
        cout << "\nTotal cost is " << total_cost << "\n";
    }
}
