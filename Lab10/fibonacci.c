#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    int* fits; 
    int size;  
    int value; 
} Fitstring;


Fitstring* initFitstring() {
    Fitstring* fs = (Fitstring*)malloc(sizeof(Fitstring));
    if (!fs) {
        perror("Memory allocation failed for Fitstring");
        exit(EXIT_FAILURE);
    }
    
    fs->size = 6;
    fs->fits = (int*)calloc(fs->size, sizeof(int));
    if (!fs->fits) {
        perror("Memory allocation failed for fits array");
        free(fs);
        exit(EXIT_FAILURE);
    }

   
    fs->fits[5] = 1; 
    fs->fits[3] = 1; 
    fs->fits[2] = 1; 
    fs->fits[1] = 1; 
    fs->value = 14;

    return fs;
}


void printFitstring(const Fitstring* fs) {
    printf("Value: %-3d | Fitstring (F%d...F1): ", fs->value, fs->size);
   
    for (int i = fs->size - 1; i >= 0; i--) {
        printf("%d", fs->fits[i]);
    }
    printf("\n");
}


void checkAndResize(Fitstring* fs) {
    int new_size = fs->size;
    
    
    if (fs->fits[0] < 0 && fs->size > 1) {

        return; 
    }

   
    if (fs->fits[fs->size - 1] >= 2) {
        new_size += 1;
    }
    
    
    if (fs->size > 1 && fs->fits[fs->size - 1] == 0) {
        new_size = fs->size - 1;
    }

    if (new_size != fs->size) {
        fs->fits = (int*)realloc(fs->fits, new_size * sizeof(int));
        if (!fs->fits) {
            perror("Reallocation failed");
            exit(EXIT_FAILURE);
        }
        
        
        if (new_size > fs->size) {
            fs->fits[new_size - 1] = 0;
        }
        fs->size = new_size;
    }
}
void normalize(Fitstring* fs, int carry_mode) {
    int i = 0;
    while (i < fs->size || (i == fs->size && fs->fits[fs->size - 1] != 0)) {
        
      
        if (i == fs->size) {
             checkAndResize(fs);
        }

        int fit = fs->fits[i];

        if ((carry_mode == 1 && fit >= 2) || (carry_mode == -1 && fit < 0)) {
            
            
            
            int carry = (carry_mode == 1) ? 2 : -1; // Carry is 2 (2*F_i) or Borrow is -1 (F_i - F_i)
            
            if (carry_mode == 1) { 
                fs->fits[i] -= 2; 
                
               
                fs->fits[i + 1] += 1; 

                
                if (i >= 2) {
                    fs->fits[i - 2] += 1; 
                }
            } else { 
                fs->fits[i] += 1; 
                
               
                fs->fits[i + 1] -= 1; 

                
                if (i >= 2) {
                    fs->fits[i - 2] -= 1; 
                }
            }

          
            i = 0; 
            checkAndResize(fs);
        } else {
            i++;
        }
    }
}


void increment(Fitstring* fs) {
    fs->fits[0] += 1;
    fs->value += 1;
    normalize(fs, 1);
}


void decrement(Fitstring* fs) {
    if (fs->value == 0) return; // Prevent decrementing past zero for this demo
    
    fs->fits[0] -= 1;
    fs->value -= 1;
    normalize(fs, -1);
}

// --- Main Program ---

int main() {
    // F_i sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ... (F1, F2, F3, F4, F5, F6, F7, F8, F9, ...)
    printf("--- Randomized Quick Sort Program is on Canvas ---\n");
    printf("--- Fibonacci Fitstring Counter Demonstration ---\n\n");
    
    Fitstring* fs = initFitstring();

    printf("Starting value (101110 = 8+3+2+1 = 14):\n");
    printFitstring(fs);

    // --- Increment Demonstration ---
    printf("\n--- Incrementing (3 times) ---\n");
    
    printf("-> Increment 1 (14 -> 15):\n");
    increment(fs);
    printFitstring(fs); // Should become F6 + F4 + F3 + F2 + F1 (15) or simplified form (e.g., 101111)

    printf("-> Increment 2 (15 -> 16):\n");
    increment(fs);
    printFitstring(fs);

    printf("-> Increment 3 (16 -> 17):\n");
    increment(fs);
    printFitstring(fs);

    // --- Decrement Demonstration ---
    printf("\n--- Decrementing (3 times) ---\n");

    printf("-> Decrement 1 (17 -> 16):\n");
    decrement(fs);
    printFitstring(fs);

    printf("-> Decrement 2 (16 -> 15):\n");
    decrement(fs);
    printFitstring(fs);

    printf("-> Decrement 3 (15 -> 14):\n");
    decrement(fs);
    printFitstring(fs);

    // Cleanup
    free(fs->fits);
    free(fs);

    return 0;
}

