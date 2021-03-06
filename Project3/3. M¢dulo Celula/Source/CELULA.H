#if ! defined( CELULA_ )
#define CELULA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CEL  C�lula
*
*  Arquivo gerado:          	CELULA.h
*  Letras identificadoras:  	CEL
*
*  Nome da base de software:	Arcabou�o para a automa��o de testes de programas
*                           	redigidos em C
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
*  $ED Descri��o do m�dulo
*      Este m�dulo implementa um conjunto simples de fun��es para criar e
*      explorar c�lulas.
*      A c�lula possui um Estado Atual, que diz se ela est� preenchida ou vazia
*      e um Estado Correto, que diz se era pra ela estar preenchida ou vazia.
*      Ao iniciar a execu��o do programa n�o existe c�lula.
*      A c�lula � inicializada com os estados Atual e Correto vazios.
*
***************************************************************************/

#if defined( CELULA_OWN )
   #define CELULA_EXT
#else
   #define CELULA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma c�lula */

   typedef struct tgCelula * ptCelula ;


/***********************************************************************
*
*  $TC Tipo de dados: CEL Condi��es de retorno
*
*  $ED Descri��o do tipo
* 	Condi��es de retorno das fun��es da c�lula
*
***********************************************************************/

   typedef enum {
    	 
     	CEL_CondRetOK = 0,
           	/* Concluiu corretamente */
          	 
     	CEL_CondRetFaltouMemoria = 1,
           	/* Faltou mem�ria ao tentar criar uma c�lula */

     	CEL_CondRetCelulaNaoExiste = 2,
           	/* C�lula n�o existe */
          	 
     	CEL_CondRetEstadoInvalido = 3
           	/* Obteve estado diferente de 1 ou 0 (preenchida ou
                                                          	vazia) */
    	 
   } CEL_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: CEL  Criar c�lula
*
*  $ED Descri��o da fun��o
*      Cria uma nova c�lula, com os estados atual e correto vazios.
*      Caso j� exista uma c�lula, esta ser� destru�da.
*
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser criada.
*
*  $FV Valor retornado
*      CEL_CondRetOK            - se criou sem problemas.
*      CEL_CondRetFaltouMemoria - se faltou mem�ria para alocar o espa�o da c�lula.
*
*  Assertivas de entradas esperadas - Nenhuma.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => pCelula != NULL.
*                                     CEL_CondRetFaltouMemoria => pCelula == NULL.
*                                     pCelula->EstadoAtual == 0.
*                                     pCelula->EstadoCorreto == 0.
*
***********************************************************************/

   CEL_tpCondRet CEL_CriarCelula( ptCelula * pCelula ) ;

   
/***********************************************************************
*
*  $FC Fun��o: CEL  Destruir c�lula
*
*  $ED Descri��o da fun��o
*      Destr�i a c�lula corrente.
*      Faz nada caso a c�lula corrente n�o exista.
*
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser destru�da.
*	 
*  $FV Valor retornado
*      CEL_CondRetOK - se destruiu sem problemas.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*
*  Assertivas de saidas esperadas   - pCelula == NULL.
*	 
***********************************************************************/

   CEL_tpCondRet CEL_DestruirCelula( ptCelula pCelula ) ;
   
   
/***********************************************************************
*
*  $FC Fun��o: CEL  Obter estado atual da c�lula
*
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser analisada.
*      $P Estado  - � o par�metro que receber� o estado atual da c�lula.
*                   Este par�metro � passado por refer�ncia.
*                   Se receber 0, a c�lula est� vazia.
*                   Se receber 1, a c�lula est� preenchida.
*                   Se receber -1, o estado est� inv�lido.
*
*  $FV Valor retornado
*      CEL_CondRetOK              - se obteve o estado atual sem problemas.
*      CEL_CondRetCelulaNaoExiste - se a c�lula a ser utilizada n�o existir.
*      CEL_CondRetEstadoInvalido  - se o estado atual estiver inv�lido.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*                                     pCelula->EstadoAtual == 0 || pCelula->EstadoAtual
*                                     == 1.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => Estado == 0 || Estado == 1.
*                                     CEL_CondRetCelulaNaoExiste => pCelula == NULL.
*                                     CEL_CondRetEstadoInvalido => Estado == -1.
*                                     Estado == pCelula->EstadoAtual.
*                                     pCelula->EstadoAtual n�o � alterado.
*                                     pCelula->EstadoCorreto n�o � alterado.
*	 
***********************************************************************/

   CEL_tpCondRet CEL_ObterEstadoAtual( ptCelula pCelula,
                                       int * Estado      ) ;
   
   
