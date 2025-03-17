#include "dijkstras.h"
#include <algorithm>

std::vector<int> dijkstra_shortest_path(const Graph& graph, int source, std::vector<int>& previousNodes) {
    int vertexCount = graph.numVertices;
    std::vector<int> minDistances(vertexCount, INF);
    previousNodes.assign(vertexCount, -1);
    std::vector<bool> visited(vertexCount, false);

    using DistanceVertexPair = std::pair<int, int>;  // (distance, vertex)
    std::priority_queue<DistanceVertexPair, std::vector<DistanceVertexPair>, std::greater<DistanceVertexPair>> priorityQueue;

    minDistances[source] = 0;
    priorityQueue.push({0, source});

    while (!priorityQueue.empty()) {
        int currentVertex = priorityQueue.top().second;
        priorityQueue.pop();

        if (visited[currentVertex]) continue;
        visited[currentVertex] = true;

        for (const Edge& edge : graph[currentVertex]) {
            int neighbor = edge.dst;
            int weight = edge.weight;

            if (!visited[neighbor] && minDistances[currentVertex] + weight < minDistances[neighbor]) {
                minDistances[neighbor] = minDistances[currentVertex] + weight;
                previousNodes[neighbor] = currentVertex;
                priorityQueue.push({minDistances[neighbor], neighbor});
            }
        }
    }

    return minDistances;
}

std::vector<int> extract_shortest_path(const std::vector<int>& distances, const std::vector<int>& previousNodes, int destination) {
    std::vector<int> path;
    for (int current = destination; current != -1; current = previousNodes[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void print_path(const std::vector<int>& path, int totalCost) {
    std::size_t index = 0;
    while (index < path.size()) {
        std::cout << path[index];
        if (index + 1 < path.size()) {
            std::cout << " ";
        } else {
            std::cout << "\n";
        }
        ++index;
    }
    std::cout << "Total cost is " << totalCost << "\n";
}

