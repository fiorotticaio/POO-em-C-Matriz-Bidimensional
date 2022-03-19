#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matriz.h"

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "MATRIZ"                  *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, MATRIZ).                          *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela vtbl da classe base.                   *
 * A redefinição da função na classe derivada sobrepõe a definição  *
 * da função na classe base.                                        *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso.                       *
 *                                                                  *
 * A redefinição da função virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as operações realmente executadas     *
 * por cada método da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, funções virtuais se comportam como *
 * qualquer outro tipo de função membro da classe. Entretanto, o que*
 * torna funções virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execução é o seu modo de comportamento   *
 * quando acessado através de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * contém uma função virtual, o programa irá determina qual versão  *
 * daquela função chamar baseada no tipo do objeto apontado pelo    *
 * apontador.                                                       *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/*------------------------------------------------------------------*
 * PROTOTIPOS DA IMPLEMENTACAO DAS FUNCOES VIRTUAIS                 *
 * note o "_" (underline) no final dos nomes das funções            *
 * Trata-se de uma convenção que usamos para nos lembrar que estas  *
 * funções são "static". Isto é: são declaradas e definidas pelo    *
 * compilador de tal forma que são reconhecidas apenas aqui dentro  *
 * deste arquivo  ____.c --> _______.o                              *
 * Estas funções não podem ser chamadas PELO NOME para serem        *
 * executadas por outros trechos de código em outros arquivos .c    *
 * Todavia, podem ser chamadas para serem executadas através de seus*
 * ENDEREÇOS. E são os endereços destas funções que são atribuídos  *
 * às respectivas posições da tabela vtbl que é apontada pelo campo *
 * super. O campo super a que se refere aqui é o PRIMEIRO campo da  *
 *                                                                  *
 * -----------------------------------------------------------------*/

static Numero_pt Matriz_copia_(Numero_t const *const me);
static Numero_pt Matriz_atribui_(Numero_t const *const me,Numero_t *const outro);
static Numero_pt Matriz_soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Matriz_subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Matriz_mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Matriz_divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res);
static Numero_pt Matriz_ac_soma_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Matriz_ac_subt_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Matriz_ac_mult_(Numero_t *const me, Numero_t const *const outro);
static Numero_pt Matriz_ac_divd_(Numero_t *const me, Numero_t const *const outro);
static int Matriz_compara_(Numero_t const *const me, Numero_t const *const outro);
static char *Matriz_imprime_(Numero_t const *const me);
static void Matriz_destroi_(Numero_t *me);


/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de Matriz *
 * -------------------------------------------------------------------*/

static Matriz_pt Copia_(Matriz_t const *const me);
static Matriz_pt Atribui_(Matriz_t const *const me, Matriz_t *const outro);
static Matriz_pt Soma_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);
static Matriz_pt Subt_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);
static Matriz_pt Mult_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);
static Matriz_pt Divd_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);
static Matriz_pt Ac_Soma_(Matriz_t *const me, Matriz_t const *const outro);
static Matriz_pt Ac_Subt_(Matriz_t *const me, Matriz_t const *const outro);
static Matriz_pt Ac_Mult_(Matriz_t *const me, Matriz_t const *const outro);
static Matriz_pt Ac_Divd_(Matriz_t *const me, Matriz_t const *const outro);
static int Compara_(Matriz_t const *const me, Matriz_t const *const outro);
static char *Imprime_(Matriz_t const *const me);
static void Destroi_(Matriz_t *me);


/*------------------ Outras funções ------------------------------------*/

