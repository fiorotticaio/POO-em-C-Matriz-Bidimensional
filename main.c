#include <stdio.h>
#include "matriz.h"

int main () {
	Matriz_pt ptM1 = NULL, ptM2 = NULL, ptM3 = NULL, ptM4 = NULL, ptM5 = NULL;
	Matriz_pt ptO1 = NULL, ptI1 = NULL;

	/* Criando as matrizes (DIMENSÃO MÁXIMA DE 10 x 10) */ 
	unsigned int tamM1[] = { 5, 3 };
	double valM1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
	ptM1 = Matriz_2d_criar (ptM1, tamM1, valM1);

	unsigned int tamM2[] = { 5, 3 };
	double valM2[] = { 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0 };
	ptM2 = Matriz_2d_criar (ptM2, tamM2, valM2);

	unsigned int tamM4[] = { 3, 5 };
	double valM4[] = { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };
	ptM4 = Matriz_2d_criar (ptM4, tamM4, valM4);

	unsigned int tamM5[] = { 5, 5 };
	double valM5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	ptM5 = Matriz_2d_criar (ptM5, tamM5, valM5);

	printf("\nM1:"); ptM1->Metodo->imprime(ptM1);
	
	printf("\nM2:"); ptM2->Metodo->imprime(ptM2);

	/* Aplicando as funções básicas*/

	printf("\nCopiando a M1 para M3\nM3:"); ptM3 = ptM1->Metodo->copia(ptM1); ptM3->Metodo->imprime(ptM3);

	printf("\nAtribuindo M1 a M2\nM2:"); ptM1->Metodo->atribui(ptM1, ptM2); ptM2->Metodo->imprime(ptM2); 

	ptM2 = ptM2->Metodo->soma(ptM1, ptM2, ptM2); printf("\nSomando M1 com M2 e aplicando em M2\nM2:"); ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->subt(ptM1, ptM2, ptM2); printf("\nSubtraindo M2 de M1 e aplicando em M2\nM2:"); ptM2->Metodo->imprime(ptM2);

	printf("\nM1:"); ptM1->Metodo->imprime(ptM1);
	
	printf("\nM4:"); ptM4->Metodo->imprime(ptM4);

	ptM1 = ptM1->Metodo->mult(ptM1, ptM2, ptM1); printf("\nMultiplicação escalar entre M1 com M2 atribuido em M1\nM1:"); ptM1->Metodo->imprime(ptM1);

	//divisao (?)
	// multiplicação entre a primeira e a inversa da segunda
	// naquelas funcções avançadas não tem inverter, então...

	ptM2 = ptM2->Metodo->ac_soma(ptM1, ptM2); printf("\nFazendo soma acumulada entre M1 e M2\nM2:"); ptM2->Metodo->imprime(ptM2);

	ptM2 = ptM2->Metodo->ac_subt(ptM1, ptM2); printf("\nFazendo subtração acumulada entre M1 e M2\nM2:"); ptM2->Metodo->imprime(ptM2);

	ptM4 = ptM1->Metodo->ac_mult(ptM1, ptM4); printf("\nMultiplicação escalar acumulada entre M1 com M4\nM4:"); ptM4->Metodo->imprime(ptM4);

	//ac_divisao (?)

	printf("\nComparando as duas matrizes: M1 e M2 são "); if (ptM1->Metodo->compara(ptM1, ptM2)) printf("iguais\n"); else printf("diferentes\n");

	
	/* Aplicando as funções avançadas */

	unsigned int newTamM1[] = { 5, 5 }; ptM1 = ptM1->Metodo->resize(ptM1, newTamM1); printf("\nM1 mudando de { 5, 3 } para { 5, 5}\nM1:"); ptM1->Metodo->imprime(ptM1);

	unsigned int tamOnes[] = { 5, 3 }; ptO1 = ptM1->Metodo->ones (ptO1, tamOnes); 	printf("\nCriando matriz de 1's (%d x %d)\n01:", tamOnes[0], tamOnes[1]); ptO1->Metodo->imprime(ptO1);

	unsigned int tamI1[] = { 3, 3 }; ptI1 = ptM1->Metodo->identidade (ptI1, tamI1); printf("\nCriando matriz identidade (%d x %d)\nI1:", tamI1[0], tamI1[1]); ptI1->Metodo->imprime(ptI1);

	ptM1 = ptM1->Metodo->multip_escalar (ptM1, 2); printf("\nM1 Multiplicada por 2\nM1:"); ptM1->Metodo->imprime(ptM1);

	// ptM1 = ptM1->Metodo->dot (ptM1, ptM2);
	// printf("\n\nDot\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	ptM1 = ptM1->Metodo->transpor (ptM1); printf("\nTranspondo M1\nM1:"); ptM1->Metodo->imprime(ptM1);

	// ptM1 = ptM1->Metodo->transpor_diag2 (ptM1);
	// printf("\n\nTranspor diagonal 2\n");
	// printf("%s", ptM1->Metodo->imprime(ptM1));

	//NAO TA AO CONTRARIO NAO? ESSA TA REVERSA VERTICALMENTE E A VERTICAL TA HORIZONTALMENTE???
	ptM1 = ptM1->Metodo->reverse_horizontal (ptM1); printf("\nM1 reversa horizontalmente\nM1:"); ptM1->Metodo->imprime(ptM1);

	ptM1 = ptM1->Metodo->reverse_vertical (ptM1); printf("\nM1 reversa verticalmente\nM1:"); ptM1->Metodo->imprime(ptM1);

	ptM1 = ptM1->Metodo->acrescenta_linha (ptM1); printf("\nAcrescentando uma linha a M1\nM1:"); ptM1->Metodo->imprime(ptM1);

	ptM1 = ptM1->Metodo->acrescenta_coluna (ptM1); printf("\nAcrescentando uma coluna a M1\nM1:"); ptM1->Metodo->imprime(ptM1);

	unsigned int newTamM2[] = { 6, 3 }; ptM2 = ptM2->Metodo->resize(ptM2, newTamM2); printf("\nM2 mudando de { 5, 3 } para { 6, 3 }\nM2:"); ptM2->Metodo->imprime(ptM2);

	ptM1 = ptM1->Metodo->dot(ptM1, ptM2); printf("Fazendo multiplicação vetorial entre M1 e M2 e armazenando em M1\nM1:"); ptM1->Metodo->imprime(ptM1);

	ptM1 = ptM1->Metodo->remove_coluna(ptM1); printf("\nRemovendo uma coluna de M1\nM1:"); ptM1->Metodo->imprime(ptM1);
	
	ptM1 = ptM1->Metodo->remove_linha(ptM1); printf("\nRemovendo uma linha de M1\nM1:"); ptM1->Metodo->imprime(ptM1);
	
	//ADICIONAR FUNÇÃO DE IVNERSA
	
	printf("\nDestruindo M1, M2, M3, M4, M5, O1 e I1\n");
	ptM1->Metodo->destroi(ptM1);
	ptM2->Metodo->destroi(ptM2);
	ptM3->Metodo->destroi(ptM3);
	ptM4->Metodo->destroi(ptM4);
	ptM5->Metodo->destroi(ptM5);
	ptO1->Metodo->destroi(ptO1);
	ptI1->Metodo->destroi(ptI1);

	return (0);
}