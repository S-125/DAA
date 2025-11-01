#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_EDGES 1000

typedef struct {
    int u, v;
    int weight;
} Edge;

int parent[MAX_NODES + 1];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unionSets(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a != root_b) {
        parent[root_b] = root_a;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskalMST(Edge edges[], int num_nodes, int num_edges) {
    qsort(edges, num_edges, sizeof(Edge), compareEdges);
    for (int i = 1; i <= num_nodes; i++) {
        parent[i] = i;
    }

    long long total_cost = 0;
    int edges_in_mst = 0;

    printf("\nOutput:\nEdge\tCost\n");

    for (int i = 0; i < num_edges && edges_in_mst < num_nodes - 1; i++) {
        Edge current_edge = edges[i];
        if (find(current_edge.u) != find(current_edge.v)) {
            unionSets(current_edge.u, current_edge.v);
            printf("%d--%d\t%d\n", current_edge.u, current_edge.v, current_edge.weight);
            total_cost += current_edge.weight;
            edges_in_mst++;
        }
    }
    
    if (edges_in_mst == num_nodes - 1) {
        printf("Total Weight of the Spanning Tree: %lld\n", total_cost);
    } else {
        printf("A Minimum Spanning Forest was found (Graph may be disconnected).\n");
        printf("Total Weight of the edges selected: %lld\n", total_cost);
    }
}

int main() {
    int n, m;
    Edge edges[MAX_EDGES];

    printf("Enter the number of nodes (n) and edges (m) (e.g., 9 14):\n");
    if (scanf("%d %d", &n, &m) != 2 || n < 1 || m < 0 || n > MAX_NODES || m > MAX_EDGES) {
        fprintf(stderr, "Invalid input for number of nodes and edges.\n");
        return 1;
    }
    
    printf("Enter the edges (u v w):\n");
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight) != 3) {
            fprintf(stderr, "Error reading edge %d details.\n", i + 1);
            return 1;
        }
        if (edges[i].u < 1 || edges[i].u > n || edges[i].v < 1 || edges[i].v > n) {
            fprintf(stderr, "Node ID out of range [1, %d] for edge %d.\n", n, i + 1);
            return 1;
        }
    }

    kruskalMST(edges, n, m);
    return 0;
}

