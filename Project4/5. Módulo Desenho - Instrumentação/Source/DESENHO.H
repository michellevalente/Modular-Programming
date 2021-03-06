#if ! defined( DESENHO_ )
#define DESENHO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: DES  M�dulo Desenho
*
*  Arquivo gerado:          	DESENHO.H
*  Letras identificadoras:  	DES
*
*  Nome da base de software:  Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*       	JG - Jo�o Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*  	Vers�o   Autor  	Data      	Observa��es
*  	1.00 	GB,JG,MV   12/abr/2014   in�cio desenvolvimento
*   2.00    GB,JG,MV   16/mai/2014   remo��o da fun��o de criar e preencher as matrizes de valores.
*   2.00    GB,JG,MV   16/mai/2014   modifica��o da fun��o de criar a matriz principal. agora ela tamb�m cria as matrizes de valores
*   2.01    GB,JG,MV   16/mai/2014   modifica��o brusca da fun��o de alterar estado correto.
*   2.02    GB,JG,MV   16/mai/2014   adi��o das fun��os de desenhar atual e correto. remo��o da fun��o anterior de desenhar
*
*  $ED Descri��o do m�dulo
*  	M�dulo que gera e gerencia o desenho utilizado no Jogo.
*
***************************************************************************/
 
#if defined( DESENHO_OWN )
	#define DESENHO_EXT
#else
	#define DESENHO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/


/* Tipo refer�ncia para um desenho */

	typedef struct tgDesenho * ptDesenho ;

/***********************************************************************
*
*  $TC Tipo de dados: DES Condi��es de retorno
*
*  $ED Descri��o do tipo
*  	Condi��es de retorno das fun��es do valor
*
***********************************************************************/

	typedef enum {

		DES_CondRetOK,
           	/* Concluiu corretamente */

		DES_CondRetFaltouMemoria,
           	/* Faltou mem�ria ao tentar alocar espa�o */

		DES_CondRetDesenhoNaoExiste,
           	/* O Desenho n�o existe */

		DES_CondRetMatrizNaoExiste,
           	/* Alguma das matrizes n�o existe quando devia existir */

		DES_CondRetMatrizVazia,
           	/* Alguma das matrizes est� vazia */

		DES_CondRetCelNaoExiste,
           	/* Alguma c�lula n�o existe quando devia existir */

		DES_CondRetEstadoCelInvalido,
			/* Alguma c�lula est� com o estado inv�lido */

		DES_CondRetValorNaoExiste,
			/* Algum valor n�o existe quando devia existir */

		DES_CondRetFimColunas,
			/* Foi atingido o fim das colunas de alguma matriz */

		DES_CondRetFimLinhas
			/* Foi atingido o fim das linhas de alguma matriz */

		#ifdef _DEBUG
			

			,DES_CondRetListasNaoCoerentes,
			/* Listas nao estao coerentes com as celulas preenchidas */

			DES_CondRetTamanhoMatrizErrado,
			/* Tamanho da matriz nao esta coerente com a cardinalidade */

			DES_CondRetTamanhoListaLinhaErrado,
			/* Tamanho da matriz ListaLinha nao esta coerente com a cardinalidade */

			DES_CondRetTamanhoListaColunaErrado
			/* Tamanho da matriz ListaColuna nao esta coerente com a cardinalidade */

		#endif

	} DES_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: DES &Gerar Matrizes
*
*  $ED Descri��o da fun��o
*  	Gera as matrizes (a de c�lulas e as duas de valores) do jogo.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho a ser criado.
*  	Altura - Altura da matriz a ser criada.
*  	Largura - Largura da matriz a ser criada.
*
*  $FV Valor retornado
*    	DES_CondRetOK
*    	DES_CondRetFaltouMemoria
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Altura e largura s�o n�meros inteiros
*                                 	maiores que zero.	 
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => pDesenho ter� sido criado com
*                                 	com uma matriz contendo valores do tipo Celula, e
*                                   duas matrizes contendo valores do tipo Valor.
*                                 	DES_CondRetFaltouMemoria => pDesenho == NULL.
*    
*
***********************************************************************/

	DES_tpCondRet DES_GerarMatrizes( ptDesenho * pDesenho, 
										int Altura, 
										int Largura
#ifdef _DEBUG
										, char tipoElemento
#endif
										) ;

/***********************************************************************
*
*  $FC Fun��o: DES &Alterar Estado Correto
*
*  $ED Descri��o da fun��o
*  	Altera o Estado Correto da c�lula cujas coordenadas s�o passadas e preenche a coluna e a linha
*   respectiva das matrizes de valores.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da c�lula.
*  	Coluna - Coluna da c�lula.
*
*  $FV Valor retornado
*  	DES_CondRetOK
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*   DES_CondRetValorNaoExiste
*	DES_CondRetFimColunas
*   DES_CondRetFimLinhas
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna s�o n�meros inteiros maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => Estado Correto da c�lula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como par�metro ir� alterar. As
*                                   matrizes de valores tamb�m ir�o alterar nas respectivas linha e coluna.
*                                 	DES_CondRetDesenhoNaoExiste => pDesenho n�o altera.
*                                 	DES_CondRetMatrizNaoExiste => pDesenho n�o altera.
*                                 	DES_CondRetMatrizVazia => pDesenho n�o altera.
*                                 	DES_CondRetCelNaoExiste => pDesenho n�o altera.
*                                   DES_CondRetValorNaoExiste => pDesenho n�o altera.
*
***********************************************************************/

	DES_tpCondRet DES_AlterarEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna ) ;

