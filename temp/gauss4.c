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

void transpose(int mat1[][2], int mat2[][2]){
    for(int row=0;row<2;row++){
        for(int col=0;col<2;col++){
            mat1[row][col] = mat2[col][row];
        }
    }
}

void eliminate(int mat[][2], int index_row, int n){
    int *temp = malloc(n * sizeof(int));
    for(int i=0;i<2;i++){
        temp[i] = mat[index_row][i];
    }
    for(int row=0;row<2;row++){
        for(int col=0;col<2;col++){
            mat[row][col] -= temp[col];
        }
    }
    for(int i=0;i<2;i++){
        mat[index_row][i] = temp[i];
    }
    free(temp);
}

int gauss_elimination(int a[][2]){
    int max_index;
    int _max = a[0][0];
    for(int i=0;i<2;i++){
        if(a[i][0]>_max){
            _max = a[i][0];
            max_index = i;
        }
    }
    printf("max: %d, max_index: %d", _max, max_index); //max=3, max_index=1
    printf("\n");

    //find lcm for first column
    int a_transpose[2][2];
    transpose(a_transpose, a);
    int col_lcm = lcm_array(a_transpose[0], 2);
    printf("lcm: %d", col_lcm);
    printf("\n");

    
    //find factor for each row
    int factor[2];
    for(int i=0;i<2;i++){
        factor[i] = col_lcm / a[i][0];
    }
    printf("factor1: %d, factor2: %d", factor[0], factor[1]);
    printf("\n");
    

    //multiply factor to row
    for(int row=0;row<2;row++){
        for(int col=0;col<2;col++){
        a[row][col] *= factor[row];
        }
    }
    printf("new arr:");
    printf("\n");
    print_matrix(a);

    eliminate(a, max_index, 2);
    printf("1st elimination: \n");
    print_matrix(a);

    //===============repeated steps==================//
    //find lcm for second col
    transpose(a_transpose, a);
    col_lcm = lcm_array(a_transpose[1], 2);

    //find factor and multiply
    for(int i=0;i<2;i++){
        factor[i] = col_lcm / a[i][1];
    }

    for(int i=0;i<2;i++){
        a[i][1] *= factor[i];
    }
    
    eliminate(a, 0, 2);
    printf("2nd elimination: \n");
    print_matrix(a);
    
}

void unify(int mat[][2], int index){
    int a_transpose[2][2];
    transpose(a_transpose, mat);
    int col_lcm;
    int factor[2];
    for(int row=index;row<2;row++){
        col_lcm = lcm_array(a_transpose[row], 2);
        printf("lcm: %d \n", col_lcm);
        for(int cursor=0;cursor<2;cursor++){
            factor[cursor] = col_lcm / a_transpose[row][cursor];
            printf("factor: %d \n", factor[cursor]);
        }
        for(int col=0;col<2;col++){
            mat[row][col] *= factor[row];
            printf("mat: %d \n", mat[row][col]);
        }
    }
}

int gauss_(int mat[][2]){
    //find lcm for first column

    for(int i=0;i<2;i++){
        unify(mat, i);
        eliminate(mat, i, 2);
    }
    print_matrix(mat);

}

int main(){
    int a[][2] = {
        {1,2},
        {3,4}
    };
    print_matrix(a);
    
    int y[] = {4,10};

    //gauss_elimination(a);
    gauss_(a);
    return 0;
}