static Matriz_pt Resize_ (Matriz_t * const me, unsigned int *tam);
static Matriz_pt Ones_ (Matriz_pt me, unsigned int *tam);
static Matriz_pt Identidade_ (Matriz_pt me, unsigned int *tam);
static Matriz_pt Multip_escalar_ (Matriz_t * const me, double escalar);
static Matriz_pt Dot_ (Matriz_t const * const me, Matriz_t const * const outro);
static Matriz_pt Transpor_ (Matriz_t * const me);
static Matriz_pt Transpor_diag2_ (Matriz_t const * const me);
static Matriz_pt Reverse_horizontal_ (Matriz_t * const me);
static Matriz_pt Reverse_vertical_ (Matriz_t * const me);
static Matriz_pt Acrescenta_linha_ (Matriz_t * const me);
static Matriz_pt Acrescenta_coluna_ (Matriz_t * const me);

static unsigned int * Get_tamanho_ (Matriz_t const * const me);
static double * Get_valores_ (Matriz_t const * const me);
static void Set_tamanho_ (Matriz_t * me, unsigned int * const tamanho);
static void Set_valores_ (Matriz_t const * me, double * valores);

/*-----------------------------------------------------------------------*/


 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
Matriz_pt Matriz_2d_criar (Matriz_pt  me, unsigned int * tam, double * mat) {
	/* tabela de funções virtuais da classe Numero_t *
	* Esta tabela estática será compartilhada por todos os números *
	* da classe Matriz_t                                        */

	static struct NumeroVtbl const vtbl = {
		&Matriz_copia_,
		&Matriz_atribui_,
		&Matriz_soma_,
		&Matriz_subt_,
		&Matriz_mult_,
		&Matriz_divd_,
		&Matriz_ac_soma_,
		&Matriz_ac_subt_,
		&Matriz_ac_mult_,
		&Matriz_ac_divd_,
		&Matriz_compara_,
		&Matriz_imprime_,
		&Matriz_destroi_
	};

	// me = (Matriz_pt) Num_constroi ((Numero_pt) me);
	me = (Matriz_pt) malloc(sizeof(Matriz_t));
	/* constroi o Numero_t  	*/
	/* no início de Matriz_t  */

	me->super.metodo = &vtbl;
	/* as operações do "numero", a partir de agora, */
	/* são as operações sobre matrizes              */
	/* metodo aponta para vtbl de Matriz_t 					*/

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	* "Matriz_t": a tabela de interface                          */
	static struct Matriz_Interface_st const interface = {
		&Copia_,
		&Atribui_,
		&Soma_,
		&Subt_,
		&Mult_,
		&Divd_,
		&Ac_Soma_,
		&Ac_Subt_,
		&Ac_Mult_,
		&Ac_Divd_,
		&Compara_,
		&Imprime_,
		&Destroi_,
		&Resize_,
		&Ones_,
		&Identidade_,
		&Multip_escalar_,
		&Dot_,
		&Transpor_,
		&Transpor_diag2_,
		&Reverse_horizontal_,
		&Reverse_vertical_,
		&Acrescenta_linha_,
		&Acrescenta_coluna_,
		&Get_tamanho_,
		&Get_valores_,
		&Set_tamanho_,
		&Set_valores_,
	};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de Matriz_t */
	/* as operações do "numero", a partir de agora */
	/* são as operações sobre matriz */

	/* aloca dinamicamente uma area de memoria para o tamanho da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->tam = (unsigned int *) malloc (2 * sizeof(unsigned int));
	if (me->tam == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores unsigned int do tamanho da matriz");
		exit (1);
	}
	// me->tam = tam;
	me->tam[0] = tam[0];
	me->tam[1] = tam[1];

	/* aloca dinamicamente uma area de memoria para os valores da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->mat = (double **) malloc (tam[0] * sizeof(double *));

	if (me->mat == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores de me->mat");
		exit (1);
	}

	int i, j, k=0;
	for (i = 0; i < tam[0]; i++) {
		me->mat[i] = (double *) malloc (tam[1] * sizeof(double));
		if (me->mat[i] == NULL)
		{	/*erro!!! não conseguiu alocar */
			printf ("Erro na alocação de memória em Matriz_2d_criar");
			printf ("Nao alocou os valores de me->mat[%d]", i);
			exit (1);
		}
		
		for(j=0;j<tam[1];j++){
			me->mat[i][j] = mat[k];
			k++;
		}
	}

	return (me);
}



