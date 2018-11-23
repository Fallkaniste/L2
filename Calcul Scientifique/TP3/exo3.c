#include <stdio.h>
#include <math.h>
int trang(float a[4][4], float b[4][4]){
  float n = 4;
  float l[4][4] = {{1,0,0,0},{1,1,0,0},{1,1,1,0},{1,1,1,1}};
  for (int r = 1; r < n; r++) {
    for (int i = r+1; i < n; i++) {
      l[i][r]=(a[i][r])/(a[r][r]);
      a[i][r]=0;
      for (int j = 0; j < n; j++) {
        a[i][j]-=l[i][j]*a[r][j];
      }
    }
  }
}

int remonte(float u[4][4], int y){

}
int main(){
float a[4][4]={{1,2,1,2},{-2,-3,0,-5},{4,8,6,7},{1,-1,0,5}};

trang(a);


for (int j = 0; j <= 3; j++) {
  for (int i = 0; i <= 3; i++) {
    printf("%f,",a[i][j]);
  }
  printf("\n");
}
}
