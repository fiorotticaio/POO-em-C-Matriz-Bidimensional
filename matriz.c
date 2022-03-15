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

static Matriz_pt Resize_ (Matriz_t const * const me, unsigned int *tam);
static Matriz_pt Ones_ (Matriz_t const * const me, unsigned int *tam);
static Matriz_pt Identidade_ (Matriz_t const * const me, unsigned int *tam);
static Matriz_pt Multip_escalar_ (Matriz_t const * const me, double escalar);
static Matriz_pt Dot_ (Matriz_t const * const me, Matriz_t const * const outro);
static Matriz_pt Transpor_ (Matriz_t const * const me);
static Matriz_pt Transpor_diag2_ (Matriz_t const * const me);
static Matriz_pt Reverse_horizontal_ (Matriz_t const * const me);
static Matriz_pt Reverse_vertical_ (Matriz_t const * const me);
static Matriz_pt Acrescenta_linha_ (Matriz_t const * const me);
static Matriz_pt Acrescenta_coluna_ (Matriz_t const * const me);

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

	me = (Matriz_pt) Num_constroi ((Numero_pt) me);
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
		me->mat[i] = (double *) malloc (tam[1]*sizeof(double));
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
	//copia
}

static Matriz_pt Atribui_(Matriz_t const *const me, Matriz_t *const outro){
	return ((Matriz_pt) Matriz_atribui_ ((Numero_pt) me, (Numero_pt)outro));
}
static Numero_pt Matriz_atribui_(Numero_t const *const me,Numero_t *const outro){
	//atribui
}

static Matriz_pt Soma_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_soma_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_soma_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	//soma
}

static Matriz_pt Subt_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_subt_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_subt_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	//subtrai
}

static Matriz_pt Mult_(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res){
	return ((Matriz_pt) Matriz_mult_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}
static Numero_pt Matriz_mult_(Numero_t const *const me, Numero_t const *const outro, Numero_t *const res){
	//multiplica
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
	//soma acumulada
}

static Matriz_pt Ac_Subt_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_subt_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_subt_(Numero_t *const me, Numero_t const *const outro){
	//subtração acumulada
}

static Matriz_pt Ac_Mult_(Matriz_t *const me, Matriz_t const *const outro){
	return ((Matriz_pt) Matriz_ac_mult_ ((Numero_pt) me, (Numero_pt) outro));
}
static Numero_pt Matriz_ac_mult_(Numero_t *const me, Numero_t const *const outro){
	//multiplica acumulada
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
	//compara
}

/*---------------------------------------------*
*        outras funções                        *
* ---------------------------------------------*/

static inline Matriz_pt Resize_ (Matriz_t const * const  me,  unsigned int *tam) {
	// resize
}

static inline Matriz_pt Ones_ (Matriz_t const * const  me, unsigned int *tam) {
	// ones
}

static inline Matriz_pt Identidade_ (Matriz_t const * const  me, unsigned int *tam) {
	// identidade
}

static inline Matriz_pt Multip_escalar_ (Matriz_t const * const  me, double escalar) {
	// multiplica escalar
}

static inline Matriz_pt Dot_ (Matriz_t const * const  me, Matriz_t const * const outro) {
	// dot
}

static inline Matriz_pt Transpor_ (Matriz_t const * const  me) {
	// transpor
}

static inline Matriz_pt Transpor_diag2_ (Matriz_t const * const  me) {
	// transpor em relação à diagonal secundária
}

static inline Matriz_pt Reverse_horizontal_ (Matriz_t const * const  me) {
	// troca as posições das linhas (última vira primeira)
}

static inline Matriz_pt Reverse_vertical_ (Matriz_t const * const  me) {
	// troca as posições das colunas
}

static inline Matriz_pt Acrescenta_linha_ (Matriz_t const * const  me) {
	// acrescenta uma linha na matriz, preenchendo com zeros
}

static inline Matriz_pt Acrescenta_coluna_ (Matriz_t const * const  me){
	// acrescenta uma coluna na matriz, preenchendo com zeros
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

static inline void Destroi_  ( Matriz_t  *   me) {
	Matriz_destroi_ ((Numero_t *)  me);
}

static void Matriz_destroi_ (Numero_t *  me) {
	// for(int i = 0; i < me->tam[0]; i++){
  //       free(((Matriz_pt) me)->mat[i]);
  //   }
  //   free((Numero_t **) me);
}