/*----------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/

static Matriz_pt Copia_(Matriz_t const *const me){
	return ((Matriz_pt) Matriz_copia_ ((Numero_pt) me));
}
static Numero_pt Matriz_copia_(Numero_t const *const me){
	assert(me != NULL);
	Numero_pt outro = NULL;

	unsigned int * tam = Get_tamanho_((Matriz_pt)me);
	double * valores = Get_valores_((Matriz_pt)me);

	outro = (Numero_pt) Matriz_2d_criar((Matriz_pt)outro, tam, valores);

	return outro;
}

static Matriz_pt Atribui_(Matriz_t const *const me, Matriz_t *const outro){
	return ((Matriz_pt) Matriz_atribui_ ((Numero_pt) me, (Numero_pt)outro));
}
static Numero_pt Matriz_atribui_(Numero_t const *const me, Numero_t *const outro){
	/* Somente pra matrizes de tamanhos iguais */

	unsigned int * tam = Get_tamanho_((Matriz_pt)me);
	double * valores = Get_valores_((Matriz_pt)me);

	// Resize_((Matriz_pt) outro, tam);

	Set_tamanho_((Matriz_pt) outro, tam);
	Set_valores_((Matriz_pt) outro, valores);

	// return (Numero_pt) outro;
}

static Matriz_pt Soma_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_soma_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	int i, j;
	
	if ( ((Matriz_pt)me)->tam[0] != ((Matriz_pt)outro)->tam[0]) assert(0);

	for(i=0; i < ((Matriz_pt)me)->tam[0];i++){
		for(j=0; j < ((Matriz_pt)me)->tam[1];j++){
			((Matriz_pt)res)->mat[i][j] =  ((Matriz_pt)me)->mat[i][j] + ((Matriz_pt)outro)->mat[i][j];
		}
	}

	return (Numero_pt)res;
}

static Matriz_pt Subt_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_subt_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	int i, j;
	
	if ( ((Matriz_pt)me)->tam[0] != ((Matriz_pt)outro)->tam[0]) assert(0);

	for(i=0; i < ((Matriz_pt)me)->tam[0];i++){
		for(j=0; j < ((Matriz_pt)me)->tam[1];j++){
			((Matriz_pt)res)->mat[i][j] =  ((Matriz_pt)me)->mat[i][j] - ((Matriz_pt)outro)->mat[i][j];
		}
	}

	return (Numero_pt)res;
}

static Matriz_pt Mult_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_mult_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	int i, j, k;
	double somaProd;

	if (((Matriz_pt)me)->tam[1] != ((Matriz_pt)outro)->tam[0]) {
		printf("\nNao eh possivel multiplicar essas matrizes!\n");
		printf("O numero de colunas da primeira tem que ser igual ao numero de linhas da segunda!\n");

	} else {
		/* Algorítmo de multiplicação de matrizes */
		for (i = 0; i < ((Matriz_pt)me)->tam[0]; i++) {
			for (j = 0; j < ((Matriz_pt)outro)->tam[1]; j++) {
				somaProd = 0;
				for (k = 0; k < ((Matriz_pt)me)->tam[1]; k++) {
					somaProd += ((Matriz_pt)me)->mat[i][k] * ((Matriz_pt)outro)->mat[k][j];
				}
				((Matriz_pt)res)->mat[i][j] = somaProd;
			}
		}
	}

	return (Numero_pt) res;
}

static Matriz_pt Divd_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_divd_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_divd_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	//divide
}

static Matriz_pt Ac_Soma_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_soma_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_soma_(Numero_t *const me, Numero_t const *const outro){
	int i, j;
	
	if ( ((Matriz_pt)me)->tam[0] != ((Matriz_pt)outro)->tam[0]) assert(0);

	for(i=0; i < ((Matriz_pt)me)->tam[0];i++){
		for(j=0; j < ((Matriz_pt)me)->tam[1];j++){
			((Matriz_pt)outro)->mat[i][j] =  ((Matriz_pt)me)->mat[i][j] + ((Matriz_pt)outro)->mat[i][j];
		}
	}

	return (Numero_pt)outro;
}

