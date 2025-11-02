#include <stdio.h>
#include <stdlib.h>

// --- HuffmanNode Structure ---
typedef struct HuffmanNode{
     char data;
     int freq;
     struct HuffmanNode *left,*right;
}HuffmanNode;

HuffmanNode* newNode(char data,int freq) {
    HuffmanNode* temp=(HuffmanNode*)malloc(sizeof(HuffmanNode));
    temp->data=data;
    temp->freq=freq;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

int getMin(HuffmanNode* list[], int size) {
    int min_idx = -1; 
    
    for(int i = 0; i < size; i++) {
        if(list[i] != NULL) {
            min_idx = i;
            break;
        }
    }
    
    if (min_idx == -1) return -1; 
    
    for(int i = 0; i < size; i++) {
       if (list[i] != NULL && list[i]->freq < list[min_idx]->freq) {
             min_idx = i;
         }
    }
    return min_idx;
}

HuffmanNode* buildHuffmanTree(char arr[],int freq[],int size) {
    HuffmanNode** list = (HuffmanNode**)malloc(size * sizeof(HuffmanNode*));
    for(int i = 0; i < size; i++) {
        list[i] = newNode(arr[i], freq[i]);
    }
    
    int merges = size - 1;
    while(merges > 0) {
        int idx1 = getMin(list, size);
        HuffmanNode* left = list[idx1];
        list[idx1] = NULL;
        
        int idx2 = getMin(list, size);
        HuffmanNode* right = list[idx2];
        list[idx2] = NULL;
        
        HuffmanNode* top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        
        for(int i = 0; i < size; i++) {
            if(list[i] == NULL) {
                list[i] = top;
                break;
            }
        }
        merges--;
    }
    
    HuffmanNode* root = NULL;
    for(int i = 0; i < size; i++) {
        if(list[i] != NULL) {
            root = list[i];
            break;
        }
    }
    return root;
}

void printCodes(HuffmanNode* root, char code[], int top, FILE *outFile) {
    if(!root) return;
    
    if(root->left) {
        code[top] = '0';
        printCodes(root->left, code, top + 1, outFile);
    }
    if(root->right) {
        code[top] = '1';
        printCodes(root->right, code, top + 1, outFile);
    }
    if(!root->left && !root->right) {
        code[top] = '\0';
        fprintf(outFile, "%c: %s\n", root->data, code);
    }
}

int main() {
    FILE *inFile = fopen("inputh.txt", "r");
    FILE *outFile = fopen("outputh.txt", "w");
    
    if (inFile == NULL) {
        fprintf(stderr, "Error: Could not open 'input.txt'. Please ensure the file exists.\n");
        if (outFile) fclose(outFile);
        return 1;
    }
    if (outFile == NULL) {
        fprintf(stderr, "Error: Could not open 'output.txt' for writing.\n");
        fclose(inFile);
        return 1;
    }

    int size;
    printf("Enter size: ");
    scanf("%d",&size);
   
    char *arr = (char*)malloc(size * sizeof(char));
    int *freq = (int*)malloc(size * sizeof(int));
    

    for (int i = 0; i < size; i++) {

        if (fscanf(inFile, " %c %d", &arr[i], &freq[i]) != 2) { 
            fprintf(stderr, "Error reading data for item %d from file. Check file format.\n", i + 1);
            fclose(inFile); fclose(outFile); return 1;
        }
    }
    printf("Successfully read %d items from input.txt.\n", size);
    fclose(inFile);

    
    HuffmanNode* root = buildHuffmanTree(arr, freq, size);

    fprintf(outFile, "Generated Huffman Codes for %d characters:\n", size);
    char code[size]; 
    printCodes(root, code, 0, outFile);

    printf("Huffman codes successfully generated and saved to output.txt\n");

    fclose(outFile);
    return 0;
}
