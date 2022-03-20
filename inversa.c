/*
ESSE ARQUIVO FOI UTILIZADO COMO BASE PARA A IMPLEMENTAÇÃO
DA FUNÇÃO DE INVERSA NO PROGRAMA PRINCIPAL.

O CÓDIGO FOI ADAPTADO DE UM MODELO EXTERNO
CREDITOS AO MODELO EXTERNO: https://www.sanfoundry.com/c-program-find-inverse-matrix/
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void destroiVetorLocal(double ** vector, double order){
  int i;
  for(i=0;i<order;i++) if (vector[i] != NULL) free(vector[i]);

  if (vector!=NULL) free(vector);
}

double determinant(double ** a, double k){
  double s = 1, det = 0;
  int i, j, m, n, c, exit=0;
  
  double ** b = (double**)malloc(k*sizeof(double*));
  for(i=0;i<k;i++) b[i] = (double*)malloc(k*sizeof(double));

  // if (k == 1) return (a[0][0]);
  if (k==1) exit=1;
  else {
    det = 0;
    for (c = 0; c < k; c++){
      m = 0;
      n = 0;

      for (i = 0;i < k; i++){
        for (j = 0 ;j < k; j++){
          b[i][j] = 0;
          if (i != 0 && j != c){
            b[m][n] = a[i][j];
            if (n < (k - 2)) n++;
            else {
              n = 0;
              m++;
            }
          }
        }
      }

      det = det + s * (a[0][c] * determinant(b, k - 1));
      s = -1 * s;
      
    }
  }

  destroiVetorLocal(b, k);
  if (exit) return a[0][0];
  
  return (det);
}

double ** transpose(double ** num, double ** fac, double r){
  int i, j;
  double d;
  
  double ** b = (double**)malloc(r*sizeof(double*));
  for(i=0;i<r;i++) b[i] = (double*)malloc(r*sizeof(double));
 
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++){
      b[i][j] = fac[j][i];
    }
  }

  d = determinant(num, r);
  for (i = 0;i < r; i++) for (j = 0;j < r; j++) num[i][j] = b[i][j] / d;

  destroiVetorLocal(b, r);

  return num;
}
 
double ** cofactor(double ** num, double f){
  int p, q, m, n, i, j;

  double ** b = (double**)malloc(f*sizeof(double*));
  for(i=0;i<f;i++) b[i] = (double*)malloc(f*sizeof(double));

  double ** fac = (double**)malloc(f*sizeof(double*));
  for(i=0;i<f;i++) fac[i] = (double*)malloc(f*sizeof(double));
  
  for (q = 0;q < f; q++) {
    for (p = 0;p < f; p++){
      m = 0;
      n = 0;
      for (i = 0;i < f; i++){
        for (j = 0;j < f; j++){
          if (i != q && j != p){
            b[m][n] = num[i][j];
            if (n < (f - 2)) n++;
            else {
              n = 0;
              m++;
            }
          }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }


  num = transpose(num, fac, f);

  destroiVetorLocal(b, f);
  destroiVetorLocal(fac, f);

  return num;
}



int main() {
  double d;
  int i, j, order=3;

  double ** a = (double**)malloc(order*sizeof(double*));
  for(i=0;i<order;i++) a[i] = (double*)malloc(order*sizeof(double));
  
  a[0][0] = 3; a[0][1] = 5; a[0][2] = 2;
  a[1][0] = 1; a[1][1] = 5; a[1][2] = 8;
  a[2][0] = 3; a[2][1] = 9; a[2][2] = 2;

  d = determinant(a, order);
  if (d == 0) printf("\nImpossível calcular inversa dessa matriz\n");
  else a = cofactor(a, order);


  for (i = 0;i < order; i++) {
    for (j = 0;j < order; j++) printf("\t%f", a[i][j]);
    printf("\n");
  }

  destroiVetorLocal(a, order);
}
 