/***********************************************************************
*
*  $FC Fun��o: CEL  Obter estado correto da c�lula
*	 
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser analisada.
*      $P Estado - � o par�metro que receber� o estado correto da c�lula.
*                  Este par�metro � passado por refer�ncia.
*                  Se receber 0, o estado correto da c�lula � vazia.
*                  Se receber 1, o estado correto da c�lula � preenchida.
*                  Se receber -1, o estado est� inv�lido.
*
*  $FV Valor retornado
*      CEL_CondRetOK              - se obteve o estado correto sem problemas.
*      CEL_CondRetCelulaNaoExiste - se a c�lula a ser utilizada n�o existir.
*      CEL_CondRetEstadoInvalido  - se o estado correto estiver inv�lido.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*                                     pCelula->EstadoCorreto == 0 || pCelula->EstadoCorreto
*                                     == 1.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => Estado == 0 || Estado == 1.
*                                     CEL_CondRetCelulaNaoExiste => pCelula == NULL.
*                                     CEL_CondRetEstadoInvalido => Estado == -1.
*                                     Estado == pCelula->EstadoCorreto.
*                                     pCelula->EstadoAtual n�o � alterado.
*                                     pCelula->EstadoCorreto n�o � alterado.
*                                	 
*
***********************************************************************/

   CEL_tpCondRet CEL_ObterEstadoCorreto( ptCelula pCelula,
                                         int * Estado      ) ;
   
   
/***********************************************************************
*
*  $FC Fun��o: CEL  Alterar estado atual da c�lula
*
*  $ED Descri��o da fun��o
*      Altera o estado atual da c�lula.
*      Se estiver vazia, passa a ser preenchida.
*      Se estiver preenchida, passa a ser vazia.
*
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser alterada.
*
*  $FV Valor retornado
*      CEL_CondRetOK              - se alterou o estado atual sem problemas.
*      CEL_CondRetCelulaNaoExiste - se a c�lula a ser alterada n�o existir.
*      CEL_CondRetEstadoInvalido  - se o estado atual estiver inv�lido.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*                                     pCelula->EstadoAtual == 0 || pCelula->EstadoAtual
*                                     == 1.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => (pCelula->EstadoAtual == 0 =>
*                                     pCelula->EstadoAtual == 1) || (pCelula->EstadoAtual
*                                     == 1 => pCelula->EstadoAtual == 0).
*                                     CEL_CondRetCelulaNaoExiste => pCelula == NULL.
*                                     CEL_CondRetEstadoInvalido => pCelula->EstadoAtual
*                                     != 1 && pCelula->EstadoAtual != 0.
*                                     pCelula->EstadoCorreto n�o � alterado.
*
***********************************************************************/

   CEL_tpCondRet CEL_AlterarEstadoAtual( ptCelula pCelula ) ;
   
   
/***********************************************************************
*
*  $FC Fun��o: CEL  Alterar estado correto da c�lula
*
*  $ED Descri��o da fun��o
*      Altera o estado correto da c�lula.
*      Se o estado correto � preenchida, este passa a ser vazia.
*      Se o estado correto � vazia, este passa a ser preenchida.
*
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser alterada.
*
*  $FV Valor retornado
*      CEL_CondRetOK              - se alterou o estado correto sem problemas.
*      CEL_CondRetCelulaNaoExiste - se a c�lula a ser alterada n�o existir.
*      CEL_CondRetEstadoInvalido  - se o estado correto estiver inv�lido.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*                                     pCelula->EstadoCorreto == 0 || pCelula->EstadoCorreto
*                                 	== 1.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => (pCelula->EstadoCorreto == 0 =>
*                                     pCelula->EstadoCorreto == 1) || (pCelula->EstadoCorreto
*                                     == 1 => pCelula->EstadoCorreto == 0).
*                                     CEL_CondRetCelulaNaoExiste => pCelula == NULL.
*                                     CEL_CondRetEstadoInvalido => pCelula->EstadoCorreto
*                                     != 1 && pCelula->EstadoCorreto != 0.
*                                     pCelula->EstadoAtual n�o � alterado.
*
***********************************************************************/

   CEL_tpCondRet CEL_AlterarEstadoCorreto( ptCelula pCelula ) ;
   
   
/***********************************************************************
*
*  $FC Fun��o: CEL  Comparar estados da c�lula
*
*  $ED Descri��o da fun��o
*      Compara os estados atual e correto da c�lula.
*	 
*  $EP Par�metros
*      $P pCelula - ponteiro para a c�lula a ser analisada.
*      $P Comparacao - � o par�metro que receber� a compara��o.
*                      Este par�metro � passado por refer�ncia.
*                      Se receber 0, os estados est�o iguais.
*                      Se receber 1, os estados est�o diferentes.
*                      Se receber -1, algum dos estados est� inv�lido.
*
*  $FV Valor retornado
*      CEL_CondRetOK              - se a compara��o ocorreu sem problemas.
*      CEL_CondRetCelulaNaoExiste - se a c�lula a ser utilizada n�o existir.
*      CEL_CondRetEstadoInvalido  - se algum dos estados estiver inv�lido.
*
*  Assertivas de entradas esperadas - pCelula != NULL.
*                                     pCelula->EstadoAtual == 0 || pCelula->EstadoAtual
*                                     == 1.
*
*  Assertivas de saidas esperadas   - CEL_CondRetOK => Comparacao == 0 || Comparacao == 1.
*                                     CEL_CondRetCelulaNaoExiste => pCelula == NULL.
*                                     CEL_CondRetEstadoInvalido => Comparacao == -1.
*                                     pCelula->EstadoAtual n�o � alterado.
*                                     pCelula->EstadoCorreto n�o � alterado.
*
***********************************************************************/

   CEL_tpCondRet CEL_CompararEstados( ptCelula pCelula,
                                      int * Comparacao  ) ;
   
   
/********** Fim do m�dulo de defini��o: CEL  C�lula **********/

#else
#endif
