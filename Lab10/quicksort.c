#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 100 
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
     
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


int randomPartition(int arr[], int low, int high) {
   
    static int seed_initialized = 0;
    if (!seed_initialized) {
        srand(time(NULL)); 
        seed_initialized = 1;
    }
    int pivot_index = low + rand() % (high - low + 1);
    swap(&arr[pivot_index], &arr[high]);
    return partition(arr, low, high);
}


void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
       
        int pi = randomPartition(arr, low, high);

        
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5, 3, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array (example): ");
    printArray(arr, n);

    randomizedQuickSort(arr, 0, n - 1);

    printf("Sorted array (example): ");
    printArray(arr, n);
    
    // Example with dynamic user input
    printf("\n--- User Input Demonstration ---\n");
    int user_arr[MAX_LENGTH];
    int user_n;
    
    printf("Enter the number of elements (max %d): ", MAX_LENGTH);
    if (scanf("%d", &user_n) != 1 || user_n <= 0 || user_n > MAX_LENGTH) {
        fprintf(stderr, "Invalid input size. Using default size 10.\n");
        return 1;
    }

    printf("Enter %d integers:\n", user_n);
    for (int i = 0; i < user_n; i++) {
        if (scanf("%d", &user_arr[i]) != 1) {
            fprintf(stderr, "Invalid integer input. Exiting.\n");
            return 1;
        }
    }
    
    printf("\nSorting array...\n");
    randomizedQuickSort(user_arr, 0, user_n - 1);
    
    printf("Sorted array: ");
    printArray(user_arr, user_n);

    return 0;
}

