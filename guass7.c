#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_pAug(int **pAug, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%d ", pAug[i][j]);
        }printf("\n");
    }
}

void print_pAugT(int **pAug, int n){
    for(int i=0;i<n+1;i++){
        for(int j=0;j<n;j++){
            printf("%d ", pAug[i][j]);
        }printf("\n");
    }
}

void print_x(int *x, int n){
    printf("[ ");
    for(int i=0;i<n;i++){
        printf("%d ", x[i]);
    }printf("] \n");
}

int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a % b);
}

int lcm_array2(int *arr){
    int gcd_result = arr[0];
    int lcm = 1;
    int size = sizeof(arr) / sizeof(arr[0]);
    for(int i=0;i<size+1;i++){
        lcm *= arr[i];
        gcd_result = gcd(arr[i], gcd_result);
    }
    lcm /= gcd_result;
    return lcm;
}

void transpose2(int **mat1, int **mat2, int rows, int cols){
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            mat1[col][row] = mat2[row][col];
        }
    }
}

void eliminate2(int **mat, int index_row, int n){
    int *temp = (int *)malloc(n * sizeof(int));
    for(int i=0;i<n+1;i++){
        temp[i] = mat[index_row][i];
    }
    for(int row=0;row<n;row++){
        for(int col=0;col<n+1;col++){
            mat[row][col] -= temp[col];
        }
    }
    for(int i=0;i<n+1;i++){
        mat[index_row][i] = temp[i];
    }
    free(temp);
}

void unify2(int **mat, int index, int n){
    int _r = n, _c = n+1;
    int **a_transpose = (int **)malloc(_c * sizeof(int *));
    for(int i=0;i<_c;i++){
        a_transpose[i] = (int *)malloc(_r * sizeof(int));
    }

    transpose2(a_transpose, mat, _r, _c);

    int col_lcm;
    int *factor = (int *)malloc(_r * sizeof(int));

    col_lcm = lcm_array2(a_transpose[index]);
    //printf("lcm: %d \n", col_lcm);
    for(int cursor=0;cursor<_r;cursor++){
            factor[cursor] = col_lcm / a_transpose[index][cursor];
            //printf("factor: %d \n", factor[cursor]);
        }
    for(int row=index;row<_r;row++){
        for(int col=0;col<_c;col++){
            mat[row][col] *= factor[row];
        }
    }
    for(int i=0;i<_c;i++){
        free(a_transpose[i]);
    }
    free(a_transpose);
    free(factor);
}

void merge(int n, int* pA, int* py, int **Aug){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Aug[i][j] = *(pA + i*n + j);
        }
    }
    for(int i=0;i<n;i++){
        Aug[i][n] = py[i];
    }
}

void solve_x(int **Aug, int n, int *x){
    int *temp = (int *)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        temp[i] = Aug[i][n];
    }
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--){
            temp[i] -= Aug[i][j] * x[j];
        }
        x[i] = temp[i] / Aug[i][i];
    }
    free(temp);
}

void eliminate3(int **mat, int index_row, int n){
    int *temp = (int *)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        temp[i] = mat[index_row][i];
    }
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++){
            mat[row][col] -= temp[col];
        }
    }
    for(int i=0;i<n;i++){
        mat[index_row][i] = temp[i];
    }
    free(temp);
}


void check(int n, int* pA){
    int **temp = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        temp[i] = (int *)malloc((n) * sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            temp[i][j] = *(pA + i*n + j);
        }
    }
    for(int index=0;index<n;index++){
        eliminate3(temp, index, n);
    }
    free(temp);
}

int gaussian_(int n, int* pA, int* py, int **px){
    int **Aug = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        Aug[i] = (int *)malloc((n+1) * sizeof(int));
    }
    merge(n, pA, py, Aug);
    printf("Augmented: \n");
    print_pAug(Aug, n);
    for(int index=0;index<n;index++){
        unify2(Aug, index, n);
        eliminate2(Aug, index, n);
    }
    printf("After Elimination: \n");
    print_pAug(Aug, n);
    solve_x(Aug, n, *px);
    printf("x: \n");
    print_x(*px, n);

}

int main(){

    int n = 3;
    int b_y[3] = {6,17,34};
    int B[][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    int* b_x = malloc(n * sizeof(int));
    check(n, (int *)B);

    gaussian_(n, (int *)B, b_y, &b_x);
    free(b_x);
    
    return 0;
}