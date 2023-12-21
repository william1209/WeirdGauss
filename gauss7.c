#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_pA(int **pA, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ", pA[i][j]);
        }printf("\n");
    }
}

int findMax(int arr[], int idx, int n) {
    int max = arr[idx];
    int index = 0;
    for (int i = idx; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMax_index(int arr[], int idx, int n) {
    int max = arr[idx];
    int index = 0;
    for (int i = idx; i < n; i++) {
        if (arr[i] > max) {
            index = i;
        }
    }
    return index;
}

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
        if(arr[i]==0){
            lcm*=1;
        }else{
            lcm *= arr[i];
        }
        //lcm *= arr[i];
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
        if(a_transpose[index][cursor]==0){
            factor[cursor] = col_lcm / 1;
        }else{
            factor[cursor] = col_lcm / a_transpose[index][cursor];
        }
        //factor[cursor] = col_lcm / a_transpose[index][cursor];
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

int check_U(int n, int** Aug){
    /*
    int *diagnal = (int *)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        diagnal[i] = temp[i][i];
    }
    int dia_lcm = lcm_array2(diagnal);
    for(int i=0;i<n;i++){
        diagnal[i] /= dia_lcm;
    }
    */
    //check U here
    for(int col=0;col<n;col++){
        for(int row=col+1;row<n;row++){
            if(Aug[row][col]!=0){
                return 0;
            }
        }
    }// check U
    return 1; 
}

void swap_row(int **Aug, int row1, int row2, int n){
    int *temp = (int *)malloc((n+1) * sizeof(int));
    for(int i=0;i<n+1;i++){
        temp[i] = Aug[row1][i];
    }
    for(int i=0;i<n+1;i++){
        Aug[row1][i] = Aug[row2][i];
    }
    for(int i=0;i<n+1;i++){
        Aug[row2][i] = temp[i];
    }
    free(temp);
}

void rearrange(int n, int **Aug){
    int _r = n, _c = n+1;
    int **a_transpose = (int **)malloc(_c * sizeof(int *));
    for(int i=0;i<_c;i++){
        a_transpose[i] = (int *)malloc(_r * sizeof(int));
    }

    transpose2(a_transpose, Aug, _r, _c);

    int **temp = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        temp[i] = (int *)malloc((n) * sizeof(int));
    }
    for(int i=0;i<_r;i++){
        for(int j=0;j<_c;j++){
            temp[i][j] = Aug[i][j];
        }
    }

    for(int i=0;i<n;i++){ 
        if(Aug[i][i] != findMax(a_transpose[i], i, n)){
            //printf("%d \n", i);
            //printf("%d \n", findMax(a_transpose[i], i, n));
            swap_row(Aug, i, findMax_index(a_transpose[i], i, n), n);
            transpose2(a_transpose, Aug, _r, _c);
            print_pAug(Aug, n);
        }
    }
}


int gaussian_(int n, int* pA, int* py, int **px){
    int **Aug = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        Aug[i] = (int *)malloc((n+1) * sizeof(int));
    }
    merge(n, pA, py, Aug);
    rearrange(n, Aug);
    printf("Rearranged & Augmented: \n");
    print_pAug(Aug, n);
    int check = check_U(n, Aug);
    printf("Check Upper: %d \n", check);
    if(check==1){
        //merge(n, pA, py, Aug);
        solve_x(Aug, n, *px);
        print_x(*px, n);
        return 1;
    }
    //merge(n, pA, py, Aug);
    //printf("Original: \n");
    //solve_x(Aug, n, *px);
    //print_x(*px, n);

    //print_pAug(Aug, n);
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
    int b_y[3] = {2,1,1};
    int B[][3] = {
        {0,1,1},
        {0,1,0},
        {1,0,0}
    };

    int* b_x = malloc(n * sizeof(int));
    gaussian_(n, (int *)B, b_y, &b_x);
    free(b_x);
    
    return 0;
}