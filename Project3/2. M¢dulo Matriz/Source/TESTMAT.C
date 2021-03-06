/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TNAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*           JG - Jo�o Lucas Gardenberg
*           MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o   Autor      Data          Observa��es
*      2.01     GB,JG,MV   20/abr/2013   mudan�a no jeito como o par�metro � utilizado na fun��o de inserir.
*      2.00     GB,JG,MV   11/abr/2013   reformula��o de todas as fun��es
*      1.00     GB,JG,MV   28/mar/2013   in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*     
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*     "=criar" <Int> <Int> <Int>
*                    - chama a fun��o MAT_CriarMatriz( ).
*                      Obs. nota��o: O 1o <Int> � a altura da matriz.
*                      Obs. nota��o: O 2o <Int> � a largura da matriz.
*                      Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
*     "=destruir" <Int>
*                    - chama a fun��o MAT_DestruirMatriz( ).
*                      Obs. nota��o: <Int> � a condi��o de retorno esperada.
*     "=inserir" <Int> <Int> <Int> <Int>
*                    - chama a fun��o MAT_InserirValor( ).
*                      Obs. nota��o: O 1o <Int> � o valor a ser inserido.
*                      Obs. nota��o: O 2o <Int> � a linha onde o valor ser� inserido.
*                      Obs. nota��o: O 3o <Int> � a coluna onde o valor ser� inserido.
*                      Obs. nota��o: O 4o <Int> � a condi��o de retorno esperada.
*     "=obter" <Int> <Int> <Int> <Int>
*                    - chama a fun��o MAT_ObterValor( ).
*                      Obs. nota��o: O 1o <Int> � o valor esperado que ser� obtido.
*                      Obs. nota��o: O 2o <Int> � a linha onde o valor est�.
*                      Obs. nota��o: O 3o <Int> � a coluna onde o valor est�.
*                      Obs. nota��o: O 4o <Int> � a condi��o de retorno esperada.
*     "=obteraltlar" <Int> <Int> <Int>
*                    - chama a fun��o MAT_ObterAlturaLargura( ).
*                      Obs. nota��o: O 1o <Int> � a altura esperada da matriz.
*                      Obs. nota��o: O 2o <Int> � a largura esperada da matriz.
*                      Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
*
***************************************************************************/

#include	<string.h>
#include	<stdio.h>

#include	"TST_ESPC.H"

#include	"generico.h"
#include	"lerparm.h"

#include	"MATRIZ.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define 	CRIAR_MAT_CMD    	"=criar"
#define    	DESTRUIR_MAT_CMD	"=destruir"
#define    	INSERIR_MAT_CMD    	"=inserir"
#define    	OBTERVAL_MAT_CMD	"=obter"
#define     OBTER_ALT_LAR_CMD   "=obteraltlar"

/*****  Declara��es de vari�veis  *****/

    int AlturaObtida ;
	int LarguraObtida ;

	ptMatriz Matriz ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TMAT  Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{
		MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
		MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;

		char ValorEsperado = '?'  ;
		char ValorObtido   = '!'  ;
		char ValorDado 	= '\0' ;

		int  NumLidos = -1 ;

		TST_tpCondRet Ret;

		/* Testar Criar Matriz */

			if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
			{
     			int Altura = -1, Largura = -1 ;
     			NumLidos = LER_LerParametros( "iii" ,
                           			&Altura, &Largura, &CondRetEsperada ) ;

        			if ( NumLidos != 3 )
        			{
           				return TST_CondRetParm ;
        			} /* if */

        			CondRetObtido = MAT_CriarMatriz( &Matriz, Altura, Largura ) ;

        			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                			"Retorno errado ao criar matriz." ) ;
			} /* Fim Ativa: Testar CriarMatriz */
    
		/* Testar Destruir Matriz */

			else if( strcmp( ComandoTeste, DESTRUIR_MAT_CMD ) == 0 )
			{

     			NumLidos = LER_LerParametros( "i", &CondRetEsperada );

     			CondRetObtido = MAT_DestruirMatriz( Matriz );

     			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                			"Retorno errado ao destruir matriz." ) ;
			} /* Fim Ativa: Testar Destruir Matriz */

		/* Testar Inserir Valor no Elemento */

			else if( strcmp( ComandoTeste, INSERIR_MAT_CMD ) == 0 )
			{
     			int Linha = -1, Coluna = -1, Valor = -1 ;

     			NumLidos = LER_LerParametros( "iiii", &Valor,
                                    			&Linha, &Coluna, &CondRetEsperada ) ;

     			CondRetObtido = MAT_InserirValor( Matriz, (int *) Valor, Linha, Coluna ) ;

     			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                			"Retorno errado ao inserir elemento em matriz." ) ;
			} /* Fim Ativa: Testar Inserir Valor */

		/* Testar Obter Valor do Elemento */

			else if( strcmp( ComandoTeste, OBTERVAL_MAT_CMD ) == 0 )
			{

     			int Linha = -1, Coluna = -1, ValorObtido = -1, ValorEsperado = -1 ;
				void * ValObtido ;

     			NumLidos = LER_LerParametros( "iiii", &ValorEsperado, &Linha, &Coluna, &CondRetEsperada ) ;

     			CondRetObtido = MAT_ObterValor( Matriz, Linha, Coluna, &ValObtido ) ;

				ValorObtido = (int) ValObtido ;

     			Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
                            			"Retorno errado ao obter valor." ) ;

     			if ( Ret != TST_CondRetOK || CondRetObtido != MAT_CondRetOK )
     			{
         			return Ret ;
     			} /* if */

     			return TST_CompararInt( ValorEsperado, ValorObtido,
                            			"Valor errado do elemento."  ) ;

			} /* Fim Ativa: Testar Obter Elemento */

		/* Testar Obter Altura e Largura da Matriz */

			else if( strcmp( ComandoTeste, OBTER_ALT_LAR_CMD ) == 0 )
			{
				int AlturaEsperada = 0, LarguraEsperada = 0 ;

				NumLidos = LER_LerParametros( "iii", &AlturaEsperada, &LarguraEsperada, &CondRetEsperada ) ;

				CondRetObtido = MAT_ObterAlturaLargura( Matriz, &AlturaObtida, &LarguraObtida ) ;

				Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
					                   "Retorno errado ao obter altura e largura da matriz." ) ;

				if( Ret != TST_CondRetOK || CondRetObtido != MAT_CondRetOK )
				{
					return Ret ;
				} /* if */

				Ret = TST_CompararInt( AlturaEsperada, AlturaObtida,
					                    "Valor errado da altura." ) ;

				if( Ret != TST_CondRetOK )
				{
					return Ret ;
				} /* if */

				Ret = TST_CompararInt( LarguraEsperada, LarguraObtida,
					                   "Valor errado da largura." ) ;

				return Ret ;

			} /* Fim Ativa: Testar Obter Altura e Largura da Matriz */

		return TST_CondRetNaoConhec ;
	} /* Fim fun��o: TMAT  Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/