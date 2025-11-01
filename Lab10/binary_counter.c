#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 5 

typedef struct {
    int bits[BITS];       
    int high_bit_index;   
} BinaryCounter;


void initializeCounter(BinaryCounter *counter) {
    memset(counter->bits, 0, sizeof(counter->bits));
    counter->high_bit_index = -1;
}


void printState(const BinaryCounter *counter, const char *operation, int cost, int total_cost) {
    printf("%-10s | ", operation);
    
    for (int i = BITS - 1; i >= 0; i--) {
        printf("%d ", counter->bits[i]);
    }
    printf("| %-8d | %-8d\n", cost, total_cost);
}


int increment(BinaryCounter *counter) {
    int cost = 0;
    int i = 0;
    
   
    while (i < BITS && counter->bits[i] == 1) {
        counter->bits[i] = 0;
        cost++;
        i++;
    }

    
    if (i < BITS) {
        counter->bits[i] = 1;
        cost++;
        
       
        if (i > counter->high_bit_index) {
            counter->high_bit_index = i;
        }
    }
    
   

    return cost;
}


int reset(BinaryCounter *counter) {
    int cost = 0;
    
   
    for (int i = 0; i <= counter->high_bit_index; i++) {
        if (counter->bits[i] == 1) {
            counter->bits[i] = 0;
            cost++;
        }
    }
    
  
    counter->high_bit_index = -1;

    return cost;
}

int main() {
    BinaryCounter counter;
    initializeCounter(&counter);
    int total_cost = 0;
    int current_cost;

    printf("Binary Counter Demonstration (BITS=%d)\n", BITS);
    printf("Operation  | Bit %d Bit 3 Bit 2 Bit 1 Bit 0 | Cost     | Total Cost\n", BITS - 1);
    printf("-----------|-----------------------------|----------|-----------\n");

    // Initial state
    printState(&counter, "Initial", 0, 0);

    // Sequence of operations based on the example
    
    // 1. Increment (00000 -> 00001)
    current_cost = increment(&counter);
    total_cost += current_cost;
    printState(&counter, "Increment", current_cost, total_cost);

    // 2. Increment (00001 -> 00010)
    current_cost = increment(&counter);
    total_cost += current_cost;
    printState(&counter, "Increment", current_cost, total_cost);

    // 3. Reset (00010 -> 00000)
    current_cost = reset(&counter);
    total_cost += current_cost;
    printState(&counter, "Reset", current_cost, total_cost);

    // 4. Increment (00000 -> 00001)
    current_cost = increment(&counter);
    total_cost += current_cost;
    printState(&counter, "Increment", current_cost, total_cost);

    // 5. Reset (00001 -> 00000)
    current_cost = reset(&counter);
    total_cost += current_cost;
    printState(&counter, "Reset", current_cost, total_cost);
    
    // Example of an expensive increment
    printf("\n--- Sequence continues ---\n");
    for (int i = 0; i < 7; i++) { // INC 7 more times (0 to 7)
        current_cost = increment(&counter);
        total_cost += current_cost;
        char op_name[20];
        snprintf(op_name, 20, "INC #%d", i + 6);
        printState(&counter, op_name, current_cost, total_cost);
    }
    
    // Reset after full count (01111 -> 00000)
    printf("\n--- Expensive Reset ---\n");
    current_cost = reset(&counter);
    total_cost += current_cost;
    printState(&counter, "Reset", current_cost, total_cost);
    
    printf("\nTotal Cost for 13 operations: %d\n", total_cost);

    return 0;
}

