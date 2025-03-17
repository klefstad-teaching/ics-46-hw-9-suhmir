#include "dijkstras.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <graph_file>\n";
        return 1;
    }

    Graph graph;
    file_to_graph(argv[1], graph);

    std::vector<int> previousNodes;
    std::vector<int> shortestDistances = dijkstra_shortest_path(graph, 0, previousNodes);

    int currentVertex = 0;
    while (currentVertex < graph.numVertices) {
        std::vector<int> path = extract_shortest_path(shortestDistances, previousNodes, currentVertex);
        print_path(path, shortestDistances[currentVertex]);
        ++currentVertex;
    }

    return 0;
}

