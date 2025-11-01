#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void findLCS(char *X, char *Y, int m, int n) {
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    int lcs_length = L[m][n];

    char *lcs = (char *)malloc(sizeof(char) * (lcs_length + 1));
    if (lcs == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    lcs[lcs_length] = '\0';

    int i = m, j = n;
    int index = lcs_length;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--index] = X[i - 1];
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("\nLCS: %s\n", lcs);
    printf("\nLCS Length: %d\n", lcs_length);

    free(lcs);
}

int main() {
    char X[MAX_LENGTH];
    char Y[MAX_LENGTH];

    printf("Enter the first string into an array: ");
    if (scanf("%s", X) != 1) {
        fprintf(stderr, "Error reading the first string.\n");
        return 1;
    }

    printf("Enter the second string into an array: ");
    if (scanf("%s", Y) != 1) {
        fprintf(stderr, "Error reading the second string.\n");
        return 1;
    }

    int m = strlen(X);
    int n = strlen(Y);

    if (m >= MAX_LENGTH || n >= MAX_LENGTH) {
        fprintf(stderr, "Input strings exceed maximum allowed length (%d).\n", MAX_LENGTH);
        return 1;
    }

    findLCS(X, Y, m, n);

    return 0;
}

