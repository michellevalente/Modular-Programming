/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: avs - Arndt von Staa
*           GB - Gustavo Bach
*           JG - Jo�o Lucas Gardenberg
*           MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor      Data          Observa��es
*     5.01    GM,JG,MV   20/abr/2014   mudan�a no jeito como o par�metro � utilizado na fun��o de alterar valor
*     5.00    GM,JG,MV   12/abr/2014   todas as fun��es exportadas pelo m�dulo retornam
*                                      condi��es de retorno
*     5.00    GB,JG,MV   11/abr/2014   adicionar fun��o de alterar valor do elemento
*     4.00    avs        01/fev/2006   criar linguagem script simb�lica
*     3.00    avs        08/dez/2004   uniformiza��o dos exemplos
*     2.00    avs        07/jul/2003   unifica��o de todos os m�dulos em um s� projeto
*     1.00    avs        16/abr/2003   in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
	#include "CESPDIN.H"
#endif
/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

		 #ifdef _DEBUG
			char tipoElemento;
		 #endif

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

		 #ifdef _DEBUG
		 char tipoElemento;
		 #endif

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  
										#ifdef _DEBUG
											,char tipoElemento
										#endif 
											) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
             void   ( * ExcluirValor ) ( void * pDado ) 
			 #ifdef _DEBUG
		,
		 char tipoElemento
		#endif
		 )
   {

      if ( *pLista != NULL )
      {
		  LIS_DestruirLista( *pLista ) ;
      } /* if */

      *pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista ) ) ;
      if ( *pLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      (*pLista)->pOrigemLista = NULL ;
      (*pLista)->pFimLista = NULL ;
      (*pLista)->pElemCorr = NULL ;
      (*pLista)->numElem   = 0 ;

      (*pLista)->ExcluirValor = ExcluirValor ;

	#ifdef _DEBUG
	  CED_MarcarEspacoAtivo(pLista);
	#endif

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
	  
	  if( pLista != NULL )
	  {
		 LIS_tpCondRet CondRet ;

         CondRet = LIS_EsvaziarLista( pLista ) ;
		 if( CondRet != LIS_CondRetOK )
		 {
			 return CondRet ;
		 } /* if */
	  } /* if */

      free( pLista ) ;

	  pLista = NULL ;
		#ifdef _DEBUG
			  CED_MarcarEspacoNaoAtivo(pLista);
		#endif
	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

	  if( pLista == NULL )
	  {
		  return LIS_CondRetListaNaoExiste ;
	  } /* if */

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor       
										   #ifdef _DEBUG
											 ,char tipoElemento
											#endif
											 )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor 
										#ifdef _DEBUG
											,tipoElemento
										#endif
											) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

#ifdef _DEBUG
		 CED_MarcarEspacoAtivo(pElem);
#endif
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        
										  #ifdef _DEBUG
											,char tipoElemento
										  #endif
											)
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir ap�s */

         pElem = CriarElemento( pLista , pValor
										#ifdef _DEBUG
											,tipoElemento
										#endif 
											);
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;

#ifdef _DEBUG
		 CED_MarcarEspacoAtivo(pElem);
#endif
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

	#ifdef _DEBUG
		  CED_MarcarEspacoNaoAtivo(pElem);
	#endif

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista,
	                             void ** pValor         )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

	  if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      if ( pLista->pElemCorr == NULL )
      {
	    *pValor = NULL ;
        return LIS_CondRetListaVazia ;
      } /* if */

      *pValor = pLista->pElemCorr->pValor ;

	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if( pLista == NULL )
	  {
		  return LIS_CondRetListaNaoExiste ;
	  } /* if */

	  if( pLista->pElemCorr == NULL )
	  {
		  return LIS_CondRetListaVazia ;
	  } /* if */

      pLista->pElemCorr = pLista->pOrigemLista ;

	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if( pLista == NULL )
	  {
		  return LIS_CondRetListaNaoExiste ;
	  } /* if */

	  if( pLista->pElemCorr == NULL )
	  {
		  return LIS_CondRetListaVazia ;
	  } /* if */

      pLista->pElemCorr = pLista->pFimLista ;

	  return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */

/***************************************************************************
*
*  Fun��o: LIS  &Alterar valor de um elemento
*  ****/

   LIS_tpCondRet LIS_AlterarValor( LIS_tppLista pLista,
	                               void * pValor          
		#ifdef _DEBUG
				,char tipoElemento
		#endif
		)
   {

	   if( pLista == NULL )
	   {
	   	   return LIS_CondRetListaNaoExiste ;
	   } /* if */

	   if( pLista->pElemCorr == NULL || pLista->pOrigemLista == NULL )
	   {
	   	   return LIS_CondRetListaVazia ;
	   } /* if */

	   pLista->pElemCorr->pValor = pValor ;

	   #ifdef _DEBUG
	   pLista->pElemCorr->tipoElemento = tipoElemento;
	  #endif

	   return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Alterar valor de um elemento */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  
								#ifdef _DEBUG
									,char tipoElemento
								#endif
									)
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;
	  #ifdef _DEBUG
			pElem->tipoElemento = tipoElemento;
	  #endif
      pLista->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */

