#include <stdio.h>

int main() {
    // Method 1: Declaration and initialization
    int matrix1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Method 2: Declaration without initialization
    int matrix2[2][3];
    
    // Assign values individually
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            matrix2[i][j] = i * 3 + j + 1;
        }
    }
    
    // Method 3: Compile-time calculation of dimensions
    int matrix3[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows3 = sizeof(matrix3[0]) / sizeof(matrix3[0][0]);
    (matrix3) / sizeof(matrix3[0]);
    int cols3 = sizeof
    printf("Matrix3 has %d rows and %d columns\n", rows3, cols3);
    
    return 0;
}