static Matriz_pt Ac_Subt_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_subt_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_subt_(Numero_t *const me, Numero_t const *const outro){
	int i, j;
	
	if ( ((Matriz_pt)me)->tam[0] != ((Matriz_pt)outro)->tam[0]) assert(0);

	for(i=0; i < ((Matriz_pt)me)->tam[0];i++){
		for(j=0; j < ((Matriz_pt)me)->tam[1];j++){
			((Matriz_pt)outro)->mat[i][j] =  ((Matriz_pt)me)->mat[i][j] - ((Matriz_pt)outro)->mat[i][j];
		}
	}

	return (Numero_pt)outro;
}

static Matriz_pt Ac_Mult_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_mult_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_mult_(Numero_t *const me, Numero_t const *const outro){
	int i, j, k;
	double somaProd;

	if (((Matriz_pt)me)->tam[1] != ((Matriz_pt)outro)->tam[0]) {
		printf("\nNao eh possivel multiplicar essas matrizes!\n");
		printf("O numero de colunas da primeira tem que ser igual ao numero de linhas da segunda!\n");

	} else {
		Matriz_t * aux = NULL;
		aux = ((Matriz_t*)outro)->Metodo->copia((Matriz_t*)outro);

		/* Mudando o tamanho da segunda matriz pro tamanho resultante da multiplicação */
		int novoTam[] = { ((Matriz_pt)me)->tam[0], ((Matriz_pt)outro)->tam[1] };
		Resize_((Matriz_pt) outro, novoTam);

		/* Algorítmo de multiplicação de matrizes */
		for (i = 0; i < ((Matriz_pt)me)->tam[0]; i++) {
			for (j = 0; j < aux->tam[1]; j++) {
				somaProd = 0;
				for (k = 0; k < ((Matriz_pt)me)->tam[1]; k++) {
					somaProd += ((Matriz_pt)me)->mat[i][k] * aux->mat[k][j];
				}
				((Matriz_pt) outro)->mat[i][j] = somaProd;
			}
		}

		aux->Metodo->destroi(aux);
	}

	

	return (Numero_pt) outro;
}

static Matriz_pt Ac_Divd_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_divd_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_divd_(Numero_t *const me, Numero_t const *const outro){
	//divide acumulada
}

static int Compara_(Matriz_t const *const me, Matriz_t const *const outro){
	return (Matriz_compara_ ((Numero_pt) me, (Numero_pt) outro));
}
static int Matriz_compara_(Numero_t const *const me, Numero_t const *const outro){
	int i, j;
	if ( ((Matriz_pt)me)->tam[0] != ((Matriz_pt)outro)->tam[0]) return 0;

	for(i=0; i < ((Matriz_pt)me)->tam[0];i++){
		for(j=0; j < ((Matriz_pt)me)->tam[1];j++){
			if (((Matriz_pt)me)->mat[i][j] != ((Matriz_pt)outro)->mat[i][j]) return 0;
		}
	}
	return 1;
}


/*---------------------------------------------*
*        getters e setters                     *
* ---------------------------------------------*/

static unsigned int * Get_tamanho_ (Matriz_t const * const me){
	static unsigned int tamanho[2];

	
	tamanho[0] = me->tam[0];
	tamanho[1] = me->tam[1];
	
	return tamanho;
}
static double * Get_valores_ (Matriz_t const * const me){ 
	static double val[100];
	int i, j, k=0;
	
	for(i=0 ; i < me->tam[0] ; i++){
		for(j=0 ; j < me->tam[1] ; j++){
			val[k] = me->mat[i][j];
			k++;
		}
	}

	return val;
}
static void Set_tamanho_ (Matriz_t * me, unsigned int * const tamanho){ 
	int i, j, k=0;

	me->tam[0] = tamanho[0];
	me->tam[1] = tamanho[1];

	me->mat = (double **) realloc (me->mat, me->tam[0] * sizeof(double *));

	// Realocando espaço de memoria
	for (i = 0; i < me->tam[0]; i++) {
		me->mat[i] = (double *) realloc (me->mat[i], me->tam[1] * sizeof(double));
		for(j=0;j<me->tam[1];j++) if (!me->mat[i][j]) me->mat[i][j] = 0;
	}
	
 }
