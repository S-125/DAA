#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int main() {
    FILE *fp;
    int arr[MAX_SIZE];
    int n, i, j;

    
    printf("Enter number of integers (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Invalid input for n.\n");
        return 1;
    }

    
    fp = fopen("Q3.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    
    for (i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("Failed to read integer %d from file.\n", i+1);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    
    int visited[MAX_SIZE] = {0};
    int total_duplicates = 0;
   printf("\n Content of Array:      ");
   for(i=0;i<n;i++){
   	printf("%d\t", arr[i]);
   }
   printf("\n");
    for (i = 0; i < n; i++) {
        if (visited[i]) continue;
        int count = 1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;  
            }
        }
        if (count > 1) {
            total_duplicates += (count - 1);
        }
    }

   
    int max_count = 0;
    int most_repeated = arr[0];
    for (i = 0; i < n; i++) {
        if (visited[i]) continue;
        int count = 1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            most_repeated = arr[i];
        }
    }

    
    printf("Total number of duplicate elements: %d\n", total_duplicates);
    printf("Most repeating element is %d with %d occurrences\n", most_repeated, max_count);

    return 0;
}

