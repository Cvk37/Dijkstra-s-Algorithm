#include <limits.h>
#include <iostream>
#include <vector>
#define V 5

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int parent[], int src, int dest) {
    std::cout << "Shortest Path from " << src << " to " << dest << ":\n";
    std::vector<int> path;
    int current = dest;

    while (current != src) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(src);

    std::cout << "Path: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i];
        if (i > 0) std::cout << " -> ";
    }

    std::cout << "\nCost: " << dist[dest] << "\n";
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    printSolution(dist, parent, src, dest);
}

int main() {
    int graph[V][V] = {
       {0, 3, 0, 0, 0},
       {3, 0, 4, 0, 0},
       {0, 4, 0, 5, 0},
       {0, 0, 5, 0, 6},
       {0, 0, 0, 6, 0}
    };

    int src, dest;

    // Get valid starting node
    do {
        std::cout << "Enter the starting node (0 to " << V - 1 << "): ";
        std::cin >> src;

        if (src < 0 || src >= V) {
            std::cout << "Invalid input. Please enter a number within the specified range.\n";
        }
    } while (src < 0 || src >= V);

    // Get valid ending node
    do {
        std::cout << "Enter the ending node (0 to " << V - 1 << "): ";
        std::cin >> dest;

        if (dest < 0 || dest >= V) {
            std::cout << "Invalid input. Please enter a number within the specified range.\n";
        }
    } while (dest < 0 || dest >= V);

    dijkstra(graph, src, dest);

    return 0;
}
