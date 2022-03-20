//ESSE ARQUIVO FOI UTILIZADO PARA TESTAR UMA METODOLOGIA DE ALOCAÇÃO
//E DESALOCAÇÃO NO VETOR DE PONTEIROS QUE SERA UTILLZADO NO STRUCT
//DA MATRIZ

#include <stdio.h>
#include <stdlib.h>


void imprime(double**v, unsigned int * tam){
  printf("\n");

  int i, j;
  for(i=0;i<tam[0];i++) {
    for(j=0;j<tam[1];j++) printf("%.2lf     ", v[i][j]);
    printf("\n");
  }

  printf("\n");
}


int main () {
  int i=0, j=0;
  
  unsigned int * tam = (unsigned int*) malloc(2*sizeof(unsigned int));
  tam[0] = 3;
  tam[1] = 4;


  //alocando vetor principal
  double ** val = (double**)malloc(tam[0] * sizeof(double*));
  for(i=0;i<tam[0];i++){
    val[i] = (double*)malloc(tam[1]*sizeof(double));
    for(j=0;j<tam[1];j++) val[i][j] = 1;
  }

  imprime(val, tam);


  //alocando vetor de backup
  double ** backup = (double**)malloc(tam[0] * sizeof(double*));
  for(i=0;i<tam[0];i++){
    backup[i] = (double*)malloc(tam[1]*sizeof(double));
    for(j=0;j<tam[1];j++) backup[i][j] = val[i][j];
  }
  
  //desalocando o vetor principal para mudar o tamanho (sem realloc)
  for(i=0;i<tam[0];i++) free(val[i]);
  free(val);

  //alocando vetor principal no novo tamanho
  tam[0] = 4;
  val = (double**) malloc (tam[0]*sizeof(double*));
  for(i=0;i<tam[0];i++){
    val[i] = (double*) malloc (tam[1]*sizeof(double));
    for(j=0;j<tam[1];j++) {
      if (i==3) val[i][j] = 0;
      else val[i][j] = backup[i][j];
    }
  }

  //deasalocando vetor de backup
  for(i=0;i<3;i++) free(backup[i]);
  free(backup);


  imprime(val, tam);

  //desalocando vetor principal
  for(i=0;i<tam[0];i++) free(val[i]);
  free(val);

  free(tam);

  return 0;
}