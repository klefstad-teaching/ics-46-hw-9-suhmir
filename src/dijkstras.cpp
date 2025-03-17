#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& graph, int start_node, vector<int>& predecessors) {
    int num_nodes = graph.numVertices;
    vector<int> distances(num_nodes, INF);
    predecessors.assign(num_nodes, -1);
    vector<bool> is_visited(num_nodes, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    
    distances[start_node] = 0;
    min_heap.push({0, start_node});

    while (!min_heap.empty()) {
        int current_node = min_heap.top().second;
        min_heap.pop();
        
        if (is_visited[current_node]) 
            continue;
        
        is_visited[current_node] = true;

        for (const Edge& edge : graph[current_node]) {
            int neighbor_node = edge.dst;
            int edge_weight = edge.weight;

            if (!is_visited[neighbor_node] && distances[current_node] + edge_weight < distances[neighbor_node]) {
                distances[neighbor_node] = distances[current_node] + edge_weight;
                predecessors[neighbor_node] = current_node;
                min_heap.push({distances[neighbor_node], neighbor_node});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& predecessors, int end_node) {
    vector<int> path;
    int node = end_node;
    while (node != -1) {
        path.push_back(node);
        node = predecessors[node];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.size() == 1) {
        cout << "Path not found" << endl;
        return;
    }
    
    size_t index = 0;
    while (index < path.size()) {
        cout << path[index];
        if (index < path.size() - 1)
            cout << " ";
        index++;
    }

    cout << "\nTotal cost is " << total_cost << "\n";
}
