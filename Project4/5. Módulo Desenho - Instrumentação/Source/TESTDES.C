/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:          	DESTMAT.C
*  Letras identificadoras:  	TDES
*
*  Nome da base de software:	Exemplo de teste automatizado
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
*  	Este m�dulo cont�m as fun��es espec�ficas para o teste do
*  	m�dulo desenho. Ilustra como redigir um interpretador de comandos
*  	de teste espec�ficos utilizando o arcabou�o de teste para C.
*	 
*  $EIU Interface com o usu�rio pessoa
*  	Comandos de teste espec�ficos para testar o m�dulo desenho:
*
* 	"=gerarmatriz" <Int> <Int> <Int>
*                	- chama a fun��o DES_GerarMatriz( ).
*                  	Obs. nota��o: O 1o <Int> � a altura da matriz.
*                  	Obs. nota��o: O 2o <Int> � a largura da matriz.
*                  	Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
* 	"=altestadocorreto" <Int> <Int> <Int>
*                	- chama a fun��o DES_AlterarEstadoCorreto( ).
*                  	Obs. nota��o: O 1o <Int> � a linha onde o estado correto ser� alterado.
*                  	Obs. nota��o: O 2o <Int> � a coluna onde o estado correto ser� alterado.
*                  	Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
* 	"=altestadoatual" <Int> <Int> <Int>
*                	- chama a fun��o DES_AlterarEstadoAtual( ).
*                  	Obs. nota��o: O 1o <Int> � a linha onde o estado atual ser� alterado.
*                  	Obs. nota��o: O 2o <Int> � a coluna onde o estado atual ser� alterado.
*                  	Obs. nota��o: O 3o <Int> � a condi��o de retorno esperada.
* 	"=obterestadocorreto" <Int> <Int> <Int> <Int>
*                	- chama a fun��o DES_ObterEstadoCorreto( ).
*                  	Obs. nota��o: O 1o <Int> � o estado correto esperado.
*                  	Obs. nota��o: O 2o <Int> � a linha onde o estado correto ser� obtido.
*                  	Obs. nota��o: O 3o <Int> � a coluna onde o estado correto ser� obtido.
*                  	Obs. nota��o: O 4o <Int> � a condi��o de retorno esperada.
* 	"=obterestadoatual" <Int> <Int> <Int> <Int>
*                	- chama a fun��o DES_ObterEstadoAtual( ).
*                  	Obs. nota��o: O 1o <Int> � o estado atual esperado.
*                  	Obs. nota��o: O 2o <Int> � a linha onde o estado atual ser� obtido.
*                  	Obs. nota��o: O 3o <Int> � a coluna onde o estado atual ser� obtido.
*                  	Obs. nota��o: O 4o <Int> � a condi��o de retorno esperada.
* 	"=desenharatual" <Int>
*                	- chama a fun��o DES_DesenharAtual( ).
*                  	Obs. nota��o: O <Int> � a condi��o de retorno esperada.
* 	"=desenharcorreto" <Int>
*                	- chama a fun��o DES_DesenharCorreto( ).
*                  	Obs. nota��o: O <Int> � a condi��o de retorno esperada.
*
***************************************************************************/

#include	<string.h>
#include	<stdio.h>

#include	"TST_ESPC.H"

#include	"generico.h"
#include	"lerparm.h"

#include	"DESENHO.H"
#include	"CONTA.H"
#include	"CESPDIN.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define  	GERAR_MATRIZ_CMD        	"=gerarmatriz"
#define  	ALT_ESTADO_CORRETO_CMD  	"=altestadocorreto"
#define  	ALT_ESTADO_ATUAL_CMD    	"=altestadoatual"
#define  	OBT_ESTADO_CORRETO_CMD  	"=obterestadocorreto"
#define  	OBT_ESTADO_ATUAL_CMD    	"=obterestadoatual"
#define		DESENHAR_ATUAL_CMD			"=desenharatual"
#define		DESENHAR_CORRETO_CMD		"=desenharcorreto"
#define		DETURPA_CMD					"=deturpar"
#define		VERIFICA_CMD				"=verifica"
#define		DESTROI_CMD					"=destruir"

