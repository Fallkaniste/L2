#include <stdio.h>
#include <math.h>
int trang(int A[][],int b[]){
  for (int r = 1; r < n; i++) {
    for (int i = r+1; i < n; i++) {
      L[i][r]=(A[i][r])/(A[r][r]);
      b[i]-=L[i][r]*B[r];
      A[i][r]=0;
      for (int j = 0; r+1 < n; j++) {
        A[i][j]-=L[i][j]*A[r][j]
      }
    }
  }
}
int main(){

}
