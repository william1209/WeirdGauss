#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int gaussian_elimination(int n, int *pA, int *py, int **px) {
  // 检查参数
  if (n <= 0 || pA == NULL || py == NULL || px == NULL) {
    return -1;
  }

  // 动态分配内存
  int **a = malloc(sizeof(int *) * n);
  for (int i = 1; i <= n; i++) {
    a[i] = malloc(sizeof(int) * (n + 1));
  }

  // 复制矩阵
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) {
      a[i][j] = pA[(i-1) * (n + 1) + j];
    }
  }

  // 使用高斯消去法
  for (int i = 1; i <= n-1; i++) {
    if (fabs(a[i][i]) < 1e-6) {
      printf("Matrix is singular!\n");
      return -1;
    }
    for (int j = i + 1; j <= n; j++) {

      int ratio = a[j][i] / a[i][i];

      for (int k = 1; k <= n + 1; k++) {
        a[j][k] -= ratio * a[i][k];
      }
    }
  }

  // 回代求解
  int temp = a[n][n + 1] / a[n][n];
  px[n] = &temp;

  for (int i = n - 1; i >= 1; i--) {
    if(a[i][i] != 0){
        px[i] = malloc(sizeof(int));
        *px[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            *px[i] -= a[i][j] * (*px[j]);
        }
        *px[i] /= a[i][i];
    }else{
        px[i] = &py[i];
    }

  }

  // 释放内存
  for (int i = 1; i <= n; i++) {
    free(a[i]);
  }

  free(a);

  return 0;
}

int main() {
  int n;
  int *pA, *py;
  int **px;

  // 输入未知数个数
  printf("Enter number of unknowns: ");
  scanf("%d", &n);

  // 分配内存
  pA = malloc(sizeof(int) * n * (n + 1));
  py = malloc(sizeof(int) * n);
  px = malloc(sizeof(int *) * n);

  // 输入增广矩阵
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) {
      printf("a[%d][%d] = ", i, j);
      scanf("%d", &pA[(i - 1) * (n + 1) + j]);
    }
  }

  // 调用函数
  if (gaussian_elimination(n, pA, py, px) != 0) {
    return -1;
  }

  // 输出解
  printf("\nSolution:\n");
  for (int i = 1; i <= n; i++) {
    printf("x[%d] = %d\n", i , *px[i]);
  }

  // 释放内存
  free(pA);
  free(py);
  free(px);

  return 0;
}