ptDesenho pDesenho;
int LinhaMatrizValores, ColunaMatrizValores ;

ptDesenho VetDesenhos[10];

/***********************************************************************
*
*  $FC Fun��o: TDES  Efetuar opera��es de teste espec�ficas para desenho
*
*  $ED Descri��o da fun��o
*  	Efetua os diversos comandos de teste espec�ficos para o m�dulo
*  	desenho sendo testado.
*
*  $EP Par�metros
*  	$P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*  	Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{
    
    	DES_tpCondRet CondRetObtido   = DES_CondRetOK ;
    	DES_tpCondRet CondRetEsperada = DES_CondRetFaltouMemoria ;

    	int  NumLidos = -1 ;
		int AcaoDeturpa;
		int NumErros = 0;
		int NumDesenho;
		char tipoElemento = 'C' ;

   	 TST_tpCondRet Ret ;

    	/* Testar Gera Matriz */

        	if ( strcmp( ComandoTeste , GERAR_MATRIZ_CMD ) == 0 )
        	{
             	int Altura = -1, Largura = -1 ;
				NumLidos = LER_LerParametros( "ciiii" ,
                                   	&tipoElemento, &NumDesenho, &Altura, &Largura, &CondRetEsperada ) ;

             	if ( NumLidos != 5 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

				CondRetObtido = DES_GerarMatrizes( &VetDesenhos[NumDesenho], Altura, Largura, tipoElemento ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao gerar matrizes." ) ;
        	} /* Fim Ativa: Testar Gera Matriz */
    
    	/* Testar Alterar Estado Correto */

        	else if ( strcmp( ComandoTeste , ALT_ESTADO_CORRETO_CMD ) == 0 )
        	{
             	int Linha = -1, Coluna = -1 ;
             	NumLidos = LER_LerParametros( "iiii" ,
                                   	&NumDesenho, &Linha, &Coluna, &CondRetEsperada ) ;

             	if ( NumLidos != 4 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

             	CondRetObtido = DES_AlterarEstadoCorreto( VetDesenhos[NumDesenho], Linha, Coluna ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao alterar estado correto." ) ;
        	} /* Fim Ativa: Testar Alterar Estado Correto */

    	/* Testar Alterar Estado Atual */

        	else if ( strcmp( ComandoTeste , ALT_ESTADO_ATUAL_CMD ) == 0 )
        	{
             	int Linha = -1, Coluna = -1 ;
             	NumLidos = LER_LerParametros( "iiii" ,
                                   	&NumDesenho, &Linha, &Coluna, &CondRetEsperada ) ;

             	if ( NumLidos != 4 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

             	CondRetObtido = DES_AlterarEstadoAtual( VetDesenhos[NumDesenho], Linha, Coluna ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao alterar estado atual." ) ;
        	} /* Fim Ativa: Testar Alterar Estado Atual */

    	/* Testar Obter Estado Correto */

        	else if ( strcmp( ComandoTeste , OBT_ESTADO_CORRETO_CMD ) == 0 )
        	{
   			 int Linha = -1, Coluna = -1, EstadoEsperado, EstadoObtido ;
   			 NumLidos = LER_LerParametros( "iiiii", &NumDesenho, &EstadoEsperado
   				               	, &Linha, &Coluna, &CondRetEsperada ) ;

   			 if( NumLidos != 5 )
   			 {
   				 return TST_CondRetParm ;
   			 } /* if */

   			 CondRetObtido = DES_ObterEstadoCorreto( VetDesenhos[NumDesenho], Linha, Coluna, &EstadoObtido ) ;

   			 Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
   				                	"Retorno errado ao obter estado correto." ) ;

   			 if( Ret != TST_CondRetOK || CondRetObtido != DES_CondRetOK )
   			 {
   				 return Ret ;
   			 } /* if */

   			 return TST_CompararInt( EstadoEsperado, EstadoObtido,
   				                      	"Valor errado do estado ao obter estado correto." ) ;
   		 } /* Fim Ativa: Testar Obter Estado Correto */

    	/* Testar Obter Estado Atual */

        	else if ( strcmp( ComandoTeste , OBT_ESTADO_ATUAL_CMD ) == 0 )
        	{
   			 int Linha = -1, Coluna = -1, EstadoEsperado, EstadoObtido ;
   			 NumLidos = LER_LerParametros( "iiiii", &NumDesenho, &EstadoEsperado
													, &Linha, &Coluna, &CondRetEsperada ) ;

   			 if( NumLidos != 5 )
   			 {
   				 return TST_CondRetParm ;
   			 } /* if */

   			 CondRetObtido = DES_ObterEstadoAtual( VetDesenhos[NumDesenho], Linha, Coluna, &EstadoObtido ) ;

   			 Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
   				                	"Retorno errado ao obter estado atual." ) ;

   			 if( Ret != TST_CondRetOK || CondRetObtido != DES_CondRetOK )
   			 {
   				 return Ret ;
   			 } /* if */

   			 return TST_CompararInt( EstadoEsperado, EstadoObtido,
   				                      	"Valor errado do estado ao obter estado atual." ) ;
   		 } /* Fim Ativa: Testar Obter Estado Atual */

    	/* Testar Desenhar Atual */

        	else if ( strcmp( ComandoTeste , DESENHAR_ATUAL_CMD ) == 0 )
        	{
             	NumLidos = LER_LerParametros( "ii" ,
                                   	&NumDesenho, &CondRetEsperada ) ;

             	if ( NumLidos != 2 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

				printf("\n\n");
             	CondRetObtido = DES_DesenharAtual( VetDesenhos[NumDesenho] ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao fazer o desenho atual." ) ;
        	} /* Fim Ativa: Testar Desenhar Atual */

		/* Testar Desenhar Correto */

        	else if ( strcmp( ComandoTeste , DESENHAR_CORRETO_CMD ) == 0 )
        	{
             	NumLidos = LER_LerParametros( "ii" ,
                                   	&NumDesenho, &CondRetEsperada ) ;

             	if ( NumLidos != 2 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

				printf("\n\n");
             	CondRetObtido = DES_DesenharCorreto( VetDesenhos[NumDesenho] ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao fazer o desenho correto." ) ;
        	} /* Fim Ativa: Testar Desenhar Correto */

		/* Testar DES Deturpa */

         else if ( strcmp( ComandoTeste , DETURPA_CMD ) == 0 )
         {
			int AcaoDeturpadora;
            NumLidos = LER_LerParametros( "iii" , &NumDesenho, &CondRetEsperada, &AcaoDeturpa) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_Deturpar( VetDesenhos[NumDesenho], AcaoDeturpa ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao verificar se o jogo terminou." );

         } /* fim ativa: Testar DES Deturpa */

		/* Testar DES Verifica */

		 else if ( strcmp( ComandoTeste , VERIFICA_CMD ) == 0 )
         {
		
			int numErrosEsperados;
			int numErrosOcorridos;
            NumLidos = LER_LerParametros( "ii" , &NumDesenho, &numErrosEsperados) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            DES_Verifica( VetDesenhos[NumDesenho], &numErrosOcorridos ) ;

            return TST_CompararInt( numErrosEsperados , numErrosOcorridos ,
                                    "Contagem de erros errada." );

         } /* fim ativa: Testar DES Verifica */

		 else if( strcmp(ComandoTeste, DESTROI_CMD) == 0 )
		 {
			CED_InicializarIteradorEspacos();
			while( CED_ExisteEspacoCorrente() != 0)
			{
				CED_ExcluirEspacoCorrente();
			}

			return TST_CondRetOK;
		 }

    	return TST_CondRetNaoConhec ;
   	 
	} /* Fim fun��o: TMAT  Efetuar opera��es de teste espec�ficas para matriz */



/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
