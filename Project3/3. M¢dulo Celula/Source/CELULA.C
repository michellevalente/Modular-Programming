/***************************************************************************
*  $MCI M�dulo de implementa��o: CEL  C�lula
*
*  Arquivo gerado:          	CELULA.c
*  Letras identificadoras:  	CEL
*
*  Nome da base de software:	Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*       	JG - Jo�o Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o  Autor      Data          Observa��es
*      1.00    GB,JG,MV   12/abr/2014   Corre��es das condi��es de retorno
*                                       e par�metros por refer�ncia.
*      1.00    GB,JG,MV   03/abr/2014   In�cio do desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <malloc.h>

#define CELULA_OWN
#include "CELULA.h"
#undef CELULA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: CEL C�lula
*
*
***********************************************************************/

   typedef struct tgCelula {
    	 
     	int EstadoAtual ;
           	/* Estado atual da c�lula
           	*
           	*$EED Assertivas estruturais
           	*   Vari�vel booleana.
           	*   Se for 1, a c�lula atualmente est� preenchida.
           	*   Se for 0, a c�lula atualmente est� vazia.
           	*   � inicializado com 0. */
    	 
     	int EstadoCorreto ;
           	/* Estado correto da c�lula
           	*
           	*$EED Assertivas estruturais
           	*   Vari�vel booleana.
           	*   Se for 1, o estado correto da c�lula � preenchida.
           	*   Se for 0, o estado correto da c�lula � vazia.
           	*   � inicializado com 0. */
    	 
   } tpCelula ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CEL Criar c�lula
