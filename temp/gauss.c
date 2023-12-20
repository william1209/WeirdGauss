#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 10

int main() {
  // 动态分配内存
  float **a = malloc(sizeof(float *) * SIZE);
  for (int i = 0; i < SIZE; i++) {
    a[i] = malloc(sizeof(float) * (SIZE + 1));
  }
  float *x = malloc(sizeof(float) * SIZE);

  int i, j, k, n;

  // 输入未知数个数
  printf("Enter number of unknowns: ");
  scanf("%d", &n);

  // 输入增广矩阵
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n + 1; j++) {
      printf("a[%d][%d] = ", i, j);
      scanf("%f", &a[i - 1][j - 1]);
    }
  }

  // 使用高斯消去法
  for (i = 1; i <= n - 1; i++) {
    if (fabs(a[i - 1][i - 1]) < 1e-6) {
      printf("Matrix is singular!\n");
      exit(0);
    }
    for (j = i + 1; j <= n; j++) {
      float ratio = a[j - 1][i - 1] / a[i - 1][i - 1];
      for (k = 1; k <= n + 1; k++) {
        a[j - 1][k - 1] -= ratio * a[i - 1][k - 1];
      }
    }
  }

  // 回代求解
  x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];
  for (i = n - 2; i >= 0; i--) {
    x[i] = a[i][n];
    for (j = i + 1; j <= n - 1; j++) {
      x[i] -= a[i][j] * x[j];
    }
    x[i] /= a[i][i];
  }

  // 输出解
  printf("\nSolution:\n");
  for (i = 0; i < n; i++) {
    printf("x[%d] = %f\n", i + 1, x[i]);
  }

  // 释放内存
  for (i = 0; i < SIZE; i++) {
    free(a[i]);
  }
  free(a);
  free(x);

  return 0;
}
