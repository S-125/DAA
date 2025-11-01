#include <stdio.h>
#include <limits.h>

#define V 5 
#define INF 99999 
int dist[V][V]; 
int path[V][V]; 


int readGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening input file inDiAdjMat2.dat");
        return 1;
    }

    int weight;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (fscanf(file, "%d", &weight) != 1) {
                fprintf(stderr, "Error reading matrix content from file.\n");
                fclose(file);
                return 1;
            }

            if (i == j) {
              
                dist[i][j] = 0;
            } else if (weight == 0) {
               
                dist[i][j] = INF;
            } else {
              
                dist[i][j] = weight;
            }

            if (i != j && dist[i][j] != INF) {
                path[i][j] = j + 1; 
            } else {
                path[i][j] = 0; 
            }
        }
    }
    fclose(file);
    return 0;
}


void floydWarshall() {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
              
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                  
                    path[i][j] = path[i][k];
                }
            }
        }
    }
}
void printDistMatrix() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("%-3s ", "INF");
            } else {
                printf("%-3d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}


void printPath(int u, int v) {
    
    int i = u - 1;
    int j = v - 1;

   
    if (dist[i][j] == INF) {
        printf("No path exists.\n");
        return;
    }

    
    printf("%d", u);

   
    int current = u;
    
    while (current != v) {
        int next_node = path[current - 1][j];
        
      
        if (next_node == 0 || next_node == current) {
            
             if (current != v) {
                next_node = v; 
             } else {
                break;
             }
        }

        printf("-->%d", next_node);
        current = next_node;
    }
}

int main() {
    int source_vertex, destination_vertex;

    printf("Number of Vertices: %d\n", V);

    // 1. Read Graph from file
    if (readGraphFromFile("inDiAdjMat2.dat")) {
        return 1;
    }

    // 2. Execute Floyd-Warshall algorithm
    floydWarshall();
    
    // Check for negative cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("\nGraph contains a negative cycle! Results may be invalid.\n");
            // Still proceed to show the resulting distance matrix
        }
    }

    // 3. Print the shortest-path weight matrix
    printf("\nShortest-path Weight Matrix:\n");
    printf("---------------------------\n");
    printDistMatrix();
    
    // 4. Get the specific pair for path tracing
    printf("\nEnter the source and destination vertex (u v): ");
    if (scanf("%d %d", &source_vertex, &destination_vertex) != 2 || 
        source_vertex < 1 || source_vertex > V || 
        destination_vertex < 1 || destination_vertex > V) {
        fprintf(stderr, "Invalid vertex input. Must be between 1 and %d.\n", V);
        return 1;
    }

    // 5. Display the shortest path and weight
    printf("\nShortest Path from vertex %d to vertex %d: ", source_vertex, destination_vertex);
    printPath(source_vertex, destination_vertex);
    printf("\nPath weight: %d\n", dist[source_vertex - 1][destination_vertex - 1]);

    return 0;
}