static void Set_valores_ (Matriz_t const * me, double * valores){ 
	int i=0, j=0, k=0;

	for(i=0;i < me->tam[0];i++){
		for(j=0;j < me->tam[1];j++){
			me->mat[i][j] = valores[k];
			k++;
		}
	}	
 }


/*---------------------------------------------*
*        funções avançadas                     *
* ---------------------------------------------*/

static inline Matriz_pt Resize_ (Matriz_t * const me,  unsigned int *tam) {
	Matriz_t * aux = NULL;
	aux = me->Metodo->copia(me);

	/* Atualizando o tamanho da matriz */
	me->tam[0] = tam[0];
	me->tam[1] = tam[1];

	/* realoca dinamicamente uma area de memoria para os valores da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->mat = (double **) realloc (me->mat, tam[0] * sizeof(double *));

	if (me->mat == NULL) {	
		/* erro!!! não conseguiu alocar */
		printf ("Erro na realocação de memória em Resize_");
		printf ("Nao realocou os valores de me->mat");
		exit (1);
	}


	int i = 0, j;
	for (i = 0; i < tam[0]; i++) {
		me->mat[i] = (double *) realloc (me->mat[i], tam[1] * sizeof(double));
		if (me->mat[i] == NULL) {
			/* erro!!! não conseguiu alocar */
			printf ("Erro na realocação de memória em Resize_");
			printf ("Nao realocou os valores de me->mat[%d]", i);
			exit (1);
		}

		if (i < aux->tam[0]) {
			for (j = 0; j < tam[1]; j++) {
				if (j < aux->tam[1]) { 
					//colocando os elementos antigos na nova matriz (mesmas linhas e mesmas colunas)
					me->mat[i][j] = aux->mat[i][j];
				} else { 
					//inserindo zeros nos novos espaços (mesma linha porem novas colunas)
					me->mat[i][j] = 0;
				}
			}

		} else { 
			//inserindo zeros nos novos espaços (novas linhas))
			for (j = 0; j < tam[1]; j++) {
				me->mat[i][j] = 0;
			}
		}
		
	}

	aux->Metodo->destroi(aux);
	return me;
}

