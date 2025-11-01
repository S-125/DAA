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

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].profit_weight_ratio > arr[largest].profit_weight_ratio) {
        largest = l;
    }

    if (r < n && arr[r].profit_weight_ratio > arr[largest].profit_weight_ratio) {
        largest = r;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void fractional_knapsack(ITEM items[], int n, double capacity) {
    
    heapSort(items, n);

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
    
    printf("Item No\tProfit\t\tWeight\t\tAmount to be taken\n");
    
    
    for (int i = n - 1; i >= 0; i--) {
        printf("%d\t%.6f\t%.6f\t%.6f\n", 
               items[i].item_id, 
               items[i].item_profit, 
               items[i].item_weight, 
               items[i].amount_taken);
    }

    printf("Maximum profit: %.6f\n", max_profit);
}

int main() {
    int num_items;
    double capacity;
    
    printf("--- Fractional Knapsack Solver ---\n");
    
    printf("Enter the number of items: ");
    if (scanf("%d", &num_items) != 1 || num_items <= 0) {
        fprintf(stderr, "Invalid number of items.\n");
        return 1;
    }

    ITEM* items = (ITEM*)malloc(num_items * sizeof(ITEM));
    if (items == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num_items; i++) {
        double profit, weight;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        
        if (scanf("%lf %lf", &profit, &weight) != 2) {
            fprintf(stderr, "Invalid input format for item %d. Exiting.\n", i + 1);
            free(items);
            return 1;
        }
        
        items[i].item_id = i + 1;
        items[i].item_profit = profit;
        items[i].item_weight = weight;
        
        items[i].profit_weight_ratio = (weight > 0) ? (profit / weight) : 0.0;
        items[i].amount_taken = 0.0;
    }

    printf("Enter the capacity of knapsack:");
    if (scanf("%lf", &capacity) != 1 || capacity < 0) {
        fprintf(stderr, "Invalid knapsack capacity.\n");
        free(items);
        return 1;
    }
    
    printf("\nOutput:\n");
    fractional_knapsack(items, num_items, capacity);
    
    free(items);

    return 0;
}