#ifdef _DEBUG
/**********************************************************************************
*
*  Fun��o: LIS Liberar n� corrente.
*
***********************************************************************/

   LIS_tpCondRet LIS_LiberarNoCorrente( LIS_tppLista pLista)
   {

	  tpElemLista * pElem ;

	  if ( pLista == NULL )
	  {
		  return LIS_CondRetListaNaoExiste;
	  }

	  if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Libera � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx  = pElem->pProx ;
            pLista->pElemCorr = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Libera � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

		 LiberarElemento(pLista,pElem);

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS Liberar n� corrente*/

/***********************************************************************
*
*  $FC Fun��o: LIS Alterar Ponteiro Sucessor
*
***********************************************************************/

   void LIS_AlteraPonteiroSucessor ( LIS_tppLista pLista , void *ponteiro )
   {
	   pLista->pElemCorr->pProx = (tpElemLista *) ponteiro;
   } /* Fim fun��o: LIS  Altera Ponteiro Sucessor*/

/***********************************************************************
*
*  $FC Fun��o: LIS Alterar Ponteiro Predecessor
*
***********************************************************************/

   void LIS_AlteraPonteiroPredecessor ( LIS_tppLista pLista , void *ponteiro )
   {
	   pLista->pElemCorr->pAnt = (tpElemLista *) ponteiro;
   } /* Fim fun��o: LIS  Altera Ponteiro Predecessor */

/***********************************************************************
*
*  $FC Fun��o: LIS Corrente NULL
*
***********************************************************************/

   void LIS_CorrenteNull ( LIS_tppLista pLista )
   {
	   pLista->pElemCorr = NULL ;
   } /* Fim fun��o: LIS Corrente NULL */

/***********************************************************************
*
*  $FC Fun��o: LIS Origem NULL
*
***********************************************************************/

   void LIS_OrigemNull ( LIS_tppLista pLista )
   {
	   pLista->pOrigemLista = NULL ;
   } /* Fim fun��o: LIS Origem NULL*/

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Prox Elemento
*
***********************************************************************/

   int LIS_VerificaProxElemento ( LIS_tppLista pLista )
   {
	   if(pLista->pElemCorr != NULL)
	   {
		   if(pLista->pElemCorr->pProx == NULL)
			   return 1;
		   else
			   return 0;
	   }
	   return 0;

   }/* Fim fun��o: LIS Verifica Prox Elemento  */

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Ant Elemento
*
***********************************************************************/

   int LIS_VerificaAntElemento ( LIS_tppLista pLista )
   {
	   if(pLista->pElemCorr != NULL)
	   {
	   if(pLista->pElemCorr->pAnt == NULL)
		   return 1;
	   else
		   return 0;
	   }
	   return 0;
   
   }/* Fim fun��o: LST  Verifica Ant Elemento  */

   /***********************************************************************
*
*  $FC Fun��o: LIS Verifica Lista Vazia
*
***********************************************************************/

   int LIS_VerificaListaVazia ( LIS_tppLista pLista)
   {
	   
	   
	   if ( pLista->numElem == 0 )
	   {
		   if ( pLista->pElemCorr != NULL || pLista -> pOrigemLista != NULL || pLista -> pFimLista != NULL )
		   {
			   return 1;
		   } /* if */
		   return 0;
	   }
	   return 0;
   }/* Fim fun��o: LST  Verifica Lista Vazia  */

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Lista Elemento Unico
*
***********************************************************************/

   int LIS_VerificaListaElemUnico ( LIS_tppLista pLista )
   {  
	   if ( pLista->numElem == 1 )
	   {
		   if ( pLista -> pElemCorr != pLista -> pOrigemLista || pLista -> pElemCorr != pLista -> pFimLista )
		   {
			   return 1;
		   } /* if */

		   if ( pLista -> pElemCorr-> pProx != NULL || pLista -> pElemCorr-> pAnt != NULL )
		   {
			   return 1;
		   } /* if */

		   return 0;
	   }
	   return 0;
   }/* Fim fun��o: LIS  Verifica Lista Elemento Unico  */

   /***********************************************************************
*
*  $FC Fun��o: LIS Verifica Lista Preenchida
*
***********************************************************************/

   int LIS_VerificaListaPreenchida ( LIS_tppLista pLista )
   {
	   if ( pLista->numElem > 1 )
	   {
		   if ( pLista -> pElemCorr == NULL || pLista -> pFimLista == NULL || pLista -> pOrigemLista == NULL )
		   {
			   return 1;
		   } /* if */

		   return 0;
	   }
	   return 0;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Tipo Elemento
*
***********************************************************************/

   int LIS_VerificaTipoElemento ( LIS_tppLista pLista, char TipoElemento )
   {
	   if(pLista!=NULL && pLista->pElemCorr != NULL )
	   {
		   if(pLista->pElemCorr->tipoElemento != TipoElemento )
			   return 1;
		   else 
			   return 0;
	   }else
		   return 0;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Altera Tipo Elemento
*
***********************************************************************/

   void LIS_AlteraTipoElemento ( LIS_tppLista pLista, char TipoElemento )
   {
	   pLista->pElemCorr->tipoElemento = TipoElemento ;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Altera Tipo Elemento
*
***********************************************************************/

   int LIS_VerificaTamanho ( LIS_tppLista pLista, int tamanho)
   {
	   if( pLista->numElem != tamanho )
		   return 1;
	   else
		   return 0;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Elemento NULL
*
***********************************************************************/

   int LIS_VerificaElementoNULL ( LIS_tppLista pLista )
   {
	   if( pLista->pElemCorr == NULL )
		   return 1;
	   else
		   return 0;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Lixo Sucessor
*
***********************************************************************/

   void LIS_LixoSucessor ( LIS_tppLista pLista, int lixo )
   {
	   pLista->pElemCorr->pProx = (tpElemLista *) &lixo;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: LIS Verifica Duplamente Encadeada
*
***********************************************************************/

   int LIS_VerificaDuplamenteEncadeada ( LIS_tppLista pLista )
   {
	   if(pLista->pElemCorr != NULL && pLista->pElemCorr->pProx != NULL )
	   {
		   if(pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr )
			   return 1;
		   else
				return 0;
	   }
   }/* Fim fun��o: LIS  Verifica Lista Encadeada  */

#endif


/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/


