#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Input matrix
void inputMatrix(int mat[MAX][MAX], int rows, int cols) 
{
    printf("Enter elements of %d x %d matrix:\n", rows, cols);
    for(int i=0; i<rows; i++) 
    {
        for(int j=0; j<cols; j++) 
        {
            printf("Enter element at [%d][%d] = ", i+1, j+1);
            scanf("%d", &mat[i][j]);
        }
    }
}

// Display matrix
void displayMatrix(int mat[MAX][MAX], int rows, int cols) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

// Addition
void addMatrix() {
    int r, c;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter rows and cols: ");
    scanf("%d %d", &r, &c);

    printf("Matrix A:\n");
    inputMatrix(A, r, c);

    printf("Matrix B:\n");
    inputMatrix(B, r, c);

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            C[i][j] = A[i][j] + B[i][j];

    printf("Result of Addition:\n");
    displayMatrix(C, r, c);
}

// Multiplication
void multiplyMatrix() 
{
    int r1, c1, r2, c2;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};

    printf("Enter rows and cols of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Matrix A:\n");
    inputMatrix(A, r1, c1);

    printf("Enter rows and cols of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("Matrix B:\n");
    inputMatrix(B, r2, c2);

    if(c1 != r2) 
    {
        printf("Multiplication not possible! (c1 != r2)\n");
        return;
    }

    for(int i=0; i<r1; i++)
        for(int j=0; j<c2; j++)
            for(int k=0; k<c1; k++)
                C[i][j] += A[i][k] * B[k][j];

    printf("Result of Multiplication:\n");
    displayMatrix(C, r1, c2);
}

// Transpose
void transposeMatrix() 
{
    int r, c;
    int A[MAX][MAX], T[MAX][MAX];

    printf("Enter rows and cols of Matrix: ");
    scanf("%d %d", &r, &c);
    inputMatrix(A, r, c);

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            T[j][i] = A[i][j];

    printf("Transpose:\n");
    displayMatrix(T, c, r);
}

// Main Menu
int main() 
{
    int choice;
    while(1) {
        printf("\n=== Matrix Operations ===\n");
        printf("1. Addition\n");
        printf("2. Multiplication\n");
        printf("3. Transpose\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addMatrix(); break;
            case 2: multiplyMatrix(); break;
            case 3: transposeMatrix(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
