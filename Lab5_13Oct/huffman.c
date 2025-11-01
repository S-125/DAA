#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MinHeapNode {char data; unsigned freq; struct MinHeapNode *left, *right;} HuffmanNode;
typedef struct MinHeap {unsigned size; unsigned capacity; HuffmanNode** array;} MinHeap;

HuffmanNode* newNode(char data, unsigned freq) {
    HuffmanNode* temp = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0; minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

void swapNode(HuffmanNode** a, HuffmanNode** b) {HuffmanNode* t = *a; *a = *b; *b = t;}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) smallest = right;
    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

void buildMinHeap(MinHeap* minHeap) {
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i) minHeapify(minHeap, i);
}

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    minHeap->size = size;
    for (int i = 0; i < size; ++i) minHeap->array[i] = newNode(data[i], freq[i]);
    buildMinHeap(minHeap);
    return minHeap;
}

HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printInOrder(HuffmanNode* root) {
    if (root) {
        printInOrder(root->left);
        if (root->data != '$') printf("%c ", root->data);
        printInOrder(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    if (scanf("%d", &n) != 1 || n <= 0) {fprintf(stderr, "Invalid number of alphabets.\n"); return 1;}
    
    char* a = (char*)malloc(n * sizeof(char));
    int* f = (int*)malloc(n * sizeof(int));
    
    if (!a || !f) {fprintf(stderr, "Memory allocation failed.\n"); free(a); free(f); return 1;}

    printf("Enter the alphabets :\n");
    int c; while ((c = getchar()) != '\n' && c != EOF); 
    for (int i = 0; i < n; i++) {
        if (scanf(" %c", &a[i]) != 1) {
            fprintf(stderr, "Failed to read alphabet.\n"); free(a); free(f); return 1;
        }
    }

    printf("Enter its frequencies :\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &f[i]) != 1) {
            fprintf(stderr, "Failed to read frequency.\n"); free(a); free(f); return 1;
        }
    }

    HuffmanNode* root = buildHuffmanTree(a, f, n);
    printf("\nOutput:\nIn-order traversal of the tree (Huffman): ");
    printInOrder(root);
    printf("\n");

    free(a);
    free(f);
    return 0;
}

