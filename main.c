#include <stdio.h>
#include "matriz.h"

int main () {
	Matriz_pt ptM1 = NULL, ptM2 = NULL;

	/* Criando as matrizes */
	int tamM1[] = { 5, 3 };
	double valM1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
	ptM1 = Matriz_2d_criar (ptM1, tamM1, valM1);

	printf("M1: ");
	printf("%s\n", ptM1->Metodo->imprime(ptM1));

	// ptM2 = Matriz_2d_criar (ptM1, [5,3], [13,14,15,16,17,18,19,20,21,22,23,24]);
	// printf("\n\nMatriz criada\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));


	// /* Aplicando as funções */
	// ptM1 = ptM1->Metodo->resize (ptM1, [5,3]);
	// printf("\n\nResize\n");
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


	// /* Outras funções */
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

	
	// /* Liberando o espaço de memória */
	// ptM1->Metodo->destroi (ptM1);
	// ptM2->Metodo->destroi (ptM2);

	return (0);
}








