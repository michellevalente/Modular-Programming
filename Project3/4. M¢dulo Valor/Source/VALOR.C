/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Valor
*
*  Arquivo gerado:          	VALOR.C
*  Letras identificadoras:  	VAL
*
*  Nome da base de software:	Exemplo de teste automatizado
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*       	JG - Jo�o Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o  Autor      Data          Observa��es
*      1.00    GB,JG,MV   28/mar/2014   in�cio desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define VALOR_OWN
#include "VALOR.H"
#undef VALOR_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VAL Descritor do valor
*
*  $ED Descri��o do tipo
*      Descreve a organiza��o do valor
*
***********************************************************************/

   typedef struct tgValor {

      int NumCel;
            /* N�mero de C�lulas */
          	 
      int Estado ;
            /* Estado do valor. 1 para resolvido e 0 para n�o resolvido. */

   } tpValor ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: VAL Criar Valor
*  ****/

   VAL_tpCondRet VAL_CriarValor( ptValor * pValor, int NumCel )
   {

      if ( *pValor != NULL )
      {
         VAL_DestruirValor( *pValor ) ;
      } /* if */

      (*pValor) = ( tpValor * ) malloc( sizeof( tpValor )) ;
 	 
      if ( *pValor == NULL )
      {
         return VAL_CondRetFaltouMemoria ;
      } /* if */

      (*pValor)->NumCel = NumCel ;
      (*pValor)->Estado = 0 ;

      return VAL_CondRetOK ;

   } /* Fim fun��o: VAL Criar valor */

/***************************************************************************
*
*  Fun��o: ARV Destruir valor
*  ****/

   VAL_tpCondRet VAL_DestruirValor( ptValor pValor )
   {

      if ( pValor != NULL )
      {    	 
         free( pValor ) ;
         pValor = NULL ;
      } /* if */

      return VAL_CondRetOK;

   } /* Fim fun��o: VAL Destruir valor */

/***************************************************************************
*
*  Fun��o: VAL Alterar N�mero de C�lulas
*  ****/

   VAL_tpCondRet VAL_AlterarNumCel( ptValor pValor, int NumCel )
   {

      if( pValor == NULL )
      {
         return VAL_CondRetValorNaoExiste ;
      } /* if */

      pValor->NumCel = NumCel;

      return VAL_CondRetOK ;

   } /* Fim fun��o: VAL Alterar N�mero de C�lulas */

/***************************************************************************
*
*  Fun��o: VAL Alterar Estado
*  ****/

   VAL_tpCondRet VAL_AlterarEstado( ptValor pValor, int Estado )
   {

      if( pValor == NULL )
      {
         return VAL_CondRetValorNaoExiste ;
      } /* if */

      pValor->Estado = Estado;

      return VAL_CondRetOK ;

   } /* Fim fun��o: VAL Alterar Estado */

/***************************************************************************
*
*  Fun��o: VAL Obter estado
*  ****/

   VAL_tpCondRet VAL_ObterEstado( ptValor pValor, int * Estado )
   {

      if ( pValor == NULL )
      {
         return VAL_CondRetValorNaoExiste ;
      } /* if */
 	 
      *Estado = pValor->Estado ;

      return VAL_CondRetOK ;

   } /* Fim fun��o: VAL Obter estado */

/***************************************************************************
*
*  Fun��o: VAL Obter n�mero de c�lulas
*  ****/

   VAL_tpCondRet VAL_ObterNumCel( ptValor pValor, int * NumCel )
   {

      if ( pValor == NULL )
      {
         return VAL_CondRetValorNaoExiste ;
      } /* if */
 	 
      *NumCel = pValor->NumCel ;

      return VAL_CondRetOK ;

   } /* Fim fun��o: VAL Obter n�mero de c�lulas */

/********** Fim do m�dulo de implementa��o: M�dulo Valor **********/
