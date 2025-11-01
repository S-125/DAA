#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 10 
#define INF INT_MAX   

int V_count = 0;

int extractMin(int key[], bool inMST[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V_count; v++) {
        if (inMST[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}


void printMSTMatrix(int parent[], int graph[MAX_VERTICES][MAX_VERTICES]) {
    printf("\nCost Adjacency Matrix of the Minimum Spanning Tree (T):\n");
    int mst_matrix[MAX_VERTICES][MAX_VERTICES] = {0};
    long long total_cost = 0;

    
    for (int i = 0; i < V_count; i++) {
        if (parent[i] != -1) { 
          
            int u = parent[i];
            int v = i;
            int weight = graph[u][v];

           
            mst_matrix[u][v] = weight;
            mst_matrix[v][u] = weight;
            total_cost += weight;
        }
    }

    
    for (int i = 0; i < V_count; i++) {
        for (int j = 0; j < V_count; j++) {
            printf("%d%s", mst_matrix[i][j], (j == V_count - 1) ? "" : " ");
        }
        printf("\n");
    }

    
    printf("Total Weight of the Spanning Tree: %lld\n", total_cost);
}


void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int start_vertex) {
    
    int parent[MAX_VERTICES]; 
    
    
    int key[MAX_VERTICES];
    
    
    bool inMST[MAX_VERTICES]; 

    
    for (int i = 0; i < V_count; i++) {
        key[i] = INF;
        inMST[i] = false;
        parent[i] = -1; 
    }

    
    int start_index = start_vertex - 1;
    key[start_index] = 0; 

    
    for (int count = 0; count < V_count; count++) {
        
        int u = extractMin(key, inMST);


        if (u == -1) {
            fprintf(stderr, "\nError: Graph may be disconnected.\n");
            return;
        }

        
        inMST[u] = true;

     
        for (int v = 0; v < V_count; v++) {
            int weight = graph[u][v];

           
            if (weight > 0 && inMST[v] == false && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    
    printMSTMatrix(parent, graph);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    char filename[] = "inUnAdjMat.dat";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s. Please ensure the file exists.\n", filename);
        return 1;
    }

    int n, start_vertex;
    
    
    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        fprintf(stderr, "Invalid number of vertices. Max allowed is %d.\n", MAX_VERTICES);
        fclose(file);
        return 1;
    }
    V_count = n; 

    printf("Enter the Starting Vertex: ");
    if (scanf("%d", &start_vertex) != 1 || start_vertex < 1 || start_vertex > n) {
        fprintf(stderr, "Invalid starting vertex. Must be between 1 and %d.\n", n);
        fclose(file);
        return 1;
    }
    
    
    printf("\nReading graph data from '%s'...\n", filename);
    bool read_success = true;
    for (int i = 0; i < V_count; i++) {
        for (int j = 0; j < V_count; j++) {
            if (fscanf(file, "%d", &graph[i][j]) != 1) {
                fprintf(stderr, "Error: Failed to read element at row %d, column %d from file.\n", i+1, j+1);
                read_success = false;
                break;
            }
        }
        if (!read_success) break;
    }
    fclose(file);

    if (!read_success) return 1;
    printf("\nApplying Prim's Algorithm (Starting from Vertex %d)...\n", start_vertex);
    primMST(graph, start_vertex);

    return 0;
}