*  ****/

   CEL_tpCondRet CEL_CriarCelula( ptCelula * pCelula )
   {
   
   	if( *pCelula != NULL )
   	{
       	CEL_DestruirCelula( *pCelula ) ;
   	} /* if */

  	*pCelula = ( tpCelula * ) malloc( sizeof( tpCelula ) ) ;
  	if( *pCelula == NULL )
  	{
      	return CEL_CondRetFaltouMemoria ;
  	} /* if */
 	 
  	/* Inicializar os estados com 0 (vazia) */

     	(*pCelula)->EstadoAtual = 0 ;
     	(*pCelula)->EstadoCorreto = 0 ;
 	 
  	return CEL_CondRetOK ;
 	 
   } /* Fim fun��o: CEL Criar c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Destruir c�lula
*  ****/
   
   CEL_tpCondRet CEL_DestruirCelula( ptCelula pCelula )
   {
   
  	if( pCelula != NULL )
  	{
     	free( pCelula ) ;
     	pCelula = NULL ;
  	} /* if */

  	return CEL_CondRetOK ;
 	 
   } /* Fim fun��o: CEL Destruir c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Obter estado atual da c�lula
*  ****/
   
   CEL_tpCondRet CEL_ObterEstadoAtual( ptCelula pCelula, int * Estado )
   {
   
  	if( pCelula == NULL ) {
     	return CEL_CondRetCelulaNaoExiste ;
  	} /* if */
 	 
  	if( pCelula->EstadoAtual == 1 )
  	{
     	/* Passar por refer�ncia o estado atual (preenchida) */
       	 
        	*Estado = 1 ;
        	return CEL_CondRetOK ;
  	} else if ( pCelula->EstadoAtual == 0 ) {
     	/* Passar por refer�ncia o estado atual (vazia) */
       	 
        	*Estado = 0 ;
        	return CEL_CondRetOK ;
  	} else {
     	/* Se o estado estiver diferente de 1 ou 0, � um estado inv�lido */
       	 
        	*Estado = -1 ;
        	return CEL_CondRetEstadoInvalido ;
  	} /* if */
    	 
   } /* Fim fun��o: CEL Obter estado atual da c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Obter estado correto da c�lula
*  ****/
   
   CEL_tpCondRet CEL_ObterEstadoCorreto( ptCelula pCelula, int * Estado )
   {
   
  	if( pCelula == NULL ) {
     	return CEL_CondRetCelulaNaoExiste ;
  	} /* if */
 	 
  	if( pCelula->EstadoCorreto == 1 )
  	{
     	/* Passar por refer�ncia o estado correto (preenchida) */
       	 
        	*Estado = 1 ;
        	return CEL_CondRetOK ;
  	} else if ( pCelula->EstadoCorreto == 0 ) {
     	/* Passar por refer�ncia o estado correto (vazia) */
       	 
        	*Estado = 0 ;
        	return CEL_CondRetOK ;
  	} else {
     	/* Se o estado estiver diferente de 1 ou 0, � um estado inv�lido */
       	 
        	*Estado = -1 ;
        	return CEL_CondRetEstadoInvalido ;
  	} /* if */
 	 
   } /* Fim fun��o: CEL Obter estado correto da c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Alterar estado atual da c�lula
*  ****/
   
   CEL_tpCondRet CEL_AlterarEstadoAtual( ptCelula pCelula )
   {
   
  	if( pCelula == NULL ) {
     	return CEL_CondRetCelulaNaoExiste ;
  	} /* if */
 	 
  	if( pCelula->EstadoAtual == 1 )
  	{
     	/* Se o estado atual � 1 (preenchida), vira 0 (vazia) */
    	 
        	pCelula->EstadoAtual = 0 ;
        	return CEL_CondRetOK ;
  	} else if ( pCelula->EstadoAtual == 0 ) {
     	/* Se o estado atual � 0 (vazia), vira 1 (preenchida) */
    	 
        	pCelula->EstadoAtual = 1 ;
        	return CEL_CondRetOK ;
  	} else {
     	/* Se o estado estiver diferente de 1 ou 0, � um estado inv�lido */
       	 
        	return CEL_CondRetEstadoInvalido ;
  	} /* if */
 	 
   } /* Fim fun��o: CEL Alterar estado atual da c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Alterar estado correto da c�lula
*  ****/
   
   CEL_tpCondRet CEL_AlterarEstadoCorreto( ptCelula pCelula )
   {
   
  	if( pCelula == NULL ) {
     	return CEL_CondRetCelulaNaoExiste ;
  	} /* if */
 	 
  	if( pCelula->EstadoCorreto == 1 )
  	{
     	/* Se o estado correto � 1 (preenchida), vira 0 (vazia) */
    	 
        	pCelula->EstadoCorreto = 0 ;
        	return CEL_CondRetOK ;
  	} else if ( pCelula->EstadoCorreto == 0 ) {
     	/* Se o estado correto � 0 (vazia), vira 1 (preenchida) */
    	 
     	pCelula->EstadoCorreto = 1 ;
     	return CEL_CondRetOK ;
  	} else {
     	/* Se o estado estiver diferente de 1 ou 0, � um estado inv�lido */
    	 
        	return CEL_CondRetEstadoInvalido ;
  	} /* if */
 	 
   } /* Fim fun��o: CEL Alterar estado correto da c�lula */
   
/***************************************************************************
*
*  Fun��o: CEL Comparar estados da c�lula
*  ****/
   
   CEL_tpCondRet CEL_CompararEstados( ptCelula pCelula, int * Comparacao )
   {
   
  	if( pCelula == NULL ) {
     	return CEL_CondRetCelulaNaoExiste ;
  	} /* if */
 	 
  	if( ( pCelula->EstadoAtual == 0 && pCelula->EstadoCorreto == 0 ) || ( pCelula->EstadoAtual == 1 && pCelula->EstadoCorreto == 1 ) )
  	{
     	/* Passa por refer�ncia a compara��o dos estados (iguais) */
    	 
        	*Comparacao = 0 ;
        	return CEL_CondRetOK ;
  	} else if ( ( pCelula->EstadoAtual == 1 && pCelula->EstadoCorreto == 0 ) || ( pCelula->EstadoAtual == 0 && pCelula->EstadoCorreto == 1 ) ) {
     	/* Passa por refer�ncia a compara��o dos estados (diferentes) */
    	 
        	*Comparacao = 1 ;
        	return CEL_CondRetOK ;
  	} else {
     	/* Se algum estado estiver diferente de 1 ou 0, � um estado inv�lido */
       	 
        	*Comparacao = -1 ;
        	return CEL_CondRetEstadoInvalido ;
  	} /* if */
 	 
   } /* Fim fun��o: CEL Comparar estados atual e correto da c�lula */
   
/********** Fim do m�dulo de implementa��o: CEL  C�lula **********/
