#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_MATRICES 100
#define INF INT_MAX

int p[MAX_MATRICES + 1];

int m[MAX_MATRICES][MAX_MATRICES];
int s[MAX_MATRICES][MAX_MATRICES];

void printOptimalParenthesis(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(i, s[i][j]);

        printf(" ");

        printOptimalParenthesis(s[i][j] + 1, j);

        printf(")");
    }
}


void matrixChainOrder(int n) {
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INF;

            for (int k = i; k <= j - 1; k++) {
                long long cost = (long long)m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = (int)cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printTables(int n) {
    printf("\nM Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j >= i) {
                printf("%-5d ", m[i][j]);
            } else {
                printf("0     ");
            }
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > i) {
                printf("%-5d ", s[i][j]);
            } else {
                printf("0     ");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;

    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_MATRICES) {
        fprintf(stderr, "Invalid number of matrices. Must be between 1 and %d.\n", MAX_MATRICES);
        return 1;
    }

    printf("Note: Matrix A_i has dimension p[i-1] x p[i]\n");
    for (int i = 1; i <= n; i++) {
        int r, c;
        printf("Enter row and col size of A%d: ", i);
        if (scanf("%d %d", &r, &c) != 2 || r <= 0 || c <= 0) {
            fprintf(stderr, "Invalid dimension entered.\n");
            return 1;
        }

        if (i == 1) {
            p[i - 1] = r;
            p[i] = c;
        } else {
            if (p[i - 1] != r) {
                fprintf(stderr, "Dimension compatibility error: Column size of A%d (%d) does not match row size of A%d (%d).\n",
                        i - 1, p[i - 1], i, r);
                return 1;
            }
            p[i] = c;
        }
    }

    matrixChainOrder(n);

    printTables(n);

    printf("Optimal parenthesization: ");
    printOptimalParenthesis(1, n);
    printf("\n");

    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);

    return 0;
}

