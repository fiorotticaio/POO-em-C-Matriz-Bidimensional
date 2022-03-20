#include <stdio.h>
#include "matriz.h"

int main () {
	Matriz_pt ptM1 = NULL, ptM2 = NULL, ptM3 = NULL, ptM4 = NULL, ptM5 = NULL;
	Matriz_pt ptO1 = NULL, ptI1 = NULL;

	int comparacao;

	/*  ==================== CRIANDO AS MATRIZES ==================== */ 

	unsigned int tamM1[] = { 5, 3 };
	double valM1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0 };
	ptM1 = Matriz_2d_criar (ptM1, tamM1, valM1);

	unsigned int tamM2[] = { 5, 3 };
	double valM2[] = { 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0 };
	ptM2 = Matriz_2d_criar (ptM2, tamM2, valM2);

	unsigned int tamM4[] = { 3, 5 };
	double valM4[] = { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 };
	ptM4 = Matriz_2d_criar (ptM4, tamM4, valM4);

	unsigned int tamM5[] = { 3, 3 };
	double valM5[] = { 3, 5, 2, 1, 5, 8, 3, 9, 2 };
	ptM5 = Matriz_2d_criar (ptM5, tamM5, valM5);

	/*  ==================== APLICANDO AS FUNÇÇÕES BÁSICAS ==================== */
	
	
	// Imprimindo matrizes M1 e M2
	printf("\nM1:"); 
	ptM1->Metodo->imprime(ptM1);
	printf("\nM2:");
	ptM2->Metodo->imprime(ptM2);
	
	
	// Copia de toda a estrutura da matriz
	printf("\nCopiando a M1 para M3\nM3:");
	ptM3 = ptM1->Metodo->copia(ptM1);
	ptM3->Metodo->imprime(ptM3);


	// Atribuição dos valores de uma matriz à outra
	ptM1->Metodo->atribui(ptM1, ptM2);
	printf("\nAtribuindo M1 a M2\nM2:"); 
	ptM2->Metodo->imprime(ptM2); 



	// Soma entre matrizes
	ptM2 = ptM2->Metodo->soma(ptM1, ptM2, ptM2);
	printf("\nSomando M1 com M2 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);



	// Subtração entre matrizes
	ptM2 = ptM2->Metodo->subt(ptM1, ptM2, ptM2);
	printf("\nSubtraindo M2 de M1 e aplicando em M2\nM2:");
	ptM2->Metodo->imprime(ptM2);



	// Imprimindo matrizes M1 e M4
	printf("\nM1:"); ptM1->Metodo->imprime(ptM1);
	printf("\nM4:"); ptM4->Metodo->imprime(ptM4);


	// Multiplicação escalar (elemento à elemento) entre matrizes
	ptM1 = ptM1->Metodo->mult(ptM1, ptM2, ptM1);
	printf("\nMultiplicação escalar entre M1 com M2 atribuido em M1\nM1:");
	ptM1->Metodo->imprime(ptM1);

	
	// Divisão escalar (elemento à elemento) entre matrizes
	ptM1 = ptM1->Metodo->divd(ptM1, ptM2, ptM1);
	printf("\nDivisão escalar entre M1 com M2 atribuido em M1\nM1:");
	ptM1->Metodo->imprime(ptM1);

	
	// Soma entre matrizes de forma acumulada (na segunda matriz) 
	ptM2 = ptM2->Metodo->ac_soma(ptM1, ptM2);
	printf("\nFazendo soma acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);
		

	// Subtração entre matrizes de forma acumulada (na segunda matriz) 
	ptM2 = ptM2->Metodo->ac_subt(ptM1, ptM2);
	printf("\nFazendo subtração acumulada entre M1 e M2\nM2:");
	ptM2->Metodo->imprime(ptM2);


	// Multiplicação escalar entre matrizes de forma acumulada (na segunda matriz) 
	ptM2= ptM1->Metodo->ac_mult(ptM1, ptM2);
	printf("\nMultiplicação escalar acumulada entre M1 com M2\nM2:");
	ptM2->Metodo->imprime(ptM2);


	// Divisão escalar entre matrizes de forma acumulada (na segunda matriz) 
	ptM2 = ptM1->Metodo->ac_divd(ptM1, ptM2);
	printf("\nDivisão escalar acumulada entre M1 com M2\nM2:");
	ptM2->Metodo->imprime(ptM2);


	// Comparação entre tamanho e elementos de matrizes	
	printf("\nComparando as duas matrizes: M1 e M2 "); 
	comparacao = ptM1->Metodo->compara(ptM1, ptM2);
	if (!comparacao) printf("são iguais\n"); 
	else if (comparacao>0) printf("têm tamanhos e/ou valores diferentes\n");
	else if (comparacao<0) printf("têm apenas valores diferentes\n");




	
	/*  ==================== APLICANDO AS FUNÇÇÕES AVANÇADAS ==================== */


	// Redimensionamento de matrizes
	unsigned int newTamM1[] = { 5, 5 };
	ptM1 = ptM1->Metodo->resize(ptM1, newTamM1);
	printf("\nM1 mudando de { 5, 3 } para { 5, 5}\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Matriz com algarismo 1 em todos os seus espaços
	unsigned int tamOnes[] = { 5, 3 };
	ptO1 = ptM1->Metodo->ones (ptO1, tamOnes);
	printf("\nCriando matriz de 1's (%d x %d)\n01:", tamOnes[0], tamOnes[1]);
	ptO1->Metodo->imprime(ptO1);


	// Matriz identidade
	unsigned int tamI1[] = { 3, 3 };
	ptI1 = ptM1->Metodo->identidade (ptI1, tamI1);
	printf("\nCriando matriz identidade (%d x %d)\nI1:", tamI1[0], tamI1[1]);
	ptI1->Metodo->imprime(ptI1);


	// Multiplicação de uma matriz por um escalar
	ptM1 = ptM1->Metodo->multip_escalar (ptM1, 2);
	printf("\nM1 Multiplicada por 2\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Transposição de matriz em relação à digonal principal
	ptM1 = ptM1->Metodo->transpor (ptM1);
	printf("\nTranspondo M1\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Transposição de matriz em relação à digonal secundária
	ptM1 = ptM1->Metodo->transpor_diag2 (ptM1);
	printf("\nTranspondo M1 na diagonal secundária\n");
	printf("%s", ptM1->Metodo->imprime(ptM1));


	// Espelhamento horizontal dos valores da matriz
	ptM1 = ptM1->Metodo->reverse_horizontal (ptM1);
	printf("\nM1 reversa horizontalmente\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Espelhamento vertical dos valores da matriz
	ptM1 = ptM1->Metodo->reverse_vertical (ptM1);
	printf("\nM1 reversa verticalmente\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Acréscimo de uma linha à matriz
	ptM1 = ptM1->Metodo->acrescenta_linha (ptM1);
	printf("\nAcrescentando uma linha a M1\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Acréscimo de uma coluna à matriz
	ptM1 = ptM1->Metodo->acrescenta_coluna (ptM1);
	printf("\nAcrescentando uma coluna a M1\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Multiplicação vetorial entre matrizes
	unsigned int newTamM2[] = { 6, 3 };
	ptM2 = ptM2->Metodo->resize(ptM2, newTamM2);
	printf("\nM2 mudando de { 5, 3 } para { 6, 3 }\nM2:");
	ptM2->Metodo->imprime(ptM2);

	ptM1 = ptM1->Metodo->dot(ptM1, ptM2);
	printf("Fazendo multiplicação vetorial entre M1 e M2 e armazenando em M1\nM1:");
	ptM1->Metodo->imprime(ptM1);


	// Deleção da ultima coluna na matriz
	ptM1 = ptM1->Metodo->remove_coluna(ptM1);
	printf("\nRemovendo a última coluna de M1\nM1:");
	ptM1->Metodo->imprime(ptM1);
	
	// Deleção da ultima coluna na matriz
	ptM1 = ptM1->Metodo->remove_linha(ptM1);
	printf("\nRemovendo a última linha de M1\nM1:");
	ptM1->Metodo->imprime(ptM1);
	

	// Impressão da matriz M5
	printf("\nM5:"); ptM5->Metodo->imprime(ptM5);

	// Inversão de matriz
	ptM5 = ptM5->Metodo->inversa(ptM5);
	printf("\nInversa de M5 (aprox)\nM5:");
	ptM5->Metodo->imprime(ptM5);
	
	/*  ==================== APLICANDO A DESTRUIÇÃO DE MATRIZES ==================== */

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