#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;
    double amount_taken;
} ITEM;

void swap(ITEM* a, ITEM* b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(ITEM arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].profit_weight_ratio > arr[j + 1].profit_weight_ratio) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void fractional_knapsack(ITEM items[], int n, double capacity, FILE *outFile) {
    
    bubbleSort(items, n);

    double current_capacity = capacity;
    double max_profit = 0.0;

    
    for (int i = n - 1; i >= 0; i--) {
        ITEM* current_item = &items[i];
        double fraction = 0.0;
        
        if (current_capacity == 0) {
            fraction = 0.0;
        } else if (current_item->item_weight <= current_capacity) {
            current_capacity -= current_item->item_weight;
            max_profit += current_item->item_profit;
            fraction = 1.0;
        } else {
            fraction = current_capacity / current_item->item_weight;
            max_profit += current_item->item_profit * fraction;
            current_capacity = 0;
        }
        
        current_item->amount_taken = fraction;
    }
    
    fprintf(outFile, "--- Fractional Knapsack Solution ---\n");
    fprintf(outFile, "Knapsack Capacity: %.2f\n\n", capacity);
    fprintf(outFile, "Item No\tProfit\t\tWeight\t\tAmount to be taken\n");
    
    for (int i = n - 1; i >= 0; i--) {
        fprintf(outFile, "%d\t%.6f\t%.6f\t%.6f\n", 
                items[i].item_id, 
                items[i].item_profit, 
                items[i].item_weight, 
                items[i].amount_taken);
    }

    fprintf(outFile, "\nMaximum profit: %.6f\n", max_profit);
}

int main() {
    FILE *inFile = fopen("input.txt", "r");
    FILE *outFile = fopen("output.txt", "w");
    
    int num_items;
    double capacity;
    
  printf("Enter number of items");
  scanf("%d",&num_items);
  printf("Enter capacity");
  scanf("%lf",&capacity);

    ITEM* items = (ITEM*)malloc(num_items * sizeof(ITEM));
 
    for (int i = 0; i < num_items; i++) {
        double profit, weight;
        if (fscanf(inFile, "%lf %lf", &profit, &weight) != 2) {
            fprintf(stderr, "Error reading profit and weight for item %d from file. Check format.\n", i + 1);
            free(items); fclose(inFile); fclose(outFile); return 1;
        }
        
        items[i].item_id = i + 1;
        items[i].item_profit = profit;
        items[i].item_weight = weight;
        
        items[i].profit_weight_ratio = (weight > 0) ? (profit / weight) : 0.0;
        items[i].amount_taken = 0.0;
    }
    
    fclose(inFile);

    fractional_knapsack(items, num_items, capacity, outFile);
    
    printf("Knapsack solution calculated and written to output.txt.\n");
    
    free(items);
    fclose(outFile);

    return 0;
}
