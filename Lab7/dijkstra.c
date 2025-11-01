#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 10
#define INF 99999


int V_count = 0;


int extractMin(int dist[], bool processed[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V_count; v++) {
        if (processed[v] == false && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}


void printPath(int parent[], int j, int source) {
    if (parent[j] == -1) {
        return;
    }

    printPath(parent, parent[j], source);
    printf("->%d", j + 1);
}


void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];
    bool processed[MAX_VERTICES];

    int start_index = source - 1;

    for (int i = 0; i < V_count; i++) {
        dist[i] = INF;
        parent[i] = -1;
        processed[i] = false;
    }

    dist[start_index] = 0;

    for (int count = 0; count < V_count; count++) {
        int u = extractMin(dist, processed);

        if (u == -1) break;

        processed[u] = true;

        for (int v = 0; v < V_count; v++) {
            int weight = graph[u][v];

            if (!processed[v] && weight < INF && dist[u] != INF && (dist[u] + weight < dist[v])) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    printf("\nOutput:\n");
    printf("Source\tDestination\tCost\tPath\n");

    for (int i = 0; i < V_count; i++) {
        int destination = i + 1;

        printf("%d\t%d\t\t", source, destination);

        if (dist[i] == INF) {
            printf("INF\t-\n");
        } else {
            printf("%d\t", dist[i]);

            if (i == start_index) {
                printf("-\n");
            } else {
                printf("%d", source);
                printPath(parent, i, source);
                printf("\n");
            }
        }
    }
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    char filename[] = "inDiAdjMat1.dat";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s. Please create the file with the graph matrix.\n", filename);
        return 1;
    }

    int n, source_vertex;

    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        fprintf(stderr, "Invalid number of vertices. Max allowed is %d.\n", MAX_VERTICES);
        fclose(file);
        return 1;
    }
    V_count = n;

    printf("Enter the Source Vertex: ");
    if (scanf("%d", &source_vertex) != 1 || source_vertex < 1 || source_vertex > n) {
        fprintf(stderr, "Invalid source vertex. Must be between 1 and %d.\n", n);
        fclose(file);
        return 1;
    }

    while (getchar() != '\n');


    printf("\nReading graph data from '%s'...\n", filename);
    bool read_success = true;
    for (int i = 0; i < V_count; i++) {
        for (int j = 0; j < V_count; j++) {
            int weight;
            if (fscanf(file, "%d", &weight) != 1) {
                fprintf(stderr, "Error: Failed to read element at row %d, column %d from file.\n", i+1, j+1);
                read_success = false;
                break;
            }

            if (weight == 0 && i != j) {
                graph[i][j] = INF;
            } else {
                graph[i][j] = weight;
            }
        }
        if (!read_success) break;
    }
    fclose(file);

    if (!read_success) return 1;


    printf("\nApplying Dijkstra's Algorithm (Starting from Vertex %d)....\n", source_vertex);
    dijkstra(graph, source_vertex);

    return 0;
}