static inline Matriz_pt Ones_ (Matriz_pt me, unsigned int *tam) {
	/* tabela de funções virtuais da classe Numero_t *
	* Esta tabela estática será compartilhada por todos os números *
	* da classe Matriz_t                                        */

	static struct NumeroVtbl const vtbl = {
		&Matriz_copia_,
		&Matriz_atribui_,
		&Matriz_soma_,
		&Matriz_subt_,
		&Matriz_mult_,
		&Matriz_divd_,
		&Matriz_ac_soma_,
		&Matriz_ac_subt_,
		&Matriz_ac_mult_,
		&Matriz_ac_divd_,
		&Matriz_compara_,
		&Matriz_imprime_,
		&Matriz_destroi_
	};

	// me = (Matriz_pt) Num_constroi ((Numero_pt) me);
	me = (Matriz_pt) malloc(sizeof(Matriz_t));
	/* constroi o Numero_t  	*/
	/* no início de Matriz_t  */

	me->super.metodo = &vtbl;
	/* as operações do "numero", a partir de agora, */
	/* são as operações sobre matrizes              */
	/* metodo aponta para vtbl de Matriz_t 					*/

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	* "Matriz_t": a tabela de interface                          */
	static struct Matriz_Interface_st const interface = {
		&Copia_,
		&Atribui_,
		&Soma_,
		&Subt_,
		&Mult_,
		&Divd_,
		&Ac_Soma_,
		&Ac_Subt_,
		&Ac_Mult_,
		&Ac_Divd_,
		&Compara_,
		&Imprime_,
		&Destroi_,
		&Resize_,
		&Ones_,
		&Identidade_,
		&Multip_escalar_,
		&Dot_,
		&Transpor_,
		&Transpor_diag2_,
		&Reverse_horizontal_,
		&Reverse_vertical_,
		&Acrescenta_linha_,
		&Acrescenta_coluna_,
		&Get_tamanho_,
		&Get_valores_,
		&Set_tamanho_,
		&Set_valores_,
	};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de Matriz_t */
	/* as operações do "numero", a partir de agora */
	/* são as operações sobre matriz */

	/* aloca dinamicamente uma area de memoria para o tamanho da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->tam = (unsigned int *) malloc (2*sizeof(unsigned int));
	if (me->tam == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores unsigned int do tamanho da matriz");
		exit (1);
	}
	me->tam = tam;

	/* aloca dinamicamente uma area de memoria para os valores da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->mat = (double **) malloc (tam[0] * sizeof(double *));

	if (me->mat == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores de me->mat");
		exit (1);
	}

	int i, j, k=0;
	for (i = 0; i < tam[0]; i++) {
		me->mat[i] = (double *) malloc (tam[1] * sizeof(double));
		if (me->mat[i] == NULL)
		{	/*erro!!! não conseguiu alocar */
			printf ("Erro na alocação de memória em Matriz_2d_criar");
			printf ("Nao alocou os valores de me->mat[%d]", i);
			exit (1);
		}
		
		for(j=0;j<tam[1];j++){
			me->mat[i][j] = 1;
		}
	}

	return (me);
}

static inline Matriz_pt Identidade_ (Matriz_pt me, unsigned int *tam) {
	/* tabela de funções virtuais da classe Numero_t *
	* Esta tabela estática será compartilhada por todos os números *
	* da classe Matriz_t                                        */

	static struct NumeroVtbl const vtbl = {
		&Matriz_copia_,
		&Matriz_atribui_,
		&Matriz_soma_,
		&Matriz_subt_,
		&Matriz_mult_,
		&Matriz_divd_,
		&Matriz_ac_soma_,
		&Matriz_ac_subt_,
		&Matriz_ac_mult_,
		&Matriz_ac_divd_,
		&Matriz_compara_,
		&Matriz_imprime_,
		&Matriz_destroi_
	};

	// me = (Matriz_pt) Num_constroi ((Numero_pt) me);
	me = (Matriz_pt) malloc(sizeof(Matriz_t));
	/* constroi o Numero_t  	*/
	/* no início de Matriz_t  */

	me->super.metodo = &vtbl;
	/* as operações do "numero", a partir de agora, */
	/* são as operações sobre matrizes              */
	/* metodo aponta para vtbl de Matriz_t 					*/

	/* Agora, mais uma tabela estática a ser compartilhada pelos     *
	* "Matriz_t": a tabela de interface                          */
	static struct Matriz_Interface_st const interface = {
		&Copia_,
		&Atribui_,
		&Soma_,
		&Subt_,
		&Mult_,
		&Divd_,
		&Ac_Soma_,
		&Ac_Subt_,
		&Ac_Mult_,
		&Ac_Divd_,
		&Compara_,
		&Imprime_,
		&Destroi_,
		&Resize_,
		&Ones_,
		&Identidade_,
		&Multip_escalar_,
		&Dot_,
		&Transpor_,
		&Transpor_diag2_,
		&Reverse_horizontal_,
		&Reverse_vertical_,
		&Acrescenta_linha_,
		&Acrescenta_coluna_,
		&Get_tamanho_,
		&Get_valores_,
		&Set_tamanho_,
		&Set_valores_,
	};

	me->Metodo = &interface;
	/* metodo aponta para vtbl de Matriz_t */
	/* as operações do "numero", a partir de agora */
	/* são as operações sobre matriz */

	/* aloca dinamicamente uma area de memoria para o tamanho da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->tam = (unsigned int *) malloc (2*sizeof(unsigned int));
	if (me->tam == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores unsigned int do tamanho da matriz");
		exit (1);
	}
	me->tam = tam;

	/* aloca dinamicamente uma area de memoria para os valores da matriz  */
	/* e atribui o endereço de memória alocada para o ponteiro */
	/* valor que está dentro da estrutura Matriz_st */
	me->mat = (double **) malloc (tam[0] * sizeof(double *));

	if (me->mat == NULL)
	{	/*erro!!! não conseguiu alocar */
		printf ("Erro na alocação de memória em Matriz_2d_criar");
		printf ("Nao alocou os valores de me->mat");
		exit (1);
	}

	int i, j, k=0;
	for (i = 0; i < tam[0]; i++) {
		me->mat[i] = (double *) malloc (tam[1] * sizeof(double));
		if (me->mat[i] == NULL)
		{	/*erro!!! não conseguiu alocar */
			printf ("Erro na alocação de memória em Matriz_2d_criar");
			printf ("Nao alocou os valores de me->mat[%d]", i);
			exit (1);
		}
		
		for (j = 0; j < tam[1]; j++) {
			if (i == j) {
				me->mat[i][j] = 1;
			} else {
				me->mat[i][j] = 0;
			}
		}
	}

	return (me);
}

