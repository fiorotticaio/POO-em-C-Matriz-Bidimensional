#include <stdio.h>
#include "matriz.h"

int main () {
	Matriz_pt ptM1 = NULL, ptM2 = NULL, ptM3 = NULL;

	/* Criando as matrizes (DIMENSÃO MÁXIMA DE 10 x 10) */ 
	int tamM1[] = { 5, 3 };
	double valM1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
	ptM1 = Matriz_2d_criar (ptM1, tamM1, valM1);

	int tamM2[] = { 5, 3 };
	double valM2[] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	ptM2 = Matriz_2d_criar (ptM2, tamM2, valM1);

	printf("\nM1:");
	ptM1->Metodo->imprime(ptM1);
	
	printf("\nM2:");
	ptM2->Metodo->imprime(ptM2);

	
	/* Aplicando as funções básicas*/

	printf("\nCopiando a M1 para M3\nM3:");
	ptM3 = ptM1->Metodo->copia(ptM1);
	ptM2->Metodo->imprime(ptM2);

	//atribuição (precisa de setters, que estão com problema no momento)

	ptM2 = ptM2->Metodo->soma(ptM1, ptM2, ptM2);
	printf("\nSomando M1 com M2 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->subt(ptM1, ptM2, ptM2);
	printf("\nSubtraindo M2 de M1 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	//multiplicação

	//divisao (?)

	ptM2 = ptM2->Metodo->ac_soma(ptM1, ptM2);
	printf("\nFazendo soma acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->ac_subt(ptM1, ptM2);
	printf("\nFazendo subtração acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	//ac_multiplicação

	//ac_divisao (?)

	printf("\nComparando as duas matrizes: M1 e M2 são ");
	if (ptM1->Metodo->compara(ptM1, ptM2)) printf("iguais\n");
	else printf("diferentes\n");

	


	/* Aplicando as funções avançadas */

	// int newtamM1[] = { 5, 5 };
	// ptM1 = ptM1->Metodo->resize (ptM1, newtamM1);
	// printf("\n\nCopiar\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->ones (ptM1, [5,3])
	// printf("\n\nOnes\n")
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->identidade (ptM1, [5,3]);
	// printf("\n\nIdentidade\n")
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->multip_escalar (ptM1, 2);
	// printf("\n\nMultiplica por escalar\n")
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->dot (ptM1, ptM2);
	// printf("\n\nDot\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->transpor (ptM1);
	// printf("\n\nTranspor\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->transpor_diag2 (ptM1);
	// printf("\n\nTranspor diagonal 2\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->reverse_horizontal (ptM1);
	// printf("\n\nReversa horizontal\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->reverse_vertical (ptM1);
	// printf("\n\nReversa vertical\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->acrescenta_linha (ptM1);
	// printf("\n\nAcrescenta linha\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->acrescenta_coluna (ptM1);
	// printf("\n\nAcrescenta coluna\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	
	printf("\nDestruindo M1, M2 e M3");
	ptM1->Metodo->destroi(ptM1);
	// ptM2->Metodo->destroi(ptM2);
	// ptM3->Metodo->destroi(ptM3);

	return (0);
}








