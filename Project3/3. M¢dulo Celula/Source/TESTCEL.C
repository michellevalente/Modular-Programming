/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTCEL.C
*  Letras identificadoras:      TCEL
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*           JG - Jo�o Lucas Gardenberg
*           MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o  Autor      Data          Observa��es
*      1.00    GB,JG,MV   12/abr/2014   Corre��es das condi��es de retorno
*                                       e par�metros por refer�ncia.
*      1.00    GB,JG,MV   03/abr/2014   In�cio do desenvolvimento.
*
*  $ED Descri��o do m�dulo
*     
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo c�lula:
*
*     "=criar" <Int> <Int>
*                    - chama a fun��o CEL_CriarCelula( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=destruir" <Int> <Int>
*                    - chama a fun��o CEL_DestruirCelula( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=obteratual" <Int> <Int> <Int>
*                    - chama a fun��o CEL_ObterEstadoAtual( ) e compara o valor
*                      retornado com o 2o <Int>.
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � o estado atual esperado.
*                      Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
*     "=obtercorreto" <Int> <Int> <Int>
*                    - chama a fun��o CEL_ObterEstadoCorreto( ) e compara o valor
*                      retornado com o 2o <Int>.
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � o estado correto esperado.
*                      Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
*     "=alteraratual" <Int> <Int>
*                    - chama a fun��o CEL_AlterarEstadoAtual( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=alterarcorreto" <Int> <Int>
*                    - chama a fun��o CEL_AlterarEstadoCorreto( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=comparar" <Int> <Int> <Int>
*                    - chama a fun��o CEL_CompararEstados( ) e compara o valor 
*                      retornado com o 2o <Int>.
*                      Obs. nota��o: O 1o <Int> � o n�mero da c�lula.
*                      Obs. nota��o: O 2o <Int> � a compara��o esperada.
*                      0 = Iguais; 1 = Diferentes.
*                      Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CELULA.H"

#define		NUM_CELULAS			2

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_CEL_CMD         "=criar"
#define     DESTRUIR_CEL_CMD      "=destruir"
#define     OBTER_ATUAL_CMD       "=obteratual"
#define     OBTER_CORRETO_CMD     "=obtercorreto"
#define     ALTERAR_ATUAL_CMD     "=alteraratual"
#define     ALTERAR_CORRETO_CMD   "=alterarcorreto"
#define     COMPARAR_CEL_CMD      "=comparar"

/*****  Declara��es de vari�veis  *****/

   ptCelula VetCelula [ NUM_CELULAS ] ;
            /* Vetor contendo os ponteiros para as c�lulas */

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TCEL Efetuar opera��es de teste espec�ficas para c�lula
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     c�lula sendo testado.
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
	  
      CEL_tpCondRet CondRetObtido   = CEL_CondRetOK ;
      CEL_tpCondRet CondRetEsperada = CEL_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
	  int NumCelula ;
	  int ValorEsperado = 0 ;
      int ValorObtido   = 0 ;

	  int  NumLidos = -1 ;

	  TST_tpCondRet Ret ;

	  /* Testar CEL Criar c�lula */

	     if( strcmp( ComandoTeste, CRIAR_CEL_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "ii",
				                          &NumCelula,
										  &CondRetEsperada ) ;
			if( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRetObtido = CEL_CriarCelula( &VetCelula[ NumCelula-1 ] ) ;

			return TST_CompararInt( CondRetEsperada,
				                    CondRetObtido,
				                    "Retorno errado ao criar c�lula." ) ;

		 } /* fim ativa: Testar CEL Criar c�lula */

	  /* Testar CEL Destruir c�lula */

	     else if( strcmp( ComandoTeste, DESTRUIR_CEL_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "ii",
				                          &NumCelula,
										  &CondRetEsperada ) ;
			if( NumLidos != 2 )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRetObtido = CEL_DestruirCelula( VetCelula[ NumCelula-1 ] ) ;

			return TST_CompararInt( CondRetEsperada,
				                    CondRetObtido,
				                    "Retorno errado ao destruir c�lula." ) ;

		 } /* fim ativa: Testar CEL Destruir c�lula */

	  /* Testar CEL Obter estado atual da c�lula */

	     else if( strcmp( ComandoTeste, OBTER_ATUAL_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "iii",
				                          &NumCelula,
										  &ValorEsperado,
										  &CondRetEsperada ) ;
			if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = CEL_ObterEstadoAtual( VetCelula[ NumCelula-1 ],
				                                  &ValorObtido              ) ;

			Ret = TST_CompararInt( CondRetEsperada,
				                   CondRetObtido,
								   "Retorno errado ao obter estado atual." ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararInt( ValorEsperado,
				                    ValorObtido,
									"Conte�do do estado atual da c�lula est� errado." ) ;

		 } /* fim ativa: Testar CEL Obter estado atual da c�lula */

	  /* Testar CEL Obter estado correto da c�lula */

	     else if( strcmp( ComandoTeste, OBTER_CORRETO_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "iii",
				                          &NumCelula,
										  &ValorEsperado,
										  &CondRetEsperada ) ;
			if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = CEL_ObterEstadoCorreto( VetCelula[ NumCelula-1 ],
				                                     &ValorObtido             ) ;

			Ret = TST_CompararInt( CondRetEsperada,
				                   CondRetObtido,
								   "Retorno errado ao obter estado correto da c�lula." ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararInt( ValorEsperado,
				                    ValorObtido,
									"Conte�do do estado correto da c�lula est� errado." ) ;

		 } /* fim ativa: Testar CEL Obter estado correto da c�lula */

	  /* Testar CEL Alterar estado atual da c�lula */

	     else if( strcmp( ComandoTeste, ALTERAR_ATUAL_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "ii",
				                           &NumCelula,
										   &CondRetEsperada ) ;
			if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = CEL_AlterarEstadoAtual( VetCelula[ NumCelula-1 ] ) ;

			return TST_CompararInt( CondRetEsperada,
				                    CondRetObtido,
									"Retorno errado ao alterar estado atual da c�lula." ) ;

		 } /* fim ativa: Testar CEL Alterar estado atual da c�lula */

	  /* Testar CEL Alterar estado correto da c�lula */

	     else if( strcmp( ComandoTeste, ALTERAR_CORRETO_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "ii",
				                           &NumCelula,
										   &CondRetEsperada ) ;
			if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = CEL_AlterarEstadoCorreto( VetCelula[ NumCelula-1 ] ) ;

			return TST_CompararInt( CondRetEsperada,
				                    CondRetObtido,
									"Retorno errado ao alterar estado correto da c�lula." ) ;

		 } /* fim ativa: Testar CEL Alterar estado correto da c�lula */

	  /* Testar CEL Comparar estados da c�lula */

	     else if( strcmp( ComandoTeste, COMPARAR_CEL_CMD ) == 0 )
		 {

            NumLidos = LER_LerParametros( "iii",
				                          &NumCelula,
										  &ValorEsperado,
										  &CondRetEsperada ) ;
			if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = CEL_CompararEstados( VetCelula[ NumCelula-1 ],
				                                 &ValorObtido              ) ;

			Ret = TST_CompararInt( CondRetEsperada,
				                   CondRetObtido,
								   "Retorno errado ao comparar estados da c�lula." ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararInt( ValorEsperado,
				                    ValorObtido,
									"O valor retornado pela compara��o dos estados da c�lula est� errado." ) ;

		 } /* fim ativa: Testar CEL Comparar estados da c�lula */

   } /* Fim fun��o: TCEL Efetuar opera��es de teste espec�ficas para c�lula */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/