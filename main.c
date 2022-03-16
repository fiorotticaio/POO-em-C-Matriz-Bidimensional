#include <stdio.h>
#include "matriz.h"

int main () {
	Matriz_pt ptM1 = NULL, ptM2 = NULL, ptM3 = NULL, ptM4 = NULL, ptM5 = NULL;
	Matriz_pt ptO1 = NULL;

	/* Criando as matrizes (DIMENSÃO MÁXIMA DE 10 x 10) */ 
	int tamM1[] = { 5, 3 };
	double valM1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
	ptM1 = Matriz_2d_criar (ptM1, tamM1, valM1);

	int tamM2[] = { 5, 3 };
	double valM2[] = { 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0 };
	ptM2 = Matriz_2d_criar (ptM2, tamM2, valM2);

	int tamM4[] = { 3, 5 };
	double valM4[] = { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };
	ptM4 = Matriz_2d_criar (ptM4, tamM4, valM4);

	int tamM5[] = { 5, 5 };
	double valM5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	ptM5 = Matriz_2d_criar (ptM5, tamM5, valM5);

	printf("\nM1:");
	ptM1->Metodo->imprime(ptM1);
	
	printf("\nM2:");
	ptM2->Metodo->imprime(ptM2);

	printf("\nM4:");
	ptM4->Metodo->imprime(ptM4);

	
	/* Aplicando as funções básicas*/

	printf("\nCopiando a M1 para M3\nM3:");
	ptM3 = ptM1->Metodo->copia(ptM1);
	ptM3->Metodo->imprime(ptM3);

	// atribui (?)
	// se as matrizes tiverem tamanhos diferentes tem que fazer o resize

	ptM2 = ptM2->Metodo->soma(ptM1, ptM2, ptM2);
	printf("\nSomando M1 com M2 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->subt(ptM1, ptM2, ptM2);
	printf("\nSubtraindo M2 de M1 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM5 = ptM5->Metodo->mult(ptM1, ptM4, ptM5);
	printf("\nMultiplicando M1 com M4 e colocando o resultado em M5\nM5:");
	ptM5->Metodo->imprime(ptM5);

	//divisao (?)
	// multiplicação entre a primeira e a inversa da segunda
	// naquelas funcções avançadas não tem inverter, então...

	ptM2 = ptM2->Metodo->ac_soma(ptM1, ptM2);
	printf("\nFazendo soma acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->ac_subt(ptM1, ptM2);
	printf("\nFazendo subtração acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);

	//ac_mult (?)
	// mais complicado pois vai ter que mexer com o tamanho da matriz

	//ac_divisao (?)

	printf("\nComparando as duas matrizes: M1 e M2 são ");
	if (ptM1->Metodo->compara(ptM1, ptM2)) printf("iguais\n");
	else printf("diferentes\n");

	
	/* Aplicando as funções avançadas */

	// int newTamM1[] = { 5, 5 };
	// ptM1 = ptM1->Metodo->resize(ptM1, newTamM1);
	// printf("\nResize\nM1:");
	// ptM1->Metodo->imprime(ptM1);

	// int tamO1[] = { 5, 3 };
	// ptO1 = ptO1->Metodo->ones (ptO1, tamO1);
	// printf("\nOnes\nO1:");
	// ptM1->Metodo->imprime(ptM1);

	// ptM1 = ptM1->Metodo->identidade (ptM1, [5,3]);
	// printf("\n\nIdentidade\n")
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	ptM1 = ptM1->Metodo->multip_escalar (ptM1, 2);
	printf("\nM1 Multiplicada por 2\nM1:");
	ptM1->Metodo->imprime(ptM1);

	// ptM1 = ptM1->Metodo->dot (ptM1, ptM2);
	// printf("\n\nDot\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->transpor (ptM1);
	// printf("\n\nTranspor\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->transpor_diag2 (ptM1);
	// printf("\n\nTranspor diagonal 2\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	ptM1 = ptM1->Metodo->reverse_horizontal (ptM1);
	printf("\nM1 reversa horizontalmente\nM1:");
	ptM1->Metodo->imprime(ptM1);

	ptM1 = ptM1->Metodo->reverse_vertical (ptM1);
	printf("\nM1 reversa verticalmente\nM1:");
	ptM1->Metodo->imprime(ptM1);

	// ptM1 = ptM1->Metodo->acrescenta_linha (ptM1);
	// printf("\n\nAcrescenta linha\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	// ptM1 = ptM1->Metodo->acrescenta_coluna (ptM1);
	// printf("\n\nAcrescenta coluna\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	
	printf("\nDestruindo M1, M2, M3, M4 e M5");
	ptM1->Metodo->destroi(ptM1);
	// ptM2->Metodo->destroi(ptM2);
	// ptM3->Metodo->destroi(ptM3);
	// ptM4->Metodo->destroi(ptM4);
	// ptM5->Metodo->destroi(ptM5);

	return (0);
}