static inline Matriz_pt Multip_escalar_ (Matriz_t * const me, double escalar) {
	int i, j;
	for (i = 0; i < me->tam[0]; i++) {
		for (j = 0; j < me->tam[1]; j++) {
			me->mat[i][j] *= 2;
		}
	}
	return (Matriz_pt) me;
}

static inline Matriz_pt Dot_ (Matriz_t const * const  me, Matriz_t const * const outro) {
	// dot
}

static inline Matriz_pt Transpor_ (Matriz_t * const  me) {
	Matriz_t * aux = NULL;
	aux = me->Metodo->copia(me);

	int novoTam[] = { me->tam[1], me->tam[0] };
	Resize_(me, novoTam);

	int i, j;
	for (i = 0; i < me->tam[0]; i++) {
		for (j = 0; j < me->tam[1]; j++) {
			me->mat[i][j] = aux->mat[j][i];
		}
	}

	aux->Metodo->destroi(aux);

	return (Matriz_pt) me;
}

static inline Matriz_pt Transpor_diag2_ (Matriz_t const * const  me) {
	// transpor em relação à diagonal secundária
}

static inline Matriz_pt Reverse_horizontal_ (Matriz_t * const  me) {
	Matriz_t * aux = NULL;
	aux = me->Metodo->copia(me);

	int i, j, m, n;
	for (i = 0, m = (me->tam[0])-1; i < me->tam[0]; i++, m--) {
		for (j = 0, n = 0; j < me->tam[1]; j++, n++) {
			me->mat[i][j] = aux->mat[m][n];
		}
	}
	aux->Metodo->destroi(aux);

	return (Matriz_pt) me;
}

static inline Matriz_pt Reverse_vertical_ (Matriz_t * const  me) {
	Matriz_t * aux = NULL;
	aux = me->Metodo->copia(me);

	int i, j, m, n;
	for (i = 0, m = 0; i < me->tam[0]; i++, m++) {
		for (j = 0, n = (me->tam[1])-1; j < me->tam[1]; j++, n--) {
			me->mat[i][j] = aux->mat[m][n];
		}
	}

	aux->Metodo->destroi(aux);

	return (Matriz_pt) me;
}