/***********************************************************************
*
*  $FC Fun��o: DES &Alterar Estado Atual
*
*  $ED Descri��o da fun��o
*  	Altera o Estado Atual da c�lula cujas coordenadas s�o passadas.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da c�lula.
*  	Coluna - Coluna da c�lula.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste

*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna s�o n�meros inteiros
*                                 	maiores que zero.
*                                   Esta fun��o � intencionada a ser executada AP�S todas as chamadas 
*                                   da fun��o DES &Alterar Estado Correto (que preenche as matrizes).
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => Estado Atual da c�lula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como par�metro ir� alterar.
*                                 	DES_CondRetDesenhoNaoExiste => pDesenho n�o altera.
*                                 	DES_CondRetMatrizNaoExiste => pDesenho n�o altera.
*                                 	DES_CondRetMatrizVazia => pDesenho n�o altera.
*                                 	DES_CondRetCelNaoExiste => pDesenho n�o altera.
*    
*
***********************************************************************/

	DES_tpCondRet DES_AlterarEstadoAtual( ptDesenho pDesenho, 
											int Linha, 
											int Coluna ) ;


/***********************************************************************
*
*  $FC Fun��o: DES &Obter Estado Correto
*
*  $ED Descri��o da fun��o
*  	Obt�m o Estado Correto da c�lula cujas coordenadas s�o passadas.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da c�lula.
*  	Coluna - Coluna da c�lula.
*  	pValor - Ponteiro onde o estado ser� armazenado.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna s�o n�meros inteiros
*                                 	maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOK => Estado Correto da c�lula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como par�metro ser� obtido
*                                 	via pValor.
*                                 	Com qualquer outro retorno, nenhum valor � obtido.
*
***********************************************************************/

	DES_tpCondRet DES_ObterEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna, 
											int * pValor ) ;


/***********************************************************************
*
*  $FC Fun��o: DES &Obter Estado Atual
*
*  $ED Descri��o da fun��o
*  	Obt�m o Estado Atual da c�lula cujas coordenadas s�o passadas.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da c�lula.
*  	Coluna - Coluna da c�lula.
*  	pValor - Ponteiro onde o estado ser� armazenado.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna s�o n�meros inteiros
*                                 	maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOK => Estado Atual da c�lula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como par�metro ser� obtido
*                                 	via pValor.
*                                 	Com qualquer outro retorno, nenhum valor � obtido.
*
***********************************************************************/

	DES_tpCondRet DES_ObterEstadoAtual( ptDesenho pDesenho, 
										int Linha, 
										int Coluna, 
										int * pValor ) ;


/***********************************************************************
*
*  $FC Fun��o: DES &Desenhar atual
*
*  $ED Descri��o da fun��o
*  	Desenha na tela a matriz de c�lulas com seus estados atuais, as 
*   matrizes de valores � esquerda e em cima, e se as linhas/colunas
*   est�o corretas � direita e em baixo. "o" significa que a linha/coluna
*   est� correta. "x" significa que a linha/coluna est� errada.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*
*  $FV Valor retornado
* 	 DES_CondRetOK
* 	 DES_CondRetDesenhoNaoExiste
* 	 DES_CondRetMatrizNaoExiste
* 	 DES_CondRetMatrizVazia
* 	 DES_CondRetValorNaoExiste
* 	 DES_CondRetCelNaoExiste
* 	 DES_CondRetEstadoCelInvalido
*
*  Assertivas de entradas esperadas - pDesenho != NULL.  
*
*  Assertivas de saidas esperadas   - O desenho do estado atual do jogo na tela.
*
***********************************************************************/

	DES_tpCondRet DES_DesenharAtual( ptDesenho pDesenho ) ;


/***********************************************************************
*
*  $FC Fun��o: DES &Desenhar correto
*
*  $ED Descri��o da fun��o
*  	Desenha na tela a matriz de c�lulas com seus estados corretosas 
*   matrizes de valores � esquerda e em cima, e obviamente (o)'s �
*   direita e em baixo, indicando como seria o desenho correto.
*
*  $EP Par�metros
*  	pDesenho - Ponteiro para o campo desenho.
*
*  $FV Valor retornado
* 	 DES_CondRetOK
* 	 DES_CondRetDesenhoNaoExiste
* 	 DES_CondRetMatrizNaoExiste
* 	 DES_CondRetMatrizVazia
* 	 DES_CondRetCelNaoExiste
* 	 DES_CondRetEstadoCelInvalido
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*
*  Assertivas de saidas esperadas   - O desenho do estado correto do jogo na tela.
*
***********************************************************************/

	DES_tpCondRet DES_DesenharCorreto( ptDesenho pDesenho ) ;

#ifdef _DEBUG
	DES_tpCondRet DES_Verifica ( ptDesenho pDesenho, int* numErros );
	DES_tpCondRet DES_Deturpar( ptDesenho pDesenho, int acao );
#endif
#undef DES_EXT

/********** Fim do m�dulo de defini��o: DES  M�dulo Desenho **********/

#else
#endif
