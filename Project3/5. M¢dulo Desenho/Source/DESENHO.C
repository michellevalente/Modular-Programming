/***************************************************************************
*  $MCI M�dulo de implementa��o: DES  M�dulo Desenho
*
*  Arquivo gerado:          	DESENHO.c
*  Letras identificadoras:  	DEF
*
*  Nome da base de software:	Arcabou�o para a automa��o de testes de programas redigidos em C
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
***************************************************************************/


#include <stdio.h>
#include <malloc.h>

#define DESENHO_OWN
#include "DESENHO.h"
#undef DESENHO_OWN

#include "CELULA.h"
#include "VALOR.h"
#include "LISTA.h"
#include "MATRIZ.h"

/***********************************************************************
*
*  $TC Tipo de dados: DES Desenho
*
*
***********************************************************************/
   typedef struct tgDesenho {

  	ptMatriz pMatriz ;
        	/* Ponteiro para a matriz */

  	ptMatriz pListaColuna ;
        	/* Lista de listas para os valores das colunas da matriz */

  	ptMatriz pListaLinha ;
        	/* Lista de listas para os valores das linhas da matriz */

   } tpDesenho ;

/***** Vari�veis encapsuladas no m�dulo *****/

	static ptCelula pCelula = NULL ;
	static ptValor pValor = NULL ;
	static void * pVoid = NULL ;
	static VAL_tpCondRet CondRetVal ;
	static MAT_tpCondRet CondRetMat ;
	static CEL_tpCondRet CondRetCel ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

	static void ZerarNumCelLinhaColunaMatrizValores( ptDesenho pDesenho,
														int LinhaMatCel, 
														int ColunaMatCel, 
														int AlturaMatVal, 
														int LarguraMatVal ) ;

	static void ZerarEstadosLinhaColunaMatrizValores( ptDesenho pDesenho, 
														int LinhaMatCel, 
														int ColunaMatCel, 
														int AlturaMatVal, 
														int LarguraMatVal ) ;

	static void DestruirElemento ( void * pValor ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: DES  Gerar Matriz
*  ****/

	DES_tpCondRet DES_GerarMatrizes( ptDesenho * pDesenho, 
										int Altura, 
										int Largura )
	{

		int IteradorAltura, IteradorLargura ;

		*pDesenho = ( tpDesenho * ) malloc ( sizeof( tpDesenho ) ) ;
		CondRetMat = MAT_CriarMatriz( &(*pDesenho)->pMatriz, Altura, Largura) ;

		if( CondRetMat == MAT_CondRetFaltouMemoria )
		{
			return DES_CondRetFaltouMemoria ;
		} /* if */

		CondRetMat = MAT_CriarMatriz( &(*pDesenho)->pListaColuna, (Altura+1)/2, Largura) ;

		if( CondRetMat == MAT_CondRetFaltouMemoria )
		{
			return DES_CondRetFaltouMemoria ;
		} /* if */

		CondRetMat = MAT_CriarMatriz( &(*pDesenho)->pListaLinha, Altura, (Largura+1)/2) ;

		if( CondRetMat == MAT_CondRetFaltouMemoria )
		{
			return DES_CondRetFaltouMemoria ;
		} /* if */

		for (IteradorAltura = 1 ; IteradorAltura <= Altura ; IteradorAltura++ )
		{
			for( IteradorLargura = 1 ; IteradorLargura <= Largura ; IteradorLargura++ )
			{
				ptCelula pLocalCelula = NULL ;
				CondRetCel = CEL_CriarCelula( &pLocalCelula ) ;

				if( CondRetCel == CEL_CondRetFaltouMemoria )
				{
					return DES_CondRetFaltouMemoria ;
				} /* if */

				CondRetMat = MAT_InserirValor ( (*pDesenho)->pMatriz, pLocalCelula, IteradorAltura, IteradorLargura ) ;
			} /* for */
		} /* for */

		for (IteradorAltura = 1 ; IteradorAltura <= (Altura+1)/2 ; IteradorAltura++ )
		{
			for( IteradorLargura = 1 ; IteradorLargura <= Largura ; IteradorLargura++ )
			{
				ptValor pLocalValor = NULL ;
				CondRetVal = VAL_CriarValor( &pLocalValor, 0 ) ;

				if( CondRetVal == VAL_CondRetFaltouMemoria )
				{
					return DES_CondRetFaltouMemoria ;
				} /* if */

				CondRetMat = MAT_InserirValor ( (*pDesenho)->pListaColuna, pLocalValor, IteradorAltura, IteradorLargura ) ;
			} /* for */
		} /* for */

		for (IteradorAltura = 1 ; IteradorAltura <= Altura ; IteradorAltura++ )
		{
			for( IteradorLargura = 1 ; IteradorLargura <= (Largura+1)/2 ; IteradorLargura++ )
			{
				ptValor pLocalValor = NULL ;
				CondRetVal = VAL_CriarValor( &pLocalValor, 0 ) ;

				if( CondRetVal == VAL_CondRetFaltouMemoria )
				{
					return DES_CondRetFaltouMemoria ;
				} /* if */

				CondRetMat = MAT_InserirValor ( (*pDesenho)->pListaLinha, pLocalValor, IteradorAltura, IteradorLargura ) ;
			} /* for */
		} /* for */

		return DES_CondRetOK ;

	}


/***************************************************************************
*
*  Fun��o: DES  Alterar Estado Correto
*  ****/

	DES_tpCondRet DES_AlterarEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna )
	{

		int Altura = 0, Largura = 0, AlturaMatrizCima = 0, LarguraMatrizCima = 0, AlturaMatrizEsquerda = 0, LarguraMatrizEsquerda = 0 ;
		int Iterador, EstadoCorreto, Somador = 0, LinhaMatrizValores, ColunaMatrizValores ;

		if( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterAlturaLargura( pDesenho->pMatriz, &Altura, &Largura ) ;
		LinhaMatrizValores = (Altura+1)/2 ;
		ColunaMatrizValores = (Largura+1)/2 ;
		CondRetMat = MAT_ObterValor( pDesenho->pMatriz, Linha, Coluna, &pVoid ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizVazia ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimColunas )
		{
			pVoid = NULL ;
			return DES_CondRetFimColunas ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimLinhas )
		{
			pVoid = NULL ;
			return DES_CondRetFimLinhas ;
		} /* if */

		pCelula = ( ptCelula ) pVoid ;
		pVoid = NULL ;
		CondRetCel = CEL_AlterarEstadoCorreto( pCelula ) ;
		pCelula = NULL ;

		if( CondRetCel == CEL_CondRetCelulaNaoExiste )
		{
			return DES_CondRetCelNaoExiste ;
		} /* if */

		ZerarNumCelLinhaColunaMatrizValores( pDesenho, Linha, Coluna, (Altura+1)/2, (Largura+1)/2 ) ;

		for( Iterador = 1 ; Iterador <= ColunaMatrizValores ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaColuna, Iterador, Coluna, &pVoid ) ;
			VAL_AlterarEstado( ( ptValor ) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

		for( Iterador = 1 ; Iterador <= LinhaMatrizValores ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaLinha, Linha, Iterador, &pVoid ) ;
			VAL_AlterarEstado( ( ptValor ) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

		for( Iterador = Altura ; Iterador >= 1 ; Iterador-- )
		{
			CondRetMat = MAT_ObterValor( pDesenho->pMatriz , Iterador, Coluna, &pVoid ) ;

			if( CondRetMat == MAT_CondRetMatrizNaoExiste )
			{
				return DES_CondRetMatrizNaoExiste ;
			} /* if */

			if( CondRetMat == MAT_CondRetMatrizVazia )
			{
				return DES_CondRetMatrizVazia ;
			} /* if */

			pCelula = ( ptCelula ) pVoid ;
			pVoid = NULL ;
			CondRetCel = CEL_ObterEstadoCorreto( pCelula, &EstadoCorreto );
			pCelula = NULL ;

			if( CondRetCel == CEL_CondRetCelulaNaoExiste )
			{
				return DES_CondRetCelNaoExiste ;
			} /* if */

			if(	EstadoCorreto == 1 )
			{
				Somador++ ;
			} else if( EstadoCorreto == 0 )
			{
				if ( Somador != 0 )
				{
					CondRetMat = MAT_ObterValor( pDesenho->pListaColuna, LinhaMatrizValores, Coluna, &pVoid ) ;

					if( CondRetMat == MAT_CondRetMatrizNaoExiste )
					{
						return DES_CondRetMatrizNaoExiste ;
					} /* if */

					if( CondRetMat == MAT_CondRetMatrizVazia )
					{
						return DES_CondRetMatrizVazia ;
					} /* if */

					pValor = ( ptValor ) pVoid ;
					pVoid = NULL ;
					CondRetVal = VAL_AlterarNumCel( pValor, Somador ) ;

					if( CondRetVal == VAL_CondRetValorNaoExiste )
					{
						return DES_CondRetValorNaoExiste ;
					} /* if */

					pValor = NULL ;
					LinhaMatrizValores-- ;
					Somador = 0 ;
				} /* if */
			} /* if */
		} /* for */

		if ( Somador != 0 )
		{
			CondRetMat = MAT_ObterValor( pDesenho->pListaColuna, LinhaMatrizValores, Coluna, &pVoid ) ;

			if( CondRetMat == MAT_CondRetMatrizNaoExiste )
			{
				return DES_CondRetMatrizNaoExiste ;
			} /* if */

			if( CondRetMat == MAT_CondRetMatrizVazia )
			{
				return DES_CondRetMatrizVazia ;
			} /* if */

			pValor = ( ptValor ) pVoid ;
			pVoid = NULL ;
			CondRetVal = VAL_AlterarNumCel( pValor, Somador ) ;

			if( CondRetVal == VAL_CondRetValorNaoExiste )
			{
				return DES_CondRetValorNaoExiste ;
			} /* if */

			pValor = NULL ;
			Somador = 0 ;
		} /* if */

		LinhaMatrizValores = (Altura+1)/2 ;

		for( Iterador = Largura ; Iterador >= 1 ; Iterador-- )
		{
			CondRetMat = MAT_ObterValor( pDesenho->pMatriz , Linha, Iterador, &pVoid ) ;

			if( CondRetMat == MAT_CondRetMatrizNaoExiste )
			{
				return DES_CondRetMatrizNaoExiste ;
			} /* if */

			if( CondRetMat == MAT_CondRetMatrizVazia )
			{
				return DES_CondRetMatrizVazia ;
			} /* if */

			pCelula = ( ptCelula ) pVoid ;
			CondRetCel = CEL_ObterEstadoCorreto( pCelula, &EstadoCorreto );

			if( CondRetCel == CEL_CondRetCelulaNaoExiste )
			{
				return DES_CondRetCelNaoExiste ;
			} /* if */

			if(	EstadoCorreto == 1 )
			{
				Somador++ ;
			} else if( EstadoCorreto == 0 )
			{
				if ( Somador != 0 )
				{
					CondRetMat = MAT_ObterValor( pDesenho->pListaLinha, Linha, ColunaMatrizValores, &pVoid ) ;

					if( CondRetMat == MAT_CondRetMatrizNaoExiste )
					{
						return DES_CondRetMatrizNaoExiste ;
					} /* if */

					if( CondRetMat == MAT_CondRetMatrizVazia )
					{
						return DES_CondRetMatrizVazia ;
					} /* if */

					pValor = ( ptValor ) pVoid ;
					pVoid = NULL ;
					CondRetVal = VAL_AlterarNumCel( pValor, Somador ) ;

					if( CondRetVal == VAL_CondRetValorNaoExiste )
					{
						return DES_CondRetValorNaoExiste ;
					} /* if */

					pValor = NULL ;
					ColunaMatrizValores-- ;
					Somador = 0 ;
				} /* if */
			} /* if */
		} /* for */

		if( Somador != 0 )
		{
			CondRetMat = MAT_ObterValor( pDesenho->pListaLinha, Linha, ColunaMatrizValores, &pVoid ) ;

			if( CondRetMat == MAT_CondRetMatrizNaoExiste )
			{
				return DES_CondRetMatrizNaoExiste ;
			} /* if */

			if( CondRetMat == MAT_CondRetMatrizVazia )
			{
				return DES_CondRetMatrizVazia ;
			} /* if */

			pValor = ( ptValor ) pVoid ;
			pVoid = NULL ;
			CondRetVal = VAL_AlterarNumCel( pValor, Somador ) ;

			if( CondRetVal == VAL_CondRetValorNaoExiste )
			{
				return DES_CondRetValorNaoExiste ;
			} /* if */

			pValor = NULL ;
			Somador = 0 ;
		} /* if */

		ColunaMatrizValores = (Largura+1)/2 ;

		return DES_CondRetOK ;

	}

/***************************************************************************
*
*  Fun��o: DES  Alterar Estado Atual
*  ****/

	DES_tpCondRet DES_AlterarEstadoAtual( ptDesenho pDesenho, 
											int Linha, 
											int Coluna )
	{

		int Iterador, Altura = 0, Largura = 0, AlturaColuna = 0, LarguraLinha = 0, EstadoAtual, Somador = 0 ;
		int NumCel, NumCelVal, Contador = 0, ContadorVal = -1, ContadorExc = 0 ;
		LIS_tppLista ListaLinha = NULL, ListaColuna = NULL ;
		LIS_tpCondRet CondRetLis ;

		if ( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterValor( pDesenho->pMatriz, Linha, Coluna, &pVoid ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizVazia ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimColunas )
		{
			pVoid = NULL ;
			return DES_CondRetFimColunas ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimLinhas )
		{
			pVoid = NULL ;
			return DES_CondRetFimLinhas ;
		} /* if */

		pCelula = ( ptCelula ) pVoid ;
		pVoid = NULL ;
		CondRetCel = CEL_AlterarEstadoAtual( pCelula );
		pCelula = NULL ;

		if( CondRetCel == CEL_CondRetCelulaNaoExiste )
		{
			return DES_CondRetCelNaoExiste ;
		} /* if */

		return DES_CondRetOK ;

	}/* Fim fun��o: DES  Alterar Estado Atual */

/***************************************************************************
*
*  Fun��o: DES  Obter Estado Correto
*  ****/

    DES_tpCondRet DES_ObterEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna, 
											int * pValor    	)
    {

		if ( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterValor( pDesenho->pMatriz, Linha, Coluna, &pVoid ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizVazia ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimColunas )
		{
			pVoid = NULL ;
			return DES_CondRetFimColunas ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimLinhas )
		{
			pVoid = NULL ;
			return DES_CondRetFimLinhas ;
		} /* if */

		pCelula = ( ptCelula ) pVoid ;

		pVoid = NULL ;

		CondRetCel = CEL_ObterEstadoCorreto( pCelula, pValor ) ;

		pCelula = NULL ;

		if( CondRetCel == CEL_CondRetCelulaNaoExiste )
		{
			return DES_CondRetCelNaoExiste ;
		} /* if */

		return DES_CondRetOK ;

    } /* Fim fun��o: DES  Obter Estado Correto */

/***************************************************************************
*
*  Fun��o: DES  Obter Estado Atual
*  ****/

    DES_tpCondRet DES_ObterEstadoAtual( ptDesenho pDesenho, 
										int Linha, 
										int Coluna, 
										int * pValor    	)
    {

		if ( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterValor( pDesenho->pMatriz, Linha, Coluna, &pVoid ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			pVoid = NULL ;
			return DES_CondRetMatrizVazia ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimColunas )
		{
			pVoid = NULL ;
			return DES_CondRetFimColunas ;
		} /* if */

		if( CondRetMat == MAT_CondRetFimLinhas )
		{
			pVoid = NULL ;
			return DES_CondRetFimLinhas ;
		} /* if */

		pCelula = ( ptCelula ) pVoid ;

		pVoid = NULL ;

		CondRetCel = CEL_ObterEstadoAtual( pCelula, pValor ) ;

		pCelula = NULL ;

		if( CondRetCel == CEL_CondRetCelulaNaoExiste )
		{
			return DES_CondRetCelNaoExiste ;
		} /* if */

		return DES_CondRetOK ;

    } /* Fim fun��o: DES  Obter Estado Atual */

/***************************************************************************
*
*  Fun��o: DES  Desenhar atual
*  ****/

    DES_tpCondRet DES_DesenharAtual( ptDesenho pDesenho )

	{

		int Altura = 0, Largura = 0, AlturaListaCima = 0, LarguraListaCima = 0, AlturaListaEsquerda = 0, LarguraListaEsquerda = 0 ;
		int Iterador, IteradorAltura, IteradorLargura, IteradorEspaco, Contador = 0, EstadoAtual = 0, NumCel = 0 ;

		if( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterAlturaLargura( pDesenho->pMatriz, &Altura, &Largura ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			return DES_CondRetMatrizVazia ;
		} /* if */

		AlturaListaCima = (Altura+1)/2 ;
		LarguraListaCima = Largura ;
		AlturaListaEsquerda = Altura ;
		LarguraListaEsquerda = (Largura+1)/2 ;
		printf("\n") ;

		for( IteradorAltura = 1 ; IteradorAltura <= AlturaListaCima ; IteradorAltura++ )
		{
			printf("  ") ;

			for( IteradorEspaco = 1 ; IteradorEspaco <= LarguraListaEsquerda ; IteradorEspaco++ )
			{
				printf("  ") ;
			} /* for */

			printf("   ") ;

			for( IteradorLargura = 1 ; IteradorLargura <= LarguraListaCima ; IteradorLargura++ )
			{
				CondRetMat = MAT_ObterValor(pDesenho->pListaColuna, IteradorAltura, IteradorLargura, &pVoid) ;

				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */

				pValor = (ptValor) pVoid ;
				pVoid = NULL ;
				CondRetVal = VAL_ObterNumCel( pValor, &NumCel ) ;

				if( CondRetVal == VAL_CondRetValorNaoExiste )
				{
					return DES_CondRetValorNaoExiste ;
				} /* if */

				if(NumCel == 0)
				{
					printf("    ") ;
				} else {
					printf("%d   ", NumCel) ;
				} /* if */

				pValor = NULL ;
				NumCel = 0 ;
			} /* for */
			printf("\n");
		} /* for */

		printf("\n") ;

		for( IteradorAltura = 1 ; IteradorAltura <= AlturaListaEsquerda ; IteradorAltura++ )
		{
			printf("  ") ;

			for( IteradorLargura = 1 ; IteradorLargura <= LarguraListaEsquerda ; IteradorLargura++ )
			{
				CondRetMat = MAT_ObterValor(pDesenho->pListaLinha, IteradorAltura, IteradorLargura, &pVoid) ;
				
				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */
				
				pValor = (ptValor) pVoid ;
				pVoid = NULL ;
				CondRetVal = VAL_ObterNumCel(pValor, &NumCel) ;

				if( CondRetVal == VAL_CondRetValorNaoExiste )
				{
					return DES_CondRetValorNaoExiste ;
				} /* if */

				if(NumCel == 0)
				{
					printf("  ") ;
				} else {
					printf("%d ", NumCel) ;
				} /* if */

				pValor = NULL ;
				NumCel = 0 ;
			} /* for */

			printf("  ") ;

			for( IteradorLargura = 1; IteradorLargura <= Largura ; IteradorLargura++)
			{
				CondRetMat = MAT_ObterValor( pDesenho->pMatriz, IteradorAltura, IteradorLargura, &pVoid ) ;
				
				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */

				if( CondRetMat == MAT_CondRetMatrizVazia )
				{
					return DES_CondRetMatrizVazia ;
				} /* if */
				
				pCelula = ( ptCelula ) pVoid ;
				pVoid = NULL ;
				CondRetCel = CEL_ObterEstadoAtual( pCelula, &EstadoAtual ) ;

				if( CondRetCel == CEL_CondRetCelulaNaoExiste )
				{
					return DES_CondRetCelNaoExiste ;
				} /* if */

				if( CondRetCel == CEL_CondRetEstadoInvalido )
				{
					return DES_CondRetEstadoCelInvalido ;
				} /* if */

				if( EstadoAtual == 1 )
				{
					printf("(X) ");
				} else {
					printf("( ) ");
				} /* if */

				pCelula = NULL ;
				EstadoAtual = 0 ;
			} /* for */

			printf("\n\n");
		} /* for */

		printf("\n\n");

		return DES_CondRetOK;

    } /* Fim fun��o: DES  Desenhar atual */

/***************************************************************************
*
*  Fun��o: DES  Desenhar correto
*  ****/

	DES_tpCondRet DES_DesenharCorreto( ptDesenho pDesenho )
	{
		
		int Altura = 0, Largura = 0, AlturaListaCima = 0, LarguraListaCima = 0, AlturaListaEsquerda = 0, LarguraListaEsquerda = 0 ;
		int IteradorAltura, IteradorLargura, IteradorEspaco, EstadoCorreto = 0, NumCel = 0 ;

		if( pDesenho == NULL )
		{
			return DES_CondRetDesenhoNaoExiste ;
		} /* if */

		if( pDesenho->pMatriz == NULL || pDesenho->pListaColuna == NULL || pDesenho->pListaLinha == NULL )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		CondRetMat = MAT_ObterAlturaLargura( pDesenho->pMatriz, &Altura, &Largura ) ;

		if( CondRetMat == MAT_CondRetMatrizNaoExiste )
		{
			return DES_CondRetMatrizNaoExiste ;
		} /* if */

		if( CondRetMat == MAT_CondRetMatrizVazia )
		{
			return DES_CondRetMatrizVazia ;
		} /* if */

		AlturaListaCima = (Altura+1)/2 ;
		LarguraListaCima = Largura ;
		AlturaListaEsquerda = Altura ;
		LarguraListaEsquerda = (Largura+1)/2 ;
		printf("\n");

		for( IteradorAltura = 1 ; IteradorAltura <= AlturaListaCima ; IteradorAltura++ )
		{
			printf("  ") ;

			for( IteradorEspaco = 1 ; IteradorEspaco <= LarguraListaEsquerda ; IteradorEspaco++ )
			{
				printf("  ") ;
			} /* for */

			printf("   ") ;

			for( IteradorLargura = 1 ; IteradorLargura <= LarguraListaCima ; IteradorLargura++ )
			{
				CondRetMat = MAT_ObterValor(pDesenho->pListaColuna, IteradorAltura, IteradorLargura, &pVoid) ;

				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */

				pValor = (ptValor) pVoid ;
				pVoid = NULL ;
				VAL_ObterNumCel(pValor, &NumCel) ;

				if( CondRetVal == VAL_CondRetValorNaoExiste )
				{
					return DES_CondRetValorNaoExiste ;
				} /* if */

				if(NumCel == 0)
				{
					printf("    ") ;
				} else {
					printf("%d   ", NumCel) ;
				} /* if */

				pValor = NULL ;
				NumCel = 0 ;
			} /* for */
			printf("\n");
		} /* for */

		printf("\n") ;

		for( IteradorAltura = 1 ; IteradorAltura <= AlturaListaEsquerda ; IteradorAltura++ )
		{
			printf("  ") ;

			for( IteradorLargura = 1 ; IteradorLargura <= LarguraListaEsquerda ; IteradorLargura++ )
			{
				CondRetMat = MAT_ObterValor(pDesenho->pListaLinha, IteradorAltura, IteradorLargura, &pVoid) ;
				
				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */
				
				pValor = (ptValor) pVoid ;
				pVoid = NULL ;
				VAL_ObterNumCel(pValor, &NumCel) ;

				if( CondRetVal == VAL_CondRetValorNaoExiste )
				{
					return DES_CondRetValorNaoExiste ;
				} /* if */

				if(NumCel == 0)
				{
					printf("  ") ;
				} else {
					printf("%d ", NumCel) ;
				} /* if */

				pValor = NULL ;
				NumCel = 0 ;
			} /* for */

			printf("  ") ;

			for( IteradorLargura = 1; IteradorLargura <= Largura ; IteradorLargura++)
			{
				CondRetMat = MAT_ObterValor( pDesenho->pMatriz, IteradorAltura, IteradorLargura, &pVoid ) ;
				
				if( CondRetMat == MAT_CondRetMatrizNaoExiste )
				{
					return DES_CondRetMatrizNaoExiste ;
				} /* if */

				if( CondRetMat == MAT_CondRetMatrizVazia )
				{
					return DES_CondRetMatrizVazia ;
				} /* if */
				
				pCelula = ( ptCelula ) pVoid ;
				pVoid = NULL ;
				CondRetCel = CEL_ObterEstadoCorreto( pCelula, &EstadoCorreto ) ;

				if( CondRetCel == CEL_CondRetCelulaNaoExiste )
				{
					return DES_CondRetCelNaoExiste ;
				} /* if */

				if( CondRetCel == CEL_CondRetEstadoInvalido )
				{
					return DES_CondRetEstadoCelInvalido ;
				} /* if */

				if( EstadoCorreto == 1 )
				{
					printf("(X) ");
				} else {
					printf("( ) ");
				} /* if */

				pCelula = NULL ;
				EstadoCorreto = 0 ;
			} /* for */

			printf("\n\n");

		} /* for */

		return DES_CondRetOK;

	} /* Fim fun��o: DES  Desenhar correto */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: DES  Zerar NumCel da Linha e Coluna das Matrizes de Valores
*
*  $ED Descri��o da fun��o
* 	Coloca zero em todos os NumCel da linha da Matriz de Valores � 
*   esquerda e em todos os NumCel da coluna da Matriz de Valores � 
*   direita, correspondentes ao elemento da matriz de c�lulas.
*
***********************************************************************/

	void ZerarNumCelLinhaColunaMatrizValores( ptDesenho pDesenho, 
												int LinhaMatCel, 
												int ColunaMatCel, 
												int AlturaMatVal, 
												int LarguraMatVal )
	{

		int Iterador ;

		for( Iterador = 1 ; Iterador <= AlturaMatVal ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaColuna, Iterador, ColunaMatCel, &pVoid ) ;
			VAL_AlterarNumCel( (ptValor) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

		for( Iterador = 1 ; Iterador <= LarguraMatVal ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaLinha, LinhaMatCel, Iterador, &pVoid ) ;
			VAL_AlterarNumCel( (ptValor) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

	} /* Fim fun��o: DES  Zerar NumCel da Linha e Coluna das Matrizes de Valores */

/***********************************************************************
*
*  $FC Fun��o: DES  Zerar Estados da Linha e Coluna das Matrizes de Valores
*
*  $ED Descri��o da fun��o
* 	Coloca zero em todos os estados da linha da Matriz de Valores � 
*   esquerda e em todos os estados da coluna da Matriz de Valores � 
*   direita, correspondentes ao elemento da matriz de c�lulas.
*
***********************************************************************/

	void ZerarEstadosLinhaColunaMatrizValores( ptDesenho pDesenho, 
												int LinhaMatCel, 
												int ColunaMatCel, 
												int AlturaMatVal, 
												int LarguraMatVal )
	{

		int Iterador ;

		for( Iterador = 1 ; Iterador <= AlturaMatVal ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaColuna, Iterador, ColunaMatCel, &pVoid ) ;
			VAL_AlterarEstado( (ptValor) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

		for( Iterador = 1 ; Iterador <= LarguraMatVal ; Iterador++ )
		{
			MAT_ObterValor( pDesenho->pListaLinha, LinhaMatCel, Iterador, &pVoid ) ;
			VAL_AlterarEstado( (ptValor) pVoid, 0 ) ;
			pVoid = NULL ;
		} /* for */

	} /* Fim fun��o: DES  Zerar Estados da Linha e Coluna das Matrizes de Valores */

/***********************************************************************
*
*  $FC Fun��o: DES  Destruir elemento
*
*  $ED Descri��o da fun��o
* 	Fun��o de destruir elemento apontada pelo ponteiro para fun��o
* 	utilizado na fun��o LIS_CriarLista do m�dulo Lista.
*
***********************************************************************/

	void DestruirElemento ( void * pValor )
	{

    	if( pValor != NULL )
    	{
        	pValor = NULL ;
        	free(pValor) ;
    	} /* if */

	} /* Fim fun��o: MAT  Destruir elemento */

/********** Fim do m�dulo de implementa��o: DES  M�dulo Desenho **********/