static inline Matriz_pt Acrescenta_linha_ (Matriz_t * const  me) {
	// Matriz_t * aux = NULL;
	// aux = me->Metodo->copia(me);

	int novoTam[] = { (me->tam[0])+1, me->tam[1] };
	Resize_(me, novoTam);

	// int i, j;
	// for (i = 0; i < me->tam[0]; i++) {
	// 	if (i < aux->tam[0]) {
	// 		for (j = 0; j < me->tam[1]; j++) {
	// 			me->mat[i][j] = aux->mat[i][j];
	// 		}
	// 	} else {
	// 		for (j = 0; j < me->tam[1]; j++) {
	// 			me->mat[i][j] = 0;
	// 		}
	// 	}
	// }

	// aux->Metodo->destroi(aux);

	return (Matriz_pt) me;
}

static inline Matriz_pt Acrescenta_coluna_ (Matriz_t * const  me){
	// Matriz_t * aux = NULL;
	// aux = me->Metodo->copia(me);

	int novoTam[] = { me->tam[0], (me->tam[1])+1 };
	Resize_(me, novoTam);

	// int i, j;
	// for (i = 0; i < me->tam[0]; i++) {
	// 	for (j = 0; j < me->tam[1]; j++) {
	// 		if (j < aux->tam[1]) {
	// 			me->mat[i][j] = aux->mat[i][j];
	// 		} else {
	// 			me->mat[i][j] = 0;
	// 		}
	// 	}
	// }

	// aux->Metodo->destroi(aux);

	return (Matriz_pt) me;
}


/*---------------------------------------------*
* implementação da impressão                   *
* ---------------------------------------------*/

static inline char * Imprime_  ( Matriz_t const * const  me) {
	return ( Matriz_imprime_ ((Numero_pt) me));
}
static inline char * Matriz_imprime_  (Numero_t const * const  me) {
	// static char buffer[100];
	// int i, j;

	// sprintf(buffer, "{");
	// for(i = 0; i < ((Matriz_pt) me)->tam[0]; i++){
	// 	sprintf(buffer, "%s\n\t", buffer);
	// 	for (j = 0; j < ((Matriz_pt) me)->tam[1]; j++) {
	// 		sprintf(buffer, "%s%.2lf\t", buffer, ((Matriz_pt) me)->mat[i][j]);
	// 	}
	// }
	// sprintf(buffer, "%s\n}\n", buffer);

	// return buffer;


	int i, j;

	// unsigned int newTam[] = { 5, 5 };
	// Set_tamanho_((Matriz_pt)me, newTam);

	// double newVal[] = { 
	// 	-1,	 		-2,	 			-3,	 			-4,	 		-5,	
	// 	-6,	 		-7,		 		-8,	 			-9,	 		-10,	
	// 	-11,	 	-12,			-13,	 		-14,	 	-15,	
	// 	-16,		-17,			-18,	 		-19,	 	-20,	
	// 	-21,	 	-22,			-23,	 		-24,	 	-25 };
	// Set_valores_((Matriz_pt)me, newVal);


	printf("{");
	for(i = 0; i < ((Matriz_pt) me)->tam[0]; i++){
		printf("\n\t");
		for (j = 0; j < ((Matriz_pt) me)->tam[1]; j++) {
			printf("%.2lf\t", ((Matriz_pt) me)->mat[i][j]);
		}
	}
	printf("\n}\n");

	return "";
}

/*---------------------------------------------*
* implementação do destrutor                   *
* ---------------------------------------------*/

static inline void Destroi_  (Matriz_t * me) {
	Matriz_destroi_ ((Numero_t *)  me);
}
static void Matriz_destroi_ (Numero_t * me) {
	for(int i = 0; i < ((Matriz_pt)me)->tam[0]; i++){
		if (((Matriz_pt) me)->mat[i]!=NULL) free(((Matriz_pt) me)->mat[i]);
	}
	if (((Matriz_pt) me)->mat!=NULL) free(((Matriz_pt) me)->mat);
	if (((Matriz_pt) me)->tam!=NULL) free(((Matriz_pt) me)->tam);
	if ((Matriz_pt)me!=NULL) free((Matriz_pt)me);
}