#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

int** MagicSquare(int n) {
    int** data = (int**) malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        data[i] = (int*) malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) {
            data[i][j] = 0;
        }
    }
    int row = 0, col = n / 2;
    for (int i = 1; i <= n * n; i++) {
        data[row][col] = i;
        int nextRow = row == 0 ? n - 1 : row - 1;
        int nextCol = col == (n - 1) ? 0 : col + 1;
        if (data[nextRow][nextCol] != 0) {
            nextRow = row == (n - 1) ? 0 : row + 1;
            nextCol = col;
        }
        row = nextRow;
        col = nextCol;
    }
    return data;
}

void FreeMagicSquare(int** magicSquare, int n) {
    for (int i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

int main() {
    int n;
    scanf("%d", &n);
    int** magicSquare = MagicSquare(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    return 0;
}
