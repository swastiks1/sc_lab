//max size 10
//min max func
//i/o
//loop 



#include <stdio.h>
#define MAX_SIZE 10
float min(float a, float b)
{return (a < b) ? a : b;}
float max(float a, float b)
{return (a > b) ? a : b;}
int main() {
  int m, n, p;
  float u1[MAX_SIZE][MAX_SIZE], u2[MAX_SIZE][MAX_SIZE], u3[MAX_SIZE][MAX_SIZE];

  printf("Enter the number of elements in fuzzy set A, B & C: ");
  scanf("%d %d %d", &m, &n, &p);

  printf("Enter the entries in fuzzy relational matrix R (A x B):\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%f", &u1[i][j]);
    }
  }
  printf("Enter the entries in fuzzy relational matrix S (B x C):\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      scanf("%f", &u2[i][j]);
    }
  }

  printf("Composed fuzzy relation (A x C):\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      float max_val = 0.0f;
      for (int k = 0; k < n; k++) {
        max_val = max(max_val, (u1[i][k]*u2[k][j]));
      }
      u3[i][j] = max_val;
      printf("%.2f ", u3[i][j]);
    }
    printf("\n");
  }
  return 0;
}