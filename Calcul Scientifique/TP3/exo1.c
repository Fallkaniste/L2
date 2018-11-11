#include <stdio.h>
#include <math.h>
int main(){
  int A[100][100];
  int n;
  int v[100];
  int u[100];

  printf("entrez n\n");
  scanf("%d",&n);
for (int i = 0; i < n; i++) {
  u[i]=1;
}
  for (int j = 0; j <= n-1; j++) {
    for (int i = 0; i <= n-1; i++) {
      A[i][j]= pow(j+1,i);
      printf("%d,",A[i][j]);
    }
    printf("\n");
  }
  for (int j = 0; j <= n-1; j++) {
    for (int i = 0; i <= n-1; i++) {
      v[j] += (A[i][j] * u[i]);
  }
}
for (int i = 0; i <= n-1; i++) {
printf("%d;",v[i]);
}
}
