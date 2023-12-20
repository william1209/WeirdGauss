#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_matrix(int arr[][2]){
    for(int row=0;row<2;row++){
        for(int col=0;col<2;col++){
            printf("%d ", arr[row][col]);
        }printf("\n");
    }
}

void print_matrix3(int arr[][3]){
    for(int row=0;row<2;row++){
        for(int col=0;col<3;col++){
            printf("%d ", arr[row][col]);
        }printf("\n");
    }
}


void print_array(int arr[], int n){
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }printf("\n");
}

int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a % b);
}

int lcm_array(int arr[], int n){
    int gcd_result = arr[0];
    int lcm = 1;
    for(int i=0;i<n;i++){
        lcm *= arr[i];
        gcd_result = gcd(arr[i], gcd_result);
    }
    lcm /= gcd_result;
    return lcm;
}

void transpose(int mat1[][2], int mat2[][3]){
    for(int row=0;row<2;row++){
        for(int col=0;col<3;col++){
            mat1[row][col] = mat2[col][row];
        }
    }
}

void eliminate(int mat[][3], int index_row, int n){
    int *temp = malloc(n * sizeof(int));
    for(int i=0;i<3;i++){
        temp[i] = mat[index_row][i];
    }
    for(int row=0;row<2;row++){
        for(int col=0;col<3;col++){
            mat[row][col] -= temp[col];
        }
    }
    for(int i=0;i<3;i++){
        mat[index_row][i] = temp[i];
    }
    free(temp);
}

void unify(int mat[][3], int index){
    int _r = 2, _c = 3;
    int a_transpose[3][2];
    transpose(a_transpose, mat);
    int col_lcm;
    int factor[2];//factor[row]
    for(int row=index;row<_r;row++){
        col_lcm = lcm_array(a_transpose[row], 2);
        //printf("lcm: %d \n", col_lcm);
        for(int cursor=0;cursor<_r;cursor++){
            factor[cursor] = col_lcm / a_transpose[row][cursor];
            //printf("factor: %d \n", factor[cursor]);
        }
        for(int col=0;col<_c;col++){
            mat[row][col] *= factor[row];
            //printf("mat: %d \n", mat[row][col]);
        }
    }
}

int gauss_(int mat[][3]){
    for(int i=0;i<2;i++){
        unify(mat, i);
        eliminate(mat, i, 2);
    }
    printf("After Elimination: \n");
    print_matrix3(mat);

}

int main(){

    int a[][2] = {
        {1,2},
        {3,4}
    };
    int y[2] = {4,10}; //x=2, y=1

    int A[][3] = {
        {1,2,4},
        {3,4,10}
    };
    
    printf("Before Elimination: \n");
    print_matrix3(A);
    gauss_(A);
    //print_array(y, 2);
    return 0;
}