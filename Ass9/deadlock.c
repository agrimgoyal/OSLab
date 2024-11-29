#include <stdio.h>
#include <stdlib.h>

#define N 4  // Number of vertices in the graph

void addEdge(int graph[N][N], int u, int v) {
    graph[u][v] = 1;
}

void printGraph(int graph[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int graph[N][N] = {0}; // Adjacency matrix

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0); // Creating a cycle which needs to be avoided

    printGraph(graph);

    return 0;
}
