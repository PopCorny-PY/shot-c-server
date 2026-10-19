/********************************************************************************************************************


                                                \FLUXOGRAMA \DO \CODIGO \FONTE

                                                0...Licença do SHOT-C
                                                1...Bibliotecas do código
                                                2...Escopo do código
                                                3...Funções em disponibilidade                      linha 727
                                                4...Corredor de funções principais                  linha 1.100
                                                    \fluxograma \descritivo
                                                5...Núcleo duro do código fonte (int main)          linha 15.808
                                                6...Funções de alternância de toggles               linha 16.510


Referência para leitura deste código fonte:
--> IDE do Code:Blocks 20.03
--> Fundo branco e modo Default
--> Perspectiva em modo Default
--> Tela LCD 15.6"
--> Deslocamento de linha: CRTL+G
--> Deslocamento de rastreio do contra barra: CRTL+F 1x + F3
 ********************************************************************************************************************/




/***
                                    Licença SHOT-C/SHOT-C \License
==================================================================================================================
 * THE SOFTWARE IS PROVIDED "AS IS"
 *
 * THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
 * IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR
 * OR CORRECTION.
 *
 * IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY COPYRIGHT HOLDER,OR ANY
 * OTHER PARTY WHO MAY MODIFY AND/OR REDISTRIBUTETHE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
 * INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGESARISING OUT OF THE USE OR INABILITY TO
 * USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES
 * SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF
 * SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 ***/

/***
    Licença SHOT-C
    ==============================================================================================================

    Copyright (c) 2022 \Hyan \Lima. All rights reserved.

    This software is distributed under the following license:

            \Academic \Software \License \v1.0 (ASL)

    ***********************************************************************
                            PREAMBULE
                    Version 1, 17 August 2022

    SHOT-C is (c) 2022, Hyan Lima.

    SHOT-C is published and distributed under the Academic Software License v1.0 (ASL).

    SHOT-C is distributed in the hope that it will be useful for non-commercial academic research, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the ASL for more details.

    You should have received a copy of the ASL along with this program; if not, write to \<andreacosta@utfpr.edu.br>. It is also published at \<repositorio-ct@utfpr.edu.br>.

    You may contact the original licensor at \<hyanlima@alunos.utfpr.edu.br>.


    ***********************************************************************
***/

/***

    Why can't I use the \creative \commons license?
    https://creativecommons.org/faq/#can-i-apply-a-creative-commons-license-to-software

***/


/***
    \Source \code \SHOT-\C
    ==============================================================================================================
***/


/********************************************************************************************************************


                                                \BIBLIOTECAS \DO \CODIGO


 ********************************************************************************************************************/

#include <stdio.h> ///standard input-output header for C language --> cabeçalho padrão de entrada/saída para linguagem C.
#include <stdlib.h> ///Defines numeric conversion functions, pseudo-random numbers generation functions, memory allocation, process control functions --> funções envolvendo alocação de memória, controle de processos, conversões e outras.
#include <string.h> ///Defines string-handling functions --> série de funções para manipular strings
#include <ctype.h> ///Defines set of functions used to classify characters by their types --> biblioteca p/ as funções isalpha isdigit toupper tolower


#include <iup.h> ///tecgraf
#include <iupgl.h> ///tecgraf + OpenGL
#include <iup_config.h> ///tecgraf
#include <iupglcontrols.h> ///tecgraf -- crítico

#include <windows.h> ///declarations for all of the functions in the Windows API

#include <GL/glew.h> ///acesso às extensões OpenGL
#include <GL/glext.h> ///anti-aliasing
/***#include <GL/glut.h> ///sistema de janela OpenGL
NÃO ATIVAR***/

#include <GL/gl.h>     ///* OpenGL functions */
#include <GL/glu.h>    ///* OpenGL utility functions */


#include <iupdraw.h> ///tecgraf

#include <iupim.h> ///tecgraf

#include<math.h> /// declares a set of functions to perform mathematical operations --> fornece protótipos para funções, macros e definição de tipos da biblioteca padrão da linguagem de programação C para funções matemáticas básicas



#define M_PI   3.14159265358979323846264338327950288
#define MAX_STRING_FULL 1000000*1024 ///fator             //1000 KB = 1MBytes >>> x1024 = 1GB    --> alocação de memória das listas

#define to_radians(angle_degree) ((angle_degree) * M_PI / 180.0) ///macro função para fasores
#define to_degree(angle_radians) ((angle_radians)*180.0)/M_PI ///macro função para fasores

#include <cd.h> ///tecgraf
#include <cdiup.h> ///tecgraf

#include <iupcontrols.h> ///tecgraf
#include <iup_mglplot.h> ///tecgraf + MathGL

/*** inserido em 21abr22 ***/
#include <locale.h> ///para manipulação decimal com vírgula, o comando para acessar a biblioteca é setlocale
                    ///setlocale(LC_ALL, "Portuguese"); //Inserido no int main 21abr22 22h


/********************************************************************************************************************


                                                \ESCOPO \DO \CODIGO


 ********************************************************************************************************************/

/*************************************** INÍCIO - VARIÁVEIS COMPLEXAS - INÍCIO **************************************/

#include <complex.h> ///06/03/2020 início dos cálculos complexos    \biblioteca
using namespace std; /***libera o uso e acesso a códigos c++ ***/
/*
#if __cplusplus
    #include <complex>
    typedef std::complex<double> cdouble;
#else
    typedef double complex cdouble;
#endif
*/
#define OPERADOR_A -0.5 + ((sqrt(3))/2)*I   ///Operador rotacional a

    //double complex
    complex<double> T[3][3]; ///É inicializado pela FUNÇÃO init_matrix_T

    //void
    complex<double> init_matrix_T (void){ ///isso é uma função complexa

        ///define a matriz de transformação T com o operador complexo a_dot
        T[0][0] = 1.0;        T[0][1] = 1.0+0*I;                  T[0][2] = 1.0+0*I;
        T[1][0] = 1.0+0*I;    T[1][1] = cpow(OPERADOR_A, 2);      T[1][2] = OPERADOR_A;
        T[2][0] = 1.0+0*I;    T[2][1] = OPERADOR_A;               T[2][2] = cpow(OPERADOR_A, 2);

    }


    /*** se tu quiser usar toda matriz, use dois for, i e j para utilizar toda ela para operar com outra matriz! ***/

    ///Variáveis em stand by
    Ihandle *TextIa0, *TextIa1, *TextIa2, *CurrentIa0, *CurrentIa1, *CurrentIa2;
    Ihandle *anglePhasorIa0, *anglePhasorIa1, *anglePhasorIa2, *TextAngleIa0, *TextAngleIa1, *TextAngleIa2;


/******************************************** FIM - VARIÁVEIS COMPLEXAS - FIM ***************************************/

/*********************************************** VARIÁVEIS DE DEPURAÇÃO *********************************************/
int depurar_gerador = 0;
int depurar_motor = 0;
int depurar_trafo = 0;
int depurar_SEP = 0;
int depurar_base = 0;
int depurar_LT = 0;
int depurar_admitancia = 0;
int depurar_ilhamento = 0;
/********************************************************************************************************************/
/****** \CODIGO \EXTERNO

    //#include <winver.h> //<<<<< icon.ico

    *** \icon: raiz do projeto se encontra o arquivo resource.rc ***
    //inicializar ícone <<<<<<<< DEIXEI comentado se precisar, tu deve criar um arquivo externo puro C ... crie um arquivo chamdo resource.rc

        #ifndef _resource_rc
        #define _resource_rc

        MAINCON ICON "icon.ico"

        #endif _resource_rc

    //concluído ícone

    //#ifdef __cplusplus
    //extern "C" {
    //#endif

****/


/*********************************************** Variáveis GLOBAIS ********************************************/
int btn_n_call; /*** \SELETOR - VARIÁVEL PARA CÁLCULO DAS CORRENTES DE CURTO-CIRCUITO ***/
/*
    btn_n_call = 1; curto-circuito fase-terra
    btn_n_call = 2; curto-circuito bifásico
    btn_n_call = 3; curto-circuito bifásico-terra
    btn_n_call = 4; curto-circuito trifásico

*/

/*** Variável global - basta inserir static que já é o suficiente, nada externamente à função ***/
static Ihandle* counter_dlg = NULL; //para barra de progresso
Ihandle* counter_dlg_00 = NULL; //para resetar o Ihandle estático

/*********************************************** Marcadores de funções *****************************************/

static int status_memory_Base_SEP = 0; /*** é preciso deixar bem no começo do código para todas funções terem acesso ***/
static int status_memory_trafo_1 = 0;
static int status_memory_trafo_2 = 0;
static int status_memory_load_full_finish = 0;
static int status_memory_load_full_finish_pu = 0;
static int status_btn_home = 0; //Variável global
static int status_memory_size_SEP_bars = 0;  //Variável global
static int status_memory_Tension_Fault_SEP = 0;
static int status_memory_Fault_phase_GND_SEP = 0;

/***** \COMENTARIOS
//Lembre-se, a variável estática local é inicializada somente uma vez, na segunda vez que a função é chamada ela congela o valor,
//o último valor manipulado, se foi iniciado em zero e incrementou, então a segunda chamada vai estar um...poderia inclusive decrementar

*****/

/************************************************ Toggles marcadores e acumuladores ***************************************/

int id_toggle_definition_tr1=0; /*** identificador/marcador de passagem para os 11 toggles do Trafo 1 de núcleo envolvente ***/
int id_toggle_definition_tr1_envolvido=0; /*** identificador/marcador de passagem para os 3 toggles do Trafo 1 de núcleo envolvido ***/

int id_toggle_esquema_TR1 = 0; /*** variável global...carregará sob uma função de memória o atributo de esquema: ligação de 1 a 11 ***/
int id_toggle_TR1_nucleo = 0; /*** variável global...carregará sob uma função de memória o atributo de núcleo: envolvido ou envolvente ***/

int id_toggle_Xg = 0; /*** variável global...GERADOR: carregará sob uma função de memória o atributo de grandeza: reatância síncrona, transitoria ou subtransitória ***/
int id_toggle_Xm = 0; /*** variável global...MOTOR: carregará sob uma função de memória o atributo de grandeza: reatância síncrona, transitoria ou subtransitória ***/

int id_toggle_GE_estrela = 0; /*** variável global...GERADOR: carregará sob uma função de memória o atributo de ligação ***/
int id_toggle_MOTOR_estrela = 0; /*** variável global...MOTOR: carregará sob uma função de memória o atributo de ligação ***/


/************************************************ FUNÇÕES DE CRIAÇÃO DE PLANILHAS *************************************/

static Ihandle *create_mat_sequencia_positiva(int mati); /*** 3 planilhas de sequência positiva abas mat(1), mat(2) e mat(3) ***/
static Ihandle *create_mat_sequencia_negativa(int mati); /*** 3 planilhas de sequência negativa abas mat(1), mat(2) e mat(3) ***/
static Ihandle *create_mat_sequencia_zero(int mati); /*** 3 planilhas de sequência zero abas mat(1), mat(2) e mat(3) ***/


/************************************************ FUNCTIONS TYPE IHANDLE RETURN (boxes) *******************************/


static Ihandle* gerador_Form_Frame(void);           /*** FRAME DOS GERADORES ***/
static Ihandle* transformador1_Form_Frame(void);    /*** FRAME DOS TRANSFORMADORES ***/
static Ihandle* linha_LT_Form_Frame(void);          /*** FRAME DAS LTS ***/
static Ihandle* motor_Form_Frame(void);             /*** FRAME DOS MOTORES ***/
//static Ihandle* transformador2_Form_Frame(void);


static Ihandle* createForm_ligacoes_nucleo_envolvente_trafo1(void); /*** JANELA 1 DO TRANSFORMADOR 1 ***/
static Ihandle* createForm_ligacoes_nucleo_envolvido_trafo1(void);  /*** JANELA 2 DO TRANSFORMADOR 1 ***/

/********************************************** FUNÇÕES DOS BOTÕES DA JANELA PRINCIPAL ***************************************************************/

static int btn_HOME_call(Ihandle *btn);

static int createForm_Shot_C_1fase_1_terra(void); //btn_1_call - refatorado
static int createForm_Shot_C_2fase_2(void);       //btn_2_call - refatorado
static int createForm_Shot_C_2fase_3_terra(void); //btn_3_call - refatorado
static int createForm_Shot_C_3fase_4(void);       //btn_4_call - refatorado


/**************************************** DECLARAÇÃO DE VARIÁVEIS GLOBAIS: INDEXAÇÃO, LISTA E STRINGS DAS BARRAS NA JANELA FORM ************************/

static int size_SEP_bars = 1; //Variável global -- mínimo 1 barra
static int size_SEP_bars_OLD = 1; //Variável global -- Crítico, manter

//static int MAX_size_SEP_bars = 4; //Variável global -- Stand By, contornei

int *indexs_conj_SEP; //Ponteiro global com alocação dinâmica à função function_size_SEP_bars...Stand By (não setá sendo utilizada)

char* indexs_conj_GERADOR_FULL; //Ponteiro global com alocação dinâmica à função function_size_SEP_bars, conteúdo é a strings indices em char
char* indexs_conj_TRAFO_FULL;
char* indexs_conj_LT_FULL;
char* indexs_conj_MOTOR_FULL;

/*********************************************** Marcadores das listas *****************************************/

static int id_size_bars = 0;  //identificador que foi criado a indexação das barra

static int id_Zbox_GE = 0;
static int id_Zbox_TRAFO = 0;
static int id_Zbox_LT = 0;
static int id_Zbox_MOTOR = 0;

static int id_Zbox_FULL = 0;

/********************************************** FUNÇÕES E ROTINAS: INDEXAÇÃO, LISTA E STRINGS DAS BARRAS NA JANELA FORM ******************************/

static int function_message_sincrona(void); //dropbutton list
static int function_message_trafo(void);
static int function_message_LT(void);



/***** Criação do button drop list pelo Form/btn_HOME_call *****/
static Ihandle* function_List_gerador(void);
static Ihandle* function_List_TR1(void);
static Ihandle* function_List_LT(void);
static Ihandle* function_List_motor(void);
//static Ihandle* function_List_TR2(void);



/***** Criação da lista estática do button drop list *****/
static Ihandle* CreateList_Gerador(void);
static Ihandle* CreateList_Trafo(void);
static Ihandle* CreateList_LT(void);
static Ihandle* CreateList_Motor(void);


/***** Cálculo da String int e disparo da criação da lista dinâmica, tudo pelo button size *****/
int string_comprimento(int* string);    //Stand By (não setá sendo utilizada)
static int function_size_SEP_bars(Ihandle *button_Size_bars);


/***** Criação da lista dinâmica pelo button size *****/
void function_STRING_FULL_GERADOR(int disparo);
void function_STRING_FULL_TRAFO(int disparo);
void function_STRING_FULL_LT(int disparo);
void function_STRING_FULL_MOTOR(int disparo);



/***** Carregamento da lista dinâmica pelo button Zbox de índices XY -- Cascateamento *****/
//static int
void function_INDEX_Zbox_Gerador(Ihandle* disparo);
//static int
void function_INDEX_Zbox_Trafo(int GE_Zbox_function);
//static int
void function_INDEX_Zbox_LT(int Trafo_Zbox_function);
static int function_INDEX_Zbox_Motor(int LT_Zbox_function);


/****************************************************** FUNCTIONS MEMÓRIA, CARREGAMENTO E CÁLCULO *******************************************/
//static int function_memory_transformador2(Ihandle *ih);
static int function_memory_base(Ihandle *ih);


static int function_memory_motor_id_k (Ihandle *h, char *t, int i, int selected);
static int function_memory_gerador_id_k (Ihandle *h, char *t, int i, int selected);
static int function_memory_transformador1_id_k (Ihandle* ih, char *t, int i, int selected);
static int function_memory_LT_id_k (Ihandle* ih, char *t, int i, int selected);

static int function_memory_gerador(int id_x_arg, int id_y_arg);
static int function_memory_motor(int id_x_arg, int id_y_arg);
static int function_memory_transformador1(int id_x_arg, int id_y_arg);
static int function_memory_LT(int id_x_arg, int id_y_arg);


void Carregar_Struct_Matrix_Gerador(struct gerador Gerador_index, int id_x_arg, int id_y_arg);
void Carregar_Struct_Matrix_Trafo_1(struct transformador Trafo_index, int id_x_arg, int id_y_arg);
void Carregar_Struct_Matrix_LT(struct linha_LT LT_index, int id_x_arg, int id_y_arg);
void Carregar_Struct_Matrix_Motor(struct motor Motor_index, int id_x_arg, int id_y_arg);


/****************************************************** FUNCTIONS CÁLCULO DE BASES  DO SEP *************************************/

void Carregar_Base(struct base base_SEP_coleta);

static int Calc_Bases_SEP(Ihandle* button_Form_Load_Full); //FUNÇÃO id_k_Bases = roteamento de bases


/*********************************************** FUNCTIONS CÁLCULO DE TENSÃO DE FALTA  DO SEP ************************/

void Carregar_Falta(struct dados_falta coleta);




/*********************************************** Funções de Cálculo por-unidade **************************************/
/**** GERADORES ****/
float function_Z_base_gerador(float Xg_subtr_percent, int i, int pet_ON);
void Calc_Positiva_Xg_pu(Ihandle* ih);
void Calc_Negativa_Xg_pu(Ihandle* ih);
void Calc_Zero_Xg_pu(Ihandle *ih);

/**** MOTORES ****/
float function_Z_base_motor(float Xg_subtr_percent, int i, int pet_ON);
void Calc_Positiva_Xm_pu(Ihandle* ih);
void Calc_Negativa_Xm_pu(Ihandle* ih);
void Calc_Zero_Xm_pu(Ihandle* ih);


/**** LTS ****/

/*** \for \duplo ***/
float function_Z_base_LT(float Xeq_LT, int j);
void Calc_Positiva_Xeq_LT_pu(Ihandle *ih);
void Calc_Negativa_Xeq_LT_pu(Ihandle *ih);
void Calc_Zero_Xeq_LT_pu(Ihandle *ih);


/**** TRANSFORMADORES ****/

//void Calc_Positiva_Xeq_TR1_pu(Ihandle *ih);
/*** \for \duplo ***/
void Calc_Positiva_Xeq_TR1_pu(float Tensao_TR_primario, float Tensao_BASE_primario, int i, int j);

/**** TRANSFORMADORES E LINHAS DE TRANSMISSÃO  --> NÃO LANÇADOS ****/

/*** \for \duplo ***/
float function_Z_pu_Positiva_TR_LT(Ihandle* disparo_load_full);

/*********************************************** Funções de Cálculo de \Zpu **************************************/

     /*********************************************** SOBREPOSIÇÃO  **************************************/

void Calc_Matrix_Z_positiva_pu(Ihandle* disparo_load_full);
void Calc_Matrix_Z_negativa_pu(Ihandle* disparo_load_full);
void Calc_Matrix_Z_zero_pu(Ihandle* disparo_load_full);

/*********************************************** Funções de Cálculo de \YBarra **************************************/

void Calc_Matrix_Y_positiva_pu(Ihandle* disparo_load_full);
void Calc_Matrix_Y_negativa_pu(Ihandle* disparo_load_full);
void Calc_Matrix_Y_zero_pu(Ihandle* disparo_load_full);



/*********************************************** Funções de Cálculo de \ZBarra **************************************/


    /**************************************** \Z \THEVENIN, \DETERMINANTE E \INVERSA *****************************/

/*** \START ***/
void Calc_Matrix_Z_th_pu(Ihandle* disparo_load_full, int tipo);

float determinante(float matrix[25][25], float ordem);

void cofatores(float matrix[25][25], float ordem, int tipo);

void inversa(float matrix[25][25], float minor_M[25][25], float ordem, int tipo);

//float buffer_Minor_M[25][25]; //rastreio



/****************************************************** FUNCTIONS ILHAMENTO ADMITÂNCIA Y DIAGONAL *************************************/

//float
struct struct_buffer_ligacao function_struct_buffer_ligacao (int i, int j);
int function_ilhamento(int i, int barra_fixa);
int detector_dupla_passagem(int k, int i, int reset);//ddp


/****************************************************** FUNCTIONS PLANILHAS POR UNIDADE *************************************/
static int button_Seq_Positiva_in_Form(Ihandle *ih);
static int button_Seq_Negativa_in_Form(Ihandle *ih);
static int button_Seq_Zero_in_Form(Ihandle *ih);

static int btn_function_alternar_Zpu(Ihandle* ih);
static int btn_function_alternar_Ypu(Ihandle* ih);
static int btn_function_alternar_Zpu_th(Ihandle* ih);


/*** as três funções que se seguem não estão sendo utilizadas - stand by ***/
static char* value_NEW_zerosCells(Ihandle *self, int lin, int col);
static char* value_NEW(Ihandle *self, int lin, int col);
static char* value_CELL(Ihandle *self, int lin, int col);


/*************************************************** FUNCTIONS TOGGLES *****************************************************/
/**** TRANSFORMADORES ****/

static int function_memory_toggle_envolvido_TR1(Ihandle *toggle1_tr, int boolean_toggle, int status);
static int function_memory_toggle_envolvente_TR1(Ihandle *toggle1_tr, int boolean_toggle, int status);


/**** GERADORES ****/
static int function_memory_toggle_Xg_sub(Ihandle *toggle_Xg_sub, int boolean_toggle, int status);
static int function_memory_toggle_Xg_trans(Ihandle *toggle_Xg_sub, int boolean_toggle, int status);
static int function_memory_toggle_Xg_sinc(Ihandle *toggle_Xg_sub, int boolean_toggle, int status);

/**** MOTORES ****/
static int function_memory_toggle_Xm_sub(Ihandle *toggle_Xm_sub, int boolean_toggle, int status);
static int function_memory_toggle_Xm_trans(Ihandle *toggle_Xm_sub, int boolean_toggle, int status);
static int function_memory_toggle_Xm_sinc(Ihandle *toggle_Xm_sub, int boolean_toggle, int status);


/*************************************************************************************************************/
/**** GERADORES ****/
static int function_memory_toggle_Y_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status);
static int function_memory_toggle_Yat_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status);
static int function_memory_toggle_YZn_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status);


/**** MOTORES ****/
static int function_memory_toggle_Y_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status);
static int function_memory_toggle_Yat_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status);
static int function_memory_toggle_YZn_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status);


/***************************************** FUNCTIONS MEMORY - JANELA DE LIGAÇÕES DO TRAFO *****************************************************/

static int button_memory_Ligacao_Trafo1(Ihandle *ih); ///Não está sendo utilizada, pois o marcador bloqueia ajuste para mais de um trafo
//static int button_memory_Ligacao_Trafo2(Ihandle *ih);

/***************************************** FUNCTIONS MEMORY - RESET LIGAÇÕES DO TRAFO *****************************************************/

void function_zerar_options_esquema_ligacao(int num_disparo); //envolvente
void function_zerar_options_esquema_ligacao_envolvido(int num_disparo);


/******************************************* FUNCTIONS TOGGLES - JANELA DE LIGAÇÕES DO TRAFO ************************************************/
/**** TRANSFORMADOR ENVOLVENTE (1und.) ****/

static int function_memory_toggle_01_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_02_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_02b_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_03_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_03b_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_04_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_04b_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_05_TR1(Ihandle *toggle, int boolean_toggle);
static int function_memory_toggle_06_TR1(Ihandle *toggle, int boolean_toggle);
//static int function_memory_toggle_07_TR1(Ihandle *toggle, int boolean_toggle);
//static int function_memory_toggle_08_TR1(Ihandle *toggle, int boolean_toggle);

/**** TRANSFORMADOR ENVOLVIDO (1und.) ****/

static int function_memory_toggle_01_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle);
static int function_memory_toggle_02_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle);
static int function_memory_toggle_03_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle);



/*********************************************** Listagem/Declaração de estruturas ********************************************/


typedef struct gerador {
    float Vg_nominal=2121.0;
    float Pg_nominal=22.0;
    float Xg_seq_pos=23.0;
    float Xg_seq_neg=24.0;
    float Xg_seq_zero=25.0;
    float Xg_pet=26.0;
    int id_k_Gerador = 0;
    int id_x = 0;
    int id_y = 0;
    int ligacao_esquema = 0;
    int ligacao_nucleo_TR = 0; //equivalência para transformador envolvido
};


typedef struct transformador {

    float Vt_nominal_primario = 2122.0;
    float Vt_nominal_secundario = 22.0;
    float Pt_nominal = 23.0;
    float Xeq_trafo = 24.0;
    int ligacao_nucleo = 0;
    int ligacao_esquema = 0;
    float X_TR_seq_pos=23.0;
    float X_TR_seq_neg=24.0;
    float X_TR_seq_zero=25.0;
    int id_k_Trafo = 0;
    int id_x = 0;
    int id_y = 0;
};



typedef struct linha_LT {
    float Xeq_LT_seq_pos=2123.0;
    float Xeq_LT_seq_neg=22.0;
    float Xeq_LT_seq_zero=23.0;
    int id_k_LT = 0;
    int id_x = 0;
    int id_y = 0;
};




typedef struct motor {
    float Vm_nominal = 2124.0;
    float Pm_nominal = 22.0;
    float Xm_seq_pos = 23.0;
    float Xm_seq_neg = 24.0;
    float Xm_seq_zero = 25.0;
    float Xm_pet = 26.0;
    int id_k_Motor = 0;
    int id_x = 0;
    int id_y = 0;
    int ligacao_esquema = 0;
};
//    int tipo_reatancia_Xm = 0;



typedef struct base {
    float V_base=2125.0;
    float P_base=22.0;
    int Regiao_base=0;
    int id_k_Base = 0;
    //int id_x = 0;
    //int id_y = 0;
};

typedef struct dados_falta{
    float V_Falta = 1.0;
    float phasor_V_Falta = 0.0;
    int Barra_V_Falta = 1;
};

typedef struct toggle_TR{
    int option = 0;
};

typedef struct inicializacao{
    int init = 0; //crítico que não seja static
};


typedef struct struct_buffer_ligacao{
    float buffer1;
    float buffer2;
};


typedef struct matrix_universal{
    gerador gerador_indices;
    transformador trafo_indices;
    linha_LT LT_indices;
    motor motor_indices;
};


typedef struct phase{
    float module = 1.73;
    float phasor = 0.00;
};

typedef struct matrix_phasor{
    //tipo phase
    phase a;
    phase b;
    phase c;
};

/*** Structs Blocks precisam estar antes da definição da matrix_struct ***/

/*A princípio consegui manipular o tamanho da matrix via função carregar***/

/******************************************* MEMORY TOGGLES (BUFFER) - JANELAS DE LIGAÇÕES DO TRAFO ************************************************/
/**** TRANSFORMADOR ENVOLVENTE (BUFFER) ****/

struct toggle_TR options_TR1[11]; //options_TR1 = option... options_TR1 é um nome genérico para acessar toggle_TR1, usando .field = .option
//struct toggle_TR options_TR2[11];

/**** TRANSFORMADOR ENVOLVIDO (BUFFER) ****/
struct toggle_TR options_TR1_envolvido[3]; //A struct é a mesma, contudo o vetor é menor.

/******************************************* MODELAGEM TRANSFORMADOR ENVOLVIDO Yat:Yat  ************************************************************/
struct inicializacao continua_v[16]; //atrelado ao tempo de execução, quando qualquer trafo é acionado é verificado se é envolvido Yat:Yat

struct inicializacao G[16];//vetor de impedância pu antecipadas, para modelagem do trafo envolvido Yat:Yat

/******************************************* ARMAZENAMENTO DE BASES DO SEP ************************************************************/
struct base base_SEP_coleta[16]; /*** VETOR DE 16 BASES STRUCT GLOBAL ***/ //precisa de uma a mais porque a posição zero é buffer (a definida pelo Formulário)



/******************************************* ARMAZENAMENTO DE MATRIZES ************************************************************/

//Estudar como alocar memória para matrizes simples tipo float
float matrix_admitancia_positiva_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/
float matrix_admitancia_negativa_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/
float matrix_admitancia_zero_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/
int continua_j[16]; /// análise de ilhamento
int array_passagem_ki[16][16]; /// análise de ilhamento
int array_passagem_pq[16][16]; /// análise de ilhamento

float matrix_impedancia_positiva_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/
float matrix_impedancia_negativa_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/
float matrix_impedancia_zero_pu[16][16]; /*** MATRIX ADMITANCIA GLOBAL EM PU ***/

float matrix_thevenin_positiva_pu[16][16]; /*** MATRIX THEVENIN SEQUÊNCIA POSITIVA GLOBAL ***/
float matrix_thevenin_negativa_pu[16][16]; /*** MATRIX THEVENIN SEQUÊNCIA NEGATIVA GLOBAL ***/
float matrix_thevenin_zero_pu[16][16]; /*** MATRIX THEVENIN SEQUÊNCIA ZERO GLOBAL ***/

struct matrix_phasor matrix_current_seq_positiva_pu[16][16]; /*** MATRIX CORRENTE SEQUÊNCIA POSITIVA GLOBAL ***/
struct matrix_phasor matrix_current_seq_negativa_pu[16][16]; /*** MATRIX CORRENTE SEQUÊNCIA NEGATIVA GLOBAL ***/
struct matrix_phasor matrix_current_seq_zero_pu[16][16]; /*** MATRIX CORRENTE SEQUÊNCIA ZERO GLOBAL ***/

struct matrix_phasor matrix_current_fase_a_Amper[16][16]; /*** MATRIX CORRENTE FASE A GLOBAL ***/
struct matrix_phasor matrix_current_fase_b_Amper[16][16]; /*** MATRIX CORRENTE FASE B GLOBAL ***/
struct matrix_phasor matrix_current_fase_c_Amper[16][16]; /*** MATRIX CORRENTE FASE C GLOBAL ***/

struct matrix_universal matrix_struct_pu[16][16]; /*** MATRIX STRUCT GLOBAL EM PU ***/

struct matrix_universal matrix_struct[16][16]; /*** MATRIX STRUCT GLOBAL ***/



/*** array de 1 dimensão ***/
//carregamento individual via matrix_struct.gerador_indices[0].Vg_nominal = 13,8;
//envio massivo matrix_struct.gerador_indices[0] = {Vg_nominal, Pg_nominal, X_seq_pos, X_seq_neg, X_seq_zero, X_neutro}; //gerador 1 do SEP
//matrix_struct[0] = {{gerador_indices[0], transformador trafo_indices[0]}, {gerador_indices[1], transformador trafo_indices[1]},...}

/*** array de 2 dimensões ***/
//carregamento individual via matrix_struct[0][0].gerador_indices.Vg_nominal = 13,8;
//envio massivo de matrix_struct[0][0].gerador_indices = {Vg_nominal, Pg_nominal, X_seq_pos, X_seq_neg, X_seq_zero, X_neutro}; //gerador 1 do SEP
//matrix_struct[0][0] = {gerador_indices[0]};

/********************************************************************************************************************


                                                \FUNCTIONS \RUNNER \DO \CODIGO


 ********************************************************************************************************************/





/****************************************************** \FUNCTION \ABOUT  *******************************************/

int about_text(void)  /*** TEXTO DO SOBRE/ABOUT DO SOFTWARE ***/
{
/* Executes IupMessage */
  IupMessage("Bem Vindo(a)!","Este software foi desenvolvido por Hyan K. G. de Lima "
             "sob a orientação da Prof.a Dra. Andrea Lucia Costa na Universidade Tecnológica Federal do Paraná - UTFPR. Todos direitos reservados.");

  return IUP_DEFAULT;
}



/*************************************************** \FUNCTION \ABOUT \LICENSES  *******************************************/

int about_licenses(void)  /*** TEXTO DO SOBRE/ABOUT DAS LICENÇAS DO SOFTWARE SHOT-C ***/
{
/* Executes IupMessage */
  IupMessage("Bem Vindo(a)!",
             "Licenses:\t https://drive.google.com/drive/u/1/folders/1KHndHw1yaMguT2gyFipyDqp3MD-Y3fls"
             "\n\n1. End User License Agreement - SHOT-C.txt"
             "\n2. License MathGL LGPL.txt"
             "\n3. COPYING.MinGW-w64-runtime.txt"
            );

  return IUP_DEFAULT;
}


/****************************************************** \FUNCTION \BLANK  *******************************************/


int blank_text(void)  /*** TEXTO DO SOBRE/ABOUT DO SOFTWARE ***/
{
/* Executes IupMessage */
  IupMessage("Bem Vindo(a)!","A barra de menu só possui dois informativos em About");

  return IUP_DEFAULT;
}


/****************************************************** \FUNCTIONS \DEBUG  ******************************************/


static int function_message_sincrona(void)
{

  int i = 0;

  i++;
  i = 10 + i;

  IupMessage("Aviso!", "Este botão, após se definir o número de barras e carregar a indexação, possui uma listagem de barras disponíveis para inserção de uma máquina síncrona em cada barra.\n"
             "\nO primeiro item da lista é o topo da lista. A indexação i:i para uma barra i pode estar ou não conectada à terra, isso vai depender do lançamento.");

  return IUP_DEFAULT;
}





static int function_message_trafo(void)
{

  int i = 0;

  i++;
  i = 10 + i;

  IupMessage("Aviso!", "Este botão, após se definir o número de barras e carregar a indexação, possui uma listagem de barras disponíveis para inserção de um transformador entre barras.\n"
              "\nO primeiro item da lista é o topo da lista e que instrui sobre o primário e o secundário.");


  return IUP_DEFAULT;
}





static int function_message_LT(void)
{

  int i = 0;

  i++;
  i = 10 + i;

  IupMessage("Aviso!", "Este botão, após se definir o número de barras e carregar a indexação, possui uma listagem de barras disponíveis para inserção de uma linha de transmissão entre barras.\n"
              "\nO primeiro item da lista é o topo da lista. A ordem de lançamento não importa.");

  return IUP_DEFAULT;
}







/******************************************************* \Functions \Mdi \Windows  **************************************************/



static int mdi_activate(Ihandle* ih) /**************** ATIVA A JANELA EM USO ************/
{
  printf("mdi_activate(%s)\n", IupGetName(ih));
  return IUP_DEFAULT;
}

/*****************************************(  \BAR \PROGRESS \SHOT \C  )**************************************************

***/




/************************************** INÍCIO - Janela de inicialização INÍCIO *****************************************/



static int cancel_cb(Ihandle* ih) //Esta função vai na barra de progresso
{
  int ret = IupAlarm("Warning!", "Interrupt Processing?", "Yes", "No", NULL);
  if (ret == 1) /* Yes Interrupt */
  {
    IupSetAttribute(ih, "SIMULATEMODAL", "No");
    IupHide(ih);
    return IUP_DEFAULT;
  }

  return IUP_CONTINUE;
}



static void counter_start(int totalcount)
{

    counter_dlg = counter_dlg_00;//resetando o Ihandle estático

  if (!counter_dlg)
  {
    counter_dlg = IupProgressDlg();

    //IupSetAttribute(counter_dlg, "PARENTDIALOG", "MainWindow");
    IupSetAttribute(counter_dlg, "TITLE", "Carregando...");
    if(btn_n_call==1){
        IupSetAttribute(counter_dlg, "DESCRIPTION", "Cálculo de correntes de curto-circuito fase-terra");
    }
    if(btn_n_call==2){
        IupSetAttribute(counter_dlg, "DESCRIPTION", "Cálculo de correntes de curto-circuito bifásico");
    }
    if(btn_n_call==3){
        IupSetAttribute(counter_dlg, "DESCRIPTION", "Cálculo de correntes de curto-circuito bifásico-terra");
    }
    if(btn_n_call==4){
        IupSetAttribute(counter_dlg, "DESCRIPTION", "Cálculo de correntes de curto-circuito trifásico");
    }
    IupSetCallback(counter_dlg, "CANCEL_CB", cancel_cb);
    IupSetInt(counter_dlg, "TOTALCOUNT", totalcount);
    IupSetAttribute(counter_dlg, "RESIZE", "YES");
//    IupSetAttribute(counter_dlg, "MINCLOCK", "500");
//    IupSetAttribute(counter_dlg, "MINPERCENT", "20");
  }

  IupSetAttribute(counter_dlg, "STATE", NULL);

  IupShow(counter_dlg);

  IupSetAttribute(counter_dlg, "SIMULATEMODAL", "Yes");

//  Ihandle* main_window = IupGetHandle("MainWindow");
//  IupSetAttribute(main_window, "TASKBARPROGRESSSTATE", "NORMAL");
//  IupSetAttribute(main_window, "TASKBARPROGRESSVALUE", "0");

  system("chcp 65001");

  //printf("Olá vamos começar\n");
}



static int counter_inc(void) /*** incremento ***/
{
  IupSetAttribute(counter_dlg, "INC", NULL);
//  IupSetInt(counter_dlg, "COUNT", count);

  if (strcmp(IupGetAttribute(counter_dlg, "STATE"), "ABORTED") == 0)
  {
    //printf("Interrupted\n");
    return 0;
  }

  IupLoopStep();

//  Ihandle* main_window = IupGetHandle("MainWindow");
//  IupSetInt(main_window, "TASKBARPROGRESSVALUE", (IupGetInt(counter_dlg, "COUNT") * 100) / IupGetInt(counter_dlg, "TOTALCOUNT"));

  //printf("Step\n");
  return 1;
}



static void counter_stop(void) /*** parada ***/
{
  // force one last update
  IupSetInt(counter_dlg, "COUNT", IupGetInt(counter_dlg, "TOTALCOUNT"));

  IupSetAttribute(counter_dlg, "SIMULATEMODAL", "No");

  IupHide(counter_dlg);

//  Ihandle* main_window = IupGetHandle("MainWindow");
//  IupSetAttribute(main_window, "TASKBARPROGRESSVALUE", "100");
//  IupSetAttribute(main_window, "TASKBARPROGRESSSTATE", "NOPROGRESS");

  //printf("Stop\n");
}



static void counter_release(void) /*** reiniciar? ***/
{
  if (counter_dlg)
    IupDestroy(counter_dlg);
  counter_dlg = NULL;
}



void LongProcessing(void) /*** progresso ***/
{
  int i, j;

  counter_start(4000);

  for (i = 0; i < 4000; i++)
  {
    for (j = 0; j < 4000; j++)
    {
      double x = fabs(sin(j * 100.) + cos(j * 100.)); //<math.h>, valor absoluto
      x = sqrt(x * x);
    }

    if (!counter_inc())
      break;
  }

  counter_stop();
}


/************************************************ FIM - Janela de inicialização FIM *****************************************/







/***************************************************** SHOT-C RUNNER FUNCTIONS ********************************************************
 \FLUXOGRAMA \DESCRITIVO

    >>> AS FUNÇÕES QUE SE SEGUEM SÃO PILARES DO CÓDIGO FONTE. DEVIDO A EVIDÊNCIA DO CARREGAMENTO TOTAL, A FUNÇÃO DESTE VEIO PRIMEIRO.
    >>> O ROTEIRO DE CÁLCULO QUE SE SEGUE:
        >>> DAS IMPEDÂNCIAS DE THÉVENIN
            >>> \BUTTON \LOAD \FULL (calculado por último, porém acionado do começo do runner functions)
        >>> DAS IMPEDÂNCIAS EM PU
            >>> \GERADORES
            >>> \MOTORES
            >>> \TRANSFORMADORES  (cálculo antecipado) < < < < < < < < < <
            >>> \LT                                                      ^
            >>> \TRANSFORMADORES \E \LTs                                 ^
            >>> \IMPEDANCIA \TOTAL \SOPREPOSICAO                         ^
        >>> DAS ADMITÂNCIAS EM PU                                        ^
            >>> \ADMITANCIA \TOTAL                                       ^
            >>> \Y \BARRA \POSITIVA                                      ^
            >>> \Y \BARRA \NEGATIVA                                      ^
            >>> \Y \BARRA \ZERO                                          ^
                >>> \ILHAMENTO                                           ^
                    >>> \ILHAMENTO > \LIGACAO                            ^
                    >>> \ILHAMENTO > \SEP \ANEL                          ^
                    >>> \ILHAMENTO > \FUNCTION \RECURSSIVA               ^
                    >>> \ILHAMENTO > \FUNCTION \Y \BARRA \ZERO           ^
        >>> DAS BASES ---------------------------------------------------^
            >>> \FUNCTIONS \BASES \SEP
                >>> \FUNCTION \CONFIRMACAO \BASE \DEFINIDA
                >>> \FUNCTION \FRAME \FORMULARIO \DA \BASE
                >>> \FUNCTION \JANELA \FORMULARIO \DA \BASE
                >>> \FUNCTION \COLETA \DA \BASE  \DEFINIDA
                >>> \FUNCTION \CARREGAMENTO \DA \BASE  \DEFINIDA
        >>> \DESCONTINUIDADE --- disparo via \BUTTON \LOAD \FULL
                >>> \FUNCTION \CALCULO \DAS \BASES
        >>> DA INDEXAÇÃO DOS GERADORES
            >>> \FUNCTION \MEMORY \GERADOR \INDEX
            >>> \FUNCTION \MEMORY \GERADOR
            >>> \FUNCTION \CARREGAR \MEMORY \GERADOR
        >>> DA INDEXAÇÃO DOS TRANSFORMADORES
            >>> \FUNCTION \MEMORY \TRAFO \INDEX
            >>> \FUNCTION \MEMORY \TRAFO
            >>> \FUNCTION \CARREGAR \MEMORY \TRAFO
        >>> DA INDEXAÇÃO DAS LTS
            >>> \FUNCTION \MEMORY \LT \INDEX
            >>> \FUNCTION \MEMORY \LT
            >>> \FUNCTION \CARREGAR \MEMORY \LT
        >>> DA INDEXAÇÃO DOS MOTORES
            >>> \FUNCTION \MEMORY \MOTOR \INDEX
            >>> \FUNCTION \MEMORY \MOTOR
            >>> \FUNCTION \CARREGAR \MEMORY \MOTOR
        >>> DOS TOGGLES DOS TRANSFORMADORES
            >>> \FUNCTION \LICAGAO \TRAFO \ENVOLVENTE \TOGGLES
            >>> \FUNCTION \LICAGAO \TRAFO \ENVOLVIDO \TOGGLES
            >>> \FUNCTION \NUCLEO \TRAFO \SELETOR \TOGGLES
        >>> DOS FRAMES DO FORMULÁRIO
            >>> \MAQUINAS - \FORM \FRAMES \BOXES
                >>> \FORM \GERADOR
                    >>> \RESET \BOXES \VALUES \GERADOR
                >>> \FORM \TRANSFORMADOR 1
                    >>> \RESET \BOXES \VALUES \TRANSFORMADOR
                >>> \FORM \LINHA \DE \TRANSMISSAO
                    >>> \RESET \BOXES \VALUES \LT
                >>> \FORM \MOTOR
                    >>> \RESET \BOXES \VALUES \GERADOR
        >>> DAS PLANILHAS DO FORMULÁRIO
                >>> \FUNCTIONS \IN \PER \UNIT \TABS -- \ABAS
                    >>> \TABS \ABAS \ALTERNAR \Zpu
                    >>> \TABS \ABAS \ALTERNAR \Ypu
                    >>> \TABS \ABAS \ALTERNAR \Zth \pu
                >>> \JANELAS \DAS \PLANILHAS
                    >>> \button \Seq \Zero (0, 0, 0)
                    >>> \button \Seq \Negativa (-, -, -)
                    >>> \button \Seq \Positiva (+, +, +)
                >>> \THEVENIN \Z \BARRA
                    >>> \THEVENIN \Z \BARRA \SELETOR (0, -, +)
                    >>> \DETERMINANTE
                    >>> \COFATORES
                    >>> \INVERSA
                >>> \PLANILHAS (9)
                    >>> \PLANILHAS \SEQ \POSITIVA  (3)
                    >>> \PLANILHAS \SEQ \NEGATIVA  (3)
                    >>> \PLANILHAS \SEQ \ZERO      (3)
            >>> DAS LISTAS DINÂMICAS
                >>> \LISTAS \DINAMICAS \STRING \FULL \IN \TAGS
                    >>> \CARREGAR \LISTA \DINAMICA \GERADOR
                    >>> \CARREGAR \LISTA \DINAMICA \TRAFO
                    >>> \CARREGAR \LISTA \DINAMICA \LT
                    >>> \CARREGAR \LISTA \DINAMICA \MOTOR
                >>> \CARREGAR \BARRAS \INICIALIZAR \LISTAS \DINAMICAS
                    >>> \CRIAR \LISTA \DINAMICA \STRING \GERADOR
                    >>> \CRIAR \LISTA \DINAMICA \STRING \TRAFO
                    >>> \CRIAR \LISTA \DINAMICA \STRING \LT
                    >>> \CRIAR \LISTA \DINAMICA \STRING \MOTOR
            >>> DOS FRAMES DAS LISTAS
                >>> \FRAMES \LISTAS \IN \FORM
                    >>> \FRAME \LISTA \GERADOR \IN \FORM
                    >>> \FRAME \LISTA \TRAFO \IN \FORM
                    >>> \FRAME \LISTA \LT \IN \FORM
                    >>> \FRAME \LISTA \MOTOR \IN \FORM
            >>> DAS LISTAS ESTÁTICAS
                >>> \CRIAR \LISTAS \ESTATICAS \IN \FORM
                    >>> \LISTA \ESTATICA \GERADOR \IN \FORM
                    >>> \LISTA \ESTATICA \TRAFO \IN \FORM
                    >>> \LISTA \ESTATICA \LT \IN \FORM
                    >>> \LISTA \ESTATICA \MOTOR \IN \FORM
            >>> DOS FORMULÁRIO DO SHOT-C PARA ENTRADA DE DADOS
                >>> \FORMULARIO \FORM \SHOT \C
                    >>> \BUTTON \HOME \FORM \SHOT \C
            >>> DO CÁLCULO DAS CORRENTES DE CURTO-CIRCUITO
                >>> \CALCULADORA \CURRENTS \SHOT \C (aqui há um seletor de fórmula)
                    >>> \BUTTON \CALCULAR \CURRENTS \MONOFASICO \SHOT \C
                    >>> \BUTTON \CALCULAR \CURRENTS \BIFASICO \SHOT \C
                    >>> \BUTTON \CALCULAR \CURRENTS \BIFASICO \TERRA \SHOT \C
                    >>> \BUTTON \CALCULAR \CURRENTS \TRIFASICO \SHOT \C
                    >>> \BUTTON \MEMORY \TENSION \FAULT
                    >>> \BUTTON \DEFINIR \TENSION \FAULT
                    >>> \VALUES \BOXES \CORRENTES \SEQ \POSITIVA
                    >>> \VALUES \BOXES \CORRENTES \SEQ \NEGATIVA
                    >>> \VALUES \BOXES \CORRENTES \SEQ \ZERO
                    >>> \VALUES \BOXES \CORRENTES \REAIS
                    >>> \VALUE \BOX \CORRENTE \BASE
            >>> DOS FORMULÁRIOS DAS CORRENTES DE CURTO-CIRCUITO
                >>> \FORM \BTN \ONE \SHOT \C
                >>> \FORM \BTN \TWO \SHOT \C
                >>> \FORM \BTN \THREE \SHOT \C
                >>> \FORM \BTN \FOUR \SHOT \C
            >>> DOS UTILITÁRIOS OPERACIONAIS PARA O SHOT-C
                >>> \ICON \SHOT \C
                >>> \OPEN \TXT \FILE \SHOT \C
                >>> \IUP \CLOSE \SHOT \C
            >>> DO NÚCLEO PRINCIPAL DO CÓDIGO DO SHOT-C
                >>> \INT \MAIN \DO \SHOT \C
            >>> DAS FUNÇÕES DE ALTERNÂNCIA DOS TOGGLES
                >>> \TOGGLES \ALTERNANCE






****/

/***************************************************** CARREGAMENTO COMPLETO DO SEP ********************************************************/


/******************************************* \BUTTON \LOAD \FULL \CARREGAR \E \CALCULAR \DADOS ***********************************************************/


static int button_load_full_memory (Ihandle *ih) /*** BOTÃO TEMPORÁRIO: MARCADOR DO BOTÃO CARREGAR FORMULÁRIO ***/
{

    //static int status_memory_load_full = 0; /*** Variável global ***/
                                           /*** Variável local - basta inserir static que já é o suficiente, nada externamente à função ***/
                                           /*** Só é local enquanto estiver dentro da função, não é vista por outras funções ***/
                                           /*** Mas não é reinciada, ficando congelada desde a primeira chamada, exceto se fizer um decremento ***/

    printf("criar uma função que armazene a base do SEP e possa ser acionar remotamente a qualquer instante");

    //crie um botão para sua validação interna, para ver se entrou nesta função - botão verificar, daí ele vai entrar nesta função e coletar o que
    //foi definido, daí eu tenho certeza...ainda na Form ligação trafo preciso sinalizar após apertar definir, idela que transferisse para a segunda janela


     static int status_memory_load_full = 0; //valor temporário para sondar variáveis globais

     static int id = 0;


     status_memory_load_full = status_memory_Base_SEP;// + status_memory_trafo_1;// + status_memory_trafo_2;

     if(status_btn_home==0)
          IupMessage("Aviso!", "Favor preencher e carregar o formulário");
     if(status_btn_home!=0 && status_memory_Base_SEP==0)
          IupMessage("Aviso!", "Favor preencher e definir a base do SEP");
     //if(status_btn_home!=0 && status_memory_trafo_1==0)
       //   IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 1");
     //if(status_btn_home!=0 && status_memory_trafo_2==0)
          //IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 2");
     if(status_btn_home!=0 && status_memory_load_full==0)
          IupMessage("Aviso!", "Favor carregar o formulário");
     if(status_btn_home!=0 && status_memory_load_full == 1 && id == 0){ //status_memory_load_full == 3

        /*** PARTE 1 ***/
   //       function_memory_gerador(ih);
          /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/
          //IupSetCallback(ih, "ACTION", (Icallback) function_memory_gerador);

        /*** PARTE 2 ***/
   //       function_memory_transformador1(ih); /*** envio do botão full load form ***/


        /*** PARTE 3 ***/
   //       function_memory_transformador2(ih); /*** envio do botão full load form ***/


        /*** PARTE 4 ***/
   //       function_memory_linha_transmission(ih); /*** envio do botão full load form ***/


        /*** PARTE 5 ***/
 //         function_memory_motor(ih); /*** envio do botão full load form ***/

        /*** PARTE 6 ***/
 //         Carregar_Base(base_struct); /*** acesso duplo à função - confirmação de coleta ***/


            Calc_Bases_SEP(ih); /***
/*** \<<<<< Calc_Positiva_Xeq_TR1_pu && Calc_Zero_Xg_pu modo envolvido \>>>>>>>>>>>>>>>>>> ***/


        IupMessage("Aviso!", "CALCULADO AS BASES");

        /*** PARTE 7 ***/
          //carregamento em pu


            Calc_Positiva_Xg_pu(ih);
            Calc_Negativa_Xg_pu(ih);
            Calc_Zero_Xg_pu(ih);
            /*** \ENVIO \DE \DUPLO \ACESSO ***/
            /*** float function_Z_base_gerador(float Xg_subtr_percent, int i) \<<< função é disparada por + e - acima, após ser capturar Xg da iteração for ***/

            IupMessage("Aviso!", "CALCULADO AS REATÂNCIAS COMPLEXAS DOS GERADORES");

            Calc_Positiva_Xm_pu(ih);
            Calc_Negativa_Xm_pu(ih);
            Calc_Zero_Xm_pu(ih);
            /*** \ENVIO \DE \DUPLO \ACESSO ***/
            /*** float function_Z_base_motor(float Xm_subtr_percent, int i) \<<< função é disparada por + e - acima, após ser capturar Xg da iteração for ***/

            IupMessage("Aviso!", "CALCULADO AS REATÂNCIAS COMPLEXAS DOS MOTORES");

            Calc_Positiva_Xeq_LT_pu(ih); //NEM SEQUER HAVIA LANÇADO AQUI! 17mai22
            Calc_Negativa_Xeq_LT_pu(ih);
            Calc_Zero_Xeq_LT_pu(ih);

            /*** \FUNCTION \TRAFO está sendo acionada localmente na rotina de cálculo das bases ***/

            IupMessage("Aviso!", "CALCULADO AS REATÂNCIAS COMPLEXAS DAS LTS");


            /*** \COMPLEMENTO \Zpu \TR + \LT ***/
            function_Z_pu_Positiva_TR_LT(ih); //Visa só preenhcer de zeros os elementos não existentes, por sobreposição ...zera primeiro os trafos inexistentes, dps zera as lts inexistentes
            /*** \DEPUGRAR ***/

            IupMessage("Aviso!", "CALCULADO AS REATÂNCIAS COMPLEXAS DOS TRANSFORMADORES");


            Calc_Matrix_Z_positiva_pu(ih);
            Calc_Matrix_Z_negativa_pu(ih);
            Calc_Matrix_Z_zero_pu(ih);

            IupMessage("Aviso!", "CALCULADO Z-PU");


            Calc_Matrix_Y_positiva_pu(ih);
            Calc_Matrix_Y_negativa_pu(ih);
            Calc_Matrix_Y_zero_pu(ih);

            IupMessage("Aviso!", "CALCULADO Y-BARRA");

            //agora falta a inversa!

            Calc_Matrix_Z_th_pu(ih, 1); //SEQUÊNCIA POSITIVA tipo == 1
            Calc_Matrix_Z_th_pu(ih, 2); //SEQUÊNCIA NEGATIVA tipo == 2
            Calc_Matrix_Z_th_pu(ih, 0); //SEQUÊNCIA ZERO tipo == 0


            IupMessage("Aviso!", "CALCULADO Z-BARRA");


           /*** \BAR \PROGRESS - BARRA DE PROGRESSO ***/
           Ihandle* div_red = IupGetDialogChild(ih, "divisoria_tag_red"); //FUNCIONA, MASSS é preciso arrastar a janela para sair o frame congelado
                                                                          //De fato precisa da barra de progresso aqui, pelo menos sei onde por
           IupSetAttribute(div_red, "TITLELINEWIDTH", "10"); //espessura linha divisória
           IupSetAttribute(div_red, "COLOR", "0 255 0");



          status_memory_load_full_finish_pu++; //Variável Global = 0

          /**** \DESBLOQUEIA \PLANILHAS ***/


          id++; //bloquear o acionamento do Form novamente, impede que a planilha seja modificada, obrigando o usuário a reiniciar o software



          //IupMessage("Aviso!", "CARREGADO O FORMULÁRIO DO SEP DE 2 BARRAS (5 NÓS)! \n Minimize a janela ou encerre-a!");
          IupMessagef("Aviso!", "CARREGADO O FORMULÁRIO DO SEP DE %d BARRAS (%d NÓS)! \n Minimize a janela ou encerre-a!", size_SEP_bars, size_SEP_bars+1);
          status_memory_load_full_finish++; //Variável Global = 0 --- MARCADOR DE QUE O BOTÃO CARREGAR DO FORMULÁRIO FOI ACIONADO ---

          /*** \IMPORTANTE, com o status memory acima, os btn_call já estão habilitados para calcular correntes,
                            contudo ainda sera´necessário inverter a matriz Zpu ***/

     }
     if(status_btn_home!=0 && status_memory_load_full == 3 && id>=1)
          IupMessage("Aviso!", "Prossiga para janela principal!");


    return IUP_DEFAULT;

}






/************************************************************ FUNCTIONS CALC Zpu ****************************************/



/*******************************************(                      \GERADORES                      )********************************************

***/



/************* GERADOR **********/
void Calc_Positiva_Xg_pu(Ihandle *ih)
{

        for(int i = 1; i < size_SEP_bars_OLD+1; i++){

            float buffer = matrix_struct_pu[5][5].gerador_indices.Xg_seq_zero; //Achei o erro, de fato estava saindo lixo 25 pu pq jogou num trafo 5:5 e não no gerador 5:5
            //IupMessagef("Aviso!", "PASSOU AQUI - PÓS BASES - A impedância pu de %d:%d é igual a %.5f", 5, 5, buffer);

            float Xg_subtr_percent = matrix_struct[i][i].gerador_indices.Xg_seq_pos; //se liga está utilizando a sequência positiva

            //Implementar id_k_Gerador aqui se quiser saber Xg_percent a enviar

            int pet_ON = 0; //NÃO calcular Xg_peterson
            float Xg_subtr_pu = function_Z_base_gerador(Xg_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

            /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            //int id_k_Gerador = matrix_struct[i][i].gerador_indices.id_k_Gerador;
            //int id_k_Motor = matrix_struct[i][i].motor_indices.id_k_Motor;

            //if(id_k_Gerador == 1 && id_k_Motor == 2){
            if(Xg_subtr_pu != 0){

                matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].motor_indices.Xm_seq_pos = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }
                //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) do gerador é %.5f [pu]", Xg_subtr_pu);

                if(depurar_gerador==1){
                IupMessagef("Aviso!", "A reatância de sequência positiva do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos);
                IupMessagef("Aviso!", "A reatância de sequência positiva do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_pos);
                }

        }



}



void Calc_Negativa_Xg_pu(Ihandle *ih)
{

        for(int i = 1; i < size_SEP_bars_OLD+1; i++){

            float Xg_subtr_percent = matrix_struct[i][i].gerador_indices.Xg_seq_neg; //se liga está utilizando a sequência positiva


            int pet_ON = 0; //NÃO calcular Xg_peterson
            float Xg_subtr_pu = function_Z_base_gerador(Xg_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

            /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            if(Xg_subtr_pu != 0){
                matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].motor_indices.Xm_seq_neg = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }
                //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) do gerador é %.5f [pu]", Xg_subtr_pu);

                if(depurar_gerador==1){
                IupMessagef("Aviso!", "A reatância de sequência negativa do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg);
                IupMessagef("Aviso!", "A reatância de sequência negativa do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_neg);
                }


        }


}




void Calc_Zero_Xg_pu(Ihandle *ih)
{
        float Xg_subtr_pu;
        float Xg_subtr_percent;

        for(int i = 1; i < size_SEP_bars+1; i++){

            Xg_subtr_percent = matrix_struct[i][i].gerador_indices.Xg_seq_zero; //se liga está utilizando a sequência zero

            //putz grilo, estou enviando a impedância percentual ...a variável está definida percent filho!!
            //bom que caiu a ficha que é aqui que deve entrar um contorno para pu


            if(G[i].init == 1){ //vetor indicando que já foi preenchido com impedância em pu, no caso é parte da modelagem do trafo envolvido
                Xg_subtr_pu = matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero;

            }
            if(G[i].init == 0){

                int pet_ON = 1; //Calcular a Xg_peterson
                Xg_subtr_pu = function_Z_base_gerador(Xg_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

            }

            /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            if(Xg_subtr_pu != 0){
                matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].motor_indices.Xm_seq_zero = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }
                //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) do gerador é %.5f [pu]", Xg_subtr_pu);

                if(depurar_gerador==0){
                //IupMessagef("Aviso!", "A reatância de sequência zero do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero);
                //IupMessagef("Aviso!", "A reatância de sequência zero do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_zero);
                }


        }


}







float function_Z_base_gerador(float Xg_subtr_percent, int i, int pet_ON) //Gerador conectado à barra i ... integrada a um laço de repetição
{ //ESTA FUNÇÃO É PARA CALCULAR AS IMPEDÂNCIAS EM PU DO GERADOR, FIRMA ISSO! +, - e zero.

    int id_k_Gerador = -1;

    id_k_Gerador = matrix_struct[i][i].gerador_indices.id_k_Gerador; //recebe o status da id_k da struct



    if(id_k_Gerador == 1){
   /*** ROTINA DE CÁLCULO É SEMELHANTE A DA SEQUÊNCIA POSITIVA, PORÉM A RESULTANTE PODE SER DIFERENTE DEPENDENDO DO INPUT ****/
            /*** \RECEBIMENTO de Xg_subtr_percent via argumento ***/
            if(depurar_base==1){
            IupMessage("Aviso!", "ROTINA GERADOR");
            }


            float Vg_nominal = matrix_struct[i][i].gerador_indices.Vg_nominal;
                  Vg_nominal = Vg_nominal*pow(10.0,3.0);
            if(depurar_base==1){
            IupMessagef("Aviso!", "A tensão nominal do gerador (%d:%d) é %.2E [V]", i, i, Vg_nominal);
            }


            float Sg_nominal = matrix_struct[i][i].gerador_indices.Pg_nominal;
                  Sg_nominal = Sg_nominal*pow(10.0,6.0);
            if(depurar_base==1){
            IupMessagef("Aviso!", "A potência nominal do gerador (%d:%d) é %.2E [VA]", i, i, Sg_nominal);
            }

            float Xg_subtr_100_percent = 0;
                  Xg_subtr_100_percent = pow(Vg_nominal, 2.0)/Sg_nominal;
            if(depurar_base==1){
            IupMessagef("Aviso!", "A reatância subtransitoria nominal do gerador (%d:%d) é %.5f [100%%]", i, i, Xg_subtr_100_percent);
            }



            float Z_base = 0;
            float V_base = base_SEP_coleta[i].V_base; //note que existe 3 cenários diferentes, por isso  precisa ser global
                  V_base = V_base*pow(10.0,3.0);
            float S_base = base_SEP_coleta[0].P_base; //Lembre-se V_base e S_base não ficam em pu
                  S_base = S_base*pow(10.0,6.0);

            //IupMessagef("Aviso!", "A tensão base do gerador é %.2E [V]", V_base);
            //IupMessagef("Aviso!", "A potencia base do gerador é %.2E [VA]", S_base);


            Z_base = pow(V_base, 2.0)/S_base;

            if(depurar_base==1){
            IupMessagef("Aviso!", "A impedância de base do gerador (%d:%d) é %.5f [ohms]", i, i, Z_base);
            }

            float Xg_subtr_pu = (Xg_subtr_percent/100.0)*(Xg_subtr_100_percent/Z_base);


            /*************************************************************************************************/
            //COMPLEMENTO 12jul22
            if(pet_ON == 1){
                float Xg_peterson_ohms = matrix_struct[i][i].gerador_indices.Xg_pet;

                float Xg_peterson_pu = Xg_peterson_ohms/Z_base; //Bem simples assim, só fica atento que não é a tensão nominal, é a tensão de base

                /*************************************************************************************************/
                Xg_subtr_pu = Xg_subtr_pu + 3*Xg_peterson_pu; //TEM QUE MULTIPLICAR POR 3
            }



        return Xg_subtr_pu;
    }

    if(id_k_Gerador == 0 || id_k_Gerador == 2){ //Se a reatância não sair nula, o id_k_Gerador não está zerado ou desativo OFF!


         if(id_k_Gerador == 0){
            if(depurar_base==1){
            IupMessagef("Aviso!", "Nenhuma máquina síncrona foi lançada na barra (%d:%d), a reatância é nula.", i, i);
            }
         }

         if(id_k_Gerador == 2){
            //IupMessagef("Aviso!", "Já foi lançado um motor na barra (%d:%d), a reatância é nula.", i, i);
         }
            float Xg_subtr_pu = 0.0; //CARREGAMENTO NULO

            matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O GERADOR, O MOTOR É NA ROTINA MOTOR...

            matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O GERADOR, O MOTOR É NA ROTINA MOTOR...

            matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero = Xg_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O GERADOR, O MOTOR É NA ROTINA MOTOR...


        return Xg_subtr_pu;

    }


}



/*************************************************(                     \MOTORES                      )********************************************

***/

void Calc_Positiva_Xm_pu(Ihandle* ih)
{

        for(int i = 1; i < size_SEP_bars_OLD+1; i++){ /*** ATENÇÃO LAÇO DE REPETIÇÃO ***/

            float Xm_subtr_percent = matrix_struct[i][i].motor_indices.Xm_seq_pos; //se liga está utilizando a sequência positiva


            //IupMessagef("Aviso!", "A reatância subtransitoria percentual do motor (%d:%d) é %.2f [%%]", i, i,  Xm_subtr_percent);

            int pet_ON = 0; //NÃO calcular Xm_peterson
            float Xm_subtr_pu = function_Z_base_motor(Xm_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

            /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            int id_k_Gerador = matrix_struct[i][i].gerador_indices.id_k_Gerador;
            int id_k_Motor = matrix_struct[i][i].motor_indices.id_k_Motor;

            //if(id_k_Gerador == 1 && id_k_Motor == 2){
            if(Xm_subtr_pu!=0){
                matrix_struct_pu[i][i].motor_indices.Xm_seq_pos = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }
                //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) do gerador é %.5f [pu]", Xg_subtr_pu);

                if(depurar_motor==1){
                IupMessagef("Aviso!", "A reatância de sequência positiva do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_pos);
                IupMessagef("Aviso!", "A reatância de sequência positiva do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos);
                }

        }



}




void Calc_Negativa_Xm_pu(Ihandle* ih)
{

        for(int i = 1; i < size_SEP_bars_OLD+1; i++){ /*** ATENÇÃO LAÇO DE REPETIÇÃO ***/

            float Xm_subtr_percent = matrix_struct[i][i].motor_indices.Xm_seq_neg; //se liga está utilizando a sequência positiva

            //implementar id_k_Motor aqui
            //IupMessagef("Aviso!", "A reatância de sequência negativa percentual do motor (%d:%d) é %.2f [%%]", i, i, Xm_subtr_percent);

            int pet_ON = 0; //NÃO calcular Xm_peterson
            float Xm_subtr_pu = function_Z_base_motor(Xm_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

               /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            if(Xm_subtr_pu != 0){
                matrix_struct_pu[i][i].motor_indices.Xm_seq_neg = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22 ... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }

                if(depurar_motor==1){
                IupMessagef("Aviso!", "A reatância de sequência negativa do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_neg);
                IupMessagef("Aviso!", "A reatância de sequência negativa do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg);
                }


            //criar uma rotina, se maior que 1 entrar em loop

        }


}




void Calc_Zero_Xm_pu(Ihandle* ih)
{

        for(int i = 1; i < size_SEP_bars+1; i++){ /*** ATENÇÃO LAÇO DE REPETIÇÃO ***/

            float Xm_subtr_percent = matrix_struct[i][i].motor_indices.Xm_seq_zero; //se liga está utilizando a sequência positiva

            //implementar id_k_Motor aqui
            //IupMessagef("Aviso!", "A reatância de sequência negativa percentual do motor (%d:%d) é %.2f [%%]", i, i, Xm_subtr_percent);

            int pet_ON = 1; //calcular Xm_peterson
            float Xm_subtr_pu = function_Z_base_motor(Xm_subtr_percent, i, pet_ON); /*** \ACIONA FUNÇÃO PARA GERAR pu ***/

               /**************  OBJETIVO DA FUNÇÃO **********************************************************************************************/
            if(Xm_subtr_pu != 0){
                matrix_struct_pu[i][i].motor_indices.Xm_seq_zero = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/
                matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero = 0.0; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //CAIU A FICHA 17mai22 ... para não preenchimento ou bloqueia zerava, mas para motor não zerava o gerador
            }

                if(depurar_motor==1){
                IupMessagef("Aviso!", "A reatância de sequência zero do motor (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].motor_indices.Xm_seq_zero);
                IupMessagef("Aviso!", "A reatância de sequência zero do gerador (%d:%d) é %.5f [pu]", i, i, matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero);
                }


            //criar uma rotina, se maior que 1 entrar em loop

        }


}






//CUIDADO MÚLTIPLOS ACESSOS - restringir X perterson

float function_Z_base_motor(float Xm_subtr_percent, int i, int pet_ON) //MÚLTIPLO ACESSOS: positiva, negativa e zero...//Motor conectado à barra i
{
    /*** \MULTIPLAS \ENTRADAS 3X = SEQ. POSITIVA, SEQ. NEGATIVA E SEQ. ZERO ***/

    int id_k_Motor = -1;
    id_k_Motor = matrix_struct[i][i].motor_indices.id_k_Motor; //recebe o status da id_k da struct

    if(id_k_Motor == 1){
   /*** ROTINA DE CÁLCULO É SEMELHANTE A DA SEQUÊNCIA POSITIVA, PORÉM A RESULTANTE PODE SER DIFERENTE DEPENDENDO DO INPUT ****/
            /*** \RECEBIMENTO via argumento \Xm_subtr_percent ***/
            if(depurar_base=1){
            //IupMessage("Aviso!", "ROTINA MOTOR");
            }

            float Vm_nominal = matrix_struct[i][i].motor_indices.Vm_nominal;
                  Vm_nominal = Vm_nominal*pow(10.0,3.0);
            if(depurar_base==1){
            //IupMessagef("Aviso!", "A tensão nominal do motor (%d:%d) é %.2E [V]", i, i, Vm_nominal);
            }


            float Sm_nominal = matrix_struct[i][i].motor_indices.Pm_nominal;
                  Sm_nominal = Sm_nominal*pow(10.0,6.0);
            if(depurar_base==1){
            //IupMessagef("Aviso!", "A potência nominal do motor (%d:%d) é %.2E [VA]", i, i, Sm_nominal);
            }

            float Xm_subtr_100_percent = 0;
                  Xm_subtr_100_percent = pow(Vm_nominal, 2.0)/Sm_nominal;
            if(depurar_base==1){
            //IupMessagef("Aviso!", "A reatância subtransitoria nominal do motor (%d:%d) é %.5f [100%%]", i, i, Xm_subtr_100_percent);
            }




            float Z_base = 0;
            float V_base = base_SEP_coleta[i].V_base; //DIFERENTEMENTE DO TRAFO QUE PRECISA DE LADO CERTO
                  V_base = V_base*pow(10.0,3.0);
            float S_base = base_SEP_coleta[0].P_base; //Lembre-se V_base e S_base não ficam em pu
                  S_base = S_base*pow(10.0,6.0);

            //IupMessagef("Aviso!", "A tensão base do motor é %.2E [V]", V_base);
            //IupMessagef("Aviso!", "A potencia base do motor é %.2E [VA]", S_base);


            Z_base = pow(V_base, 2.0)/S_base;

            if(depurar_base==1){
            //IupMessagef("Aviso!", "A impedância de base do motor (%d:%d) é %.5f [ohms]", i, i, Z_base);
            }

            float Xm_subtr_pu = (Xm_subtr_percent/100.0)*(Xm_subtr_100_percent/Z_base);



            /*************************************************************************************************/
            //COMPLEMENTO 12jul22
            if(pet_ON == 1){
                float Xm_peterson_ohms = matrix_struct[i][i].motor_indices.Xm_pet;

                float Xm_peterson_pu = Xm_peterson_ohms/Z_base; //Bem simples assim, só fica atento que não é a tensão nominal, é a tensão de base

                /*************************************************************************************************/
                Xm_subtr_pu = Xm_subtr_pu + 3*Xm_peterson_pu; //TEM QUE MULTIPLICAR POR 3
            }




        return Xm_subtr_pu;
    }

    if(id_k_Motor == 0 || id_k_Motor == 2){ //Se a reatância não sair nula, o id_k_Gerador não está zerado ou desativo OFF!


         if(id_k_Motor == 0){
            if(depurar_base==1){
            //IupMessagef("Aviso!", "Nenhuma máquina síncrona foi lançada na barra (%d:%d), a reatância é nula.", i, i);
            }
         }

         if(id_k_Motor == 2){
            //IupMessagef("Aviso!", "Já foi lançado um gerador na barra (%d:%d), a reatância é nula.", i, i);
         }
            float Xm_subtr_pu = 0.0; //CARREGAMENTO NULO

            matrix_struct_pu[i][i].motor_indices.Xm_seq_pos = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O MOTOR, O GERADOR É NA ROTINA GERADOR...

            matrix_struct_pu[i][i].motor_indices.Xm_seq_neg = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O MOTOR, O GERADOR É NA ROTINA GERADOR...

            matrix_struct_pu[i][i].motor_indices.Xm_seq_zero = Xm_subtr_pu; /*** \ARMAZENAMENTO À MATRIZ PU ***/ //ESQUECI DE ARMAZENAR Á STRUCT
            //O FOCO É SÓ O MOTOR, O GERADOR É NA ROTINA GERADOR...



        return Xm_subtr_pu;

    }

}


/*****************************************(                      \TRANSFORMADORES                    )********************************************

***/





/*** CONVERSÃO PARA PU - UTILIZÁVEL EM SEQ.POSitiva E SEQ. NEGativa ***/
void Calc_Positiva_Xeq_TR1_pu(float Tensao_TR_primario, float Tensao_BASE_primario, int i, int j) //i:j precisam vim por que é trafo a trafo
{                                                                                                 //Crítico, o i está atrelado ao primário

                /*** \ACIONA \ANTECIPADO \AO \CALC \BASE ***/
                //SÓ ENTRA NESTA FUNÇÃO SE UM TRAFO DIRETO TIVER SIDO LANÇADO - ATRELADO AQUILO QUE FOI CLICADO

               if(depurar_trafo==0){
               //IupMessagef("Aviso!", "CÁLCULO DA IMPEDÂNCIA DE BASE");
               }

               //Captura a reatância do transformador digitada no form
               float Xeq_TR1_percent = matrix_struct[i][j].trafo_indices.Xeq_trafo; //se liga está utilizando a sequência positiva


                   if(depurar_trafo==0){
                   //IupMessagef("Aviso!", "A reatância equivalente percentual do TR (%d:%d) é %.2f [%%]", i, j, Xeq_TR1_percent); //vai exibir o trafo na mesma polaridade de seleção do para ordenado
                   //IupMessagef("Aviso!", "A reatância equivalente percentual do TR (%d:%d) é %.2f [%%]", j, i, matrix_struct[j][i].trafo_indices.Xeq_trafo); //vai exibir o trafo na mesma polaridade de seleção do para ordenado
                   }

                   float Xeq_TR1_100_percent = 0;
                   float V_TR1_nominal = Tensao_TR_primario; //tensão primária que estará no mesmo lado que o primário da base
                         V_TR1_nominal = V_TR1_nominal*pow(10.0,3.0);
                   float S_TR1_nominal = matrix_struct[i][j].trafo_indices.Pt_nominal; //independe do lado
                         S_TR1_nominal = S_TR1_nominal*pow(10.0,6.0);


                   if(depurar_trafo==0){
                   //IupMessagef("Aviso!", "A tensão primária nominal do TR (%d:%d) é %.2E [V]", i, j, V_TR1_nominal);
                   //IupMessagef("Aviso!", "A potencia nominal do TR (%d:%d) é %.2E [VA]", i, j, S_TR1_nominal);
                   }

                   Xeq_TR1_100_percent = pow(V_TR1_nominal, 2.0)/S_TR1_nominal;

                   if(depurar_trafo==1){
                   //IupMessagef("Aviso!", "A reatância equivalente nominal do TR1 %d:%d é %.5f [100%%]", i, j, Xeq_TR1_100_percent);
                   }

                   float Z_base = 0;
                   float V_base = Tensao_BASE_primario; //note que não pode ser base_SEP_coelta[0], pois é trafo a trafo
                         V_base = V_base*pow(10.0,3.0);
                   float S_base = base_SEP_coleta[0].P_base;//Aqui tranquilo, pq é global ao SEP
                         S_base = S_base*pow(10.0,6.0);

                   if(depurar_trafo==0){
                   //IupMessagef("Aviso!", "A tensão de base do TR (%d:%d) é %.2E [V]", i, j, V_base);
                   //IupMessagef("Aviso!", "A potência de base do TR (%d:%d)  é %.2E [VA]", i, j, S_base);
                   }

                   Z_base = pow(V_base, 2.0)/S_base;


                   if(depurar_trafo==1){
                   //IupMessagef("Aviso!", "A impedância de base do TR1 %d:%d é %.5f [ohms]", i, j, Z_base);
                   }

                    float Xeq_TR1_pu = (Xeq_TR1_percent/100.0)*(Xeq_TR1_100_percent/Z_base);

                    /*** \ACIONA \ANTECIPADO \AO \CLICK  - SÓ É PREENCHIDO UMA ÚNICA VEZ, QUANDO CLICA, ENTÃO O SIMÉTRICO j, i tbm***/


                    if(continua_v[i].init == 1){
                        continua_v[i].init = 2; //desabilito uma nova entrada à função de expansão da matriz
                    }

                    //BEMMM SIMPLES, depende do tempo de execução
                    if(continua_v[i].init == 0){
                        continua_v[i].init = 1; //habilito para somente uma entrada
                    }




                    /**************  OBJETIVO DA FUNÇÃO **************/
                    matrix_struct_pu[i][j].trafo_indices.Xeq_trafo = Xeq_TR1_pu; /*** \ARMAZENAMENTO \MATRIX \PU À MATRIZ pu ***/
                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos = Xeq_TR1_pu; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg = Xeq_TR1_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


                    /**************  CARREGAMENTO SIMÉTRICO **************/
                    matrix_struct_pu[j][i].trafo_indices.Xeq_trafo = Xeq_TR1_pu; /*** \ARMAZENAMENTO \MATRIX \PU À MATRIZ pu ***/
                    matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos = Xeq_TR1_pu; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                    matrix_struct_pu[j][i].trafo_indices.X_TR_seq_neg = Xeq_TR1_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


            /*** NOVA ROTINA - TRAFO ENVOLVIDO - 15jul22 ***/
            /*************************************************************************************************************************/
            int buffer_ligacao_nucleo = 89;
            int buffer_ligacao_esquema = 89;
            int v = 89;



            //VAI ENTRAR 89, 89 e 1...
            if(buffer_ligacao_nucleo != 2 && buffer_ligacao_esquema != 1 && continua_v[i].init == 1){
                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/
                    matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                    //IupMessagef("Aviso!", "A reatância de sequência ZERO em pu do TR (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero);
                    //IupMessagef("Aviso!", "A reatância de sequência ZERO em pu do TR (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero);

            }


            /*************************************************************************************************************************/

            buffer_ligacao_nucleo = matrix_struct[i][j].trafo_indices.ligacao_nucleo;
            buffer_ligacao_esquema = matrix_struct[i][j].trafo_indices.ligacao_esquema;


            if(buffer_ligacao_nucleo == 2 && buffer_ligacao_esquema == 1 && continua_v[i].init == 1){

                if(size_SEP_bars < 16) //se ainda tiver banda para suportar nova entrada de nós
                {



                    size_SEP_bars++; /*** \CUIDADO \CRITICO - \EXPANSAO \MATRIZ ***/




                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero = 0; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/
                    matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = 0; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                    v = size_SEP_bars;
                    //i = primário
                    //j = secundário
                    //v = size_SEP_bars último
                    matrix_struct_pu[i][v].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu/2; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/
                    matrix_struct_pu[v][i].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu/2; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                    matrix_struct_pu[j][v].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu/2; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/
                    matrix_struct_pu[v][j].trafo_indices.X_TR_seq_zero = Xeq_TR1_pu/2; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                    //ACHEI O ERRO
                    //matrix_struct_pu[v][v].trafo_indices.X_TR_seq_zero = 4.5*Xeq_TR1_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/
                    matrix_struct_pu[v][v].gerador_indices.Xg_seq_zero = 4.5*Xeq_TR1_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                    /**************  OBJETIVO DA FUNÇÃO - PARA ELEMENTOS EXPANDIDOS NÃO ITERADOS - INEXISTENTES NA SEQ.+E- **************/
                    matrix_struct_pu[i][v].trafo_indices.Xeq_trafo = 0.0; /*** \ARMAZENAMENTO \MATRIX \PU À MATRIZ pu ***/
                    matrix_struct_pu[i][v].trafo_indices.X_TR_seq_pos = 0.0; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                    matrix_struct_pu[i][v].trafo_indices.X_TR_seq_neg = 0.0; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


                    /**************  CARREGAMENTO SIMÉTRICO - PARA ELEMENTOS EXPANDIDOS NÃO ITERADOS - INEXISTENTES NA SEQ.+E-   **************/
                    matrix_struct_pu[j][v].trafo_indices.Xeq_trafo = 0.0; /*** \ARMAZENAMENTO \MATRIX \PU À MATRIZ pu ***/
                    matrix_struct_pu[j][v].trafo_indices.X_TR_seq_pos = 0.0; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                    matrix_struct_pu[j][v].trafo_indices.X_TR_seq_neg = 0.0; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/

                    /**************  CARREGAMENTO SIMÉTRICO - PARA ELEMENTOS EXPANDIDOS NÃO ITERADOS - INEXISTENTES NA SEQ.+E-   **************/
                    matrix_struct_pu[v][v].gerador_indices.Xg_seq_pos = 0.0; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                    matrix_struct_pu[v][v].gerador_indices.Xg_seq_neg = 0.0; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


                    /*** CRIAÇÃO DE ELEMENTOS VIRTUAIS AUXILIARES ***/
                    /*** X1T ***/
                    matrix_struct[i][v].trafo_indices.id_k_Trafo = 1; //cuidado, aqui não é a matrix_struct_pu
                    matrix_struct[v][i].trafo_indices.id_k_Trafo = 2; //trafo simétrico
                    matrix_struct[i][v].LT_indices.id_k_LT = 2; //não simétrica
                    matrix_struct[v][i].LT_indices.id_k_LT = 2; //simétrica
                    matrix_struct[v][i].trafo_indices.ligacao_nucleo = 1; //criando um trafo envolvente Yat:Yat
                    matrix_struct[v][i].trafo_indices.ligacao_esquema = 1;

                    /*** X2T ***/
                    matrix_struct[j][v].trafo_indices.id_k_Trafo = 1;
                    matrix_struct[v][j].trafo_indices.id_k_Trafo = 2; //trafo simétrico
                    matrix_struct[j][v].LT_indices.id_k_LT = 2; //não simétrica
                    matrix_struct[v][j].LT_indices.id_k_LT = 2; //simétrica
                    matrix_struct[j][v].trafo_indices.ligacao_nucleo = 1; //criando um trafo envolvente Yat:Yat
                    matrix_struct[j][v].trafo_indices.ligacao_esquema = 1;

                    /*** X3T ***/
                    /*** \GERADORES \ANTECIPADOS - PREENCHIMENTO VIA FUNÇÃO DO TRANSFORMADOR ***/

                    matrix_struct[v][v].gerador_indices.id_k_Gerador = 1;
                    matrix_struct[v][v].motor_indices.id_k_Motor = 2;
                    matrix_struct[v][v].gerador_indices.ligacao_esquema = 2; //Y-at do gerador
                    matrix_struct[v][v].gerador_indices.Xg_pet = 0.0;

                    matrix_struct[v][v].gerador_indices.ligacao_nucleo_TR = 2; //correspondência visando atrelar o trafo envolvido
                    G[v].init = 1; //modelagem do trafo envolvido Yat:Yat

                    if(depurar_trafo==1){
                    IupMessagef("Aviso!", "A reatância de sequência zero X1T (%d:%d) em pu do TR (%d:%d) é %.5f [pu]", i, v, i, j, matrix_struct_pu[i][v].trafo_indices.X_TR_seq_zero);
                    IupMessagef("Aviso!", "A reatância de sequência zero X2T (%d:%d) em pu do TR (%d:%d) é %.5f [pu]", j, v, i, j, matrix_struct_pu[j][v].trafo_indices.X_TR_seq_zero);
                    IupMessagef("Aviso!", "A reatância de sequência zero X3T (%d:%d) em pu do TR (%d:%d) é %.5f [pu]", v, v, i, j, matrix_struct_pu[v][v].gerador_indices.Xg_seq_zero);

                    IupMessagef("Aviso!", "A reatância de sequência ZERO em pu do TR (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero);
                    IupMessagef("Aviso!", "A reatância de sequência ZERO em pu do TR (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero);

                    }

                    //ÓLOKO, ESBAGUACEI

                }

                if(size_SEP_bars > 15) //se ainda tiver banda para suportar nova entrada de nós
                {
                        IupMessagef("Aviso!", "O lançamento para um trafo envolvido %d:%d extrapola a capacidade de 15 nós do SEP. Refazer o SEP.", i, j);
                }
            }



/********************************************************************************************************************/

            /*** \Calc_Zero_Memory_Xeq_TR1_pu(Tensao_TR_primario, Tensao_BASE_primario, i, j, Xeq_TR1_pu); ***/

            /*** Como ainda não foi obtidas as demais reatâncias é preciso enviar à uma memória tudo do trafo para calcular
                 depois calcular Xeq_TR1_pu_ZERO com botão load full.
            ***/

                    //matrix_struct_pu[j][i].trafo_indices.Xeq_trafo = Xeq_TR1_pu; //preenchimento do simétrico ..., mas o for duplo já faz isso

                    if(depurar_trafo==0){
                    //IupMessagef("Aviso!", "A reatância de sequência POSITIVA em pu do TR (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos);
                    //IupMessagef("Aviso!", "A reatância de sequência POSITIVA em pu do TR (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos);
                    }
                    //IupMessagef("Aviso!", "A reatância equivalente assimétrica do TR (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].trafo_indices.Xeq_trafo);
                    //IupMessagef("Aviso!", "A reatância equivalente simétrica do TR (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].trafo_indices.Xeq_trafo);

/*****************************************  FIM *******************************************************************/
}







/*** \SEQUENCIA \ZERO \TR \Zpu


Note que não é possível calcular sem ter as demais reatâncias...lembrando inclusive que terá que implementar uma rotina para
motores e geradores, caso da reatância recair para o trafo

float Calc_Zero_Memory_Xeq_TR1_pu(float Tensao_TR_primario, float Tensao_BASE_primario, int i, int j, float Xeq_TR1_pu)
{

***/









/*****************************************(                       \LT                         )********************************************

***/




void Calc_Positiva_Xeq_LT_pu(Ihandle *ih) //NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA PORQUE LÁ NÃO EXISTE id_k_LT = 1
{
    for(int i = 1; i < size_SEP_bars_OLD+1; i++){
        for(int j = 1; j < size_SEP_bars_OLD+1; j++){
            if(i!=j){
                    int id_k_LT = matrix_struct[i][j].LT_indices.id_k_LT;
                    //int id_k_LT_Simetric = matrix_struct[j][i].LT_indices.id_k_LT;

                    if(id_k_LT == 1){

                        float Xeq_LT = matrix_struct[i][j].LT_indices.Xeq_LT_seq_pos; //se liga está utilizando a sequência positiva

                        if(depurar_LT==1){
                        IupMessagef("Aviso!", "A reatância de sequência positiva da LT (%d:%d) é %.2f [Ohms]", i, j, Xeq_LT);
                        IupMessagef("Aviso!", "A reatância de sequência positiva da LT (%d:%d) é %.2f [Ohms]", j, i, matrix_struct[j][i].LT_indices.Xeq_LT_seq_pos);
                        //IupMessagef("Aviso!", "O id_k_LT_ij é %d e o id_k_LT_Simetric_ji é %d", id_k_LT, id_k_LT_Simetric);
                        }


                        float Z_base = 0;
                        float V_base = base_SEP_coleta[j].V_base; /*** \MONITORAR - a princípio tanto faz i ou j, basta a LT tá fincada à barra***/
                              V_base = V_base*pow(10.0,3.0);
                        float S_base = base_SEP_coleta[0].P_base;
                              S_base = S_base*pow(10.0,6.0);

                        Z_base = pow(V_base, 2.0)/S_base;

                        //IupMessagef("Aviso!", "V_base[j] = %.2f [kV] e Z_base[j] = %.2f [Ohms]", V_base, Z_base);


                        //IupMessagef("Aviso!", "A impedância de base da LT é %.5f [ohms]", Zb2);

                        float Xeq_LT_pu = (Xeq_LT/Z_base);

                        if(depurar_LT==1){
                        //IupMessagef("Aviso!", "V_base[j] = %.2f [kV], Z_base[j] = %.2f [Ohms] e Xeq_LT_pu é %.2f", V_base, Z_base, Xeq_LT_pu);
                        }

                        /**************  OBJETIVO DA FUNÇÃO **************/
                        matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos = Xeq_LT_pu; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                        //matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg = Xeq_LT_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/
                        //matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero = Xeq_LT_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                        /**************  CARREGAMENTO SIMÉTRICO **************/
                        matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos = Xeq_LT_pu; /*** \ARMAZENAMENTO \POSITIVA À MATRIZ pu ***/
                        //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = Xeq_LT_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/
                        //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = Xeq_LT_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/


                        //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) da LT é %.5f [pu]", Xeq_LT_pu);
                        if(depurar_LT==1){
                        IupMessagef("Aviso!", "A reatância de sequência positiva  da LT (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos);
                        IupMessagef("Aviso!", "A reatância de sequência positiva  da LT (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos);
                        }
                    }
            }

        }

    }

}






void Calc_Negativa_Xeq_LT_pu(Ihandle *ih) //NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA PORQUE LÁ NÃO EXISTE id_k_LT = 1
{
    for(int i = 1; i < size_SEP_bars_OLD+1; i++){
        for(int j = 1; j < size_SEP_bars_OLD+1; j++){
            if(i!=j){


                    int id_k_LT = matrix_struct[i][j].LT_indices.id_k_LT;
                    //int id_k_LT_Simetric = matrix_struct[j][i].LT_indices.id_k_LT;

                    if(id_k_LT == 1){



                        float Xeq_LT = matrix_struct[i][j].LT_indices.Xeq_LT_seq_neg; //se liga está utilizando a sequência negativa

                        if(depurar_LT==1){
                        IupMessagef("Aviso!", "A reatância de sequência negativa da LT (%d:%d) é %.2f [Ohms]", i, j, Xeq_LT);
                        IupMessagef("Aviso!", "A reatância de sequência negativa da LT (%d:%d) é %.2f [Ohms]", j, i, matrix_struct[j][i].LT_indices.Xeq_LT_seq_neg);
                        //IupMessagef("Aviso!", "O id_k_LT_ij é %d e o id_k_LT_Simetric_ji é %d", id_k_LT, id_k_LT_Simetric);
                        }


                        float Xeq_LT_pu = function_Z_base_LT(Xeq_LT, j);

                        /**************  OBJETIVO DA FUNÇÃO **************/
                        matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg = Xeq_LT_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


                        /**************  CARREGAMENTO SIMÉTRICO **************/
                        matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = Xeq_LT_pu; /*** \ARMAZENAMENTO \NEGATIVA À MATRIZ pu ***/


                        if(depurar_LT==1){
                        //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) da LT é %.5f [pu]", Xeq_LT_pu);
                        IupMessagef("Aviso!", "A reatância de sequência negativa  da LT (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg);
                        IupMessagef("Aviso!", "A reatância simétrica de sequência negativa  da LT (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg);
                        }
                    }
            }

        }

    }

}







void Calc_Zero_Xeq_LT_pu(Ihandle *ih) ////NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA PORQUE LÁ NÃO EXISTE id_k_LT = 1
{
    for(int i = 1; i < size_SEP_bars+1; i++){ //Aqui não dá para colocar o OLD, pois na sequencia zero com envolvido a size_bars expande
        for(int j = 1; j < size_SEP_bars+1; j++){
            if(i!=j){
                    //NOTE, como atribuí id_k_LT[i][v]...igual a 2 lá na função base então NÃO vai carregar a reatância de sequência zero para i:v e os outros
                int id_k_LT = matrix_struct[i][j].LT_indices.id_k_LT;
                    //int id_k_LT_Simetric = matrix_struct[j][i].LT_indices.id_k_LT;

                    if(id_k_LT == 1){ //SÓ ENTRA COM LT EXISTENTE, LANÇAMENTO DIRETO - NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA

                        float Xeq_LT = matrix_struct[i][j].LT_indices.Xeq_LT_seq_zero; //se liga está utilizando a sequência zero
                        //NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA PORQUE LÁ NÃO EXISTE id_k_LT = 1

                        if(depurar_LT==1){
                        IupMessagef("Aviso!", "A reatância de sequência zero da LT (%d:%d) é %.2f [Ohms]", i, j, Xeq_LT);
                        IupMessagef("Aviso!", "A reatância de sequência zero da LT (%d:%d) é %.2f [Ohms]", j, i, matrix_struct[j][i].LT_indices.Xeq_LT_seq_zero);
                        //IupMessagef("Aviso!", "O id_k_LT_ij é %d e o id_k_LT_Simetric_ji é %d", id_k_LT, id_k_LT_Simetric);
                        }



                        float Xeq_LT_pu = function_Z_base_LT(Xeq_LT, j); //NUNCA VAI ENTRAR NA REGIÃO EXPANDIDA PORQUE LÁ NÃO EXISTE id_k_LT = 1

                        /**************  OBJETIVO DA FUNÇÃO **************/
                        matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero = Xeq_LT_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/

                        /**************  CARREGAMENTO SIMÉTRICO **************/
                        matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = Xeq_LT_pu; /*** \ARMAZENAMENTO \PREVIO \ZERO À MATRIZ pu ***/


                        if(depurar_LT==1){
                        //IupMessagef("Aviso!", "A reatância de sequência positiva (subtransitória/transitória/permanente) da LT é %.5f [pu]", Xeq_LT_pu);
                        IupMessagef("Aviso!", "A reatância de sequência zero  da LT (%d:%d) é %.5f [pu]", i, j, matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero);
                        IupMessagef("Aviso!", "A reatância simétrica de sequência zero  da LT (%d:%d) é %.5f [pu]", j, i, matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero);
                        }
                    }
            }

        }

    }

}






float function_Z_base_LT(float Xeq_LT, int j)
{

                //IupMessagef("Aviso!", "A reatância de sequência positiva da LT (%d:%d) é %.2f [Ohms]", i, j, Xeq_LT);
                //IupMessagef("Aviso!", "A reatância de sequência positiva da LT (%d:%d) é %.2f [Ohms]", j, i, matrix_struct[j][i].LT_indices.Xeq_LT_seq_pos);
                //IupMessagef("Aviso!", "O id_k_LT_ij é %d e o id_k_LT_Simetric_ji é %d", id_k_LT, id_k_LT_Simetric);


                float Z_base = 0;
                float V_base = base_SEP_coleta[j].V_base; /*** \MONITORAR - a princípio tanto faz i ou j, basta a LT tá fincada à barra***/
                      V_base = V_base*pow(10.0,3.0);
                float S_base = base_SEP_coleta[0].P_base;
                      S_base = S_base*pow(10.0,6.0);

                Z_base = pow(V_base, 2.0)/S_base;

                //IupMessagef("Aviso!", "V_base[j] = %.2f [kV] e Z_base[j] = %.2f [Ohms]", V_base, Z_base);


                //IupMessagef("Aviso!", "A impedância de base da LT é %.5f [ohms]", Zb2);

                float Xeq_LT_pu = (Xeq_LT/Z_base);

                if(depurar_base==1){
                //IupMessagef("Aviso!", "V_base[j] = %.2f [kV], Z_base[j] = %.2f [Ohms] e Xeq_LT_pu é %.2f", V_base, Z_base, Xeq_LT_pu);
                }

                return Xeq_LT_pu;

}









/*****************************************(                      \TRANSFORMADORES \E \LTs                   )********************************************

***/




float function_Z_pu_Positiva_TR_LT(Ihandle* disparo_load_full) //Duplo acesso, positiva e negativa...//Motor conectado à barra i
{
    for(int i = 1; i < size_SEP_bars+1; i++){
        for(int j = 1; j < size_SEP_bars+1; j++){

                int id_k_Trafo = matrix_struct[i][j].trafo_indices.id_k_Trafo;
                int id_k_Trafo_Simetric = matrix_struct[j][i].trafo_indices.id_k_Trafo;
                int id_k_LT = matrix_struct[i][j].LT_indices.id_k_LT;
                int id_k_LT_Simetric = matrix_struct[j][i].LT_indices.id_k_LT;

                /*********************************** ROTINA DE NÚCLEO ENVOLVIDO LIGAÇÃO 1 ***************************************/



                /******************************************************************************************************************/



                //Nunca vou ter id_k_LT = 1 na linha/coluna expandida, só vai aparecer id_k_Trafo = 1 ou 0 (com id_k_LT = 0)
                if(id_k_LT == 1){ //No ramo que tiver uma LT, irei carregar com zero todas reatâncias pu de trafos com zero
                                  //AQUI SÓ ENTRA TRAFO NÃO LANÇADO, MAS COM PRESENÇA DE LT

                    //IupMessage("Aviso!","Entrada de id_k_LT == 1, TRAFOS E LTs");


                    if(id_k_Trafo == 2 || id_k_Trafo_Simetric == 2|| id_k_LT_Simetric == 2){


                        /*** \SEQUENCIA \POSITIVA ***/
                        //Inexistência de TR no ramo
                        matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                        matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                        //Existência de LT no ramo
                        //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos; //recebe o espelho

                        /*** \SEQUENCIA \NEGATIVA ***/
                        //Inexistência de TR no ramo
                        matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                        matrix_struct_pu[j][i].trafo_indices.X_TR_seq_neg = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                        //Existência de LT no ramo
                        //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg; //recebe o espelho

                        /*** \SEQUENCIA \ZERO ***/
                        //Inexistência de TR no ramo
                        matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                        matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                        //Existência de LT no ramo
                        //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero; //recebe o espelho

                    }

                }

                //Cara é mais fácil vc simplemente atenuar a matriz inversa do que mexer aqui


                if(id_k_Trafo == 1){ //Trafos do trafo de núcleo envolvido entram aqui

                    //IupMessage("Aviso!","Trafo == 1, TRAFOS E LTs");

                    if(id_k_LT == 2 || id_k_Trafo_Simetric == 2 || id_k_LT_Simetric == 2){//AQUI SÓ ENTRA LT NÃO LANÇADA, MAS COM PRESENÇA DE TRAFO

                        //CUIDADO ELE AINDA PRECISA ENTRAR AQUI NA SEQUENCIA POSITIVA PARA NÚCLEO ENVOLVIDO LIGAÇÃO 1, ELE SÓ NÃO PODE
                        //ENTRAR DEPOIS DA REGIÃO EXPANDIDA

                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){


                            /*** \SEQUENCIA \POSITIVA ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos; //recebe o espelho

                            /*** \SEQUENCIA \NEGATIVA ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_neg = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg; //recebe o espelho
                        }


                //NÃO É...SOMENTE ESTA SEQUÊNCIA É EXPANDIDA, a iteração passa direto, e vai até o fundo, enquanto a parte de cima esgota

                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){//desencantou, era o ou de união, entra normal depois entra na parte expandida

                            /*** \SEQUENCIA \ZERO ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero; //recebe o espelho
                        }



                    } //LT's não lançadas
                }//id_k_Trafo = 1


                if(id_k_Trafo == 0 && id_k_LT == 0){

                    //IupMessage("Aviso!","Entra na id_k_Trafo == 0 e id_k_LT == 0, TRAFOS E LTs");

                    /*** \PARTE \UM \DE \DOIS - 1/2 - COMPONENTE LT ***/

                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){ //iteração para de entrar na região expandida da matriz
                                                            //Não é só pq tem núcleo envolvido e ligação 1, mas pq não é seq zero, são 3 condições
                            /*** \SEQUENCIA \POSITIVA ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos; //recebe o espelho

                            /*** \SEQUENCIA \NEGATIVA ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_neg = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg; //recebe o espelho

                        }

                    //SOMENTE ESTA SEQUÊNCIA É EXPANDIDA
                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){

                            /*** \SEQUENCIA \ZERO ***/
                            //Inexistência de LT no ramo
                            matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero = 0.0; //id_k_LT == 2, inexistência de LT no ramo
                            matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = 0.0; //id_k_LT == 2, inexistência de LT no ramo

                            //Existência de TR no ramo
                            //matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero; //recebe o espelho
                        }



                    /*** \PARTE \DOIS \DE \DOIS - 2/2 - COMPONENTE TR ***/

                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){ //iteração para de entrar na região expandida da matriz

                            /*** \SEQUENCIA \POSITIVA ***/
                            //Inexistência de TR no ramo
                            matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                            matrix_struct_pu[j][i].trafo_indices.X_TR_seq_pos = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                            //Existência de LT no ramo
                            //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_pos = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos; //recebe o espelho

                            /*** \SEQUENCIA \NEGATIVA ***/
                            //Inexistência de TR no ramo
                            matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                            matrix_struct_pu[j][i].trafo_indices.X_TR_seq_neg = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                            //Existência de LT no ramo
                            //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_neg = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg; //recebe o espelho
                        }


                    //SOMENTE ESTA SEQUÊNCIA É EXPANDIDA
                        if(size_SEP_bars <= size_SEP_bars_OLD || size_SEP_bars > size_SEP_bars_OLD){

                            /*** \SEQUENCIA \ZERO ***/
                            //Inexistência de TR no ramo

                            matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo
                            matrix_struct_pu[j][i].trafo_indices.X_TR_seq_zero = 0.0; //id_k_Trafo == 2, inexistência de trafo no ramo

                            //Existência de LT no ramo
                            //matrix_struct_pu[j][i].LT_indices.Xeq_LT_seq_zero = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero; //recebe o espelho
                        }
                }

                /***
                if(id_k_Trafo == 0 || id_k_LT == 0){

                    matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos = 0.0; //id_k_LT == 0, inexistência de SEP no ramo
                    matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg = 0.0; //id_k_LT == 0, inexistência de SEP no ramo
                    matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero = 0.0; //id_k_LT == 0, inexistência de SEP no ramo

                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos = 0.0; //id_k_Trafo == 0, inexistência de SEP no ramo
                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg = 0.0; //id_k_Trafo == 0, inexistência de SEP no ramo
                    matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero = 0.0; //id_k_Trafo == 0, inexistência de SEP no ramo
                }
                ***/
        } //fim do laço j
    } //fim do laço i

}








/*****************************************(                \IMPEDANCIA \TOTAL \SOPREPOSICAO                   )********************************************

***/





void Calc_Matrix_Z_positiva_pu(Ihandle* disparo_load_full) //Aqui entra todo mundo gerador, motor, LT e Trafo - SOBREPOSIÇÃO
{
    float buffer=0;

    float buffer_xg = 0;
    float buffer_xm = 0;

    float buffer_xtr = 0;
    float buffer_xlt = 0;

    for(int i = 1; i < size_SEP_bars_OLD+1; i++){ //cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD

        matrix_impedancia_positiva_pu[i][i] = 0; //limpeza da diagonal
        //sobreposição
        buffer_xg = matrix_struct_pu[i][i].gerador_indices.Xg_seq_pos;
        buffer_xm = matrix_struct_pu[i][i].motor_indices.Xm_seq_pos;

        buffer = buffer_xg + buffer_xm;

        if(buffer != 0){
            matrix_impedancia_positiva_pu[i][i] = buffer;
        }
        if(buffer == 0){
            matrix_impedancia_positiva_pu[i][i] = 0.0; //evitar zero negativo
        }

        //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO DIAGONAL", i, i, buffer);
    }

    //FORA DA DIAGONAL
    for(int i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD
        for(int j=1; j < size_SEP_bars_OLD+1; j++){
            if(i != j){

                matrix_impedancia_positiva_pu[i][j] = 0; //limpeza
                //sobreposição
                buffer_xtr = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_pos;
                buffer_xlt = matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_pos;
                buffer = buffer_xtr + buffer_xlt; //sobreposição

                if(buffer != 0){
                    matrix_impedancia_positiva_pu[i][j] = buffer; //como já existe o simétrico, j:i, não é requisitado nova linha
                }
                if(buffer == 0){
                    matrix_impedancia_positiva_pu[i][j] = 0.0;
                }

                //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO", i, j, buffer);
            }
        }
    }

}







void Calc_Matrix_Z_negativa_pu(Ihandle* disparo_load_full) //Aqui entra todo mundo gerador, motor, LT e Trafo - SOBREPOSIÇÃO
{
    float buffer=0;
    for(int i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD

        matrix_impedancia_negativa_pu[i][i] = 0;
        buffer = matrix_struct_pu[i][i].gerador_indices.Xg_seq_neg + matrix_struct_pu[i][i].motor_indices.Xm_seq_neg;
        matrix_impedancia_negativa_pu[i][i] = buffer;

        //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO DIAGONAL", i, i, buffer);
    }

    for(int i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD
        for(int j=1; j < size_SEP_bars_OLD+1; j++){
            if(i != j){

                matrix_impedancia_negativa_pu[i][j] = 0;
                buffer = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_neg + matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_neg;
                matrix_impedancia_negativa_pu[i][j] = buffer;

                //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO", i, j, buffer);
            }
        }
    }

}






void Calc_Matrix_Z_zero_pu(Ihandle* disparo_load_full) //Aqui entra todo mundo gerador, motor, LT e Trafo - SOBREPOSIÇÃO
{

    /*** \REFERENCIA \DE \SUPORTE \EH \Yat : \Yat ***/

    //é diferente da sequência positiva por conter reatâncias de sequência zero


    float buffer=0, buffer_xg=0, buffer_xm=0;
    for(int i = 1; i < size_SEP_bars+1; i++){ //ELEMENTOS DA DIAGONAL //Size bars expandido

        matrix_impedancia_zero_pu[i][i] = 0;
        buffer_xg = matrix_struct_pu[i][i].gerador_indices.Xg_seq_zero;
        buffer_xm = matrix_struct_pu[i][i].motor_indices.Xm_seq_zero;

        buffer = buffer_xg + buffer_xm;



        if(buffer != 0){
            matrix_impedancia_zero_pu[i][i] = buffer;
        }
        if(buffer == 0){
            matrix_impedancia_zero_pu[i][i] = 0.0;
        }

        //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO DIAGONAL", i, i, buffer);
    }

    for(int i = 1; i < size_SEP_bars+1; i++){ //ELEMENTOS FORA DA DIAGONAL //Size bars expandido
        for(int j=1; j < size_SEP_bars+1; j++){
            if(i != j){

                matrix_impedancia_zero_pu[i][j] = 0;
                buffer = matrix_struct_pu[i][j].trafo_indices.X_TR_seq_zero + matrix_struct_pu[i][j].LT_indices.Xeq_LT_seq_zero; //sobreposição de impedâncias
                matrix_impedancia_zero_pu[i][j] = buffer;

                //IupMessagef("Aviso!", "A impedância pu de %d:%d é igual a %.5f - SOBREPOSIÇÃO", i, j, buffer);

            }
        }
    }

}









/*****************************************(                      \ADMITANCIA \TOTAL                   )********************************************

***/





/*****************************************(                      \Y \BARRA \POSITIVA                  )********************************************

***/
void Calc_Matrix_Y_positiva_pu(Ihandle* disparo_load_full)
{

    if(depurar_admitancia==1){
    //IupMessage("Aviso!", "CÁLCULO DA ADMITÂNCIA TOTAL!");
    }

    if(depurar_admitancia==1){
    //IupMessage("Aviso!", "INICIAR CÁLCULO Y_positiva_pu");
    }

    float buffer=0, admitancia_buffer=0;
    int first = 0, i, j;


    for(i = 1; i < size_SEP_bars_OLD+1; i++){ //cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD

        //Note que o foco da somatória de linha de Zpu só vale para Yii
        matrix_admitancia_positiva_pu[i][i] = 0; //limpar ...SOMENTE UMA VEZ


        for(j=1; j < size_SEP_bars_OLD+1; j++){ //cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD

            /*** \LIMITACAO \ii \VIA \COORDENADAS ***/

            //Neste caso, captura tbm Z_pu i:i
            buffer = matrix_impedancia_positiva_pu[i][j]; //Note que não é só o gerador, mas todas as máquinas!

            if(buffer != 0){
                admitancia_buffer = -1*(1/buffer); //j complexo invertido
            }
            if(buffer == 0){
                admitancia_buffer = 0.0;
            }

            matrix_admitancia_positiva_pu[i][i] = matrix_admitancia_positiva_pu[i][i]+admitancia_buffer;
            if(depurar_admitancia==1){
            //IupMessagef("Aviso!", "A admitância de sequência positiva buffer incrementada de %d:%d é %.5f", i, j, matrix_admitancia_positiva_pu[i][i]);
            }

        }
        if(depurar_admitancia==1){
        //IupMessagef("Aviso!", "A admitância total de sequência positiva de %d:%d é %.5f", i, i, matrix_admitancia_positiva_pu[i][i]);
        }
    }


    for(int i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD
        for(int j=1; j < size_SEP_bars_OLD+1; j++){ //cuidado, Seq.Positiva é ordem menor, usar size_SEP_bars_OLD
            if(i != j){ //Note, nem estava me dando conta, mas para admitância os elementos da diagonal ii não entram

                buffer = matrix_impedancia_positiva_pu[i][j]; //cenário não existe i:i

                if(buffer != 0){
                    admitancia_buffer = -1*(1/buffer); //j complexo invertido
                    admitancia_buffer = -1*(admitancia_buffer); //depois inverte o y minúsculo, caso fora da diagonal!
                }
                if(buffer == 0){
                    admitancia_buffer = 0.0;
                }

                matrix_admitancia_positiva_pu[i][j] = 0;
                matrix_admitancia_positiva_pu[i][j] = admitancia_buffer; //aqui não é um somatório, apenas uma admitância buffer negativada
            }

        }
    }

}




/*****************************************(                      \Y \BARRA \NEGATIVA                  )********************************************

***/
void Calc_Matrix_Y_negativa_pu(Ihandle* disparo_load_full)
{
    if(depurar_admitancia==1){
    //IupMessage("Aviso!", "INICIAR CÁLCULO Y_negativa_pu");
    }

    float buffer=0, admitancia_buffer=0;
    int first = 0, i, j;

    for(i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD

        //Note que o foco da somatória de linha de Zpu só vale para Yii
        matrix_admitancia_negativa_pu[i][i] = 0; //limpar ...SOMENTE UMA VEZ

        for(j=1; j < size_SEP_bars_OLD+1; j++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD

            /*** \LIMITACAO \ii \VIA \COORDENADAS ***/

            buffer = matrix_impedancia_negativa_pu[i][j]; //Note que não é só o gerador, mas todas as máquinas!

            if(buffer != 0){
                admitancia_buffer = -1*(1/buffer); //j complexo invertido
            }
            if(buffer == 0){
                admitancia_buffer = 0.0;
            }

            matrix_admitancia_negativa_pu[i][i] = matrix_admitancia_negativa_pu[i][i] + admitancia_buffer;
            //IupMessagef("Aviso!", "O valor incrementado após %d de matrix_admitancia_negativa_pu[%d][%d] é %.5f", j, i, i, matrix_admitancia_negativa_pu[i][i]);


        }
        if(depurar_admitancia==1){
        //IupMessagef("Aviso!", "A admitância total de sequência negativa de %d:%d é %.5f", i, i, matrix_admitancia_negativa_pu[i][i]);
        }
    }


    for(i = 1; i < size_SEP_bars_OLD+1; i++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD
        for(j=1; j < size_SEP_bars_OLD+1; j++){//cuidado, Seq.Negativa é ordem menor, usar size_SEP_bars_OLD
            if(i != j){ //Note, nem estava me dando conta, mas para admitância os elementos da diagonal ii não entram

                buffer = matrix_impedancia_negativa_pu[i][j]; //cenário não existe i:i

                if(buffer != 0){
                    admitancia_buffer = -1*(1/buffer); //j complexo invertido
                    admitancia_buffer = -1*(admitancia_buffer); //depois inverte o y minúsculo!
                }

                if(buffer == 0){
                    admitancia_buffer = 0.0;
                }

                matrix_admitancia_negativa_pu[i][j] = 0;
                matrix_admitancia_negativa_pu[i][j] = admitancia_buffer; //aqui não é um somatório, apenas uma admitância buffer negativada
            }

        }
    }

}





/*****************************************(                        \Y \BARRA \ZERO                   )********************************************

***/


/*****************************************(                           \ILHAMENTO                     )********************************************

As funções que se seguem se conversam para resolver o problema de ilhamento

    1) function_struct_buffer_ligacao   --->   Analisa as ligações de trafos e indiretamente de máquinas e LTs
    2) detector_dupla_passagem   --->  Marcador de SEP anel para que não haja loop infinito na análise de barras
    3) function_ilhamento  --->     análise recursiva profunda para verificar se uma barra está ou não ilhada, bem como se há ramais ilhados
    4) Calc_Matrix_Y_zero_pu  --->  é o disparo de ilhamento, ao mesmo tempo que constrói Y-Barra zero

***/






/*****************************************(                       \ILHAMENTO > \LIGACAO                   )********************************************

    1) function_struct_buffer_ligacao   --->   Analisa as ligações de trafos e indiretamente de máquinas e LTs

***/
struct struct_buffer_ligacao function_struct_buffer_ligacao (int i, int j)
{
        //OS BUFFERS DAQUI SÃO PARA PREENCHIMENTO DE Y_zero

        float buffer1, buffer2;
        int buffer_ligacao_esquema, buffer_ligacao_nucleo; //Na struct é tipo int
        struct struct_buffer_ligacao envio_massivo;

                buffer_ligacao_esquema = matrix_struct[i][j].trafo_indices.ligacao_esquema; //ADVÉM DO trafo_10
                buffer_ligacao_nucleo = matrix_struct[i][j].trafo_indices.ligacao_nucleo; //ADVÉM DO trafo_10

                //Se ele receber zero deve pegar o simétrico

                //Agora que dei fé, presumi fortemente que 5:5 ou i:i entra aqui e sai com buffer_ligacao_esquema = 0

                if(buffer_ligacao_esquema == 0){

                    /*** \REBOTE ***/
                    buffer_ligacao_esquema = matrix_struct[j][i].trafo_indices.ligacao_esquema;
                    buffer_ligacao_nucleo = matrix_struct[j][i].trafo_indices.ligacao_nucleo; //ADVÉM DO trafo_10

                    if(buffer_ligacao_esquema == 0){ //inexistência de trafo confirmada
                        //Não existe trafo
                        //LT entre i e j, o buffer1 da barra i:i recebe i_fixo:j_variavel
                        buffer1 = matrix_impedancia_zero_pu[i][j]; //Referência LT, a barra i:i recebe NORMALMENTE i:j, i fixo e j variável
                        buffer2 = 0.0; //quando o i fixar em 2 ao invés de 1 se somará todos j para i =2, enquanto isso 2:1 recebe zero, j =1 !!! rebote!
                    } //análise preliminar a sobreposição é viável 1:4 carrega, 4:1 recebe zero, depois 4:1 carrega e 1:4 recebe zero

                }

                if(depurar_ilhamento==0){
                //IupMessagef("Aviso!", "A LIGAÇÃO ESQUEMA DE %d---%d É %d", i, j, buffer_ligacao_esquema);
                }

                //matrix_impedancia_positiva_pu é baseado na sobreposição de TR e LT

                //estando analisando ii, exemplo 1:1, se ligacao_esquema != 0 então existe trafo, sendo uma ligação 02 então
                //calcula-se a admitancia_buffer e incrementa-se à barra ii
                //como não foi carregado ligacao_esquema no trafo simétrico é necessário se antecipar ao caso

                /*** \CENARIOS
                    \>>> inexistência de ramo no lado delta
                    \>>> inexistência de ramo sem lançamento
                    \>>> inexistência de TR, mas existência de LT
                    \>>> inexistência de LT, mas existência de TR para Yat:Yat

                ***/

        //A diferenciação de núcleo só precisa ser feita para as três primeiras ligações
        if(buffer_ligacao_nucleo == 1) { //NÚCLEO ENVOLVENTE

                if(buffer_ligacao_esquema == 1){ //Yat:Yat //só  entra uma vez, é um condicional! ... Yat:Yat

                    //ligação normal sem circuito aberto, o buffer1 da barra i:i recebe i_fixo:j_variavel
                    buffer1 = matrix_impedancia_zero_pu[i][j]; //Referência Y_at:Y_at, a barra i:i recebe NORMALMENTE i:j, i fixo e j variável
                    buffer2 = 0.0; //quando o i fixar em 2 ao invés de 1 se somará todos j para i =2, enquanto isso 2:1 recebe zero, j =1 !!! rebote!

                }


                /*************************** \MEU \FOCO É ESTE DAQUI DELTA E Y ****************************************************************/

                //Se 1:2 verificando-se 2:1 neste cenário Y_11 não pode receber buffer1, pois está em delta em 1:1

                if(buffer_ligacao_esquema == 2){ //Yat:D ...agora ficou evidente se 1:2, então 2:1 com i = 2 não pode receber 2:1
                                                 //O for 2:1 vai dá ligação zero, então é carregado j:i (1:2) com ligação 2

                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){         //É então testado 2:1 nulo, assim nem Y22 e nem Y11 recebe nada
                        buffer1 = 0; //no caso fica aberto e Y_11 não recebe nada       //Tenha em mente que em 1:2, Y11 recebe algo!
                        buffer2 = matrix_impedancia_zero_pu[i][j];
                    }
                    else{ //vem direto 1:2 com ligação Yat:D, o buffer1 carrega a impedância do trafo à barra i = 1
                        buffer1 = matrix_impedancia_zero_pu[i][j]; //lado Yat recebe, admitancia[i][i] = admitancia[i][i] + buffer[i][j]
                        buffer2 = 0.0; //Circuito aberto no lado delta
                        if(depurar_ilhamento==1){
                            //IupMessagef("Aviso!", "Na ligação 2 para %d:%d o buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                        }
                    }


                    //AGORA SIM PARA ESTE TIPO DE LIGAÇÃO, NÚMERO 2, PODE INICIAR A ROTINA PARA PROCURAR SABER SE A BARRA ESTÁ ILHADA

                    //DÁ PARA FAZER POR FORA


                }


                if(buffer_ligacao_esquema == 3){ //D:Yat


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = matrix_impedancia_zero_pu[i][j]; //Quer dizer que o ramo que tem a ligação 3 é destinado ao simétrico que não foi lançado trafo, este recebe a impedância!
                        buffer2 = 0;
                    }
                    else{ //Yat:D
                        buffer1 = 0.0;
                        buffer2 = matrix_impedancia_zero_pu[i][j];
                    }

                }
        }
        /*************************************************** NÚCLEO 1 ********************************************/


                if(buffer_ligacao_esquema == 4){ //Y:D


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;//Circuito aberto no lado Y/D
                        buffer2 = 0;
                    }
                    else{
                        buffer1 = 0.0; //Circuito aberto no lado Y/D
                        buffer2 = 0.0;
                    }

                }


                if(buffer_ligacao_esquema == 5){ //D:Y


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;//Circuito aberto no lado Y/D
                        buffer2 = 0;
                    }
                    else{
                        buffer1 = 0.0; //Circuito aberto no lado Y/D
                        buffer2 = 0.0;
                    }

                }

                /*** SEMPRE VAI VIM UMA LIGAÇÃO INDEPENDENTE DO LADO (POR CAUSA DO EFEITO REBOTE ***/
                if(buffer_ligacao_esquema == 6){ //Yat:Y


                    //Do system4B se fosse o contrário 4:2 não foi lançado trafo, então dá zero no buffer1...o lado aberto pode ser bivalente (tbm para 2:4), então é necessário o else
                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0; //Circuito aberto no lado Y e Y-at
                        buffer2 = 0;
                    }
                    else{ //No system4B TR 2:4 é Yat-Y   ou outro cenário com 2:4 com Y-Yat                   //OLD>>>//vem direto 1:2 com ligação Yat:D
                        buffer1 = 0.0; // ESTA LIGAÇÃO A IMPEDÂNCIA NÃO RECAI A NENHUMA BARRA! matrix_impedancia_zero_pu[i][j]; //lado Yat
                        buffer2 = 0.0;
                    }

                }

                if(buffer_ligacao_esquema == 7){ //Y:Yat


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;//Circuito aberto no lado Y e Y-at
                        buffer2 = 0;
                    }
                    else{
                        buffer1 = 0.0; //Circuito aberto no lado Y e Y-at
                        buffer2 = 0.0;
                    }

                }

                if(buffer_ligacao_esquema == 8){ //D:D


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;//Circuito aberto no lado D
                        buffer2 = 0;
                    }
                    else{
                        buffer1 = 0.0; //Circuito aberto no lado D
                        buffer2 = 0.0;
                    }

                }

                if(buffer_ligacao_esquema == 9){ //Y:Y


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;//Circuito aberto no lado Y
                        buffer2 = 0;
                    }
                    else{
                        buffer1 = 0.0; //Circuito aberto no lado Y
                        buffer2 = 0.0;
                    }

                }



        if(buffer_ligacao_nucleo == 2){ //NÚCLEO ENVOLVIDO

                if(buffer_ligacao_esquema == 1){ //Yat:Yat - //NÚCLEO ENVOLVIDO

                    buffer1 = 0.0; //matrix_impedancia_zero_pu[i][j]; <<<<<<<<<<<< //NO CASO AQUI PRECISO CONSIDERAR TRAFOS ENVOLVENTES! AQUELES CONVERTIDOS.
                    buffer2 = 0.0;

                } //Ligação sem efeito, já que o envolvido Yat:Yat foi modelado como dois trafos e um gerador Yat

                if(buffer_ligacao_esquema == 2){ //Yat:Y - //NÚCLEO ENVOLVIDO

                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = 0;
                        buffer2 = matrix_impedancia_zero_pu[i][j]; //Neste caso a exibição de lançamento é como se fosse normal
                    }
                    else{
                        buffer1 = matrix_impedancia_zero_pu[i][j];
                        buffer2 = 0.0;
                        if(depurar_ilhamento==1){
                            //IupMessagef("Aviso!", "Na ligação 2 para %d:%d o buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                        }
                    }
                }


                if(buffer_ligacao_esquema == 3){ //Yat:D - //NÚCLEO ENVOLVIDO


                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                        buffer1 = matrix_impedancia_zero_pu[i][j];
                        buffer2 = 0;
                    }
                    else{ //Yat:D
                        buffer1 = 0.0;
                        buffer2 = matrix_impedancia_zero_pu[i][j];
                    }

                }
        }
        /*************************************************** NÚCLEO 2 ********************************************/



                envio_massivo.buffer1 = buffer1;
                envio_massivo.buffer2 = buffer2;

                if(depurar_ilhamento==1){
                    //IupMessagef("Aviso!", "O envio massivo de %d:%d é buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                }


                return envio_massivo;



}



/*****************************************(                       \ILHAMENTO > \SEP \ANEL                   )********************************************

    2) detector_dupla_passagem   --->  Marcador de SEP anel para que não haja loop infinito na análise de barras

***/
int detector_dupla_passagem(int k, int i, int reset) //esta função é uma obra de arte! Marcador de SEP anel
{
    static int inicializacao = 0; //isso so vai acontecer uma vez no código, quando for testado ilhamento bom buffer1 não nulo
    int ddp = 0;
    int p, q;

    if(reset == 1){
        //IupMessagef("Aviso!", "Reinicializando a função ddp");
        inicializacao = 0;
    }

    if(reset == 0){
        if(depurar_ilhamento==0){
           //IupMessagef("Aviso!", "DETECÇÃO DE DUPLA PASSAGEM de k:i - %d:%d", k, i);
        }
    }
    if(depurar_ilhamento==0){
       //IupMessagef("Aviso!", "O valor de inicialização é %d", inicializacao);
    }

    if(reset == 0){
            if(inicializacao != 0){ //É meio zuado mas é isso mesmo, a primeira vez que armazena k:i fica retido o conteúdo ki
                            //Na terceira vez que entra (segunda vez que armazena) se k:i for diferente da primeira vez que armazenou
                            //então a ddp continuará zero, exemplo, na primeira 2:1 e na segunda 5:2, conteúdos diferentes 21 != 52
                            //Quando acontecer de repetir vai ficar 2:1 e 2:1 e então 21 == 21 e vai dá ilhado, ou seja, ddp = 1
                            //Enquanto for acionado e for empilhando o array_passagem sempre será detectado pela primeira vez, pq é nulo
                            //Exemplo o 1:3 vai disparar 3:1 e então teremos 31 no lugar de zero, quando repetir 3:1 vai dá ilhado, ddp = 1
                if((k<10 && i<10) || (k>10 && i<10)){
                    array_passagem_ki[k][i] = 10*k+i;
                }
                if((k<10 && i>10) || (k>10 && i>10)){
                    array_passagem_ki[k][i] = 100*k+i;
                }
            }

            if(depurar_ilhamento==0){
               //IupMessagef("Aviso!", "O valor de array_passagem_ki[%d][%d] é %d", k, i, array_passagem_ki[k][i]); //Se o reset for diferente de 1 a inicialização é zero e então é resetado tudo!
               //IupMessagef("Aviso!", "O valor de array_passagem_pq[%d][%d] é %d", k, i, array_passagem_pq[k][i]);
            }

    }

    for(p = 1; p < size_SEP_bars+1; p++){
        for(q = 1; q < size_SEP_bars+1; q++){
            if(inicializacao == 0){ //depois de implementar o reset ficou redundante, enfim mete marcha
                array_passagem_pq[p][q] = 0; //inicializa o array pq
                array_passagem_ki[p][q] = 0; //inicializa o array ki
            }
            if(inicializacao == 1 && p == k && q == i && reset == 0){ //ainda tem que pular, quando é armazenado a primeira vez (após inicilização)
                inicializacao++;

                //faltava esse if, exclusivamente este, pq o 2:1 precisa realizar o carregamento primário, a inicialização > 1
                //e array_pq = 0 é quase de exclusivamente para os outros pares futuros que terão o carregamento primário
                //Na real nem precisava do if de comparação abaixo - vou deixar somente para assimilação, repetição de padrão.

                if(array_passagem_pq[p][q] != array_passagem_ki[k][i]){
                    array_passagem_pq[p][q] = array_passagem_ki[k][i]; //carregamento primário (primeira vez) - segunda entrada
                    if(depurar_ilhamento==0){
                       //IupMessagef("Aviso!", "CARREGAMENTO PRIMÁRIO-1: O valor de array_passagem_ki[%d][%d] é %d", k, i, array_passagem_ki[k][i]);
                       //IupMessagef("Aviso!", "CARREGAMENTO PRIMÁRIO-1: O valor de array_passagem_pq[%d][%d] é %d", p, q, array_passagem_pq[p][q]);
                    }

                    return ddp; //no carregamento primário retorna zero!
                }

            }
            if(inicializacao >1 && p == k && q == i && reset == 0){

                if(array_passagem_pq[p][q] == array_passagem_ki[k][i]){ //se for a primeira vez não vão ser iguais! 5:2 = 0 vs 5:2 = 52
                    //Se numa segunda vez o array_pq estiver igual ao array_ki, então o ramo está ilhado!
                    return ddp = 1;
                }
                if(array_passagem_pq[p][q] != array_passagem_ki[k][i]){
                    array_passagem_pq[p][q] = array_passagem_ki[k][i]; //carregamento primário (primeira vez) - segunda entrada
                    if(depurar_ilhamento==0){
                       //IupMessagef("Aviso!", "CARREGAMENTO PRIMÁRIO-2: O valor de array_passagem_ki[%d][%d] é %d", k, i, array_passagem_ki[k][i]);
                       //IupMessagef("Aviso!", "CARREGAMENTO PRIMÁRIO-2: O valor de array_passagem_pq[%d][%d] é %d", p, q, array_passagem_pq[p][q]);
                    }

                    return ddp;
                }
            }
        }
    }

    if(inicializacao == 0 && reset == 0){
        inicializacao++; //agora fui magaiver, além de já garantir o marcador diferente de zero já consigo modificar o array inicializado!
        detector_dupla_passagem(k, i, 0);
    }



}




/*****************************************(                       \ILHAMENTO > \FUNCTION \RECURSSIVA              )********************************************

    3) function_ilhamento  --->     análise recursiva profunda para verificar se uma barra está ou não ilhada, bem como se há ramais ilhados

***/
int function_ilhamento(int i, int barra_fixa)
{

    //A barra 4:4 entrou com 4, 0, fixando 0- system7A
    int ilhamento = 2;
    int k;
    struct struct_buffer_ligacao varredura01;
    int buffer_ligacao = 89;
    int ddp = 89;
    int ilhamento_perduravel = 0;
    int buffer_rebote_ligacao = 98;
    int buffer_ligacao_gerador_motor=89;

        /***
                    Na primeira tentativa de i = 1, é carregado ii = 1:1 e ainda por cima carregado buffer1 != 0 , então vai entrar no condicional
                    de jeito nenhum.

                    Na segunda tentativa de i = 2, é carregado ii = 2:2 e recebe zero! E o buffer1 == 0, pois já foi carregado (por assim dizer) a
                    impedância do trafo 1:2 À barra 1. Atendendo duplamente a condicional é acionada para barra 2

                    Explore um outro trafo do mesmo tipo de 2 para 3! E veja se converge a lógica

        ***/
                    //No caso a barra j que poderia estar ilhada, recebe zero em ambos os casos

                    //CUIDADO É TESTADO A ADMITÂNCIA COMO EFEITO REBOTE, se tiver alguma máquina síncrona conectada a barra ficará carregada inicialmente
                    //POR ISSO DEVE FICAR DENTRO DO LAÇO i != j
                    //BUFFER 1 NULO REPRESENTA QUE NUNHUM TRAFO FOI CONECTADO à BARRA i

                    // matrix_admitancia_zero_pu[i][i] == 0 && buffer1 == 0 >>> já está subentendido

                        for(k = 1; k < size_SEP_bars+1; k++){ //VEJA SE ISSO SÓ ATENDE AO Yat:D ou TAMBÉM O CONTRÁRIO

                                if(k != barra_fixa){ //k != i && <<<<<<

                                //No system 4B o 1:1 é testado pq a barra-fixa é zero, e inicialmente é recebido 1 de ilhamento, se nada mudar então está ilhado
                                //Mas o laço não é quebrado (break) para ilhamento = 1, então ainda é possível obter ilhamento = 0.

                                //Para 1:2 existe impedância, então vai ser verificado se esta impedância está ilhada, para buffer1 não nulo!

                                //ETAPA 1 - REUTILIZANDO A FUNÇÃO COM OUTRA FINALIDADE
                                //ROTEIRO MUITO BACANA
                                    /***
                                        Exemplo System 4FOUR com Yat:D em 1:2 e D:Yat em 3:4
                                        Testa-se primeiro se há gerador à terra na barra 2, não há, então ilhamento é sinalizado como 1
                                        Disparado a função ilhamento para varredura de barras no entorno da barra 2
                                        Suposição 1: trafo foi lançado de 1:2 como Yat:D, então é carregado ligação zero para 2:1, depois recarregado
                                                     ligação igual a 2 pois há um trafo entre 1:2, porém como está a analisar 2:1, o buffer1 sai zero
                                        Suposição 2: entre 1:2 há uma LT, então é carregado ligação zero para 2:1, recarregado zero para ligação 1:2
                                                     e então o buffer1 recebe ou uma impedância LT ou...

                                                     ...ou zero na inexistência de ramo.
                                    ***/



                                    if(depurar_ilhamento==0){
                                        //IupMessagef("Aviso!", "VARREDURA DA BARRA %d:%d", i, k);
                                    }

                                    //O 5:5 advindo do 4:5 para o system7A entra aqui e sai com buffer1 cheio
                                    //O 5:5 advindo do 6:5 para o system7A entra aqui e sai com buffer1 cheio

                                    varredura01 = function_struct_buffer_ligacao(i, k); //struct .buffer1 e .buffer2
                                    //para 2:1 vai receber zero, idem buffer 2 de i:k também zero
                                    //varredura02.buffer1 = function_struct_buffer(k, i); //para 1:2 vai receber cheio, mas sob o buffer1

                                    //isso aqui vai ser animal, pq tem regiões ilhadas e não ilhadas se misturando




                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0){ //sinalização de ilhamento

                                            //ilhamento = 2 é lixo

                                            /***
                                            //Enviando recursivamente 2:2 (quem disparou externamente a função foi 2:1)
                                            ilhamento = function_ilhamento(k, i); //Não tendo gerador em 2:2 não quer dizer que a barra está ilhada
                                                                                  //por isso acionar a função ilhamento para verificar
                                            ***/

                                            //Esta função ilhamento é recursiva, mas neste caso em específico ilhamento não vem de lugar nenhum
                                            if(ilhamento == 0 && k == i){ //está a analisar somente barra à terra, barra esta sem gerador ou motor
                                                ilhamento = 0;
                                                if(depurar_ilhamento==0){
                                                //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d", i, k, ilhamento);
                                                }
                                                return ilhamento; //apesar de 2:2 não ter gerador, ele retorna para si mesmo zero a fim de garantir o caminho à terra via 2:1
                                            }
                                            else{              //FOCAAAAAAAAAAAAAA AQUI
                                                ilhamento = 1; //tanto para circuito aberto como para inexistência de ramo
                                                               //assim que achar um ramo o ilhamento é zero (válido)
                                                               //neste caso não entra nos demais ifs de buffer-varredura, então o laço é incrementado
                                                               //com o incremento ainda é possível mudar o status de ilhamento para zero!
                                            }

                                            if(depurar_ilhamento==0){
                                                //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d", i, k, ilhamento);
                                            }
                                        }




                                        /*** \CASO \DOIS \COM \IMPEDANCIA ***/



                                        buffer_ligacao = matrix_struct[i][k].trafo_indices.ligacao_esquema;
                                        buffer_rebote_ligacao = matrix_struct[k][i].trafo_indices.ligacao_esquema;

                                        if(varredura01.buffer1 != 0 && varredura01.buffer2 == 0 && buffer_ligacao == 2){ //sinalização de ilhamento
                                                //cenário de entre barras Yat:D = LIGAÇÃO 2
                                                //ilhamento = 2;
                                                ilhamento = 0; //já liquida, não tem o que ver

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - LIGAÇÃO 2---if", i, k, ilhamento);
                                                }

                                                return ilhamento; //isso serve mais para garantir o elemento à terra, pois o buffer1 só garante a existe do elemento (impedância)
                                        }

                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 != 0 && buffer_rebote_ligacao == 2){

                                                ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 2---if", i, k, ilhamento);
                                                }

                                                ilhamento_perduravel = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 2", ilhamento_perduravel, i, k);
                                                }


                                        }


                                        /*** NOVO - LIGAÇÃO 3 ***/

                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 != 0 && buffer_ligacao == 3){ //sinalização de ilhamento
                                                //cenário de entre barras D:Yat = LIGAÇÃO 3
                                                //ilhamento = 1;
                                                ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 3", i, k, ilhamento);
                                                }

                                                ilhamento_perduravel = 2; //Viabilizando terminar o laço k = 3

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 3", ilhamento_perduravel, i, k);
                                                }

                                                //return ;//o return só pode ocorrer dps que for definitivo de que no laço k = 3 não há outros caminhos
                                                //E isso só é possível quando se encerra o laço, logo o ilhamento_perdurável = 2 envia ilhamento 2

                                        }

                                        if(varredura01.buffer1 != 0 && varredura01.buffer2 == 0 && buffer_rebote_ligacao == 3){ //No caso do trafo 3:1 ligação 3 tem elemento a terra com 1:3

                                                ilhamento = 0;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA REBOTE DA BARRA %d:%d é %d - REBOTE LIGAÇÃO 3", i, k, ilhamento);
                                                }
                                                return ilhamento;


                                        }





                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 4){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                   // IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 4", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 4", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 5){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 5", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 5", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 6){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 6", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 6", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 7){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 7", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 7", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 8){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 8", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 8", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        if(varredura01.buffer1 == 0 && varredura01.buffer2 == 0 && buffer_ligacao == 9){ //sinalização de ilhamento
                                            //cenário de entre barras Y:D = LIGAÇÃO 4
                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 9", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 9", ilhamento_perduravel, i, k);
                                                }
                                        }


                                        /*** \CUIDADO, ao especificar ligacao != tu matou o laço de continuar ao achar as ligações 2 e 6 QUE TEM BUFFER != 0 ***/

                                        if(k == i){

                                            buffer_ligacao_gerador_motor = matrix_struct[i][i].motor_indices.ligacao_esquema;

                                            if(buffer_ligacao_gerador_motor == 0){ //se não for achado nada de motor na barra i:i então verifica se tem ou não pelo menos um gerador
                                                buffer_ligacao_gerador_motor = matrix_struct[i][i].gerador_indices.ligacao_esquema; //Se nunca foi inicializado com um gerador o valor vai ser zero
                                            }
                                            if(depurar_admitancia==0){
                                            //IupMessagef("Aviso!", "LAÇO k - O buffer1 impedancia pu de %d:%d é %.5f e a ligação da máquina síncrona é %d", i, i, varredura01.buffer1 , buffer_ligacao_gerador_motor);
                                            }
                                        }


                                        if(varredura01.buffer1 != 0 && varredura01.buffer2 == 0 && buffer_ligacao !=1  && buffer_ligacao !=2 && buffer_ligacao != 3 && buffer_ligacao_gerador_motor == 1){

                                            ilhamento = 2;

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - COM LIGAÇÃO 1 MOTOR/GERADOR", i, k, ilhamento);
                                                }

                                            ilhamento_perduravel = 2; //Viabilizando terminar o laço k

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento perduravel é %d da VARREDURA DA BARRA %d:%d  - COM LIGAÇÃO 1 MOTOR/GERADOR", ilhamento_perduravel, i, k);
                                                }

                                        }







                                        //O 4:5 entra aqui system7A, abaixo, pois é uma LT entre 4:5 (sem ligação)

                                        //A princípio vai entrar para transformador e LT





                                        //NO CASO AQUI VAI PODER ENTRAR SOMENTE A LIGAÇÃO Y-at:Y-at e motor/gerador com aterramento (lembre-se que tem o sinalizador duplo...então pode entrar sim).
                                        if(varredura01.buffer1 != 0 && varredura01.buffer2 == 0 && buffer_ligacao !=2 && buffer_ligacao != 3 && buffer_ligacao_gerador_motor != 1){ //curioso, assim que receber zero acima não entra mais, é o bastante, poderia até ter um brake

                                                //O FECHAMENTO VEM POR CIMA i:k, 5:5 tem buffer != 0

                                                ilhamento = 0; //é a situação que acha a LT
                                                //SE LIGA O TESTE É SÓ ENTRE A BARRA i e AS BARRAS A SUA VOLTA, EM ATÉ UMA UNIDADE!
                                                //Agora preciso fazer que nem no determinante repetir tudo até esgotar as barras! retornando o valor último
                                                //break;//força a saída imediata do loop, //pode encerrar



                                                //ISSO NÃO GARANTE O ILHAMENTO, CHEGAR O TERRA DO 5:5 TEM NADA A VER COM 3:5
                                                //ACHO QUE GARANTE SIM, É PQ O PARADIGMA ANTIGO TAVA EQUIVOCADO, ENTÃO AGORA SE CHEGA À TERRA VIA GERADOR/MOTOR É BREAK NA VEIA
                                                if(ilhamento == 0 && k == i) //sinalizador duplo , e só ocorre isso se chegar num terra!
                                                {
                                                    if(depurar_ilhamento==0){
                                                        //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SINALIZADOR DUPLO", i, k, ilhamento);
                                                    }
                                                    return ilhamento;
                                                    //break; //Tem o mesmo efeito do return
                                                }

                                                if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SEM LIGAÇÃO CONHECIDA (LT)", i, k, ilhamento);
                                                }

                                                //No caso do System4B envia 1:2 (LT) e teste 2:1 com barra fixa em 2...
                                                //Então num segundo laço da função ilhamento é verificado se 2:2 tem gerador, não tem, então a ilhamento = 1 e a impedância é nula
                                                //Então o laço k continua nesse segundo laço da função ilhamento e é testado 2:3, tem o TR, então ilhamento = 0 e a impedância não é nula
                                                //É então acionado um terceiro laço da função ilhamento para 3:2, com barra fixa em 2, verifica-se que 3:1 não existe ilhamento é 1, e 3:3 não tem gerador então ilhamento é 1, 3:4 não existe ilhamento é 1
                                                //Por enquanto está ilhado a barra 1, segue incremento de k para 4, então 2:4 tem o TR Yat-Y, então ilhamento = 0 e a impedância não é nula
                                                //E neste caso último deve-se encerrar pq não há ilhamento, e é aqui que falha...ligação 6

                                                if(barra_fixa == 0){ //vai servir para inicializar o array pelo menos!
                                                    ddp = detector_dupla_passagem(k,i,0); //System5B entra pelo 1:2 e envia 2:1
                                                }
                                                if(barra_fixa != 0){
                                                    ddp = detector_dupla_passagem (k,i,0); //System5B entra pelo 2:5 e envia 5:2 (Crítico)
                                                }


                                                if(depurar_ilhamento==0){
                                                   //IupMessagef("Aviso!", "SAÍDA BARRA-FIXA: O valor de array_passagem_ki[%d][%d] é %d", k, i, array_passagem_ki[k][i]);
                                                   //IupMessagef("Aviso!", "SAÍDA BARRA-FIXA: O valor de array_passagem_pq[%d][%d] é %d", k, i, array_passagem_pq[k][i]);
                                                }





                                                if(ddp == 1) //System 5B, quando ele detectar o 2:1 por uma nova entrada de 1:2
                                                {
                                                    ilhamento = 2; //ilhamento intermediário que vai se concretizar igual a um somente quando retonar
                                                                   //à barra_fixa = 0
                                                }

                                                if(ddp == 0){ //System5B, após inicializar via 2:1 continua pelo 2:1, inicia um novo laço de k de 2:2 até o 2:5
                                                ilhamento = function_ilhamento(k, i); //EXATO BIXÃO, É NESSE SENTIDO ...cuidado é invertido ... i e k
                                                }

                                                if(ddp == 1 && ilhamento == 2){// <<< old: ddp == 1 && ilhamento == 1
                                                    if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SE ILHMAENTO 3", i, k, ilhamento);
                                                    }
                                                    //return ilhamento; //não pode receber 1, deve receber 2 pq ainda é possível que o laço precise continuar
                                                }

                                                //acho que ele não chega a entrar aqui, lá no esquema de ligação 6 ele já encerra com return ilhamento = 2

                                                if(depurar_ilhamento==0){
                                                //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SE ILHMAENTO 2", i, k, ilhamento);
                                                }

                                                if(ilhamento == 2 && barra_fixa == 0){ //Tem que ser antecipado mesmo, pq senão o laço segue em frente
                                                    if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SE ILHMAENTO 2 REBOTE FINAL", i, k, ilhamento);
                                                    }
                                                    ilhamento_perduravel = 2; //transferi a responsabilidade para o fim do laço k = 1
                                                    //ilhamento = 1; //CUIDADO, quando chega no laço k = 1 com ilhamento 2 é que tá tudo ilhado!
                                                                   //O ilhamento 2 ganhou outra interpretação, mas no fundo equivale um um ilhado = 1 intermediário
                                                                   //SE LIGA barra_fixa igual a zero é no laço k = 1
                                                    //return ilhamento; cuidado não pode ter return aqui, é intuitivo, se laço k = 1 ainda não se encerrou ele não pode dá return
                                                }
                                                if(ilhamento == 2 && barra_fixa != 0){ //Tem que ser antecipado mesmo, pq senão o laço segue em frente
                                                    if(depurar_ilhamento==0){
                                                    //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SE ILHMAENTO 2 REBOTE PARCIAL", i, k, ilhamento);
                                                    }

                                                    ilhamento_perduravel = 2; //para prosseguir o laço k \\system5B é quando tu lança o trafo 3:1 ligação 3, e deve seguir testando 3:2 (já é lá na frente laço k distante)

                                                    //return ilhamento; //Este ilhamento igual a 2 advém das ligações com buffer1 nulo ou não nulo de outro laço k
                                                }

                                                //Todos os ifs dedicados estão com return, exceto este - monitorar
                                                if(ilhamento == 0){
                                                    return ilhamento; //inserido 06jul22
                                                                      //Não entendi, mas está seguindo o 4:6, até parece que estou usando código antigo, pq eu já me bati com isso
                                                    /*** \CRITICO ***/
                                                    /*** se o ilhamento ainda sair igual a 1, igual ao caso de 5:4 (7systemA), precisa manter o k incrementando ***/

                                                }


                                        }


                                    //ETAPA 2 - ABERTURA DE RAMO POR TRAFO -- dá para tornar o acesso a impedância algo genérico para acesso múltiplo
                                                                              //criando uma função só para verificar a ligação do trafo

                                } //Condicional k != i

                                //o ilhamento int só retorna após finalizar o laço da varredura

                        } //FIM laço k



                        //Naquela suposição de haver uma barra 6 no System5B entre 3:6, nem por aqui vai passar, pq vai dá ilhamento = 0 e vai dá return
                        //Caso contrário vai testar 3:2, 3:3 e 3:5 e não vai achar nada, então o ilhamento permanece 2 pq o perdurável se manteve
                        if(ilhamento_perduravel == 2){
                            ilhamento = 2;

                            if(depurar_ilhamento==0){
                                //IupMessagef("Aviso!", "O ilhamento é %d da VARREDURA DA BARRA %d:%d  - FIM LAÇO k", ilhamento, i, k);
                            }

                            if(ilhamento == 2 && barra_fixa == 0){ //Tem que ser antecipado mesmo, pq senão o laço segue em frente
                                if(depurar_ilhamento==0){
                                //IupMessagef("Aviso!", "O ilhamento da VARREDURA DA BARRA %d:%d é %d - SE ILHMAENTO 2 REBOTE FINAL", i, k, ilhamento);
                                }
                                ilhamento = 1;
                            }


                            return ilhamento;
                        }


                    /***
                        //Vai encerrar em cascata 4:4, 3:3, 2:2
                        if(ilhamento == 1){
                           matrix_admitancia_zero_pu[k][k] = 0.00001;
                        } //a barra 4 só estará ilhada dps que se confirmar que 3:5 está ilhada
                    ***/


            return ilhamento; //CUIDADO, NÃO APAGA ISSO NEM FERRANDO, O ilhamento = 1 só é enviado ao encerrar o ciclo de cada laço k - e ele vai cascateando e
                              //transpondo todas as camadas até o k = 1, laço final, se nada for encontrado é enviado ilhamento =1


}





/*****************************************(                       \ILHAMENTO > \FUNCTION \Y \BARRA \ZERO         )********************************************

    4) Calc_Matrix_Y_zero_pu  --->  é o disparo de ilhamento, ao mesmo tempo que constrói Y-Barra zero

***/
void Calc_Matrix_Y_zero_pu(Ihandle* disparo_load_full)
{
    if(depurar_admitancia==0){
        //IupMessage("Aviso!", "INICIAR CÁLCULO Y_zero_pu");
    }


    float buffer = 0, buffer1 = 0, buffer2 = 0, admitancia_buffer1 = 0, admitancia_buffer2 = 0, admitancia_buffer = 0;
    int first = 0, i, j, buffer_ligacao_esquema, ilhamento = 2, ilhamento_start = 2, ilhamento_start_ij = 2, ilhamento_buffer_ij = 2, buffer_ilhado = 0;
    int buffer_ligacao_nucleo;
    struct struct_buffer_ligacao recebimento_massivo;
    int fim_diagonal = 0, buffer_ligacao = -1;

    //matrix_admitancia_zero_pu[1][1] = 0; //CRÍTICO - INICIALIZAÇÃO POR FORA
    //matrix_admitancia_zero_pu[j][j] = 0; //CRÍTICO - INICIALIZAÇÃO POR FORA
    //matrix_admitancia_zero_pu[i][i] = 0;

    /*** \ANTECIPACAO \ACUMULATIVO \TRAFOS ***/

    /*** O ACUMULATIVO É SOMENTE PARA Y_ii ou Y_jj ***/
    /*** ETAPA 1: Yat:Yat, Yat:D, D:Yat ***/

    /*** \Y \MAIUSCULO \DIAGONAL  ***/

    for(i = 1; i < size_SEP_bars+1; i++){

                continua_j[i] = 0;

                if(depurar_admitancia==0){
                    //IupMessagef("Aviso!", "ELEMENTO %d:%d DA DIAGONAL PRINCIPAL CARREGADO", i, i);
                }


                //Não existe uma função de inicialização com zeros de ligação esquema dos trafos, e tem sido usado tranquilamente
                //a inicialização da função struct ligação com lixo igual a zero, mas é bom monitorar isso.


                /*** SÓ IMPORTA GERADOR/MOTOR NESTE INÍCIO - BUFFER_LIGACAO ***/
                buffer_ligacao = matrix_struct[i][i].motor_indices.ligacao_esquema; //Se nunca foi inicializado com um motor o valor vai ser zero

                if(depurar_admitancia==0){
                //IupMessagef("Aviso!", "MOTOR - O buffer1 impedancia pu de %d:%d é %.5f e a ligação da máquina síncrona é %d", i, i, buffer1, buffer_ligacao);
                }

                if(buffer_ligacao == 0){ //se não for achado nada de motor na barra i:i então verifica se tem ou não pelo menos um gerador
                    buffer_ligacao = matrix_struct[i][i].gerador_indices.ligacao_esquema; //Se nunca foi inicializado com um gerador o valor vai ser zero
                }




/*** \Y \MAIUSCULO \DIAGONAL ***/


                /*** SOMENTE NA SEQUÊNCIA ZERO, NA SEQUÊNCIA POSITIVA NÃO EXISTE ISSO ***/
                if(buffer_ligacao == 2 || buffer_ligacao == 3){ //É O QUE JÁ VINHA SENDO FEITO, carrega normalmente a impedância de sequência zero
                                                                //A função X_seq_zero já é capaz sozinha de calcular a impedância de peterson
                    buffer1 = matrix_impedancia_zero_pu[i][i]; //máquina síncrona conectada à barra, lembre-se somente o TR que é igual a Seq positiva
                } //o início do laço da admitância só importa se tem gerador/motor para saber se a barra está ilhada

                if(buffer_ligacao == 0 || buffer_ligacao == 1){ //pedacinho foi fatal, arrematou tudo = || buffer_ligacao == 1
                    buffer1 = 0.0;//vai ficar ilhada
                                  //Evidentemente a ligação 1 não tem Xpet e se tivesse nada ia adiantar!
                }//o início do laço da admitância só importa se tem gerador/motor para saber se a barra está ilhada

/*** \Y \MAIUSCULO \DIAGONAL ***/



                if(depurar_admitancia==0){
                //IupMessagef("Aviso!", "MONITORAR --- O buffer1 impedância pu de %d:%d é %.5f e a ligação da máquina síncrona é %d", i, i, buffer1, buffer_ligacao);
                }

                //buffer1 dá zero se nada estiver sido lançado

                //SE LIGA SE JÁ FOR DETECTADO ALGUMA IMPEDÂNCIA DE MÁQUINA JÁ PULA FORA DO LAÇO À FRENTE, POIS Yii VAI EXISTIR DE FATO

                if(buffer1 != 0){
                    ilhamento  = 0; //CORTA PELA RAIZ, JÁ TEM ELEMENTO À TERRA
                    matrix_admitancia_zero_pu[i][i] = 0; //inicialização da variável local - monitorar, pois não havia feito, o lixo tava saindo zero
                }
                if(buffer1 == 0){ //caso da barra 2:2 ...o caso da barra 4:4 vem por aqui primeiro 7System
                    ilhamento  = 1; //barra sem gerador
                    matrix_admitancia_zero_pu[i][i] = 0.00001;
                }
                //NOVIDADE
                if(buffer1 == 0 && buffer_ligacao == 1){ //caso da barra 2:2 ...o caso da barra 4:4 vem por aqui primeiro 7System
                    ilhamento  = 1; //barra sem gerador
                    matrix_admitancia_zero_pu[i][i] = 0.0; //TEMPORÁRIO, se for confirmado ilhamento então recebe 0.00001
                }

                if(buffer1 == 0.00001){ //<<<<<<<< ISSO AQUI ESTÁ INATIVO, era para ser acima, mas tava equivocado - aguarde, monitore e delete.
                    if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "O LAÇO VAI SE ENCERRAR EM %d:%d", i, i);
                    }
                    //matrix_admitancia_zero_pu[i][i] = 0.00001;
                    ilhamento  = 1;
                    break; //Não tem o que fazer Y33 = y33 + y31 + y32 + y34, pois a barra já está ilhada
                }


                /**************************************************** \INCREMENTO ****************************************************/


                //Nem sempre buffer1 é igual a buffer2, um pode ser nulo e outro não!
                if(buffer1 != 0){
                    admitancia_buffer1 = -1*(1/buffer1); //j complexo invertido
                    if(depurar_admitancia==0){
                    //IupMessagef("Aviso!", "A admitancia do buffer1 de %d:%d é %.5f", i, i, admitancia_buffer1);
                    }
                }

                if(buffer1 == 0){
                    admitancia_buffer1 = 0.0; //Se for lançado um gerador/motor Y sem aterramento ou não haver nada na barra então incialmente o incrmento é nulo, inicializando a variável admitância
                }

                //Note que o foco da somatória de linha de Zpu só vale para Yii

                /*** \SOMENTE \PARA \DIAGONAL ***/

                if(ilhamento == 0){

                    if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "Sem ilhamento - DIAGONAL, para %d:%d, o buffer1 = %.5f", i, i, buffer1);
                    }

                    //A inicialização da matrix de admitãncia vai realizada globalmente para múltiplo acessos

                    matrix_admitancia_zero_pu[i][i] = matrix_admitancia_zero_pu[i][i] + admitancia_buffer1; //aqui não é um somatório, apenas uma admitância buffer negativada

                    if(depurar_admitancia==0){
                    //IupMessagef("Aviso!", "O valor de matrix_admitancia_zero_pu é %.5f", matrix_admitancia_zero_pu[i][i]);
                    }

                }


                if(ilhamento == 1){ //MUDANÇA DE OBJETIVO, O FOCO AQUI É SÓ SABER SE EXISTE AO MENOS UM CAMINHO À TERRA

                        //sondagem
                        if(depurar_admitancia==1){
                            //IupMessagef("Aviso!", "COM ilhamento, para %d:%d, o buffer1 = %.5f", i, i, buffer1);
                        }

                        matrix_admitancia_zero_pu[i][i] = matrix_admitancia_zero_pu[i][i] + admitancia_buffer1;//ainda recebe zero, pois não tem gerador à barra

                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "A BARRA %d:%d DEVE ENTRAR AQUI PARA OBTER UM ilhamento_start à terra", i, i);
                        }

                        detector_dupla_passagem(i,i,1); //Só serve para apagar a memoria da última barra na varredura, reset a função ddp



                        /*** \DISPARA \FUNCTION \ILHAMENTO - que por sua vez carrega buffer1 indiretamente ***/




                        ilhamento_start = function_ilhamento(i, 0); //coloquei zero só para inicializar





                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "O ILHAMENTO STAR - DIAGONAL, para %d:%d é %d", i, i, ilhamento_start);
                        }

                        //Se depois da barra 2:2 for detectado caminho à terra o ilhamento_start é zero!!! E assim deve-se prosseguir ao somatório
                        //das impedâncias de Yat:Y

                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "O ilhamento_start da barra %d:%d é %d", i, i, ilhamento_start);
                        }


                        /*** PARECE QUE ESTÁ INDO DIRETO LÁ POR CIMA, FAZENDO ilhamento_start = 0 antes, por via das dúvida deixar abaixo ilhamento = 2 ***/

                        //CUIDADO AINDA PODE SAIR ILHAMENTO = 2 - System 4J, barra 2:2 tem ilhamento_perduravel x2 e estorna ilhamento 2
                        //transferi a responsabilidade para o fim do laço k = 1, por via das dúvida deixar em redundância:
                        if(ilhamento_start == 2){
                            ilhamento_start = 1; //O ilhamento = 2 é um ilhamento intermediário
                        }


                        if(ilhamento_start == 0){
                            matrix_admitancia_zero_pu[i][i] = 0.0; //deixa de ser matrix_admitancia_zero_pu[i][i] = 0.00001;
                        }


                        if(ilhamento_start == 1){ // || ilhamento_start == 2

                            //O FOCO É A DIAGONAL
                            matrix_admitancia_zero_pu[i][i] = 0.00001;
                            continua_j[i] = 1;

                            if(depurar_admitancia==0){
                            //IupMessagef("Aviso!", "ILHAMENTO STAR = 1 - DIAGONAL, o valor de continua_j para %d:%d é %d", i, i, continua_j[i]);
                            }

                           /*** \BREAK \SUSPENSO - a responsabilidade de saber se está ilhado e carregar 0.00001 é de cada barra agora
                                                   note que estando ilhamento_start = 1 não haverá incremento ao elemento da diagonal!
                           ***/
                            //break; //ASSIM TU  CARREGA 2:2, 3:3, e 4:4 com um único valor de 10^-6


                            //acredito que não pode ter um break agora senão tu não testa 5:5

                            //SÓ MONITORA O QUE OCORRE COM 5:5, mas não faz absolutamente nenhum sentido incrementar algo ilhado
                        }

                        //se o ilhamento for zero só vai finalizar com  matrix_admitancia_zero_pu[i][i] = 0

                        //SÓ SE CONFIRMA SE DEFINITIVAMENTE ESTIVER ILHADO!

                } //fim-if - ilhamento = 1



        if(depurar_admitancia==0){
            //IupMessagef("Aviso!", "REPETE - ILHAMENTO STAR = 1 - DIAGONAL, o valor de continua_j para %d:%d é %d", i, i, continua_j[i]);
        }

         /*** \Y \MAIUSCULO \DIAGONAL   - \continua \INCREMENTOS \DE \Y ***/
        //SE LIGA, O j NEM É IMPORTANTE (FORA DA DIAGONAL), O QUE IMPORTA É A DIAGONAL ii




        for(j = 1; j < size_SEP_bars+1; j++){

            if(depurar_ilhamento==0){
                //IupMessagef("Aviso!", "ELEMENTO i:j = %d:%d PARA A DIAGONAL PRINCIPAL EM ANÁLISE", i, j);
            }


            //SE LIGA i:i não entra aqui pow!

            if(i!=j && (ilhamento == 0 || ilhamento_start == 0)){ //SE EXISTE AO MENOS UM CAMINHO A TERRA ENTÃO PODE ENTRAR
                                                                  //ILHAMENTO_START = 0 QUER DIZER ILHAMENTO = 1 PARA BARRA i:i
                                                                  //Caso da barra 2:2 está ilhada sem gerador/motor, mas (no system4B) tem caminho a terra pelo 2:4

                    if(depurar_ilhamento==0){
                        //IupMessagef("Aviso!", "ELEMENTO %d:%d PARA A DIAGONAL PRINCIPAL CARREGADO", i, j);
                        //1:1 não entrou aqui (CERTO), é para analisar os js
                    }

                        //struct_buffer.buffer1 = function_struct_buffer_ligacao(i, j);
                        //buffer1 = struct_buffer.buffer1;
                        //buffer2 = struct_buffer.buffer2;




                    /*** \DISPARA \FUNCTION \PARA \EXISTENCIA \DE \RAMO (EXISTÊNCIA DE IMPEDÂNCIA) - \ETAPA \DOIS ***/


                    //AQUI NÃO ENTRA i:i, acordo pow!

                    recebimento_massivo = function_struct_buffer_ligacao(i, j); //envia 1:2 e carrega a impedância 1:2, carrega no envio-buffer1
                                                                                //Porém só verificou que existe o trafo, mas não se sabe se está ilhado!

                    //O ilhamento_buffer_ij é exclusivo do incremento dos ramos radiais a barra em análise, sendo ele igual a zero estará habilitado
                    //a se verificar se o ramo em análise (agora existente) está ilhado ou não, agora de forma pormenorizada.

                    if(recebimento_massivo.buffer1 != 0){ //impedância = IMPEDÂNCIA INDIVIDUALIZADA DO RAMO
                        ilhamento_buffer_ij  = 0; //NÃO DÁ PARA CORTAR PELA RAIZ DE VEZ, PRECISA ACIONAR A FUNÇÃO ILHAMENTO DEPOIS
                                                  //NÃO DÁ PARA SABER SE ESTÁ ILHADO A IMPEDÂNCIA QUE EXISTE
                    }

                    //Note que ilhamento_buffer_ij é o que garante a existência de ramo, então até aqui 1:2 está ok, carrega zero em ilhamento_buffer_ij

                    if(recebimento_massivo.buffer1 == 0){ //se não existe impedância é porque o ramo é descontínuo
                        ilhamento_buffer_ij  = 1;
                    }




                    /*** \DISPARA \FUNCTION \ILHAMENTO - \ETAPA \TRES (VERIFICAR SE O RAMO EXISTENTE ESTÁ ILHADO) ***/

                    /***

                    É necessário reproduzir/repetir a função ilhamento tudo novamente (em partes) de forma pragmática e individualizada
                    para cada ramo radial à barra em análise (cada ramo à incrementar), pois até então eu só busquei saber se havia pelo
                    menos um caminho à terra

                    ***/



                    if(ilhamento_buffer_ij == 0 ){ //O elemento 1:2 do sistema de 7 barras ou 4 barras reduzido entra aqui

                        if(depurar_ilhamento==0){
                            //IupMessagef("Aviso!", "ELEMENTO %d:%d PARA A DIAGONAL PRINCIPAL É CONTÍNUO (RAMO EXISTE)", i, j);
                        }//Ok, entendi o que fiz



                        buffer_ligacao_esquema = matrix_struct[i][j].trafo_indices.ligacao_esquema;

                        //Note que para 1:2 existe 3 retornos, por 1:1, por 2:3 e por 1:3

                        /*** \LEMBRE - \SE AQUI NÃO ENTRA i:i ***/
                        /*** AQUI O ILHAMENTO = 0 É SÓ PARA UM RAMO ***/

                        //O ramo 2:1 entra aqui
                        if(ilhamento == 0 && buffer_ligacao_esquema != 2 && buffer_ligacao_esquema != 6 && buffer_ligacao_esquema != 7){ //DIFERENTE DA LIGAÇÃO 2!!!
                            ilhamento_start_ij = 0; //A barra 1:1 já tem caminho à terra (7System) então já soma direto pow
                                                    //Qualquer coisa que ramifica da barra em análise, a i:i, com ilhamento igual a zero se soma à barra!
                        }//start = disparar/iniciar


                        //indiretamente estou pegando ilhamento_start = 0 fazendo ilhamento != 0
                        if(ilhamento != 0 && buffer_ligacao_esquema != 2 && buffer_ligacao_esquema != 6 && buffer_ligacao_esquema != 7){ //DIFERENTE DA LIGAÇÃO 2!!!
                            //NÃO TEM MAIS UTILIDADE
                            //ilhamento_start_ij = function_ilhamento(j, i); //SAGACIDADE, tu vai bloquear o teste entre a barra em estudo 2:2 e o j:j
                                                                           //pois ainda poderia existir caminho entre 3:1
                                                                           //trem está tão amarrado que um toquinho já resolveu
                            //TAMBÉM VAI DIRETO AO PONTO
                            ilhamento_start_ij = 0;
                        }//start = disparar/iniciar



                            if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 2){ //SE A LIGAÇÃO FOR A 2, ENTÃO DE IMEDIATO RECEBE ZERO
                                ilhamento_start_ij = 0;
                            }

                            if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 6){ //SE A LIGAÇÃO FOR A 6, ENTÃO DE IMEDIATO RECEBE ZERO
                                ilhamento_start_ij = 0;
                            }

                            if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 7){ //SE A LIGAÇÃO FOR A 7, ENTÃO DE IMEDIATO RECEBE ZERO
                                ilhamento_start_ij = 0;
                            }


                        //ilhamento = 2 - genérico
                        if(ilhamento_start_ij == 2){ //caso uma ligação não seja vista pela barra que não tem a impedância do trafo, sem ligação 2, 6, 7...
                            ilhamento_start_ij = 0;
                        }

                    }


                    /*** SE EU NÃO ESTIVER ENGANADO, BASTA QUE HAJA O RAMO RADIAL À BARRA PARA QUE ELE SOME A ADMITÂNCIA À BARRA ***/

                    if(depurar_ilhamento==0){
                    //IupMessagef("Aviso!", "O valor de ilhamento_start_ij para %d:%d é %d", i, j, ilhamento_start_ij);
                    }


                    //CUIDADO ilhamento_buffer_ij só garante a existência do ramo, mas não garante a continuidade, por isso é obrigatório ter start_ij

                    if(ilhamento_start_ij == 0 && ilhamento_buffer_ij == 0){ //SE EXISTIR O RAMO E SE A BARRA i:i NÃO ESTIVER ILHADA, SOME OS RAMOS RADIAIS A ELA

                            //Se (não?) houver caminho a terra então incrementa, ilhamento_start = 1
                            //Se houver então soma ilhamento_start =0

                            recebimento_massivo = function_struct_buffer_ligacao(i, j); //primeira vez acima entrou só para pegar a ligação, agora buscará o buffer1,
                                                                                        //somente acessa, não recalcula e não interfere no conteúdo.



                            buffer1 = recebimento_massivo.buffer1;
                            buffer2 = recebimento_massivo.buffer2;

                            /***
                            if(buffer1 != 0){
                                ilhamento  = 0; //CORTA PELA RAIZ, JÁ TEM ELEMENTO À TERRA
                            }
                            if(buffer1 == 0){ //caso da barra 2:2
                                ilhamento  = 1; //barra sem gerador
                            }
                            ***/
                            //Note que a princípio em 2:2 já estaria ilhado e entraria no laço
                            //Se tem um gerador com terra à barra não tem como a barra estar ilhada! Logo não irei testar i != j, por enquanto!

                            if(depurar_ilhamento==0){
                                //IupMessagef("Aviso!", "O recebimento massivo de %d:%d é buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                            }


                            //Até aqui conseguiu capcturar a impedância de 1:2






                            /**************************************************** \INCREMENTO ****************************************************/


                            //Nem sempre buffer1 é igual a buffer2, um pode ser nulo e outro não!
                            if(buffer1 != 0){
                                admitancia_buffer1 = -1*(1/buffer1); //j complexo invertido
                            }
                            if(buffer2 != 0){
                                admitancia_buffer2 = -1*(1/buffer2); //j complexo invertido
                            }

                            if(buffer1 == 0){
                                admitancia_buffer1 = 0.0;
                            }
                            if(buffer2 == 0){
                                admitancia_buffer2 = 0.0;
                            }

                            //Note que o foco da somatória de linha de Zpu só vale para Yii

                            /*** \SOMENTE \PARA \DIAGONAL ***/

                            if((ilhamento == 0 || ilhamento_start == 0) && ilhamento_start_ij == 0){ //ao menos um caminho a terra e se a barra j tem caminho a terra

                                if(depurar_ilhamento==0){
                                    //IupMessagef("Aviso!", "Sem ilhamento - PARCIAL DIAGONAL, para %d:%d, o buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                                }

                                matrix_admitancia_zero_pu[i][i] = matrix_admitancia_zero_pu[i][i] + admitancia_buffer1; //aqui não é um somatório, apenas uma admitância buffer negativada
                            //matrix_admitancia_zero_pu[j][j] = matrix_admitancia_zero_pu[j][j] + admitancia_buffer2; //start i = j, logo 1:1
                                                                                                                        //em 1:1 recebe buffer1 cheio e sobrepõe buffer2 vazio

                                //IupMessagef("Aviso!", "O valor de matrix_admitancia_zero_pu %d:%d é %.5f", i, i, matrix_admitancia_zero_pu[i][i]);
                                //IupMessagef("Aviso!", "O valor de matrix_admitancia_zero_pu %d:%d é %.5f", j, j, matrix_admitancia_zero_pu[j][j]);

                            }

                    } //ilhamento_start ij



                                            //1:2 é continuo mas não foi incrementado!


                } //CONDICIONAL IF - i != j ...praticamente todo for à condicional ilhado = 0



                        /*** O FOCO É A DIAGONAL, VC PRECISA SABER QUANDO ESTÁ ILHADO OS ELEMENTOS DA DIAGONAL PARA ZERÁ-LOS ***/


                        //Se liga quando i = j , tipo 2:2 repete duas vezes um recebe buffer1 cheio e o outro recebe buffer2 vazio

                        /*** \LIQUIDA \A \PENDENCIA \BARRA \A \TERRA ***/


                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "A admitância total de sequência zero de %d:%d é %.5f", i, i, matrix_admitancia_zero_pu[i][i]);
                        }
                    //IupMessagef("Aviso!", "A admitância total de sequência zero de %d:%d é %.5f", j, j, matrix_admitancia_zero_pu[j][j]);




        } //FIM-LAÇO j diagonal

        fim_diagonal++;

    } //FIM-LAÇO i diagonal












    /*** \Y \MAIUSCULO \FORA \DA \DIAGONAL \TR \NORMAL \E \LT ***/


    //FALTA RESOLVER O PROBLEMA DOS ELEMENTOS 2:3 E 3:2 EMPATANDO A OBTENÇÃO DA MATRIZ INVERSA

    int continua_j_const = 0;
    float buffer_continua_j;

    if(fim_diagonal > 0){


        for(i = 1; i < size_SEP_bars+1; i++){

            buffer_continua_j = matrix_admitancia_zero_pu[i][i];

            if(continua_j[i] != 1){ //o if não pegou o 0.00001 nem ferrando, problema 2 foi fazer continua_j[i] reconheceu separado continua_j e i
              continua_j_const = 0;
              if(depurar_admitancia==0){
              //IupMessagef("Aviso!","IF-1: O valor para continua_j_const para i:i = %d:%d é %d", i, i, continua_j_const);
              //IupMessagef("Aviso!","IF-1: O valor para continua_j para i:i = %d:%d é %d", i, i, continua_j[i]);
              }
            } //O i é o eixo e quem tá girando é o j

            if(continua_j[i] == 1){ //Bizonho o 3:3 entrou aqui
              continua_j_const = 1;
              if(depurar_admitancia==0){
              //IupMessagef("Aviso!","IF-2: O valor para continua_j_const para i:i = %d:%d é %d", i, i, continua_j_const);
              //IupMessagef("Aviso!","IF-2: O valor para continua_j para i:i = %d:%d é %d", i, i, continua_j[i]);
              }
            } //O i é o eixo e quem tá girando é o j

            //Quando vc entra uma vez no j não impede de somar 2>3 <<< old comment

            if(continua_j_const == 0){ //Se a barra principal recebeu 0.00001 então não pode entrar aqui
                for(j=1; j < size_SEP_bars+1; j++){
                    if(j!=i){ //Note, nem estava me dando conta, mas para admitância os elementos da diagonal ii não entram
                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!","DISPARADO A FUNÇÃO Y_BARRA FORA DA DIAGONAL - ELEMENTO i:j igual a %d:%d", i, j);
                        }

                        buffer_ligacao_esquema = matrix_struct[i][j].trafo_indices.ligacao_esquema;//ADVÉM DO trafo_10 ou trafo envolvido
                        buffer_ligacao_nucleo = matrix_struct[i][j].trafo_indices.ligacao_nucleo; //ADVÉM DO trafo_10 ou trafo envolvido



                        if(buffer_ligacao_esquema == 0){ //LT ou inexistência de ramo

                            /*** \REBOTE ***/
                            buffer_ligacao_esquema = matrix_struct[j][i].trafo_indices.ligacao_esquema; //coletando se há trafo simétrico
                            buffer_ligacao_nucleo = matrix_struct[j][i].trafo_indices.ligacao_nucleo; //ADVÉM DO trafo_10


                        }

                        /*** condicional redundante desnecessário
                        if(buffer_ligacao_esquema == 0){
                            buffer_ligacao_esquema = matrix_struct[j][i].trafo_indices.ligacao_esquema; //coletando o trafo simétrico, enchendo o buffer
                            //condicional pode ser deletada, só coloquei para reforçar a tentativa 2
                        }
                        ***/

                        //AQUI É MUITO, MAS MUITO SIMPLES!


                        if(buffer_ligacao_esquema == 0){
                                //Não existe trafo
                                //LT entre i e j
                                buffer1 = matrix_impedancia_zero_pu[i][j]; //Se houver inexistência de ramo zerá buffer nulo, senão será da LT
                                buffer2 = buffer1;
                                if(depurar_admitancia==0){
                                //IupMessagef("Aviso!","O valor de matrix_admitancia_zero_pu[%d][%d] é %.5f", i, i, matrix_admitancia_zero_pu[i][i]);
                                //IupMessagef("Aviso!","O valor de matrix_admitancia_zero_pu[%d][%d] é %.5f", j, j, matrix_admitancia_zero_pu[j][j]);
                                }


                                /*** \MONITORAR se na inexistência de ramo buffer dará zero ***/

                                if(depurar_admitancia==0){
                                //IupMessagef("Aviso!","O valor de buffer1 para i:j = %d:%d é %.5f", i, j, buffer1);
                                }

                        }


                        if(buffer_ligacao_nucleo == 1) {


                                if(buffer_ligacao_esquema == 1){ //Yat:Yat ... Se achar de primeira 1:2 já pula direto para cá, não passa no condicional nulo
                                                                 //Se for 2:1 o lançamento do trafo, então a ligação é nula para 1:2 e diferente de zero para 2:1
                                                                 //É carregado o 2:1, então sempre vem cheio

                                    buffer1 = matrix_impedancia_zero_pu[i][j]; //cenário não existe i:i...fora da diagonal
                                    buffer2 = buffer1;

                                }

                                if(buffer_ligacao_esquema == 2){ //Yat:D ...atende tranquilamente a i:j e j:i, se vem cheio bão, se vem vazio, é carregado antes e chega cheio
                                        buffer1 = 0; //abaixo tem um condicional para fazer a admitância nula
                                        buffer2 = 0; //

                                }


                                if(buffer_ligacao_esquema == 3){ //D:Yat
                                        buffer1 = 0; //abaixo tem um condicional para fazer a admitância nula
                                        buffer2 = 0; //
                                        if(depurar_admitancia==0){
                                        //IupMessagef("Aviso!","O valor de buffer1 para i:j = %d:%d é %.5f - LIGAÇÃO 3", i, j, buffer1);
                                        }
                                }

                        }

                        if(buffer_ligacao_esquema == 4){ //Y:D
                                buffer1 = 0;
                                buffer2 = 0;

                        }


                        if(buffer_ligacao_esquema == 5){ //D:Y
                                buffer1 = 0;
                                buffer2 = 0;
                        }


                        if(buffer_ligacao_esquema == 6){ //Yat:Y
                                buffer1 = 0;
                                buffer2 = 0;
                        }


                        if(buffer_ligacao_esquema == 7){ //Y:Yat
                                buffer1 = 0;
                                buffer2 = 0;
                        }

                        if(buffer_ligacao_esquema == 8){ //D:D
                                buffer1 = 0;
                                buffer2 = 0;
                        }

                        if(buffer_ligacao_esquema == 9){ //Y:Y
                                buffer1 = 0;
                                buffer2 = 0;
                        }


                        //AQUI ESTAMOS A ANALISAR A SEQUÊNCIA ZERO, E ISSO NOS GARANTE SOMA ATÉ O SIZE BARS DE MAIOR TAMANHO

                        if(buffer_ligacao_nucleo == 2){ //NÚCLEO ENVOLVIDO

                                if(buffer_ligacao_esquema == 1){ //Yat:Yat - //NÚCLEO ENVOLVIDO

                                    buffer1 = 0.0; //NO CASO AQUI PRECISO CONSIDERAR TRAFOS ENVOLVENTES! AQUELES CONVERTIDOS.
                                    buffer2 = 0.0;

                                }

                                if(buffer_ligacao_esquema == 2){ //Yat:Y - //NÚCLEO ENVOLVIDO

                                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                                        buffer1 = 0.0;
                                        buffer2 = 0.0; //matrix_impedancia_zero_pu[i][j]; //Neste caso a exibição de lançamento é como se fosse normal
                                    }
                                    else{
                                        buffer1 = 0.0; //matrix_impedancia_zero_pu[i][j];
                                        buffer2 = 0.0;
                                        if(depurar_ilhamento==1){
                                            //IupMessagef("Aviso!", "Na ligação 2 para %d:%d o buffer1 = %.5f e buffer2 = %.5f", i, j, buffer1, buffer2);
                                        }
                                    }
                                }


                                if(buffer_ligacao_esquema == 3){ //Yat:D - //NÚCLEO ENVOLVIDO

                                    if(matrix_struct[i][j].trafo_indices.ligacao_esquema == 0){
                                        buffer1 = 0.0; //matrix_impedancia_zero_pu[i][j];
                                        buffer2 = 0.0;
                                    }
                                    else{ //Yat:D
                                        buffer1 = 0.0;
                                        buffer2 = 0.0; //matrix_impedancia_zero_pu[i][j];
                                    }

                                }

                        }



                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "MONITORAR2 --- O buffer1 impedância pu de %d:%d é %.5f", i, j, buffer1);
                        }



                        //Nem sempre buffer1 é igual a buffer2, um pode ser nulo e outro não!
                        /******************************************************************************************/
                        if(buffer1 != 0){
                            admitancia_buffer1 = -1*(1/buffer1); //j complexo invertido
                            admitancia_buffer1 = -1*(admitancia_buffer1); //depois inverte o y minúsculo!
                        }

                        if(buffer1 == 0){
                            admitancia_buffer1 = 0.0;
                        }

                        /******************************************************************************************/

                        if(buffer2 != 0){
                            admitancia_buffer2 = -1*(1/buffer2); //j complexo invertido
                            admitancia_buffer2 = -1*(admitancia_buffer2); //depois inverte o y minúsculo!
                        }

                        if(buffer2 == 0){
                            admitancia_buffer2 = 0.0;
                        }

                        //Note que o foco da somatória de linha de Zpu só vale para Yii
                        matrix_admitancia_zero_pu[i][j] = 0; //inicialização
                        matrix_admitancia_zero_pu[j][i] = 0; //inicialização
                        matrix_admitancia_zero_pu[i][j] = admitancia_buffer1; //aqui não é um somatório, apenas uma admitância buffer negativada
                        matrix_admitancia_zero_pu[j][i] = admitancia_buffer1; //aqui não é um somatório, apenas uma admitância buffer negativada

                        if(depurar_admitancia==0){
                        //IupMessagef("Aviso!", "A admitância total de sequência zero de %d:%d é %.5f", i, j, matrix_admitancia_zero_pu[i][j]);
                        //IupMessagef("Aviso!", "A admitância total de sequência zero de %d:%d é %.5f", j, i, matrix_admitancia_zero_pu[j][i]);
                        }

                    }//FIM laço j!=i
                } //FIM laço j - Y_BARRA FORA DA DIAGONAL
            } //FIM laço continua_j
        }//FIM laço i - Y_BARRA FORA DA DIAGONAL

    } //CONDICIONAL PARA EXECUTAR PRIMEIRO A DIAGONAL

}


/******************************************************

    >>> \FUNCTIONS \BASES \SEP
        >>> \FUNCTION \CONFIRMACAO \BASE \DEFINIDA
        >>> \FUNCTION \FRAME \FORMULARIO \DA \BASE
        >>> \FUNCTION \JANELA \FORMULARIO \DA \BASE
        >>> \FUNCTION \COLETA \DA \BASE  \DEFINIDA
        >>> \FUNCTION \CARREGAMENTO \DA \BASE  \DEFINIDA
    >>> \DESCONTINUIDADE --- disparo via \LOAD \FULL
            >>> \FUNCTION \CALCULO \DAS \BASES

*******************************************************/


/*****************************************(                       \FUNCTIONS \BASES \SEP          )********************************************

***/





/*****************************************(                  \FUNCTION \CONFIRMACAO \BASE \DEFINIDA          )********************************************

***/

static int button_memory_Base_SEP(Ihandle *ih) /*** BOTÃO DE DEFINIÇÃO DA BASE NA JANELA BASE ***/
{

    //static int status_memory_Base_SEP = 0; /*** PRECISA SER GLOBAL PQ OUTRAS FUNÇÕES À ENXERGAM COMO MARCADOR DE EXECUÇÃO ***/
                                            /*** Variável local inicializa uma única vez, porém incrementável ***/
                                           /*** Variável local - basta inserir static que já é o suficiente, nada externamente à função ***/
                                           /*** Só é global enquanto estiver dentro da função, não é vista por outras funções ***/

    printf("criar uma função que armazene a base do SEP e possa ser acionar remotamente a qualquer instante");

    //crie um botão para sua validação interna, para ver se entrou nesta função - botão verificar, daí ele vai entrar nesta função e coletar o que
    //foi definido, daí eu tenho certeza...ainda na Form ligação trafo preciso sinalizar após apertar definir, idela que transferisse para a segunda janela

    /*** Aqui é prova viva de que a função está zerando o contador sem o static ***/
    if(status_memory_Base_SEP==0){

        /*** Assim como o botão full load ***/
        //inicializar uma função aqui

      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues IN THE FORM BASE SEP***********************************************/

        function_memory_base(ih); //disparo indireto do click

     /*** status_memory_Base_SEP++; //IupMessage("Aviso!", "CARREGADO A BASE DO SEP! \n Minimize a janela ou encerre-a!");
     /*** \LEMBRE-SE O IF A SEGUIR DEPENDE do status_memory, lá no carregamento massivo não funcionou a lógica de por ++ ***/

        if (status_memory_Base_SEP==1){
             IupMessage("Aviso!", "CARREGADO A BASE DO SEP! \nMinimize a janela ou encerre-a!"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");




    return IUP_DEFAULT;

}







/*****************************************(                   \FUNCTION \FRAME \FORMULARIO \DA \BASE           )********************************************

***/


static Ihandle* createForm_Base_SEP(void) /*** JANELA DE DEFINIÇÃO DA BASE DO SEP ***/
{
    Ihandle *box, *btn_Base_SEP;

    //Botão para carregar a base, e não para iniciar o Form da base!
    btn_Base_SEP = IupButton("Definir", NULL); //FUNCIONOU, DESVINCULEI O FORMULÁRIO DA CRIAÇÃO DA MDI CLIENT SOBREPOSTA
    IupSetCallback(btn_Base_SEP,"ACTION", (Icallback)button_memory_Base_SEP); // a função, argumento 3, recebe um Ihandle button como disparo


    /***

        A função do botão acima é armazenar todos os dados abaixo, OU sinalizar que estão na memória (status de cascateamento)
        no caso tenho como armazenar o valor numa memória, mas preciso saber como fazer isso ficar permanente (a princípio precisaria de um disparo de fixação)



    ***/

    /******************************************** TABELA COM AS LIGAÇÕES - TRAFO 2 - USE SEPARADORES ***************************************/


    Ihandle *label_Tensao_Base =  IupLabel("Tensão de Base");
    Ihandle *BoxValue_Tensao_Base =  IupText(NULL);



      IupSetAttribute(BoxValue_Tensao_Base, "NAME", "BoxValue_V_base_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Tensao_Base, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Tensao_Base, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Tensao_Base, "VALUE", "%.2f", 13.8);



    Ihandle *label_Potencia_Base =  IupLabel("Potência de Base");
    Ihandle *BoxValue_Potencia_Base =  IupText(NULL);


      IupSetAttribute(BoxValue_Potencia_Base, "NAME", "BoxValue_P_base_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Potencia_Base, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Potencia_Base, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Potencia_Base, "VALUE", "%.2f", 30.0);

    /*** alocar memória para string label ***/
     char* buffer = (char*)malloc(10000*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ***/

    /******************************************NÃO UTILIZE A ROTINA ABAIXO, MEMÓRIA NÃO É ALOCADA! **********************/
   //*** Rotina de buffer ******/
    //char Buffer[1]={""};
    //strcpy(buffer, Buffer); //estou inicializando a variável buffer

    sprintf(buffer, "Barra da base: \n 1 - Barra (1:1) \n 2 - Barra (2:2) \n 3 - ... \n %d - Barra (%d:%d) ", size_SEP_bars_OLD, size_SEP_bars_OLD, size_SEP_bars_OLD);
    Ihandle *label_Regiao_base =  IupLabel(buffer);
    Ihandle *BoxValue_Regiao_Base =  IupText(NULL);


      IupSetAttribute(BoxValue_Regiao_Base, "NAME", "BoxValue_Regiao_base_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Regiao_Base, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Regiao_Base, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetInt(BoxValue_Regiao_Base, "VALUE", 1);// seta o campo no valor desejado





      //Ihandle *label_INFO_Base = IupLabel("Definir a Base do Sistema Elétrico de Potência - SEP de 2 Barras (5 nós)");
      Ihandle *label_INFO_Base = IupLabel("Definir a Base do Sistema Elétrico de Potência - SEP de n Barras (n+1 nós)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_INFO_Base, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_INFO_Base, "FONTSTYLE", "Bold");


      Ihandle *Field_Tensao_Base = IupHbox(label_Tensao_Base, BoxValue_Tensao_Base, IupLabel(" kV"), NULL);
      Ihandle *Field_Potencia_Base = IupHbox(label_Potencia_Base, BoxValue_Potencia_Base, IupLabel(" MVA"), NULL);
      Ihandle *Field_Regiao_Base = IupHbox(label_Regiao_base, BoxValue_Regiao_Base, NULL);

     /************************ INÍCIO FRAME FORMULÁRIO - TRANSFORMADOR 2 **************************************************************************/
      Ihandle *base_SEP;

      /* Creating box that contains the fields */
      base_SEP = //IupHbox(
        IupFlatFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
            label_INFO_Base,
            Field_Tensao_Base,
            Field_Potencia_Base,
            Field_Regiao_Base,
            btn_Base_SEP,
          NULL)
          );

      IupSetAttribute(IupGetChild(base_SEP, 1), "TITLE", "Barra 3 - Transformador 2"); //interessante...

      IupSetAttribute(base_SEP, "BGCOLOR", "15 180 0"); //Fundo dos campos fica colorido

      /************************ FIM FRAME FORMULÁRIO **************************************************************************/


    //box = IupVbox(base_SEP, NULL);
    box = IupVbox(IupSetAttributes( IupScrollBox(base_SEP), "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" ), NULL);
    //Agora o FORM ficou com barra de rolagem, a sacada é a usabilidade em uma tela, viabilizando o uso simultâneo dos formulários
    IupSetAttribute(box,"MARGIN","5x5");

    return box; //É enviado a arquitetura de uma Vbox para uma dialog em definitivo


}









/*****************************************(                  \FUNCTION \JANELA \FORMULARIO \DA \BASE           )********************************************

***/

static int button_Base_SEP(Ihandle *ih) /*** DEFINIÇÃO DA BASE DO SEP ***/
{
  //static int id = 2; //a princípio posso por fora da função e vincular os índices 0 a 3 ao 4 curtos
  /*** static int status_memory_Base_SEP --- VARIÁVEL GLOBAL --- dessa maneira viabiliza reabrir a janela do form enquanto não definir ***/
  /*** contudo abriria-se uma segunda janela (ou mais)...mesmo a primeira estivesse aberta ***/
  /*** embora tenha 2 janelas, o que vale é o definir, assim evita-se o constrangimento do usuário encerrar a primeira vez sem querer ***/

  Ihandle *box, *txt, *dlg, *bt;

  //note que o dlg precisa ser indexado para que vc saiba o que afinal
  //vai encerrar, pq cada vez que entra na função é um dlg novo


      if(status_memory_size_SEP_bars == 0){

          IupMessage("Aviso!", "O número de barras do SEP ainda não foi definido! Favor quantificar e clicar no botão definir.");
      }

      if(status_memory_Base_SEP == 0 && status_memory_size_SEP_bars > 0){

          /**FORMULÁRIO
              txt = IupText(NULL);

              bt = IupButton("Test", NULL);
              IupSetCallback(bt,"ACTION", button_cb);

          box = IupVbox(IupHbox(bt, NULL), txt, NULL);
          IupSetAttribute(box,"MARGIN","5x5");
          **/
          box = createForm_Base_SEP(); /*** CRIAÇÃO VBOX DE DEFINIÇÃO DA BASE DO SEP ***/

          //Me liguei, no caso preciso usar o formulário criado para inserir botões, antes de jogar para IupDialog (finalmentes)

          dlg = IupDialog(box); //captura um Vbox (FORMULÁRIO)
          //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
          IupSetfAttribute(dlg,"TITLE","Definição da Base do SEP");//(%d) (ASPAS), id);
        //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
          //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS
        //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via a tag desta
          IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
          IupSetAttribute(dlg,"RASTERSIZE","600x600");
        //  IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");

          IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
          IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas
          IupSetHandle("mdi_tag_BASE", dlg); //tag da janela

          IupSetAttribute(dlg,"PARENTDIALOG","mdi_tag_FORM"); //atribuindo a dlg à janela do Formulário via a tag desta

          IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
          IupSetAttribute(dlg, "DEFAULTESC", "quit");


          IupShow(dlg);

          IupSetAttribute(dlg,"RASTERSIZE",NULL);
      }

      if(status_memory_Base_SEP != 0 && status_memory_size_SEP_bars > 0){

            IupMessage("Aviso!", "Formulário já foi criado!");
            //IupSetCallback(dlg, "CLOSE_CB", (Icallback)close_cb2); //mdi_closeall
            //EM CONSTRUÇÃO: use um dlg indexado e então será possível fechar o formulário
            //pelo que li, ao fechar o formulário ele também é destruído.
            //Dois gargalos o mdi_closeall não funciona e não reseta o formulário
       }
      //O MDI Close não destroy a janela em buffer, apenas fecha a existente
      //contudo isso só funcionou no iuptest.exe da versão 3.30 do iup

      return IUP_DEFAULT;
}







/*****************************************(                  \FUNCTION \COLETA \DA \BASE  \DEFINIDA         )********************************************

***/


static int function_memory_base(Ihandle *ih){

            /*** ACESSO ÚNICO PELO BOTÃO carregar base ***/

                  Ihandle *MemoryBoxValue_V_base, *MemoryBoxValue_P_base, *MemoryBoxValue_Regiao_base;


                  struct base bases_SEP_coleta; //no caso eu declarei uma base local que será transferida À universal pela função carregamento...aqui somente há captura

                  //Note que aqui não pode ter o mesmo nome da struct global


            /*** ativando o BoxValue de tensão de base para coleta***/

            /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

                MemoryBoxValue_V_base = IupGetDialogChild(ih, "BoxValue_V_base_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_V_base = IupGetFloat(MemoryBoxValue_V_base, "VALUE");

                bases_SEP_coleta.V_base = valor_V_base;


            /*** ativando o BoxValue de potência de base para coleta***/

                MemoryBoxValue_P_base = IupGetDialogChild(ih, "BoxValue_P_base_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_P_base = IupGetFloat(MemoryBoxValue_P_base, "VALUE");

                bases_SEP_coleta.P_base = valor_P_base;


            /*** ativando o BoxValue de região de base para coleta***/

                MemoryBoxValue_Regiao_base = IupGetDialogChild(ih, "BoxValue_Regiao_base_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  //float valor_Regiao_base = IupGetFloat(MemoryBoxValue_Regiao_base, "VALUE");

                int valor_Regiao_base = IupGetInt(MemoryBoxValue_Regiao_base, "VALUE");

                bases_SEP_coleta.Regiao_base = valor_Regiao_base;



                /*** envio massivo ***/
                /*** deixar no botão load full ***/

               /*** \STAND \BY***/

               if(valor_Regiao_base > size_SEP_bars_OLD || valor_Regiao_base < 1)
               {
                   IupMessage("Aviso!", "Digite um valor válido!");
               }
               else
                   Carregar_Base(bases_SEP_coleta); /*** envio massivo de uma struct***/



                //Carregar_Base(bases_SEP_coleta); /*** envio massivo de uma struct***/

                return IUP_DEFAULT;

}







/*****************************************(             \FUNCTION \CARREGAMENTO \DA \BASE  \DEFINIDA         )********************************************

***/

void Carregar_Base(struct base bases_struct) /*** recebimento massivo ***/
{

    /*** ACESSO DUPLO PELOS BOTÕES carregar base e load full ***/
    static int acesso_init = 0; //PUTZ, AGORA QUE DEI FÉ, 5 HORAS DEPOIS, NÃO ESTAVA STATIC


            /*** CONDICIONAL PARA CARREGAR A BASE ****/

            if(acesso_init==0){ //MEMÓRIA PERMANENTE <<<<<<<<<<< finalidade da função Carregar_Base()

                /*** recebimento massivo de apenas uma struct ***/
                base_SEP_coleta[0] = bases_struct; //carrega a struct_base na matrix struct, tática de nós (01mai22)
                //--- ficou insano, cuidado...toda a struct ficou numa única célula da matriz, já tá tudo carregado só nesta linha


                status_memory_Base_SEP++; //IupMessage("Aviso!", "CARREGADO A BASE DO SEP! \n Minimize a janela ou encerre-a!");

                /**** NÃO É MAIS NO SINGULAR base_struct ****/

/***
                IupMessagef("Aviso!","A tensão de base é %.2f", base_struct.V_base);
                IupMessagef("Aviso!","A potência de base é %.2f", base_struct.P_base);
                IupMessagef("Aviso!","A região de base é %d", base_struct.Regiao_base); //// NOTE É UM INTEIRO ////
***/
                //quando tu casa as estruturas base carrega-se massivamente os campos: da coleta para struct global




            }

            if(acesso_init!=0){ //Mensagem de rebote ... Carregar_Base() também era acessada pelo button load full

                //printf(" ");
/***
                IupMessagef("Aviso!","A tensão base é %.2f", base_struct.V_base);
                IupMessagef("Aviso!","A potência base é %.2f", base_struct.P_base);
                IupMessagef("Aviso!","A região de base é %d", base_struct.Regiao_base); //// NOTE É UM INTEIRO ////
***/

            }
            //else
               // IupMessage("Aviso!","Base já foi carregada");
            acesso_init++;

}





/************************************************* \DESCONTINUIDADE \BASE - \ACIONAMENTO DO CÁLCULO \DAS \BASES É VIA CARREGAR FORM *************************/



/*****************************************(             \FUNCTION \CALCULO \DAS \BASES         )********************************************

***/

static int Calc_Bases_SEP(Ihandle* button_Form_Load_Full)
{
    //static int V[size_SEP_bars]; //declaração das tensões de base em todas as barras <<<<< é um elemento já da struct

    if(depurar_base==1){
    IupMessage("Aviso!", "A função Calc_Bases_SEP foi inicializada - Laço 1");
    }

    /*************************************** CRIANDO O VETOR DE BASES ************************/
    int barra_Base_1 = 0;
    int i = 0;
    int exibir_unica = 0;
    /*************************************** WHILE BASES ************************/
    int full_bases = 0; //Outra condicional para que as bases possam ser calculadas é ter pares lado a lado, caso contrário não é possível calcular sem while

    //int size_SEP_barsOLD = size_SEP_bars;

        /****************** É INICIALIZADA A STRUCT BASE EM i = 1 ****************/
            //for(i = 0, j=2; i <size_SEP_bars;j++, i++){
            for(i = 1; i < size_SEP_bars_OLD+1;i++){ //Barra 1 até a barra n...vetor de 16 casas! --- A INDEXAÇÃO DAS MEMÓRIAS ESTÁ IGUAL AO DA LISTA 1 = (1:2)
                /**** Independe do preenchimento dos frames do Form, aqui é apenas uma inicialização limpa das bases com zeros ***/
                base_SEP_coleta[i].V_base = 0; //Importante, deve inicar em 1, pois o índice 0 carrega a definição da base
                base_SEP_coleta[i].P_base = 0;
                base_SEP_coleta[i].id_k_Base = 0;
                base_SEP_coleta[i].Regiao_base = 0;


                if(depurar_base==1){
                    //IupMessagef("Aviso!", "A tensão de base da barra %d é V[%d] = %.2f kV", i, i, base_SEP_coleta[i].V_base);
                }

            }

            //NOTE, a posição ZERO é O BUFFER, se a base for 2, então barra_Base_1 = 2...e então a ideia é armanezar numa barra até então indefinida o buffer
            barra_Base_1 = base_SEP_coleta[0].Regiao_base; //barra_Base_1 = análogo ao id_x

            if(base_SEP_coleta[barra_Base_1].V_base == 0){//evita sobrecarregamento, só ocorre uma única vez a mudança de zero para não zero
                full_bases++;
            }
            base_SEP_coleta[barra_Base_1].V_base = base_SEP_coleta[0].V_base; //V[6] = V[0] recebe a tensão da barra

            base_SEP_coleta[barra_Base_1].P_base = base_SEP_coleta[0].P_base; //V[6] = V[0] recebe a tensão da barra
            base_SEP_coleta[barra_Base_1].id_k_Base = 1; //agora ficou elegante! Lembre-se, o V[6] tá com id_k_Base = 1
            base_SEP_coleta[barra_Base_1].Regiao_base = barra_Base_1; //sagaz, utilizando o índice zero como buffer


            IupMessagef("Aviso!", "A tensão da barra de base definida, barra %d, é %.2f kV", barra_Base_1, base_SEP_coleta[barra_Base_1].V_base);
            if(depurar_base==1){
            IupMessagef("Aviso!", "A potência da barra de base, barra %d, é %.2f MVA", barra_Base_1, base_SEP_coleta[barra_Base_1].P_base);
            IupMessagef("Aviso!", "O id_k_Base da barra de base, barra %d, é %d", barra_Base_1, base_SEP_coleta[barra_Base_1].id_k_Base);
            IupMessagef("Aviso!", "O região da barra de base, barra %d, é %d", barra_Base_1, base_SEP_coleta[barra_Base_1].Regiao_base);
            }



        //Depuração Ok até aqui - perfeita!



        /********* O disparado do cálculo da base após preenchimento do Form é dado pelo id_k_Base do índice zero: *********/

        //LEMBRE-SE, TEM UMA PENDÊNCIA EM AVERIGUAR SE ESTÁ PREENCHENDO CORRETO, 1 É PARA ELEMENTO CLICADO, 2 É PARA SIMÉTRICO
        //MOTORES E GERADORES NÃO IMPORTAM, SE O SEP TEM NO n BARRAS, ENTÃO ELE TERÁ n-1 RAMOS, E COMO n>4, NÃO TEM COM O QUE SE PREOCUPAR

        float V[size_SEP_bars_OLD]; //Vetor indexação rebaixada para tratamento das tensões
        int id_k_Base_Buffer1 = -1;
        int id_k_Base_Buffer2 = -1;
        float V_base_Buffer1 = 0;
        float V_base_Buffer2 = 0;

        int id_k_Trafo = 0;
        int id_k_LT = 0;

        int id_k_Trafo_Simetric = 0;
        int id_k_LT_Simetric = 0;

        int laco_2 = 0; //<<< condicional para preencher todas as bases radiais a barra de base para então preencher as outras bases não radiais
        int j = 0;




        /********************************************* LAÇO 1 COMEÇA AQUI, SÓ VAI PARA LAÇO 2 APÓS FAZER N BARRAS ************************/

        for(i = 1; i < size_SEP_bars_OLD+1; i++){ //ELEVANDO A INDEXAÇÃO, POIS A INDEXAÇÃO DAS MEMÓRIAS DE STRUCT ESTÃO IGUAIS AO DA LIST STRING FULL

            if(barra_Base_1 != i){

                //Se estou a analisar 6:1, ou 5:0, preciso saber qual o id_k do Trafo e da LT desse par, pq daí vou saber se tem algo ou não
                //id_k_Trafo = matrix_struct[barra_Base_1-1][i].trafo_indices.id_k_Trafo; //note que a indexação da matrix está abaixo
                //id_k_LT = matrix_struct[barra_Base_1-1][i].LT_indices.id_k_LT;

                //CAPTURANDO O PAR DE BARRAS QUE FOI LANÇADO NO SEP

                //SE LIGA O id_k_Trafo[Base][i] só está capturando algo que já existe
                //Se lancei 2:1 direto (anti-simétrico) inevitavelmente id_k_Trafo[1][2] vai ser capturado id_k_Trafo = 2

                //3:2
                id_k_Trafo = matrix_struct[barra_Base_1][i].trafo_indices.id_k_Trafo; //note que a indexação da matrix está abaixo <<<DESPREZADO
                id_k_LT = matrix_struct[barra_Base_1][i].LT_indices.id_k_LT;

                //2:3
                id_k_Trafo_Simetric = matrix_struct[i][barra_Base_1].trafo_indices.id_k_Trafo; //note que a indexação da matrix está abaixo <<<DESPREZADO
                id_k_LT_Simetric = matrix_struct[i][barra_Base_1].LT_indices.id_k_LT;


                if(depurar_base==0){
                //IupMessagef("Aviso!", "MONITORAR - BARRA DE BASE - A barra %d tem um id_k_Trafo do ramo (%d:%d) é igual a %d", i, barra_Base_1, i, id_k_Trafo);//Barra 1,2,4
                //IupMessagef("Aviso!", "MONITORAR - BARRA DE BASE - A barra %d tem um id_k_LT do ramo (%d:%d) é igual a %d", i, barra_Base_1, i, id_k_LT);
                }

                /****************** CONDICIONAL PARA INEXISTÊNCIA DE RAMO ********************************************************/
                if( (id_k_Trafo == 0 && id_k_LT == 0)  ) //se não existe elemento não se fala em id_k = 2
                {
                    //V[i] = 0;  //Faz nada, pq senão estaria alterando uma tensão válida ajustada por traçado contornável
                    //base_SEP_coleta[i].V_base = V[i];

                        base_SEP_coleta[i].id_k_Base = 2; //Laço 1 .. Ao setar 2 indica que a tensão está zerada ainda, mesmo após interação no Laço 1
                        /*** QUEM ESTÁ CONDUZINDO O LAÇO É A BARRA DA BASE 1, QUANDO FOR IMPLEMENTADO UM LAÇO COM FOR DUPLO, DAÍ SIM, AS VARIÁVEIS DEVEM
                             ESTAR INICIADAS COM id_k_Base = 2 e não igual a zero! ****/

                    laco_2++;

                }


                /****************** CONDICIONAL PARA EXISTÊNCIA DE RAMO BLOQUEADO ********************************************************/
/***
                if( (id_k_Trafo == 2 && id_k_LT == 2)  ) //se não existe elemento não se fala em id_k = 2
                {

                    if(id_k_Base_Buffer1 != 1) //se não fizer nada vai manter
                    {

                        base_SEP_coleta[i].id_k_Base = 2; // Ou seja, para o par 2:1 bloqueado, devido ao lançamento 1:2, ficou id_k_TR = 2 e id_k_LT = 2
                                                          // Assim, o id_k_Base[1] precisa ser iniciado ainda no laço 1 senão morre pelo caminho no laço 2
                    }

                    laco_2++;

                }


****/

                //Este simétrico DEVE SER CALCULADO OBRIGATORIAMENTE





                //SE LIGA, SE TU REMOVER O IF DE id_k_Trafo com 2 duplo tu mata o teste anterior

/****
veja bem, vc precisa colocar, É OBRIGADO A POR, o trafo/LT simétrica, colete e veja quem é id_k_TR/LT = 1, para saber se é LT ou TR
Para calcular a base por irradiação da base, senão não funciona!
*****/
                //NOTE QUE AO DEFINIR UM TR EM 1:2, DEVE SER BLOQUEADO O TRAFO SIMÉTRICO, id_k_Trafo = 2, E AS LTS 1:2 e 2:1, id_k_Trafo = 2 também!




//ANTES DO LAÇO É SOMENTE PARA COLETAR O id_k_Trafo/id_k_LT do ramo radial à barra de base - é testado ramo por ramo, e note que o laço 1 está neste laço barra_Base_1 != i

/****** LAÇO 1 ****/

                //Se existe alguma coisa, a ideia é já calcular a base, e não só preencher o id_k_Base
                if( ( id_k_Trafo == 1 || id_k_LT == 1) || (id_k_Trafo_Simetric == 1 || id_k_LT_Simetric == 1) ) //se não existe elemento não se fala em id_k = 2, e nem 1  ...&& (id_k_Trafo != 1 && id_k_LT != 1)
                {
                    /******************* RECEBIMENTO DE id_k_Base nativo *********************************************************************/
                    V[i] = base_SEP_coleta[i].V_base; //Se ele nunca tiver sido preenchido então vai receber zero, i não pode ser a Base_1!
                        if(V[i] == 0){
                            full_bases++; //Já sano o problema pela raiz, pois se entrou tanto para TR como para LT pq a base lado a lado vai ser determinada
                        }

                    id_k_Base_Buffer1 = base_SEP_coleta[i].id_k_Base; //se não preenchido será zero

                    //CRÍTICO, A TENSÃO DE BASE DEVE ESTAR SEMPRE NO MESMO LADO DA TENSÃO DO PRIMÁRIO (CONDICIONAL QUE ESTABELECI PARA CALCULAR)
                    //CONTUDO NÃO TENHO COMO ESTABELECER ESSE CRITÉRIO PARA O USUÁRIO, ELE PODE JOGAR TANTO NO PRIMÁRIO QUANTO PODE JOGAR NO SECUNDÁRIO
                    V[barra_Base_1] = base_SEP_coleta[barra_Base_1].V_base; //transferindo para um vetor
                    id_k_Base_Buffer2 = base_SEP_coleta[barra_Base_1].id_k_Base; //Lembre-se que esse id_k_Base foi setado em 1 >>> V[6].id_k_Base = 1

                    laco_2++;

                    //IupMessagef("Aviso!", "IF id_k_Trafo == 1 e id_k_LT == 1 acionado");
                    //IupMessagef("Aviso!", "A barra %d tem um id_k_Trafo do ramo (%d:%d) é igual a %d", i, barra_Base_1, i, id_k_Trafo);
                    //IupMessagef("Aviso!", "A barra %d tem um id_k_LT do ramo (%d:%d) é igual a %d", i, barra_Base_1, i, id_k_LT);

    //somente para LT

                    //O BUFFER 1 NULO E É QUEM QUE CONDUZ O DESFECHO DO LAÇO 1
                    /****************** CONDICIONAIS PARA EXISTÊNCIA DE UMA LT NO RAMO ********************************************************/
                    //Se ele enxergou uma LT entre 6:1, ou 5:0, id_k_LT é 1...se o buffer for diferente de 2 e diferente de zero, então carrega
                    //Existe LT, mas não existe TR neste ramo Barra_Base_1:i
                    if( (id_k_LT == 1 && id_k_Trafo != 1) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1) ) //(id_k_LT == 1 && id_k_Trafo != 1 && id_k_Base_Buffer1 == 0) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1 && id_k_Base_Buffer1 == 0)
                    {
                        //V[2] = carrega V[3], ramo bloqueado
                        V[i] = base_SEP_coleta[barra_Base_1].V_base; //Não há relação de transformação, mesma tensão da base 1
                        base_SEP_coleta[i].V_base = V[i]; //base 2, com possibidade de continuar usando V[i] agora diferente de zero
                        base_SEP_coleta[i].id_k_Base = id_k_Base_Buffer2; //Laço 1
                        id_k_Base_Buffer1 = base_SEP_coleta[i].id_k_Base; //dar continuidade ao código

                        if(depurar_base==1){
                        IupMessagef("Aviso!", "MONITORAR - TENSÃO VIA LT - A tensão de base da barra %d é V[%d] = %.2f kV", i, i, V[i]);
                        }
                        IupMessagef("Aviso!", "A tensão de base da barra %d é V[%d] = %.2f kV", i, i, V[i]);

                    }



                    /************* OU O ERRO ESTÁ LÁ NO LAÇO AO AO DEIXAR DE FAZER id_k_Base = 2 na barra 1 do par 2:1 *****/
                    //ERA PRA TER ENTRADO AQUI

    //somente para trafo

                    /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UM TRAFO NO RAMO ********************************************************/
                    if( (id_k_LT != 1 && id_k_Trafo == 1) || ( id_k_LT_Simetric != 1 && id_k_Trafo_Simetric == 1) ){//id_k_Base_Buffer1 == 0) //Existe TR, mas não existe LT neste ramo Barra_Base_1:i
                        //Se for um trafo - de cara já define id_k_Base para V[i] igual a 1
                        base_SEP_coleta[i].id_k_Base = id_k_Base_Buffer2; //Laço 1 = valor fixo = 1, o Buffer 1 que é variável

                        if(V[i] != 0 || V[barra_Base_1] != 0){ //Como não estou na LT, quer dizer que V[i] ainda é zero no laço 1

                            if(V[i] == 0){ //ELE ENTRA AQUI TRAFO 2:1
                                V_base_Buffer1 = V[barra_Base_1]; // entre 6:10, seria 5:9, V[i=5] e V[base1]
                                V_base_Buffer2 = V[i];   //V[i] foi inicializado a pouco acima, com zero, se TR não existe        //CUIDADO, não confunda barra_Base_1 com size_SEP_bars

                            //Exemplo system4D eu lancei a tensão de base na barra 1 e o trafo de 2:1
                            //V[barra_Base_1] = V[1] = 13,8kV
                            //V[i] = V[2] = 69kV, pois i != barra_Base_1

                                if(depurar_base==1){
                                IupMessagef("Aviso!", "A tensão de buffer 1 da barra %d é igual a %.2f kV", barra_Base_1, V_base_Buffer1); //barra 3
                                IupMessagef("Aviso!", "A tensão de buffer 2 da barra %d é igual a %.2f kV", i, V_base_Buffer2); //barra 2
                                }

                            }
                            //NÃO FUNCIONAL NESTE LAÇO
                         //   if(V[i] != 0){ //SITUAÇÃO NÃO É FUNCIONAL NO LAÇO 1
                           //     V_base_Buffer1 = V[barra_Base_1];   //Laço 1 fixa a base 1 como primário              //CUIDADO, não confunda barra_Base_1 com size_SEP_bars
                             //   V_base_Buffer2 = V[i]; //ESTA É A INCOGNITA!


                            //Não está a pegar nenhuma referência do clique!
                            //Resolver isso é fazer


                            //Como já foi acionado a função do trafo, não há interesse em analisar a LT
                            float Vn1;  //é a tensão da barra 2, ramo 2:1 >>>> id_k_Trafo == 1
                            float Vn2; //é a tensão da barra 1, ramo 2:1 >>>>> id_k_Trafo == 1

                            /*** \JUSTIFICATIVA
                                \CLICK- \INICIO = PRIMÁRIO
                                \CLICK- \FIM = SECUNDÁRIO
                            ***/

                            //SÓ TEM COMO AFIRMAR QUE ESTÁ NO PRIMÁRIO SE EU LANÇASSE A TENSÃO DE BASE SEMPRE NO PRIMÁRIO!

                            //Como lancei 2:1 direto não entra aqui, pois id_k_Trafo[1][2] = 2, no caso o par fixado para análise radial é [barra_Base_1][i]
                            if(id_k_Trafo == 1 && id_k_Trafo_Simetric == 2) //Base tá no primário      estranho tinha feito certo, note que está afirmando que lancei a base na barra 2, mas não, lancei na barra 1
                            {
                                //A coleta errada é impossível, no caso as coordenadas espelham quando id_k_Trafo é lançado de trás para frente
                                Vn1 = matrix_struct[barra_Base_1][i].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                Vn2 = matrix_struct[barra_Base_1][i].trafo_indices.Vt_nominal_secundario;

                                //precisa ter dois ifs, para ver se o número é maior ou menor...pensar

                                if(depurar_base==0){
                                //IupMessagef("Aviso!", "MONITORAR - IF A: A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", barra_Base_1, i, barra_Base_1, Vn1);
                                //IupMessagef("Aviso!", "MONITORAR - IF B: A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", barra_Base_1, i, i, Vn2);
                                }



                            }

                            if(id_k_Trafo == 2 && id_k_Trafo_Simetric == 1) //Base tá no secundário ... coordenadas espelhadas
                            {
                                 Vn1 = matrix_struct[i][barra_Base_1].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                 Vn2 = matrix_struct[i][barra_Base_1].trafo_indices.Vt_nominal_secundario;

                                 //olha o texto IF A2 da depuração, note que é i:barra_Base_1, ou seja, vai ser impresso extamente o que diz o texto

                                //Atualização 06jul22
                                //Vn1 = matrix_struct[barra_Base_1][i].trafo_indices.Vt_nominal_secundario;
                                //Vn2 = matrix_struct[barra_Base_1][i].trafo_indices.Vt_nominal_primario;

                                if(depurar_base == 0){
                            //IupMessagef("Aviso!", "MONITORAR - IF A2: A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, barra_Base_1, i, Vn1);
                                //IupMessagef("Aviso!", "MONITORAR - IF A2: A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, barra_Base_1, i, Vn2);
                            //IupMessagef("Aviso!", "MONITORAR - IF B2: A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, barra_Base_1, barra_Base_1, Vn2);
                                //IupMessagef("Aviso!", "MONITORAR - IF B2: A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, barra_Base_1, barra_Base_1, Vn1);
                                }
                                //raciocínio: i, barra_Base_1, i, Vn1); ... dos dois primeiros o primeiro é o primário, e o segundo é o secundário!
                            }

                            //Note que agora o Vn1 e Vn2 foram tratados ou filtrados, podendo ser utilizados como bem entender!



                            //ENVIO DAS TENSÕES


                            //Se lancei o trafo 2:1 direto (anti-simétrico) o id_k_Trafo não entra aqui pq o par fixado é 1:2, id_k_Trafo[1][2] = 2
                            if(id_k_Trafo == 1) //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                            {
                                //V_base_Buffer1: primário - fixo devido ao laço 1  //5
                                //V_base_Buffer2: secundario - incógnita = V[i]     //4

                                //V_base_Buffer1 = V[barra_Base_1]
                                //V_base_Buffer2 = V[i]
                                //V_base_Buffer1/V_base_Buffer2 = Vn1/Vn2

                                V_base_Buffer2 = (Vn2/Vn1)*V_base_Buffer1;

                                /*** O GARGALO É QUE A BASE DEVE SER LANÇADA NO PRIMÁRIO DO TRAFO (QUALQUER TRAFO) ***/

                                //Se o laço corre 5:4 e o usuário clicou 5:4, o trafo é anti-simétrico e a base coincide com o primário em V[5]
                                /****** \Envio \Base - \primario e \primario *****/
                                Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer1, barra_Base_1, i); //lembrando que a primeira coordenada é vinculada ao duplo primário
                                //Note que até o fim dessa rotina o resultante é V[i] e não V[j], contudo o foco não é determinar V[i] ou V[j], mas enviar o par de primários
                                //com a posição vetorial exata


                            }
                            if(id_k_Trafo == 2) //id_k_Trafo_Simetric == 1
                            {
                                //Vn1 = V[2] = 69kV
                                //Vn2 = V[1] = 13,8kV
                                //V_base_Buffer1 = 13,8kV (tensão de base)

                                //Vn1 = V[3] = 69kV
                                //Vn2 = V[1] = 13,8kV
                                //V_base_Buffer1 = 13,8kV (tensão de base)

                                //V_base_Buffer1/V_base_Buffer2 = Vn1/Vn2  <<< na real aqui está errado, ambos Vn1 e V_base_Buffer2 devem estar no primário, pois se seguir a lógica da fixação de tensão de base em buffer1

                                //Seguindo a lógica dos reversa (não a de índices) = V_base_Buffer2 é o primário
                                //V_base_Buffer2/V_base_Buffer1 = Vn1/Vn2
                                V_base_Buffer2 = (Vn1/Vn2)*V_base_Buffer1;  //você enxerga este secundário como sendo o primário: V_base_Buffer2
                                //Vbase2

                                //Agora o envio não é do Vn1 como primário, mas o Vn2 como primário

                                //Se o laço corre 5:4 e o usuário clicou 4:5, o trafo é simétrico e a base em V[5] NÃO coincide com o primário em V[4]
                                //outrora definido Vn1 coomo primário[5][4] passa a ser virtualmente o secundário, e Vn2 passa a ser o primário
                                /****** \Envio \Base - \primario e \primario *****/
                                           //comentado loko v
                                //Calc_Positiva_Xeq_TR1_pu(Vn2, V_base_Buffer2, i, barra_Base_1);//mudança básica o trafo rotaciona então envia Vn2
                                                                                                 //lembrando que a primeira coordenada é vinculada ao duplo primário
                                Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer2, i, barra_Base_1); //REUTILIZÁVEL PARA SEQUÊNCIA ZERO
                            }

                            V[i] = V_base_Buffer2;
                            base_SEP_coleta[i].V_base = V[i]; //faltou esta linha, universalizar para outras
                                                              //princípio do laço 1 é irradiação, logo i é sempre o elemento a se determinar


                           IupMessagef("Aviso!", "A tensão de base da barra %d é igual a V[%d] = %.2f kV", i, i, V[i]); //i = desconhecida!


                        } //Relaçao de transformação

                    } //Só Trafo


                } //Trafo ou LT
                /****
                if(id_k_Gerador == 1 || id_k_Motor == 1) //LEMBRE-SE, TEM UMA PENDÊNCIA EM AVERIGUAR SE ESTÁ PREENCHENDO CORRETO, 1 É PARA ELEMENTO CLICADO, 2 É PARA SIMÉTRICO
                {
                    int passa = 0;
                    passa++;
                    //Base já foi definida
                }
                ****/

            } //i_Barra != i

        } //fim do laço 1 ou ramos radiais a barra de base

        //float V_base_exibicao[16];


    while (full_bases+1 < size_SEP_bars_OLD+1){//abaixo o valor informado vai dá menor, mas aqui incrementa então no informado assuma +1
    /**** LAÇO 2 --- SÃO LAÇOS EM COLUNAS. É AQUILO QUE RASCUNHEI EM PAPEL, ASSIM QUE FIZER O MÁXIMO POSSÍVEL NO LAÇO 1, n = barra de base, É REINICIADO DO COMEÇO, NA COLUNA 1:1-1:n, E SEGUE 2:1-2:n, n:1-n:n ****/

        if(depurar_base == 1){

            /******/
            IupMessage("Aviso!", "INÍCIO DO LAÇO 2 - TR E LT - A função Calc_Bases_SEP foi inicializada - Laço 2");
            IupMessage("Aviso!", "AS TENSÕES DE BASES SÃO:");

            for(i = 1; i < size_SEP_bars_OLD+1; i++){

                IupMessagef("Aviso!", "V_base[%d] = %.2f kV", i, base_SEP_coleta[i].V_base);
            }
            IupMessagef("Aviso!", "O valor de full_bases = %d e size_bars+1 = %d", full_bases, size_SEP_bars_OLD+1);


        }

        //LEMBRE-SE, AINDA TEM O LAÇO 2.3, LÁ EMBAIXO, SE JÁ TIVER SIDO CALCULADO AS BASES DO TRAFO VAI PRA LÁ BUFFER_1 E 2 = 1
        if(laco_2 != 0){ //como as bases serão carregadas um única vez nada demais por aqui ... starta assim que finalizar o laço 1

            for(i = 1; i < size_SEP_bars_OLD+1; i++){
                for(j = 1; j < size_SEP_bars_OLD+1; j++){ //ELEVANDO A INDEXAÇÃO, POIS A INDEXAÇÃO DAS MEMÓRIAS DE STRUCT ESTÃO IGUAIS AO DA LIST STRING FULL

                    if(i != j){

                        //O laço varia j e fixa o i, logo a busca ocorre nas barras j

                        //CAPTURANDO O PAR DE BARRAS QUE FOI LANÇADO NO SEP
                        id_k_Trafo = matrix_struct[i][j].trafo_indices.id_k_Trafo; //primeiro a carregar é o 1:2
                        id_k_LT = matrix_struct[i][j].LT_indices.id_k_LT;

                        //INVERTENDO AS COORDENADAS
                        id_k_Trafo_Simetric = matrix_struct[j][i].trafo_indices.id_k_Trafo; //CRÍTICO, falta ativar o simétrico para i e j, laço 2 agora
                        id_k_LT_Simetric = matrix_struct[j][i].LT_indices.id_k_LT;

                        //ISSO VAI DEPENDER DO QUE VC LANÇOU, AQUI QUE COMEÇA A TESTAGEM

                        //ESTÁ MOSTRANDO/PRÉ EXIBINDO O MODO POR DETRÁS, MAS NÃO TEM NENHUMA CONCLUSÃO AINDA
                        if(depurar_base==0){
                        //IupMessagef("Aviso!", "LAÇO 2 - A barra %d do ramo (%d:%d) tem um id_k_Trafo igual a %d", j, i, j, id_k_Trafo); //ISSO VAI DEPENDER DO QUE VC LANÇOU, AQUI QUE COMEÇA A TESTAGEM
                        //IupMessagef("Aviso!", "LAÇO 2 - A barra %d do ramo (%d:%d) tem um id_k_LT igual a %d", j, i, j, id_k_LT);
                        }

                        //No cenário 1:3, 3 tem base determinada no laço 1, logo abaixo Buffer1[j] = 1 = conhecida, Buffer2[i] = 2 = desconhecida
                        //A base desconhecida é pela frente, o elemento fixo que no caso tem base desconhecida! E não tem como rodar 1:1 para achar!

                        //Note que de forma geral está pegando um par ordenado de forma independente
                        id_k_Base_Buffer1 = base_SEP_coleta[j].id_k_Base; //No laço 2 vai ser 2 ou 1 ...cenário hipotético = conhecida
                        id_k_Base_Buffer2 = base_SEP_coleta[i].id_k_Base; //No laço 2 vai ser 2 ou 1 ...cenário hipotético = desconhecida

                        //Indexs id_k_Base_Buffer
                            //1 = conhecida
                            //2 = desconhecida
                                                                                                            // 2                    //1
                        if(depurar_base==0){
                        //IupMessagef("Aviso!", "BUFFER 1 E 2 - BASES - O id_k_Base [j]=[%d] é %d e o id_k_Base [i]=[%d] é %d", j, id_k_Base_Buffer1, i, id_k_Base_Buffer2);
                        }
                                                                                                            // 2                    //1
                        //Indexs id_k_Base_Buffer
                            //1 = conhecida
                            //2 = desconhecida



                        /****************** CONDICIONAL PARA INEXISTÊNCIA DE RAMO ********************************************************/
                        if( (id_k_Trafo == 0 && id_k_LT == 0) ) //se não existe elemento não se fala em id_k = 2, e nem 1 ... && (id_k_Trafo != 1 && id_k_LT != 1)
                        {
                            //Se anteriormente id_k_Base já estiver com 2 ainda ficará com 2
                            //caso de 3 barras se a base estiver no 3, e fizer 1:3 no início do laço 2, então muda-se de 1 para 3 no id_k_Base da base 3
                            //if(base_SEP_coleta[j].id_k_Base != 1) //TALVEZ TAMBÉM TENHA QUE COLOCAR i

                                //No rascunho deixo claro, se já tiver 1, mantenha, e não implementei isso
                                if(id_k_Base_Buffer1 != 1) //se não fizer nada vai manter
                                {
                                    base_SEP_coleta[j].id_k_Base = 2; //Mantêm 2, mas agora estou olhando para j ...lá atrás i = 5, recebeu 2, agora virou j = 5
                                    if(depurar_base == 1){
                                    IupMessage("Aviso!", "As tensões de bases são desconhecidas por enquanto ou elemento não lançado à barra!");
                                    }
                                }
                                if(id_k_Base_Buffer1 == 1 && id_k_Base_Buffer2 != 1)
                                {
                                    if(depurar_base == 1){
                                    IupMessagef("Aviso!", "A tensão de base conhecida V[%d] = %.2f já é conhecida", j, base_SEP_coleta[j].V_base);
                                    }
                                }
                                if(id_k_Base_Buffer1 == 1 && id_k_Base_Buffer2 == 1) //transformei isso lá no final do laço 2 em um laço 2.3 pq o trafo fica ilhado para LTs em suas extremidades
                                {
                                    if(depurar_base == 1){
                                    IupMessagef("Aviso!", "As tensões de bases conhecidas são V[%d] = %.2f e V[%d] = %.2f já são conhecidas", i, base_SEP_coleta[i].V_base, j, base_SEP_coleta[j].V_base);
                                    }
                                }
                        }



                        //if( id_k_Trafo == 1 || id_k_LT == 1  ) //segunda parte, != 2, para mitigar analisar simétricos  ...&& (id_k_Trafo != 2 && id_k_LT != 2)
                        if( ( id_k_Trafo == 1 || id_k_LT == 1) || (id_k_Trafo_Simetric == 1 || id_k_LT_Simetric == 1) )
                        {

                            if(id_k_Base_Buffer1 == 1 && id_k_Base_Buffer2 == 1){ //caso de 3 barras de LTs com base na barra 1 barras (1:2) devem entrar aqui

                                if(depurar_base == 1){
                                IupMessagef("Aviso!", "As bases das barras %d e %d já são conhecidas", i, j);
                                IupMessagef("Aviso!", "As tensões de bases conhecidas são V[%d] = %.2f e V[%d] = %.2f já são conhecidas", i, base_SEP_coleta[i].V_base, j, base_SEP_coleta[j].V_base);
                                }

                            } //PULA IF idk_Base: 1 e 1


                            if(id_k_Base_Buffer1 == 2 && id_k_Base_Buffer2 == 2){

                                if(depurar_base == 1){
                                IupMessagef("Aviso!", "O id_k_Base = %d, foi mantido para as barras %d e %d\n Nenhuma barra do ramo (%d:%d) tem bases conhecidas", id_k_Base_Buffer1, i, j, i, j);
                                }

                            } //PULA IF idk_Base: 1 e 1


                            //LEMBRE-SE O LAÇO 1 É OBRIGATÓRIO SER EXECUTADO PRIMEIRA, E DEVE RETORNAR ALGUMA COISA, DURANTE OS TESTES, PQ SEMPRE PEGAREI O NÓ CONHECIDO
/*** LAÇO 2.1
/******************* ROTINA SOMENTE PARA i fixa desconhecida *************************************************************************************/
            if(id_k_Base_Buffer1 == 1 && id_k_Base_Buffer2 == 2) //CENÁRIO QUE A BARRA FIXA É DESCONHECIDA (BARRA i) --- LAÇO 2.1
            {                                                    //buffer1 é em j, buffer2 é em i
                                if(depurar_base == 0){
                                //IupMessagef("Aviso!", "LAÇO 2.1 - CÁLCULO DA BASE %d", i); //Pela frente do par 1:3
                                }

                                //Captura y = 3
                                V[j] = base_SEP_coleta[j].V_base; //Esta tensão foi calculada no laço 1

                                //Captura x = 1
                                V[i] = base_SEP_coleta[i].V_base; //Se ele nunca tiver sido preenchido então vai receber zero!
                                    if(V[i] == 0){
                                        full_bases++; //Já sano o problema pela raiz, pois se entrou tanto para TR como para LT pq a base lado a lado vai ser determinada
                                    }


                                //Vi = 1 - desconhecida
                                //Vj = 2 - conhecida
            //somente para LT
                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UMA LT NO RAMO ********************************************************/

                                //if(id_k_LT == 1 && id_k_Trafo != 1) //Existe LT, mas não existe TR neste ramo Barra_Base_1:i //... && id_k_Base_Buffer1 == 0
                                if( (id_k_LT == 1 && id_k_Trafo != 1) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1) ) //(id_k_LT == 1 && id_k_Trafo != 1 && id_k_Base_Buffer1 == 2) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1 && id_k_Base_Buffer1 == 2)
                                {
                                    //A fixa desconhecia recebe a tensão base da conhecida
                                    V[i] = base_SEP_coleta[j].V_base; //Não há relação de transformação, captura a base do laço 1
                                    base_SEP_coleta[i].V_base = V[i]; //Agora a barra fixa desconhecida obtêm a tensão de base
                                    //A fixa desconhecida recebe o id_k_Base da conhecida j
                                    base_SEP_coleta[i].id_k_Base = id_k_Base_Buffer1; //Laço 2 = agora o status da barra fixa muda de 2 para 1
                                    id_k_Base_Buffer2 = base_SEP_coleta[i].id_k_Base; //dar continuidade ao código, id_k_Base atualizado para barra fixa

                                    //IupMessagef("Aviso!", "A tensão de base da barra %d é igual a V[%d] = %.2f kV", i, V[i]);
                                    //IupMessagef("Aviso!", "MONITORAR LT - LAÇO 2.1 - A tensão de base da barra %d é V[%d] = %.2f kV", i, i, V[i]);
                                    IupMessagef("Aviso!", "LAÇO 2.1 - LT - A tensão de base da barra %d é V[%d] = %.2f kV", i, i, V[i]);
                                }

                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UM TRAFO NO RAMO ********************************************************/
            //somente para TR
                                //if(id_k_LT != 1 && id_k_Trafo == 1){ //Existe TR, mas não existe LT neste ramo Barra_Base_1:i ...  && id_k_Base_Buffer1 == 0
                                if( (id_k_LT != 1 && id_k_Trafo == 1) || ( id_k_LT_Simetric != 1 && id_k_Trafo_Simetric == 1) ){
                                    //Se for um trafo - de cara já define id_k_Base para V[i] igual a 1
                                    base_SEP_coleta[i].id_k_Base = id_k_Base_Buffer1; //Laço 2 = valor fixo, o Buffer 2 que é variável - CENÁRIO 1/2

                                    if(V[i] != 0 || V[j] != 0){ //A tensão V[i] é nula - inicilizada no começo da função, e a tensão V[j] é obtida do laço 1

                                        if(V[i] == 0){ //A tensão V[i] é nula - inicilizada no começo da função
                                            V_base_Buffer1 = V[i]; //x = 1 //tensão desconhecida
                                            V_base_Buffer2 = V[j]; //y = 3 //tensão conhecida

                                            if(depurar_base == 1){
                                            IupMessagef("Aviso!", "A tensão de buffer1 da barra %d é igual a %.2f kV", i, V_base_Buffer1);
                                            IupMessagef("Aviso!", "A tensão de buffer2 da barra %d é igual a %.2f kV", j, V_base_Buffer2);
                                            }

                                        }

                                        //MONITORAR, MAS NECESSARIAMENTE SE A BARRA É DESCONHECIDA, FICARÁ COM V[i] = 0

                                        float Vn1 = matrix_struct[i][j].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        float Vn2 = matrix_struct[i][j].trafo_indices.Vt_nominal_secundario;

                                        float Vn1_id2 = matrix_struct[j][i].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        float Vn2_id2 = matrix_struct[j][i].trafo_indices.Vt_nominal_secundario;

                                        //Se o usuário lançou um trafo nas barras 1:3 ...lembra do exemplo pow, mentaliza --- ele existe, certo!
                                        //Então também foi definido pelo usuário o primario e secundário, suponha 1:3, e não 3:1
                                        //Logo 3:1 recebeu o id_k_Trafo = 2, enquanto o 1:3 recebeu o id_k_Trafo = 1
                                        //Independente do laço 2 ser 1:3 ou 3:1, a lógica dos id_k_Base continuram sendo 1 e 2, a rotina de cálculo
                                        //é independente, o if do id_k_Base que autorizou o cálculo de tensão de base está aguardando somente V´[i]

                                        /*** NOTE AGORA ABAIXO É COLETADO O SIMÉTRICO PARA SE DEFINIR O CÁLCULO USANDO O PRIMÁRIO E SECUNDÁRIO ****/
                                        int id_k_Trafo_simetric = matrix_struct[j][i].trafo_indices.id_k_Trafo; //captura o trafo simétrico, 3:1

                                        //Aqui passou tranquilo pela exibição

                                        if(depurar_base == 1){
                                        IupMessagef("Aviso!", "A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, i, Vn1); //Lá na hora que lançou o usário definiu i ou id_x como primário!
                                        IupMessagef("Aviso!", "A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, j, Vn2);

                                        IupMessagef("Aviso!", "A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", j, i, j, Vn1_id2); //Lá na hora que lançou o usário definiu i ou id_x como primário!
                                        IupMessagef("Aviso!", "A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", j, i, i, Vn2_id2);
                                        }

                                        //if(id_k_Trafo == 1) //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        if(id_k_Trafo == 1 && id_k_Trafo_Simetric == 2)
                                        {
                                            //Laço 2.1. = Pela frente do par 1:3, incogita é V[1]
                                            //V_base_Buffer1: primário - barra fixa i = incognita = V[i] = tensão de base desconhecida
                                            //V_base_Buffer2: secundario - barra móvel j = V[j] = tensão de base conhecida

                                            //Vn1/Vn2 = V_base_Buffer1/V_base_Buffer2

                                            V_base_Buffer1 = (Vn1/Vn2)*V_base_Buffer2;//o V_base_Buffer1 = V_base_Buffer1_i = lado primário, onde i:j de iteração coincide com i:j de lançamento
                                            //anti-simétrico

                                            //Se o laço corre 1:3 e o usuário clicou 1:3, o trafo é anti-simétrico e a base em V[1] coincide com o primário em V[1]
                                            /****** \Envio \Base - \primario e \primario *****/
                                            Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer1, i, j); //O primário é Buffer 1 com a posição i (até então desconhecida)
                                                                                                 //lembrando que a primeira coordenada é vinculada ao duplo primário

                                        }
                                        //if(id_k_Trafo == 2)
                                        if(id_k_Trafo == 2 && id_k_Trafo_Simetric == 1)
                                        {

                                            //Laço 2.1.
                                            //V_base_Buffer1: primário - barra fixa i = incognita = V[i] = tensão de base desconhecida
                                            //V_base_Buffer2: secundario - barra móvel j = V[j] = tensão de base conhecida

                                            //V_base_Buffer1/V_base_Buffer2 = (Vn1/Vn2); //OLD --- não ia dar certo nunca, tava errado a coleta de Vn1 e Vn2
                                            //V_base_Buffer2/V_base_Buffer1 = (Vn1/Vn2); //CUUUUUIDADO, o V_base_Buffer1 agora é o secundário!!!!!!
                                            //V_base_Buffer1/V_base_Buffer2 = Vn2_id2/Vn1_id2; //secundário/primário = secundário/primário

                                            //Lembre-se V_base_Buffer1 = V_base_Buffer1_i está no lado i da iteração, no caso recai no secundário do lançamento i:j

                                            //V_base_Buffer1 = (Vn2/Vn1)*V_base_Buffer2; //só inverte a relação de tensão <<< OLD
                                            V_base_Buffer1 = (Vn2_id2/Vn1_id2)*V_base_Buffer2; //só inverte a relação de tensão <<< OLD
                                            //simétrico

                                            /*** SYSTEM 4F

                                                1 - Ao fazer a base na barra 4 calcula-se a base 3
                                                2 - lançando 1:3 temos primário em 1 e secundário em 3 (Yat-D)
                                                3 - Então ao finalizar o laço em 4 inicia-se o laço em 1, segue 1:2 ambos desconhecidos
                                                4 - Na iteração 1:3 buffer1_j é index 1 (conhecido) e buffer2_i é index 2 (desconhecido)
                                                5 - Atenha-se que o i:j deste laço não é o i:j do lançamento! Então em particular i:j do lançamento coincide com i:j deste laço
                                                6 - Ou seja, primário está em i, logo Vn1_i e V_buffer1_i coincidem (note é V_buffer1 e não buffer1) - e V_buffer1_i é i deste laço, então no id_k_Trafo = 1 anterior calcula-se V_buffer1_i atrelado ao buffer2_i, e tudo certo, é enviando Vn1 e V_buffer1 que estão do mesmo lado, lado i.

                                                7 - Se tivesse lançado i:j 3:1 então este i:j, deste laço, não mais se coincidem, logo temos id_k_Trafo = 2
                                                8 - Contudo o buffer1_j ainda é 1 (conhecido) e buffer2_i ainda é 2 (desconhecido) - e por isso estamos no laço 2.1
                                                9 - Com id_k_Trafo = 2 o secundário que passa a ser desconhecido e ele representa o V_buffer1 (em i, deste laço i:j), ou seja, V_buffer1_i
                                                10 - então logo acima, vc tem que forçar a fórmula com V_base_buffer1 como secundário, além disso o Vn1 é o secundário (Ahhhhhhhh caiu a ficha, Vn1 = Vn1_i)
                                                11 - ERRO TOSCO NO LAÇO 2. LÁ EM CIMA, no laço 1, é definido Vn1 duas vezes (barra_base, i) e (i, barra_base) e por isso fica certinho.
                                                12 - NOTE QUE V[i] e V[j] nada tem a ver com Vn1 e Vn2, aqueles servem para V_buffer1 e V_buffer2

                                                13 - Depurei, confirmado, o Vn1 e Vn2 não existem para a iteração i:j igual a 1:3, ao lançar i:j igual a 3:1
                                                14 - então criei o Vn1_id2 e Vn2_id2 atrelado o id_k_Trafo = 2




                                            ***/

                                            //Se o laço corre 1:3 e o usuário clicou 3:1, o trafo é simétrico e a base em V[1] NÃO coincide com o primário em V[3]
                                            /****** \Envio \Base - \primario e \primario *****/
                                            Calc_Positiva_Xeq_TR1_pu(Vn1_id2, V_base_Buffer2, j, i); //O primário é Buffer 1 com a posição i (até então desconhecida)
                                                                                                 //lembrando que a primeira coordenada é vinculada ao duplo primário
                                            //Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer2, j, i); //nem vai precisar mexer, pq a relação de tensão já adaptou, monitore

                                            //12 de julho de 2022, sim o V_base_Buffer2 é o primário para o i:j de lançamento, pois V_base_Buffer2 = V[j]

                                        }

                                        V[i] = V_base_Buffer1; //agora a barra i, barra fixa desconhecida, recebe a tensão de base após a relação do Trafo

                                        base_SEP_coleta[i].V_base = V[i]; //Faltava esta linha, estava sem retenção

                                        IupMessagef("Aviso!", "A tensão de base da barra %d é igual a V[%d] = %.2f kV", i, i, V[i]); //i = desconhecida!

                                    } //Relaçao de transformação para barra fixa i --- pela frente

                                } //Só Trafo para barra fixa i --- pela frente

                            } // Fim do IF da barra fixa i --- pela frente

/*** LAÇO 2.2
/******************* ROTINA SOMENTE PARA j móvel desconhecida *************************************************************************************/
            if(id_k_Base_Buffer1 == 2 && id_k_Base_Buffer2 == 1) //CENÁRIO QUE A BARRA MÓVEL É DESCONHECIDA --- LAÇO 2.2
            {
                                if(depurar_base == 0){
                                //IupMessagef("Aviso!", "LAÇO 2.2 - CÁLCULO DA BASE %d", j); //Por detrás do par 1:3
                                }


                                //Captura y = 4 = recebe tensão zero
                                V[j] = base_SEP_coleta[j].V_base; //Esta tensão foi calculada no laço 1, ou zerada ou preenchida pelos possíveis
                                                                  //No system4F a barra 2:2 fica zerada com


                                    if(V[j] == 0){
                                        full_bases++; //Já sano o problema pela raiz, pois se entrou tanto para TR como para LT pq a base lado a lado vai ser determinada
                                    }



                                //Captura x = 1 = recebe a tensão calculda acima, i fixa desconhecida
                                V[i] = base_SEP_coleta[i].V_base; //Só que agora o V[1] já é conhecido do par 1:4

                                //Vj = 2 - desconhecida
                                //Vi = 1 - conhecida

                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UMA LT NO RAMO ********************************************************/

                                //if(id_k_LT == 1 && id_k_Trafo != 1) //Existe LT, mas não existe TR neste ramo Barra_Base_1:i //... && id_k_Base_Buffer1 == 0
                                if( (id_k_LT == 1 && id_k_Trafo != 1) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1) ) //(id_k_LT == 1 && id_k_Trafo != 1 && id_k_Base_Buffer1 == 2) || (id_k_LT_Simetric == 1 && id_k_Trafo_Simetric != 1 && id_k_Base_Buffer1 == 2)
                                {
                                    //A móvel desconhecia recebe a tensão base da conhecida
                                    V[j] = base_SEP_coleta[i].V_base; //Não há relação de transformação, captura a base do laço 2 ou 1
                                    base_SEP_coleta[j].V_base = V[j]; //Agora a barra fixa desconhecida obtêm a tensão de base
                                    //A móvel desconhecida recebe o id_k_Base da conhecida i
                                    base_SEP_coleta[j].id_k_Base = id_k_Base_Buffer2; //Laço 3 = agora o status da barra móvel muda de 2 para 1...cuidado, não é id_k_Buffer1
                                    id_k_Base_Buffer1 = base_SEP_coleta[j].id_k_Base; //dar continuidade ao código, id_k_Base atualizado para barra movel

                                    //IupMessagef("Aviso!", "A tensão de base da barra %d é igual a %.2f kV", j, V[j]);
                                    if(depurar_base == 1){
                                    IupMessagef("Aviso!", "MONITORAR LT - LAÇO 2.2 - A tensão de base da barra %d é V[%d] = %.2f kV", j, j, V[j]);
                                    }
                                    IupMessagef("Aviso!", "A tensão de base da barra %d é V[%d] = %.2f kV", j, j, V[j]);

                                }

                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UM TRAFO NO RAMO ********************************************************/
                                //if(id_k_LT != 1 && id_k_Trafo == 1){ //Existe TR, mas não existe LT neste ramo Barra_Base_1:i ...  && id_k_Base_Buffer1 == 0
                                if( (id_k_LT != 1 && id_k_Trafo == 1) || ( id_k_LT_Simetric != 1 && id_k_Trafo_Simetric == 1) ){
                                    //Se for um trafo - de cara já define id_k_Base para V[j] igual a 1
                                    base_SEP_coleta[j].id_k_Base = id_k_Base_Buffer2; //praticamente uma cópia da linha da LT acima, o que muda do laço 2 para o laço 3 é que recebe i = buffer1

                                    if(V[i] != 0 || V[j] != 0){ //A tensão V[i] é nula - inicilizada no começo da função, e a tensão V[j] é obtida do laço 1

                                        if(V[j] == 0){ //A tensão V[j], desconhecida, é nula - inicilizada no começo da função
                                            V_base_Buffer1 = V[i]; //x = 1 //tensão conhecida
                                            V_base_Buffer2 = V[j]; //y = 4 //tensão desconhecida

                                            if(depurar_base == 1){
                                            IupMessagef("Aviso!", "A tensão de buffer1 da barra %d é igual a %.2f kV", i, V_base_Buffer1);
                                            IupMessagef("Aviso!", "A tensão de buffer2 da barra %d é igual a %.2f kV", j, V_base_Buffer2);
                                            }

                                        }

                                        //MONITORAR, MAS NECESSARIAMENTE SE A BARRA É DESCONHECIDA, FICARÁ COM V[i] = 0

                                        float Vn1;
                                        float Vn2;



                                        if(id_k_Trafo == 1 && id_k_Trafo_Simetric == 2) //Base tá no primário
                                        {
                                            //A coleta errada é impossível, no caso as coordenadas espelham quando id_k_Trafo é lançado de trás para frente
                                            Vn1 = matrix_struct[i][j].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                            Vn2 = matrix_struct[i][j].trafo_indices.Vt_nominal_secundario;

                                            //precisa ter dois ifs, para ver se o número é maior ou menor...pensar

                                            if(depurar_base == 1){
                                            IupMessagef("Aviso!", "MONITORAR: A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, i, Vn1);
                                            IupMessagef("Aviso!", "MONITORAR: A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, j, Vn2);
                                            }

                                        }

                                        if(id_k_Trafo == 2 && id_k_Trafo_Simetric == 1) //Base tá no secundário ... coordenadas espelhadas
                                        {
                                             Vn1 = matrix_struct[j][i].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                             Vn2 = matrix_struct[j][i].trafo_indices.Vt_nominal_secundario;

                                            if(depurar_base == 1){
                                            IupMessagef("Aviso!", "MONITORAR-----: A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", j, i, j, Vn1);
                                            IupMessagef("Aviso!", "MONITORAR-----: A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", j, i, i, Vn2);
                                            }
                                            //raciocínio: i, barra_Base_1, i, Vn1); ... dos dois primeiros o primeiro é o primário, e o segundo é o secundário!
                                        }

                                        //PUTZ AQUI NO LAÇO 2.2 estava certo, gargalo era o laço 2.1 - 12jul22



                                        //ENVIO DAS TENSÕES


                                        if(id_k_Trafo == 1) //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        {
                                            //LAÇO 2.2 - Por detrás do par 1:3
                                            //V_base_Buffer1: primário - barra fixa i  = V[i] = tensão de base conhecida
                                            //V_base_Buffer2: secundario - barra móvel j = incognita = V[j] = tensão de base desconhecida

                                            //POSSO TER PEGO O CÓDIGO ERRADO - DESATUALIZADO, PQ LEMBRO DO RASCUNHO DAS FÓRMULAS, APAGUEI?
                                            //Vn1/Vn2 = V_base_Buffer1/V_base_Buffer2
                                            //Vn2/Vn1 = V_base_Buffer2/V_base_Buffer1 //rebater para obter o desconhecido

                                            V_base_Buffer2 = (Vn2/Vn1)*V_base_Buffer1;
                                            //anti-simétrico


                                            //Vn1 está do mesmo lado do V_base_Buffer1 = lado conhecido, logo V_base_Buffer1 = primário

                                            //Se o laço corre 1:3 e o usuário clicou 1:3, o trafo é anti-simétrico e a base em V[1] coincide com o primário em V[1]
                                            /****** \Envio \Base - \primario e \primario *****/
                                            Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer1, i, j); //O primário é Buffer 1 com a posição i (até então PREVIAMENTE CONHECIDA)
                                                                                              //lembrando que a primeira coordenada é vinculada ao duplo primário

                                        }


                                        if(id_k_Trafo == 2)
                                        {
                                            //É possível admitir que V_base_Buffer2 está no primário junto com Vn1 para o trafo simétrico
                                            V_base_Buffer2 = (Vn1/Vn2)*V_base_Buffer1; //só inverte a relação de tensão
                                            //simétrico

                                            //12jul22
                                            //Vn1 está do mesmo lado do V_base_Buffer2 = lado desconhecido, logo V_base_Buffer2 = primário

                                            //Se o laço corre 1:3 e o usuário clicou 3:1, o trafo é simétrico e a base em V[1] NÃO coincide com o primário em V[1]
                                            /****** \Envio \Base - \primario e \primario *****/
                                            //Calc_Positiva_Xeq_TR1_pu(Vn2, V_base_Buffer2, j, i); //O primário é Buffer 1 com a posição i (até então PREVIAMENTE CONHECIDA)
                                                                                                 //lembrando que a primeira coordenada é vinculada ao duplo primário
                                            //O laço 2.1 e laço 2.2 não muda absolutamente nada no referencial ao primário.
                                            Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer2, j, i); //Vn1 primário e Vj que é a base NO primário (desconhecida)
                                            //CORREÇÃO CRÍTICA, DE FATO É Vn1 e Vbuffer2
                                            //O id_k_buffer2 não está atrelado ao V_base_buffer2

                                        }



                                        V[j] = V_base_Buffer2; //agora a barra i, barra fixa desconhecida, recebe a tensão de base após a relação do Trafo
                                        base_SEP_coleta[j].V_base = V[j]; //faltou esta linha, universalizar para outras

                                        IupMessagef("Aviso!", "A tensão de base da barra %d é igual a V[%d] = %.2f kV", j, j, V[j]); //i = desconhecida!

                                    } //Relaçao de transformação para barra j --- por detrás

                                } //Só Trafo para barra j --- por detrás

                            } // Fim do IF da barra j --- por detrás // FIM-IF LAÇO 2.2





/*** LAÇO 2.3 - 09jul22 - Se for definido a base via LT antes de definir via TRAFO, então o trafo fica impossibilitado de calcular sua impedância
/******************* ROTINA SOMENTE PARA i fixa desconhecida *************************************************************************************/
            if(id_k_Base_Buffer1 == 1 && id_k_Base_Buffer2 == 1 && id_k_Trafo == 1) //ISSO JÁ ACONTECE LÁ NO COMECINHO, A DIFERENÇA É ROTINA DE ACIONAR AS FUNÇÕES DE CÁLCULO DE IMPEDÂNCIA
            {                                                   //Vou me focar somente no trafo direto (aquele que foi lançado de fato)

                                if(depurar_base == 0){
                                //IupMessagef("Aviso!", "LAÇO 3 - REBOTE - CÁLCULO DA IMPEDÂNCIA ILHADA");
                                }
            /*** \CUIDADO - pode acontecer de ser alculado as bases via LT de ambos lados do trafo, e o trafo ficar ilhado sem ter sua impedância ser calculada ***/


                                /*** TENSÕES DE BASE JÁ SÃO CONHECIDAS ***/

                                //Captura
                                V[j] = base_SEP_coleta[j].V_base; //Esta tensão foi calculada no laço 1 ou laço 2
                                                                  //Se ele nunca tiver sido preenchido então vai receber zero!

                                //Captura
                                V[i] = base_SEP_coleta[i].V_base; //Esta tensão foi calculada no laço 1 ou laço 2
                                                                  //Se ele nunca tiver sido preenchido então vai receber zero!

                                //CAIU A FICHA - AMBAS TENSÕES SÃO CONHECIDAS, NÃO TEM ESSA DE SOMENTE UMA SER, NO SYSTEM4G O TRAFO FICOU ILHADO POR CAUSA DAS DUAS LTS COM ÍNDICES MENORES
            //somente para LT
                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UMA LT NO RAMO ********************************************************/

                                //CENÁRIO ONDE SE OBTÉM A BASE VIA LT ANTES DE SE VERIFICAR VIA TRAFO, O QUE ACABA INVIABILIZANDO O CÁLCULO DA IMPEDÂNCIA DO TRAFO

                                /****************** CONDICIONAIS PARA EXISTÊNCIA DE SOMENTE UM TRAFO NO RAMO ********************************************************/
            //somente para TR
                                //if(id_k_LT != 1 && id_k_Trafo == 1){ //Existe TR, mas não existe LT neste ramo Barra_Base_1:i ...  && id_k_Base_Buffer1 == 0
                                if( (id_k_LT == 2 && id_k_Trafo == 1) && ( id_k_LT_Simetric == 2 && id_k_Trafo_Simetric == 2) ){
                                    //Se for um trafo - de cara já define id_k_Base para V[i] igual a 1
                                    //base_SEP_coleta[i].id_k_Base = id_k_Base_Buffer1; //NÃO PRECISA MAIS DISSO, PQ JÁ É CONHECIDO AO MENOS UM BUFFER

                                //AQUI SIM FOI UMA SACADA, SÓ PRECISO PEGAR O TRAFO DIRETO, onde i:j de lançamento coincide com i:j de iteração
                                //Assim Vn1 e V_base_Buffer1 de fato sempre estarão do mesmo lado - primário!

                                if(depurar_base == 1){
                                IupMessagef("Aviso!", "CÁLCULO DA IMPEDÂNCIA ILHADA %d", i); //
                                }



                                    if(V[i] != 0 && V[j] != 0){ //A tensão V[i] é nula - inicilizada no começo da função, e a tensão V[j] é obtida do laço 1
                                                                //É PARA ENTRAR AQUI
                                        V_base_Buffer1 = V[i]; //A questão é, só precisa que as tensões enviadas sejam do mesmo lado do trafo
                                        V_base_Buffer2 = V[j]; //

                                            if(depurar_base == 1){
                                            IupMessagef("Aviso!", "IF-ij - A tensão de buffer1 da barra %d é igual a %.2f kV", i, V_base_Buffer1);
                                            IupMessagef("Aviso!", "IF-ij - A tensão de buffer2 da barra %d é igual a %.2f kV", j, V_base_Buffer2);
                                            }



                                        //MONITORAR, MAS NECESSARIAMENTE SE A BARRA É DESCONHECIDA, FICARÁ COM V[i] = 0

                                        float Vn1 = matrix_struct[i][j].trafo_indices.Vt_nominal_primario; //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        float Vn2 = matrix_struct[i][j].trafo_indices.Vt_nominal_secundario;


                                        if(depurar_base == 0){
                                        //IupMessagef("Aviso!", "NOVO - A tensão nominal primária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, i, Vn1); //Lá na hora que lançou o usário definiu i ou id_x como primário!
                                        //IupMessagef("Aviso!", "NOVO - A tensão nominal secundária do trafo (%d:%d) na barra %d é igual a %.2f kV", i, j, j, Vn2);
                                        }

                                        //if(id_k_Trafo == 1) //Se liga, não existe Trafo n:n, isso é coordenada de máquina síncrona
                                        if(id_k_Trafo == 1 && id_k_Trafo_Simetric == 2)
                                        {


                                            if(depurar_base == 0){
                                            //IupMessagef("Aviso!", "TRAFO DIRETO");
                                            }

                                            //NÃO PRECISA CALCULAR NADA, É SÓ ENVIAR!!!!
                                            /****** \Envio \Base - \primario e \primario *****/
                                            Calc_Positiva_Xeq_TR1_pu(Vn1, V_base_Buffer1, i, j); //O primário é Buffer 1 com a posição i (até então desconhecida)
                                                                                                 //lembrando que a primeira coordenada é vinculada ao duplo primário

                                        }
                                    } //Vi && Vj, não nulo

                                } //id_ks de trafo = 1

                            } // Fim do IF - LAÇO 2.3


                        } //Trafo ou LT
                        /****
                        if(id_k_Gerador == 1 || id_k_Motor == 1) //LEMBRE-SE, TEM UMA PENDÊNCIA EM AVERIGUAR SE ESTÁ PREENCHENDO CORRETO, 1 É PARA ELEMENTO CLICADO, 2 É PARA SIMÉTRICO
                        {
                            int passa = 0;
                            passa++;
                            //Base já foi definida
                        }
                        ****/
                    } //i_Barra != i
                } //FOR i
            } //FOR j
        } //IF laco 2

}//While

/***
      Laço 1:
                Se barra da base for 1, fixa.
                barra_Base_1:1  >>> base_SEP_coleta[barra_Base_1].V_base
                barra_Base_1:2
                barra_Base_1:...
                barra_Base_1:n
***/
        /********** Só depois que for carregado o formulário, ou seja, só depois que for coletado todas as tensões, é que dispara a rotina de
                    para se definir todas as bases do SEP! ****************/
/***
      Laço 2:
                x 1:1  >>> descarta
                1:2
                1:3
                ...
                1:n

                        próximo
                .
                .
                .

                x n:n  >>> descarta
                n:2
                n:3
                ...
                n:n-1

***/


/***
      Laço 2.3:
                Se o trafo ficar ilhado ao se determinar as bases de ambos lados, pois fica impossibilitado de calcular a impedância

***/


}








/************************************************ MEMÓRIA LISTA CONCATENADA STRING FULL: disparo de item por item  ***************************/


/*****************************************(                  \FUNCTION \MEMORY \GERADOR \INDEX      )********************************************

***/





static int function_memory_gerador_id_k (Ihandle* ih, char *t, int i, int selected)
{

  static int passagem_bug = 0;

  passagem_bug++;

  //if(passagem_bug != 3){
      //IupMessage("Aviso sem repetição!", "Favor definir a ligação da máquina síncrona!")
  //}

  if (selected == 1) //Lista do gerador selecionada
  {
      int id_x = 0; //inicialização
      int id_y = 0;

            //matrix_struct[3][3].gerador_indices.id_k_Gerador = 225; --- tem que inicializar todas as variáveis - PUTZ
            //-IupMessagef("Aviso!", "O valor FIXO 3:3 de id_k_Gerador matrix é %d", matrix_struct[3][3].gerador_indices.id_k_Gerador);


            Ihandle* zbox = IupGetHandle ("list_tag_GE"); //tag da lista gerador
            IupSetAttribute (zbox, "VALUE", t); //string char* par ordenado ...por enquanto basta utilizar int i
                                                //Não recebe só um número, mas uma string inteira
                                                //Ele manda a tag e não um número

            /*** Formato 1 de t = (1:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = ) ***/
            /*** Formato 2 de t = (1:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = 0, t[6] = ) ***/
            /*** Formato 3 de t = (10:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = 0, t[7] = ) ***/
            /*** Formato 4 de t = (10:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = ) ***/



            /**** Laço de Repetição para pegar dezenas, pois vai até 15x15 ****/
            /**** No caso tem como pegar o valor certiho pela posição do vetor t ***/


            char buffer_id_x[50];
            char buffer_id_y[50];
            //char* buffer

            //if(t[2]) //String tag clicada

                /********************************/
                id_x = t[2] - '0';//a lista não está mais começando em 1, mas em 2...mais seguro capturar o elemento e converter para int

                if((t[3]) != ':'){
                    //IupMessage("Aviso!", "Condicional é válida");
                    sprintf(buffer_id_x, "%c%c", t[2], t[3]); //Não pode ser %s
                    /*** \depuracao
                    IupMessagef("Aviso!", "A string buffer id_x é %s", buffer_id_x);
                    ***/
                    id_x = atoi(buffer_id_x);
                }

                /******************************** CENÁRIO 1 ***************/

                if((t[4]) != ':'){
                    id_y = t[4] - '0';

                    if((t[5]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[4], t[5]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_x);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }

               /******************************** CENÁRIO 2 ***************/

                if((t[4]) == ':'){
                    id_y = t[5] - '0';

                    if((t[6]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[5], t[6]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_x);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }



                matrix_struct[id_x][id_y].gerador_indices.id_x = id_x;//recebe o status da id_x da struct
                matrix_struct[id_x][id_y].gerador_indices.id_y = id_y;

                /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x char_star é %s!", buffer_id_x);
                IupMessagef("Aviso!", "O valor de id_x convertido é %d!", id_x);

                IupMessagef("Aviso!", "O valor de id_y char_star é %s!", buffer_id_y);
                IupMessagef("Aviso!", "O valor de id_y convertido é %d!", id_y);

            \depuracao
            IupMessagef("Aviso!", "O string char_star de t é %s!", t);
            ***/

        /***** GARGALO 1: o "selectec" precisa englobar toda função senão dá loop 2x ******/
        /***** GARGALO 2: ao repetir a seleção está zerando id_k ...problema era o rebote da struct no envio massivo ******/

          int id_k_Gerador = -1;
          id_k_Gerador = matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador; //recebe o status da id_k da struct
          /*** \depuracao
          IupMessagef("Aviso!", "Os índexs selecionados são %d, %d e %d", id_x, id_y, id_k_Gerador);
          IupMessagef("Aviso!", "O valor de id_k_Gerador matrix é %d", matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador);
          ***/

          int id_k_Motor = -1;
          id_k_Motor = matrix_struct[id_x][id_y].motor_indices.id_k_Motor; //recebe o status da id_k da struct
          /*** \depuracao
          IupMessagef("Aviso!", "Os índexs selecionados são %d, %d e %d - 2 vez", id_x, id_y, id_k_Motor);
          ***/


        static int contador3 = 0;
        contador3++;
        /*** \depuracao
        IupMessagef("Aviso!", "FUNÇÃO INICIALIZADA - lista selecionada - contador é %d", contador3);
        ***/

      static int id_fuc_first = 0; //se a função for inicializa a primeira será zero, na segunda vez se incrementado não mais.

      if(id_k_Gerador != 0){
            id_fuc_first=+2;
      }


      //Armazenamento dos dados coletados à memória do gerador nas coordenadas ii, e desabilitação de armazenamento do motor ii
      if(id_k_Gerador == 0) //liberado para armazenamento
      {

            static int contador2 = 0;
            contador2++;
            /*** \depuracao
            IupMessagef("Aviso!", "FUNÇÃO INICIALIZADA - id_k_GE - contador é %d", contador2);
            ***/


            Ihandle* zbox = IupGetHandle ("list_tag_GE"); //tag da lista gerador
            //IupSetAttribute (zbox, "VALUE", t); //string char* par ordenado ...por enquanto basta utilizar int i
                                                //Não recebe só um número, mas uma string inteira
                                                //Ele manda a tag e não o número HUE
            //id_k é intrísico ao clique/seleção da barra da máquina
            id_k_Gerador = 1; /*** \<<<<<<< RACIOCÍNIO: 1 - ON ***/
            id_k_Motor = 2; /*** \<<<<<<< RACIOCÍNIO: 2 - OFF ***/
            matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador = id_k_Gerador;
            matrix_struct[id_x][id_y].motor_indices.id_k_Motor = id_k_Motor;

            if(depurar_gerador == 1){
            IupMessagef("Aviso!", "O valor de id_k do gerador (%d:%d) é %d", id_x, id_y, id_k_Gerador);
            IupMessagef("Aviso!", "O valor de id_k do motor (%d:%d) é %d", id_x, id_y, id_k_Motor);
            }

            id_fuc_first=0;

                                                 //TAVA PUXANDO A TAG ERRADA, digitei mdi_tag_FORM e declarei mdi_Tag_FORM
            function_memory_gerador(id_x, id_y); //ATENÇÃO TAVA DISPARANDO A FUNÇÃO MOTOR


        }

        if(id_fuc_first > 1 && id_k_Gerador != 0) //bloqueado para armazenamento     --- lógica medonha, tu tem que visualizar o que ocorre na struct do id_k do gerador
        {
            IupMessagef("Aviso!", "A barra %d só permite a inserção de uma máquina síncrona!", id_x);
        }

           return IUP_DEFAULT; // NÃO ENCERRA, ANTES DE FAZER A FUNÇÃO ACIMA! QUE POR CONSEGUINTE FARÁ A FUNÇÃO VOID E ENTÃO VAI EXIBIR A MENSAGEM
    }

}





/*****************************************(                  \FUNCTION \MEMORY \GERADOR         )********************************************

***/



static int function_memory_gerador(int id_x_arg, int id_y_arg)
{
    /*** ATIVANDO A CAPTURA DA JANELA FORM ***/
    Ihandle* ih = IupGetHandle("mdi_tag_FORM"); //CRÍTICO



    /************************************************************ CAPTURA DOS VALORES DO FRAME GERADOR *********************************/
    int id_x = id_x_arg;
    int id_y = id_y_arg;
    int id_k_Gerador = matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador;

    //IupMessagef("Aviso!", "O par lançado para o gerador é (%d:%d)", id_x, id_y);


          /*** Isto deve estar na validação do botão load full ***/
            /*** pois somente depois de validar os status 1, 2, 3 que pode ser coletado os dados ***/

                      Ihandle *MemoryBoxValue_x_seq_pos, *MemoryBoxValue_x_seq_neg, *MemoryBoxValue_x_seq_zero, *MemoryBoxValue_x_neutro;
                      Ihandle *MemoryBoxValue_Vg_nominal, *MemoryBoxValue_Pg_nominal;


    struct gerador gerador_00; //ou gerador_nos_11

                  /*** EFEITO REBOTE           --- SOLUÇÃO!!! ----       ***/
                  gerador_00.id_x = id_x_arg;
                  gerador_00.id_y = id_y_arg;
                  gerador_00.id_k_Gerador = id_k_Gerador;



                /*** ativando o BoxValue de tensão do gerador para coleta***/

                /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

                    MemoryBoxValue_Vg_nominal = IupGetDialogChild(ih, "BoxValue_Vg_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_Vg_nominal = IupGetFloat(MemoryBoxValue_Vg_nominal, "VALUE");


                    gerador_00.Vg_nominal = valor_Vg_nominal;


                /*** ativando o BoxValue de potência do gerador para coleta***/

                    MemoryBoxValue_Pg_nominal = IupGetDialogChild(ih, "BoxValue_Pg_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_Pg_nominal = IupGetFloat(MemoryBoxValue_Pg_nominal, "VALUE");

                    gerador_00.Pg_nominal = valor_Pg_nominal;


                /*** ativando o BoxValue de X_seq_pos do gerador para coleta***/


                    MemoryBoxValue_x_seq_pos = IupGetDialogChild(ih, "BoxValue_Xg_seq_pos_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_x_seq_pos = IupGetFloat(MemoryBoxValue_x_seq_pos, "VALUE");

                    gerador_00.Xg_seq_pos = valor_x_seq_pos;

                /*** ativando o BoxValue de X_seq_neg do gerador para coleta***/

                    MemoryBoxValue_x_seq_neg = IupGetDialogChild(ih, "BoxValue_Xg_seq_neg_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_x_seq_neg = IupGetFloat(MemoryBoxValue_x_seq_neg, "VALUE");

                    gerador_00.Xg_seq_neg = valor_x_seq_neg;


                /*** ativando o BoxValue de X_seq_zero do gerador para coleta***/


                    MemoryBoxValue_x_seq_zero = IupGetDialogChild(ih, "BoxValue_Xg_seq_zero_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_x_seq_zero = IupGetFloat(MemoryBoxValue_x_seq_zero, "VALUE");

                    gerador_00.Xg_seq_zero = valor_x_seq_zero;


                /*** ativando o BoxValue de X_neutro do gerador para coleta***/

                    MemoryBoxValue_x_neutro = IupGetDialogChild(ih, "BoxValue_Xg_neutro_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                      float valor_x_neutro = IupGetFloat(MemoryBoxValue_x_neutro, "VALUE");


                    if(id_toggle_GE_estrela == 1 || id_toggle_GE_estrela == 2)
                    {
                        gerador_00.Xg_pet = 0.0; //mitigando lixo deixado pelo usuário
                    }

                    if(id_toggle_GE_estrela == 3)
                    {
                        gerador_00.Xg_pet = valor_x_neutro;
                    }


        char string_buffer[50];


                /*** \CRITICO \PARADIGMA - CUIDADO TEXTO DO GERADOR ***/
                /*** Abaixo é usado o id_toggle do gerador de forma temporária para que seja possível inserir diversos geradores
                     usando o mesmo frame de dados, logo o id_toggle é armazenado permanentemente na memória do gerador em
                     lançamento através da struct que contém os atributos comuns, assim o id_toggle é armazenado no atributo
                     ligação esquema.
                ***/

                        if(id_toggle_GE_estrela != 0){
                            gerador_00.ligacao_esquema = id_toggle_GE_estrela; //CARREGAMENTO DA LIGAÇÃO DO GERADOR
                            if(id_toggle_GE_estrela == 1){
                                 sprintf(string_buffer, "%s", "Y sem aterramento no neutro");
                            }
                            if(id_toggle_GE_estrela == 2){
                                sprintf(string_buffer, "%s", "Y-at sem impedância");
                            }
                            if(id_toggle_GE_estrela == 3){
                                sprintf(string_buffer, "%s", "Y-at com impedância de peterson");
                            }
                            IupMessagef("Aviso!", "O tipo de LIGAÇÃO do gerador é %d = %s.", gerador_00.ligacao_esquema, string_buffer);
                        }


                //IupMessagef("Aviso!", "O valor de id_k do gerador (%d:%d) é %d", id_x, id_y, id_k_Gerador);
                if(depurar_gerador == 1){
                IupMessagef("Aviso!", "O valor de X_pos do gerador (%d:%d) é %.2f [%%]", id_x, id_y, gerador_00.Xg_seq_pos);
                IupMessagef("Aviso!", "O valor de X_neg do gerador (%d:%d) é %.2f [%%]", id_x, id_y, gerador_00.Xg_seq_neg);
                IupMessagef("Aviso!", "O valor de X_zero do gerador (%d:%d) é %.2f [%%]", id_x, id_y, gerador_00.Xg_seq_zero);
                IupMessagef("Aviso!", "O valor de X_peterson de aterramento do gerador (%d:%d) é %.2f [Ohms]", id_x, id_y, gerador_00.Xg_pet);
                IupMessagef("Aviso!", "O valor de ligação do gerador (%d:%d) é %d - %s", id_x, id_y, gerador_00.ligacao_esquema, string_buffer);
                }
                /*** \depuracao

                IupMessagef("Aviso!", "O valor de X_seq do gerador %d:%d é %f", id_x, id_y, matrix_struct[id_x][id_y].gerador_indices.Xg_seq_pos); //PASSOU NO TESTE, NÃO HAVIA COMO CARREGAR ACIMA!
                IupMessagef("Aviso!", "O VALOR de X_neg do gerador %d:%d é %f", id_x, id_y, matrix_struct[id_x][id_y].gerador_indices.Xg_seq_neg);

                ***/
                Carregar_Struct_Matrix_Gerador(gerador_00, id_x, id_y); /*** envio massivo ***/



        return IUP_DEFAULT; //ESTA FUNÇÃO SÓ SE ENCERRA QUANDO FIZER A VOID, DPS ENCERRA ESTA PARA ENTÃO ENCERRAR A FUNÇÃO LIST, diparado pelo item!
}






/*****************************************(                 \FUNCTION \CARREGAR \MEMORY \GERADOR         )********************************************

***/


void Carregar_Struct_Matrix_Gerador(struct gerador Gerador_index, int id_x_arg, int id_y_arg)/*** recebimento massivo ***/
{

    /*** TÁTICA 3 - POR NÓS ***/
    matrix_struct[id_x_arg][id_y_arg].gerador_indices = Gerador_index;



                if(depurar_gerador == 1){
                IupMessagef("Aviso!", "REINICIANDO GERADOR");
                }
                /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x e id_y do gerador são %d e %d", id_x_arg, id_y_arg);

                IupMessagef("Aviso!", "O valor de X_seq do gerador %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].gerador_indices.Xg_seq_pos);
                IupMessagef("Aviso!", "O VALOR de X_neg do gerador %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].gerador_indices.Xg_seq_neg);



               //+3h peguei, EFEITO REBOTE
                IupMessagef("Aviso!", "O valor de id_k do gerador %d:%d é %d - ÚLTIMA VEZ", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].gerador_indices.id_k_Gerador);
                ***/

}








/*****************************************(                 \FUNCTION \MEMORY \TRAFO \INDEX         )********************************************

***/


static int function_memory_transformador1_id_k (Ihandle* ih, char *t, int i, int selected)
{

    if(status_memory_trafo_1 == 0 && i != 1){

           // IupMessage("Aviso!", "Favor, primeiramente selecionar e definir a ligação do transformador e o tipo de núcleo.");

    } //if ligação trafo

    //if(i == 1)

      //      IupMessage("Aviso!", "Favor, selecione um item válido da lista.");        //Não funcionou como esperado, sem tempo para depurar




    //if(status_memory_trafo_1 != 0 && i != 1){
    if(status_memory_trafo_1 == 0 && i != 1){

          if (selected == 1)
          {
              int id_x = -2; //inicialização
              int id_y = -2;

                    /********************************************** CONVERSÃO CHAR PARA INT *****************************************/

                    Ihandle* zbox = IupGetHandle ("list_tag_TRAFO"); //tag da lista trafo
                                IupSetAttribute (zbox, "VALUE", t); //string char* par ordenado ...por enquanto basta utilizar int i
                                                //Não recebe só um número, mas uma string inteira
                                                //Ele manda a tag e não um número

            /*** Formato 1 de t = (1:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = ) ***/
            /*** Formato 2 de t = (1:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = 0, t[6] = ) ***/
            /*** Formato 3 de t = (10:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = 0, t[7] = ) ***/
            /*** Formato 4 de t = (10:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = ) ***/



            /**** Laço de Repetição para pegar dezenas, pois vai até 15x15 ****/
            /**** No caso tem como pegar o valor certinho pela posição do vetor t ***/


            char buffer_id_x[50];
            char buffer_id_y[50];
            //char* buffer

            //if(t[2]) //String tag clicada

                /********************************/
                id_x = t[2] - '0';//a lista não está mais começando em 1, mas em 2...mais seguro capturar o elemento e converter para int

                if((t[3]) != ':'){
                    //IupMessage("Aviso!", "Condicional é válida");
                    sprintf(buffer_id_x, "%c%c", t[2], t[3]); //Não pode ser %s
                    /*** \depuracao
                    IupMessagef("Aviso!", "A string buffer id_x é %s", buffer_id_x);
                    ***/
                    id_x = atoi(buffer_id_x);
                }

                /******************************** CENÁRIO 1 ***************/

                if((t[4]) != ':'){
                    id_y = t[4] - '0';

                    if((t[5]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[4], t[5]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }

               /******************************** CENÁRIO 2 ***************/

                if((t[4]) == ':'){
                    id_y = t[5] - '0';

                    if((t[6]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[5], t[6]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }



                matrix_struct[id_x][id_y].trafo_indices.id_x = id_x;//recebe o status da id_x da struct             <<< cuidado tava indo para o gerador_indices
                matrix_struct[id_x][id_y].trafo_indices.id_y = id_y;

                /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x char_star é %s!", buffer_id_x);
                IupMessagef("Aviso!", "O valor de id_x convertido é %d!", id_x);

                IupMessagef("Aviso!", "O valor de id_y char_star é %s!", buffer_id_y);
                IupMessagef("Aviso!", "O valor de id_y convertido é %d!", id_y);


                IupMessagef("Aviso!", "O string char_star de t é %s!", t);
                ***/

                  //Uma vez coletado os valores 1:2, abaixo procedo a verificação 2:1

                  int id_k_Trafo;// = -1;//anti-simétrico
                  id_k_Trafo = matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo; //recebe o status da id_k da struct
                      /*** \depuracao
                      IupMessagef("Aviso!", "Os índexs selecionados são id_x = %d, id_y = %d e id_k = %d", id_x, id_y, id_k_Trafo);
                      IupMessagef("Aviso!", "O valor de id_k_Trafo matrix é %d", matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo);
                      ***/


                  /*** CRÍTICO ESTAR FORA DO IF == 0 PARA INFORMAR O BLOQUEIO DE INPUT, DADO A SIMETRIA VIGENTE JÁ PREENCHIDA ***/
                  int id_k_Trafo_Simetric;// = -1;//simétrico
                  id_k_Trafo_Simetric = matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo; //recebe o status da id_k da struct - REFLETIDA
                      /*** \depuracao
                      IupMessagef("Aviso!", "Os índexs selecionados são id_x = %d, id_y = %d e id_k = %d", id_y, id_x, id_k_Trafo_Simetric);
                      IupMessagef("Aviso!", "O valor de id_k_Trafo matrix SIMÉTRICO é %d", matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo);
                      ***/

        //até aqui, todos os id_ks devem ser nulos


                static int contador1 = 0;
                contador1++;
                /*** \depuracao
                IupMessagef("Aviso!", "FIM SIMETRIA - lista selecionada - contador1 é %d", contador1);
                ***/

                static int id_fuc_first = 0; //se a função for inicializa a primeira será zero, na segunda vez se incrementado não mais.


              /*** SE LIGA, NÃO VAI PREENCHER O TRAFO, NÃO POR CAUSA DO id_k_LT = 2, MAS PQ É != 0, MELHORANDO-SE ASSIM O IF POR SEGUINTE ***/
              int id_k_LT = matrix_struct[id_x][id_y].LT_indices.id_k_LT; //coletando o id_k_LT para o if A e B
              int id_k_LT_Simetric = matrix_struct[id_y][id_x].LT_indices.id_k_LT; //Coletando o id_k_LT para o if A


              //A função consiste em estornar um id_k_Trafo, se uma das LTs está setada em 2, então ambos id_k_Trafo recebem 2
              //Só entraria no próximo if se nada tivesse sido setada no ramo
              if(id_k_LT == 2 || id_k_LT_Simetric == 2){//if A

                    id_k_Trafo = 2;
                    id_k_Trafo_Simetric = 2;
                    matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo = id_k_Trafo;
                    matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo = id_k_Trafo_Simetric; //note que as coordenadas são simétricas

                    /*** \depuracao
                    IupMessagef("Aviso!", "O id_k_Trafo e id_k_Trafo_Simetric são iguais a %d e %d", id_k_Trafo, id_k_Trafo_Simetric);
                    ***/
                    //IupMessagef("Aviso!", "O ramo (%d:%d) ou (%d:%d) já possui uma linha de transmissão", id_x, id_y, id_y, id_x);
                    IupMessagef("Aviso!", "Ramo (%d:%d) já foi definido, ou é simétrico ou já possui um elemento de SEP definido!", id_x, id_y);
              }



              //Armazenamento dos dados coletados à memória do gerador nas coordenadas ii, e desabilitação de armazenamento do motor ii
              if(id_k_Trafo == 0 && id_k_LT == 0) //liberado para armazenamento ...if B
              {

                    static int contador2 = 0;
                    contador2++;
                    /*** \depuracao
                    IupMessagef("Aviso!", "id_k_Trafo == 0... INICIALIZADA - contador2 é %d", contador2);
                    ***/



                    id_k_Trafo = 1;
                    id_k_Trafo_Simetric = 2;
                    matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo = id_k_Trafo;
                    matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo = id_k_Trafo_Simetric; //note que as coordenadas são simétricas

                    /************ UMA VEZ DEFINIDO O TRAFO NO RAMO NÃO SE DEFINE LT NESTE, LOGO LT RECEBE id_k_LT de bloqueio **************/
                    matrix_struct[id_x][id_y].LT_indices.id_k_LT = id_k_Trafo_Simetric; //cuidado é LT_indices
                    matrix_struct[id_y][id_x].LT_indices.id_k_LT = id_k_Trafo_Simetric; //note que as coordenadas são simétricas


                    if(depurar_trafo == 1){
                    IupMessagef("Aviso!", "O valor de id_k do trafo anti-simétrico %d:%d é %d", id_x, id_y, id_k_Trafo);
                    IupMessagef("Aviso!", "O valor de id_k do trafo simétrico %d:%d é %d", id_y, id_x, id_k_Trafo_Simetric);
                    }
                    if(depurar_LT == 1){
                    IupMessagef("Aviso!", "O valor de id_k da LT anti-simétrico %d:%d é %d", id_x, id_y, matrix_struct[id_x][id_y].LT_indices.id_k_LT);
                    IupMessagef("Aviso!", "O valor de id_k da LT simétrico %d:%d é %d", id_y, id_x, matrix_struct[id_y][id_x].LT_indices.id_k_LT);
                    }

                    id_fuc_first++;




                    /********************************************** CONVERSÃO CHAR PARA INT *****************************************/

                    /*** \depuracao
                        IupMessagef("Aviso!", "O valor de click de id_x char_star é %s!", buffer_id_x);
                        IupMessagef("Aviso!", "O valor de click  de id_x convertido é %d!", id_x);

                        IupMessagef("Aviso!", "O valor de click  de id_y char_star é %s!", buffer_id_y);
                        IupMessagef("Aviso!", "O valor de click  de id_y convertido é %d!", id_y);
                    ***/

                    function_memory_transformador1(id_x, id_y); //ATENÇÃO TAVA DISPARANDO A FUNÇÃO MOTOR


                }

                if(id_fuc_first > 1 || id_k_Trafo_Simetric != 0) //bloqueado para armazenamento     --- lógica medonha, tu tem que visualizar o que ocorre na struct do id_k do gerador
                {
                        if(depurar_trafo == 1){
                        IupMessagef("Aviso!", "Ramo (%d:%d) definido, ou é simétrico ou já possui um elemento de SEP definido!", id_x, id_y);
                        }
                }

            }//if "seletec" list

    } //if ligação trafo

      return IUP_DEFAULT; // NÃO ENCERRA, ANTES DE FAZER A FUNÇÃO ACIMA! QUE POR CONSEGUINTE FARÁ A FUNÇÃO VOID E ENTÃO VAI EXIBIR A MENSAGEM

}//if function id_k_Trafo










/*****************************************(                 \FUNCTION \MEMORY \TRAFO         )********************************************

***/

static int function_memory_transformador1(int id_x_arg, int id_y_arg)
{

    /*** ATIVANDO A CAPTURA DA JANELA FORM ***/
    Ihandle* ih = IupGetHandle("mdi_tag_FORM"); //CRÍTICO


    /************************************************************ CAPTURA DOS VALORES DO FRAME GERADOR *********************************/
    int id_x = id_x_arg;
    int id_y = id_y_arg;
    int id_k_Trafo = matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo; //exibi lá no final



            /*** Isto deve estar na validação do botão load full ***/
            /*** pois somente depois de validar os status 1, 2, 3 que pode ser coletado os dados ***/

            Ihandle *MemoryBoxValue_Vt_nominal_primario, *MemoryBoxValue_Vt_nominal_secundario, *MemoryBoxValue_Pt_nominal, *MemoryBoxValue_Xeq_trafo;


            struct transformador trafo_10; //ou trafo_nos_12
            char string_buffer[50];



                  /*** EFEITO REBOTE           --- SOLUÇÃO!!! ----       ***/
                  trafo_10.id_x = id_x_arg;
                  trafo_10.id_y = id_y_arg;
                  trafo_10.id_k_Trafo = id_k_Trafo; //sem brechas para carregamento de lixo na struct trafo_10


                  /*** \CRITICO \PARADIGMA - CUIDADO TEXTO 1/2 DO TRAFO***/
                  /*** Abaixo é usado o vetor de id_toggle de trafo (neste caso é o das ligações), este armazena de forma temporária
                       um conjunto binários de um inteiro ou zeros, onde o número inteiro pertence ao conjunto de números de 1 a 11,
                       o conjunto de binários sempre é zerada ao permutar de ligação antes que ocorra o carregamento do binário cheio.
                       Com a ligação definida o vetor de opções é então lido por um laço de repetição que permite saber exatamente qual
                       ligação foi definida entre as 11 ligações ou 9 ligações, se desejar (atenuação de complexidade do TCC).
                  ***/
                  int i = 1;//ESTE COMEÇA EM UM

                  if(id_toggle_TR1_nucleo == 1){
                        for(i=1; i<12;i++){   //São 1igações -- CUIDADO COMEÇA EM UM e menor que 12 - núcleo envolvente
                            if(options_TR1[i].option != 0){
                                //matrix_struct[id_x][id_y].trafo_indices.ligacao_esquema = options_TR2[i].option;
                                trafo_10.ligacao_esquema = options_TR1[i].option; //bem simples assim!

                                //Criar uma lista e buscar dessa lista string
                                if(trafo_10.ligacao_esquema == 1){
                                     sprintf(string_buffer, "%s", "Y-at:Y-at");
                                }
                                if(trafo_10.ligacao_esquema == 2){
                                    sprintf(string_buffer, "%s", "Y-at:Delta");
                                }
                                if(trafo_10.ligacao_esquema == 3){
                                    sprintf(string_buffer, "%s", "Delta:Y-at");
                                }
                                if(trafo_10.ligacao_esquema == 4){
                                    sprintf(string_buffer, "%s", "Y:Delta");
                                }
                                if(trafo_10.ligacao_esquema == 5){
                                    sprintf(string_buffer, "%s", "Delta:Y");
                                }
                                if(trafo_10.ligacao_esquema == 6){
                                    sprintf(string_buffer, "%s", "Y-at:Y");
                                }
                                if(trafo_10.ligacao_esquema == 7){
                                    sprintf(string_buffer, "%s", "Y:Y-at");
                                }
                                if(trafo_10.ligacao_esquema == 8){
                                    sprintf(string_buffer, "%s", "Delta:Delta");
                                }
                                if(trafo_10.ligacao_esquema == 9){
                                    sprintf(string_buffer, "%s", "Y:Y");
                                }

                                /*** \depuracao
                                //IupMessagef("Aviso!", "O tipo de ESQUEMA do trafo é %d", matrix_struct[id_x][id_y].trafo_indices.ligacao_esquema);//deve ser zero pq não houve envio massivo
                                ***/
                                IupMessagef("Aviso!", "NÚCLEO ENVOLVENTE: o  tipo de ESQUEMA definido é %d = %s", trafo_10.ligacao_esquema, string_buffer); //deve ser algum número pq já foi definido
                            }

                        }
                  }

                  if(id_toggle_TR1_nucleo == 2){

                        for(i=1; i<4;i++){   //São 1igações -- CUIDADO COMEÇA EM UM e menor que 4 - núcleo envolvido
                            if(options_TR1_envolvido[i].option != 0){
                                //matrix_struct[id_x][id_y].trafo_indices.ligacao_esquema = options_TR2[i].option;
                                trafo_10.ligacao_esquema = options_TR1_envolvido[i].option; //bem simples assim!

                                    //Criar uma lista e buscar dessa lista string
                                    if(trafo_10.ligacao_esquema == 1){
                                         sprintf(string_buffer, "%s", "Y-at:Y-at");
                                    }
                                    if(trafo_10.ligacao_esquema == 2){
                                        sprintf(string_buffer, "%s", "Y-at:Y");
                                    }
                                    if(trafo_10.ligacao_esquema == 3){
                                        sprintf(string_buffer, "%s", "Y-at:Delta");
                                    }

                                /*** \depuracao
                                //IupMessagef("Aviso!", "O tipo de ESQUEMA do trafo é %d", matrix_struct[id_x][id_y].trafo_indices.ligacao_esquema);//deve ser zero pq não houve envio massivo
                                ***/
                                IupMessagef("Aviso!", "NÚCLEO ENVOLVIDO: o tipo de ESQUEMA definido é %d = %s", trafo_10.ligacao_esquema, string_buffer); //deve ser algum número pq já foi definido
                            }
                        }
                  }

                        /*** \CRITICO \PARADIGMA - CUIDADO TEXTO 2/2 DO TRAFO ***/
                        /*** Abaixo é usado o id_toggle do trafo de forma temporária para que seja possível inserir diversos trafos
                             usando o mesmo frame de dados, logo o id_toggle é armazenado permanentemente na memória do trafo em
                             lançamento através da struct que contém os atributos comuns, assim o id_toggle é armazenado no atributo
                             ligação núcleo.
                        ***/

                        //EXCESSO DE AVISO - ATENUAR - somente o aviso, cuidado, ainda precisa carregar ao trafo temporário (aquele em carregamento).

                        if(id_toggle_TR1_nucleo != 0){
                            trafo_10.ligacao_nucleo = id_toggle_TR1_nucleo;
                            if(id_toggle_TR1_nucleo == 1){
                                sprintf(string_buffer, "%s", "ENVOLVENTE");
                            }
                            if(id_toggle_TR1_nucleo == 2){
                                sprintf(string_buffer, "%s", "ENVOLVIDO");
                            }
                            //IupMessagef("Aviso!", "O tipo de NÚCLEO do trafo é %d = %s", trafo_10.ligacao_nucleo, string_buffer);
                        }




            /*** ativando o BoxValue de tensão do gerador para coleta***/

            /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

            MemoryBoxValue_Vt_nominal_primario = IupGetDialogChild(ih, "BoxValue_Vtr1_nominal_primario_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
            float valor_Vt_nominal_primario = IupGetFloat(MemoryBoxValue_Vt_nominal_primario, "VALUE");


            trafo_10.Vt_nominal_primario = valor_Vt_nominal_primario;

            /*** ativando o BoxValue de potência do gerador para coleta***/

            MemoryBoxValue_Vt_nominal_secundario = IupGetDialogChild(ih, "BoxValue_Vtr1_nominal_secundario_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
            float valor_Vt_nominal_secundario = IupGetFloat(MemoryBoxValue_Vt_nominal_secundario, "VALUE");

            trafo_10.Vt_nominal_secundario = valor_Vt_nominal_secundario;



            /*** ativando o BoxValue de potência do gerador para coleta***/

            MemoryBoxValue_Pt_nominal = IupGetDialogChild(ih, "BoxValue_Ptr1_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
            float valor_Pt_nominal = IupGetFloat(MemoryBoxValue_Pt_nominal, "VALUE");

            trafo_10.Pt_nominal = valor_Pt_nominal;




            /*** ativando o BoxValue de X_seq_pos do gerador para coleta***/


            MemoryBoxValue_Xeq_trafo = IupGetDialogChild(ih, "BoxValue_Xeq_trafo1_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
            float valor_Xeq_trafo = IupGetFloat(MemoryBoxValue_Xeq_trafo, "VALUE");

            /*** \>>>>>> Diferente das outras máquinas um único BoxValue preenche vários campos. \<<<<<< ***/
            trafo_10.Xeq_trafo = valor_Xeq_trafo;
            trafo_10.X_TR_seq_pos = valor_Xeq_trafo;
            trafo_10.X_TR_seq_neg = valor_Xeq_trafo;
            trafo_10.X_TR_seq_zero = valor_Xeq_trafo;


            /*********************************** INFORMAÇÕES COMPLENTARES **************************************************************/

            //IMPORTANTE A INFORMAÇÃO DA LIGAÇÃO DO TRAFO DEVE SER COLETADA AQUI...RESOLVENDO LOGO O PROBLEMA DA BASE E SEQUÊNCIA ZERO
            //NOTE QUE AQUI PODERIA TER 2 CAMPOS PARA SABER QUAL BARRA/NÓ ESTÁ O PRIMÁRIO E O SECUNDÁRIO, MAS BASTA PEGAR O ID_K NULO DO SIMÉTRICO
                //PARA QUE SAIBA SE FOI 2:1 OU 1:2 QUE O USUÁRIO DEFINIU!



                //IupMessagef("Aviso!", "O valor de id_k do trafo %d:%d é %d", id_x, id_y, id_k_Trafo);
                if(depurar_trafo == 1){
                IupMessagef("Aviso!", "O valor de X_seq do trafo (%d:%d) é %.2f [%%]", id_x, id_y, trafo_10.X_TR_seq_pos);
                IupMessagef("Aviso!", "O valor de X_neg do trafo (%d:%d) é %.2f [%%]", id_x, id_y, trafo_10.X_TR_seq_neg);
                IupMessagef("Aviso!", "O valor de X_zero do trafo (%d:%d) é %.2f [%%]", id_x, id_y, trafo_10.X_TR_seq_zero);
                }
                /*** \depuracao
                IupMessagef("Aviso!", "O valor de X_eq_trafo do trafo %d:%d é %f", id_x, id_y, matrix_struct[id_x][id_y].trafo_indices.Xeq_trafo); //PASSOU NO TESTE, NÃO HAVIA COMO CARREGAR ACIMA!
                ***/

                Carregar_Struct_Matrix_Trafo_1(trafo_10, id_x, id_y); /*** envio massivo ***/




     return IUP_DEFAULT;

}










/*****************************************(                 \FUNCTION \CARREGAR \MEMORY \TRAFO         )********************************************

***/

void Carregar_Struct_Matrix_Trafo_1(struct transformador Trafo_index, int id_x_arg, int id_y_arg)/*** recebimento massivo --- trafo 1 = GLOBAL ***/
{

    /*** TÁTICA 3 - POR NÓS ***/
    matrix_struct[id_x_arg][id_y_arg].trafo_indices = Trafo_index; //Recebimento massico // CUIDADO, EFEITO REBOTE, CAMPOS COM LIXO
    //matrix_struct[id_y_arg][id_x_arg].trafo_indices = Trafo_index; //CARREGAR NO SIMÉTRICO, SIMPLES ASSIM


                if(depurar_trafo == 1){
                IupMessagef("Aviso!", "REINICIANDO TRAFO");
                }
            /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x e id_y do trafo são %d e %d", id_x_arg, id_y_arg);

                IupMessagef("Aviso!", "O valor de Xeq_trafo do trafo %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].trafo_indices.Xeq_trafo);
                //IupMessagef("Aviso!", "O VALOR de X_neg do trafo %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].trafo_indices.Xg_seq_neg);

            /*** \depuracao

               //+3h peguei, EFEITO REBOTE
                IupMessagef("Aviso!", "O valor de id_k do trafo %d:%d é %d - ÚLTIMA VEZ", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].trafo_indices.id_k_Trafo);

               //Pegou, pingando sono
                IupMessagef("Aviso!", "O número da ligação do trafo %d:%d é %d - ÚLTIMA VEZ", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].trafo_indices.ligacao_esquema);
           ****/
}








/*****************************************(                 \FUNCTION \MEMORY \LT \INDEX         )********************************************

***/


static int function_memory_LT_id_k(Ihandle* ih, char *t, int i, int selected)
{
  if (selected == 1)
  {
      int id_x = -2; //inicialização
      int id_y = -2;

            /********************************************** CONVERSÃO CHAR PARA INT *****************************************/

            Ihandle* zbox = IupGetHandle ("list_tag_LT"); //tag da lista trafo
                        IupSetAttribute (zbox, "VALUE", t); //string char* par ordenado ...por enquanto basta utilizar int i
                                                //Não recebe só um número, mas uma string inteira
                                                //Ele manda a tag e não um número

            /*** Formato 1 de t = (1:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = ) ***/
            /*** Formato 2 de t = (1:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = 0, t[6] = ) ***/
            /*** Formato 3 de t = (10:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = 0, t[7] = ) ***/
            /*** Formato 4 de t = (10:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = ) ***/



            /**** Laço de Repetição para pegar dezenas, pois vai até 15x15 ****/
            /**** No caso tem como pegar o valor certiho pela posição do vetor t ***/


            char buffer_id_x[50];
            char buffer_id_y[50];
            //char* buffer

            //if(t[2]) //String tag clicada

                /********************************/
                id_x = t[2] - '0';//a lista não está mais começando em 1, mas em 2...mais seguro capturar o elemento e converter para int

                if((t[3]) != ':'){
                    //IupMessage("Aviso!", "Condicional é válida");
                    sprintf(buffer_id_x, "%c%c", t[2], t[3]); //Não pode ser %s
                    /*** \depuracao
                    IupMessagef("Aviso!", "A string buffer id_x é %s", buffer_id_x);
                    ***/
                    id_x = atoi(buffer_id_x);
                }

                /******************************** CENÁRIO 1 ***************/

                if((t[4]) != ':'){
                    id_y = t[4] - '0';

                    if((t[5]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[4], t[5]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }

               /******************************** CENÁRIO 2 ***************/

                if((t[4]) == ':'){
                    id_y = t[5] - '0';

                    if((t[6]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[5], t[6]);
                       /*** \depuracao ***
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }


        /*** \depuracao
                matrix_struct[id_x][id_y].LT_indices.id_x = id_x;//recebe o status da id_x da struct            <<< cuidado, tava usando gerador_indices e não LT_indices
                matrix_struct[id_x][id_y].LT_indices.id_y = id_y;

                IupMessagef("Aviso!", "O valor de id_x char_star é %s!", buffer_id_x);
                IupMessagef("Aviso!", "O valor de id_x convertido é %d!", id_x);

                IupMessagef("Aviso!", "O valor de id_y char_star é %s!", buffer_id_y);
                IupMessagef("Aviso!", "O valor de id_y convertido é %d!", id_y);


          IupMessagef("Aviso!", "O string char_star de t é %s!", t);

          ***/

          //Uma vez coletado os valores 1:2, abaixo procedo a verificação 2:1

          int id_k_LT;// = -1;//anti-simétrico
          id_k_LT = matrix_struct[id_x][id_y].LT_indices.id_k_LT; //recebe o status da id_k da struct
          /*** \depuracao
              IupMessagef("Aviso!", "Os índexs selecionados são id_x = %d, id_y = %d e id_k = %d", id_x, id_y, id_k_LT);
              IupMessagef("Aviso!", "O valor de id_k_LT matrix é %d", matrix_struct[id_x][id_y].LT_indices.id_k_LT);
          ***/


          /*** CRÍTICO ESTAR FORA DO IF == 0 PARA INFORMAR O BLOQUEIO DE INPUT, DADO A SIMETRIA VIGENTE JÁ PREENCHIDA ***/
          int id_k_LT_Simetric;// = -1;//simétrico
          id_k_LT_Simetric = matrix_struct[id_y][id_x].LT_indices.id_k_LT; //recebe o status da id_k da struct - REFLETIDA
          /*** \depuracao
              IupMessagef("Aviso!", "Os índexs selecionados SIMÉTRICOS são id_x = %d, id_y = %d e id_k = %d", id_y, id_x, id_k_LT_Simetric);
              IupMessagef("Aviso!", "O valor de id_k_LT matrix SIMÉTRICO é %d", matrix_struct[id_y][id_x].LT_indices.id_k_LT);
          ***/

//até aqui, todos os id_ks devem ser nulos


        static int contador1 = 0;
        contador1++;
        /*** \depuracao
        IupMessagef("Aviso!", "FIM SIMETRIA - lista selecionada - contador1 é %d", contador1);
        ***/

        static int id_fuc_first = 0; //se a função for inicializa a primeira será zero, na segunda vez se incrementado não mais.



        /*** SE LIGA, NÃO VAI PREENCHER O TRAFO NÃO POR CAUSA DO id_k_LT = 2, MAS PQ É != 0, MELHORANDO-SE ASSIM O IF POR SEGUINTE ***/
        int id_k_Trafo = matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo;
        int id_k_Trafo_Simetric = matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo;

        /************************* SE JÁ EXISTIR UM TRAFO NO RAMO BLOQUEIA A INSERÇÃO DE UMA LT ANTI-SIMÉTRICA E SIMÉTRICA *****************************/
        if(id_k_Trafo == 2 || id_k_Trafo_Simetric == 2){
            //A função consiste em estornar um id_k_LT, se um dos trafos está setado em 2, então ambos id_k_LT recebem 2
            //Só entraria no próximo if se nada tivesse sido setada no ramo
            id_k_LT = 2;
            id_k_LT_Simetric = 2;
            matrix_struct[id_x][id_y].LT_indices.id_k_LT = id_k_LT;
            matrix_struct[id_y][id_x].LT_indices.id_k_LT = id_k_LT_Simetric; //note que as coordenadas são simétricas

            /*** \depuracao
            IupMessagef("Aviso!", "O id_k_LT e id_k_LT_Simetric são iguais a %d e %d", id_k_LT, id_k_LT_Simetric);
            ***/
            //IupMessagef("Aviso!", "O ramo (%d:%d) ou (%d:%d) já possui um transformador", id_x, id_y, id_y, id_x);
            IupMessagef("Aviso!", "Ramo (%d:%d) já foi definido, ou é simétrico ou já possui um elemento de SEP definido!", id_x, id_y);

        }




        //Armazenamento dos dados coletados à memória do gerador nas coordenadas ii, e desabilitação de armazenamento do motor ii
        if(id_k_LT  == 0 && id_k_Trafo == 0) //liberado para armazenamento
        {

            static int contador2 = 0;
            contador2++;
            /*** \depuracao
            IupMessagef("Aviso!", "id_k_LT == 0... INICIALIZADA - contador2 é %d", contador2);
            ***/

            id_k_LT = 1;
            id_k_LT_Simetric = 2;
            matrix_struct[id_x][id_y].LT_indices.id_k_LT = id_k_LT;
            matrix_struct[id_y][id_x].LT_indices.id_k_LT = id_k_LT_Simetric; //note que as coordenadas são simétricas

            /************ UMA VEZ DEFINIDO A LT NO RAMO NÃO SE DEFINE TRAFO NELE...TRAFO ANTI-SIMÉTRICO E SIMÉTRICO BLOQUEADOS **************/
            matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo = id_k_LT_Simetric;
            matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo = id_k_LT_Simetric;


            if(depurar_LT == 1){
            IupMessagef("Aviso!", "O valor de id_k da LT anti-simétrico (%d:%d) é %d", id_x, id_y, id_k_LT);
            IupMessagef("Aviso!", "O valor de id_k da LT simétrico (%d:%d) é %d", id_y, id_x, id_k_LT_Simetric);
            }
            if(depurar_trafo == 1){
            IupMessagef("Aviso!", "O valor de id_k do Trafo anti-simétrico (%d:%d) é %d", id_x, id_y, matrix_struct[id_x][id_y].trafo_indices.id_k_Trafo);
            IupMessagef("Aviso!", "O valor de id_k do Trafo simétrico (%d:%d) é %d", id_y, id_x, matrix_struct[id_y][id_x].trafo_indices.id_k_Trafo);
            }

            id_fuc_first++;




            /********************************************** CONVERSÃO CHAR PARA INT *****************************************/

            /*** \depuracao
                IupMessagef("Aviso!", "O valor de click de id_x char_star é %s!", buffer_id_x);
                IupMessagef("Aviso!", "O valor de click  de id_x convertido é %d!", id_x);

                IupMessagef("Aviso!", "O valor de click  de id_y char_star é %s!", buffer_id_y);
                IupMessagef("Aviso!", "O valor de click  de id_y convertido é %d!", id_y);
            ***/

            function_memory_LT(id_x, id_y); //ATENÇÃO TAVA DISPARANDO A FUNÇÃO MOTOR


        }

        if(id_fuc_first > 1 || id_k_LT_Simetric != 0) //bloqueado para armazenamento     --- lógica medonha, tu tem que visualizar o que ocorre na struct do id_k do gerador
        {
                if(depurar_LT == 1){
                IupMessagef("Aviso!", "Ramo (%d:%d) já foi definido, ou é simétrico ou já possui um elemento de SEP definido!", id_x, id_y);
                }
        }

           return IUP_DEFAULT; // NÃO ENCERRA, ANTES DE FAZER A FUNÇÃO ACIMA! QUE POR CONSEGUINTE FARÁ A FUNÇÃO VOID E ENTÃO VAI EXIBIR A MENSAGEM
    }

}








/*****************************************(                 \FUNCTION \MEMORY \LT         )********************************************

***/


static int function_memory_LT(int id_x_arg, int id_y_arg)
{

    /*** ATIVANDO A CAPTURA DA JANELA FORM ***/
    Ihandle* ih = IupGetHandle("mdi_tag_FORM"); //CRÍTICO


    /************************************************************ CAPTURA DOS VALORES DO FRAME GERADOR *********************************/
    int id_x = id_x_arg;
    int id_y = id_y_arg;
    int id_k_LT = matrix_struct[id_x][id_y].LT_indices.id_k_LT; //exibi lá no final


            /*** Isto deve estar na validação do botão load full ***/
            /*** pois somente depois de validar os status 1, 2, 3 que pode ser coletado os dados ***/

            Ihandle *MemoryBoxValue_x_seq_pos_LT, *MemoryBoxValue_x_seq_neg_LT, *MemoryBoxValue_x_seq_zero_LT;


            struct linha_LT linha_12; //ou por nós linha_23

                              /*** EFEITO REBOTE           --- SOLUÇÃO!!! ----       ***/
                  linha_12.id_x = id_x_arg;
                  linha_12.id_y = id_y_arg;
                  linha_12.id_k_LT = id_k_LT; //sem brechas para carregamento de lixo na struct trafo_10


            /*** ativando o BoxValue de tensão do gerador para coleta***/

            /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

            /*** ativando o BoxValue da reatância positiva da LT para coleta***/

             MemoryBoxValue_x_seq_pos_LT = IupGetDialogChild(ih, "BoxValue_x_seq_pos_LT_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
             float valor_x_seq_pos_LT = IupGetFloat(MemoryBoxValue_x_seq_pos_LT, "VALUE");

            linha_12.Xeq_LT_seq_pos = valor_x_seq_pos_LT;

            /*** ativando o BoxValue de potência do gerador para coleta***/

             MemoryBoxValue_x_seq_neg_LT = IupGetDialogChild(ih, "BoxValue_x_seq_neg_LT_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
             float valor_x_seq_neg_LT = IupGetFloat(MemoryBoxValue_x_seq_neg_LT, "VALUE");

            linha_12.Xeq_LT_seq_neg = valor_x_seq_neg_LT;


            /*** ativando o BoxValue de potência do gerador para coleta***/

             MemoryBoxValue_x_seq_zero_LT = IupGetDialogChild(ih, "BoxValue_x_seq_zero_LT_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
             float valor_x_seq_zero_LT = IupGetFloat(MemoryBoxValue_x_seq_zero_LT, "VALUE");

            linha_12.Xeq_LT_seq_zero = valor_x_seq_zero_LT;




            /*********************************** INFORMAÇÕES COMPLENTARES **************************************************************/

            //IMPORTANTE A INFORMAÇÃO DA LIGAÇÃO DO TRAFO DEVE SER COLETADA AQUI...RESOLVENDO LOGO O PROBLEMA DA BASE E SEQUÊNCIA ZERO
            //NOTE QUE AQUI PODERIA TER 2 CAMPOS PARA SABER QUAL BARRA/NÓ ESTÁ O PRIMÁRIO E O SECUNDÁRIO, MAS BASTA PEGAR O ID_K NULO DO SIMÉTRICO
                //PARA QUE SAIBA SE FOI 2:1 OU 1:2 QUE O USUÁRIO DEFINIU!


                //IupMessagef("Aviso!", "O valor de id_k da LT (%d:%d) é %d", id_x, id_y, id_k_LT);
                if(depurar_LT == 1){
                IupMessagef("Aviso!", "O valor de Xeq_LT_seq_pos da LT (%d:%d) é %.2f [Ohms]", id_x, id_y, linha_12.Xeq_LT_seq_pos);
                IupMessagef("Aviso!", "O valor de Xeq_LT_seq_neg da LT (%d:%d) é %.2f [Ohms]", id_x, id_y, linha_12.Xeq_LT_seq_neg);
                IupMessagef("Aviso!", "O valor de Xeq_LT_seq_zero da LT (%d:%d) é %.2f [Ohms]", id_x, id_y, linha_12.Xeq_LT_seq_zero);
                }
                /*** \depuracao
                IupMessagef("Aviso!", "O valor de Xeq_LT_seq_pos matrix da LT (%d:%d) é %.2f [Ohms]", id_x, id_y, matrix_struct[id_x][id_y].LT_indices.Xeq_LT_seq_pos); //PASSOU NO TESTE, NÃO HAVIA COMO CARREGAR ACIMA!
                ***/



                Carregar_Struct_Matrix_LT(linha_12, id_x, id_y); /*** envio massivo ***/




     return IUP_DEFAULT;

}








/*****************************************(                 \FUNCTION \CARREGAR \MEMORY \LT         )********************************************

***/


void Carregar_Struct_Matrix_LT(struct linha_LT LT_index, int id_x_arg, int id_y_arg)/*** recebimento massivo --- trafo 1 = GLOBAL ***/
{

    /*** TÁTICA 3 - POR NÓS ***/
    matrix_struct[id_x_arg][id_y_arg].LT_indices = LT_index; //Recebimento massico // CUIDADO, EFEITO REBOTE, CAMPOS COM LIXO
    //matrix_struct[id_y_arg][id_x_arg].LT_indices = LT_index; //CARREGAR NO SIMÉTRICO

    IupMessagef("Aviso!", "Carregado a LT_%d%d!", id_x_arg, id_y_arg);

                if(depurar_LT == 1){
                IupMessagef("Aviso!", "REINICIANDO LT");
                }
                /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x e id_y da LT são %d e %d", id_x_arg, id_y_arg);

                IupMessagef("Aviso!", "O valor de Xeq_LT_seq_pos da LT %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].LT_indices.Xeq_LT_seq_pos);
                //IupMessagef("Aviso!", "O VALOR de X_neg do trafo %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].LT_indices.Xg_seq_neg);



               //+3h peguei, EFEITO REBOTE
                IupMessagef("Aviso!", "O valor de id_k da LT %d:%d é %d - ÚLTIMA VEZ", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].LT_indices.id_k_LT);
               ***/
}








/*****************************************(                 \FUNCTION \MEMORY \MOTOR \INDEX         )********************************************

***/

//static int function_memory_motor(Ihandle *ih){
static int function_memory_motor_id_k (Ihandle *ih, char *t, int i, int selected) //recebe a list Ihandle...não é o botão, SetCallback pode enviar btn, canvas e list
{
  if (selected == 1) //Disparo da lista
  {
      int id_x = -2; //inicialização
      int id_y = -2;


            Ihandle* zbox = IupGetHandle ("list_tag_MOTOR"); //tag da lista gerador
                        IupSetAttribute (zbox, "VALUE", t); //string char* par ordenado ...por enquanto basta utilizar int i
                                                //Não recebe só um número, mas uma string inteira
                                                //Ele manda a tag e não um número

            /*** Formato 1 de t = (1:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = ) ***/
            /*** Formato 2 de t = (1:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = :, t[4] = 1, t[5] = 0, t[6] = ) ***/
            /*** Formato 3 de t = (10:10) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = 0, t[7] = ) ***/
            /*** Formato 4 de t = (10:1) NESTE CASO t[1] = (, t[2] = 1, t[3] = 0, t[4] = :, t[5] = 1, t[6] = ) ***/



            /**** Laço de Repetição para pegar dezenas, pois vai até 15x15 ****/
            /**** No caso tem como pegar o valor certiho pela posição do vetor t ***/


            char buffer_id_x[50];
            char buffer_id_y[50];
            //char* buffer

            //if(t[2]) //String tag clicada

                /********************************/
                id_x = t[2] - '0';//a lista não está mais começando em 1, mas em 2...mais seguro capturar o elemento e converter para int

                if((t[3]) != ':'){
                    //IupMessage("Aviso!", "Condicional é válida");
                    sprintf(buffer_id_x, "%c%c", t[2], t[3]); //Não pode ser %s
                    /*** \depuracao
                    IupMessagef("Aviso!", "A string buffer id_x é %s", buffer_id_x);
                    ***/
                    id_x = atoi(buffer_id_x);
                }

                /******************************** CENÁRIO 1 ***************/

                if((t[4]) != ':'){
                    id_y = t[4] - '0';

                    if((t[5]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[4], t[5]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }

               /******************************** CENÁRIO 2 ***************/

                if((t[4]) == ':'){
                    id_y = t[5] - '0';

                    if((t[6]) != ')'){
                       sprintf(buffer_id_y, "%c%c", t[5], t[6]);
                       /*** \depuracao
                       IupMessagef("Aviso!", "A string buffer id_y é %s", buffer_id_y);
                       ***/
                       id_y = atoi(buffer_id_y);
                    }
                }



                matrix_struct[id_x][id_y].gerador_indices.id_x = id_x;//recebe o status da id_x da struct
                matrix_struct[id_x][id_y].gerador_indices.id_y = id_y;

            /*** \depuracao

                IupMessagef("Aviso!", "O valor de id_x char_star é %s!", buffer_id_x);
                IupMessagef("Aviso!", "O valor de id_x convertido é %d!", id_x);

                IupMessagef("Aviso!", "O valor de id_y char_star é %s!", buffer_id_y);
                IupMessagef("Aviso!", "O valor de id_y convertido é %d!", id_y);


            IupMessagef("Aviso!", "O string char_star de t é %s!", t);
            ***/

    /***** GARGALO 1: o "selectec" precisa englobar toda função senão dá loop 2x ******/
    /***** GARGALO 2: ao repetir a seleção está zerando id_k ******/

      int id_k_Gerador = -1;
      id_k_Gerador = matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador; //recebe o status da id_k da struct
      /*** \depuracao
      IupMessagef("Aviso!", "Os índexs selecionados são %d, %d e %d", id_x, id_y, id_k_Gerador);
      ***/


      int id_k_Motor = -1;
      id_k_Motor = matrix_struct[id_x][id_y].motor_indices.id_k_Motor; //recebe o status da id_k da struct
      /*** \depuracao
      IupMessagef("Aviso!", "Os índexs selecionados são %d, %d e %d - 2 vez", id_x, id_y, id_k_Motor);
      ***/


        static int contador3 = 0;
        contador3++;
        /*** \depuracao
        IupMessagef("Aviso!", "FUNÇÃO INICIALIZADA - TARDE - lista selecionada - contador é %d", contador3);
        IupMessagef("Aviso!", "O valor de id_k_Gerador é %d", id_k_Gerador);
        IupMessagef("Aviso!", "O valor de id_k_Motor é %d", id_k_Motor);
        ***/

      static int id_fuc_first = 0; //se a função for inicializa a primeira será zero, na segunda vez se incrementado não mais.

/****
      int id_k_Gerador = matrix_struct[i][i].gerador_indices.id_k; //recebe o status da id_k da struct
      int id_k_Motor = matrix_struct[i][i].motor_indices.id_k; //recebe o status da id_k da struct
****/
      if(id_k_Motor != 0){
            id_fuc_first=+2;
      }

      //Armazenamento dos dados coletados à memória do gerador nas coordenadas ii, e desabilitação de armazenamento do motor ii
      if(id_k_Motor == 0) //liberado para armazenamento ... SE NADA foi carregado a barra, então id_k_Motor é nulo, assim como id_k_GE
      {
            static int contador2 = 0;
            contador2++;
            /*** \depuracao
            IupMessagef("Aviso!", "FUNÇÃO INICIALIZADA - id_k - contador é %d", contador2);
            ***/

            //id_k é intrísico ao clique/seleção da barra da máquina
            id_k_Gerador = 2; /*** \<<<<<<< RACIOCÍNIO: 2 - OFF (BLOQUEADO) ***/
            id_k_Motor = 1; /*** \<<<<<<< RACIOCÍNIO: 1 - ON ***/

            //id_k_Gerador = 1;
            //id_k_Motor = 2;
            matrix_struct[id_x][id_y].gerador_indices.id_k_Gerador = id_k_Gerador;
            matrix_struct[id_x][id_y].motor_indices.id_k_Motor = id_k_Motor;


            if(depurar_motor==1){
            IupMessagef("Aviso!", "O valor de id_k do motor (%d:%d) é %d", id_x, id_y, id_k_Motor);
            IupMessagef("Aviso!", "O valor de id_k do gerador (%d:%d) é %d", id_x, id_y, id_k_Gerador);
            //IupMessagef("Aviso!", "O valor de id_k do motor (%d:%d) é %d", id_x, id_y, id_k_Motor); //sob a ordem de exibição
            }

            id_fuc_first=0;

            /********************************************** CONVERSÃO CHAR PARA INT *****************************************/




                                                //TAVA PUXANDO A TAG ERRADA, digitei mdi_tag_FORM e declarei mdi_Tag_FORM
            function_memory_motor(id_x, id_y);



        }


        if(id_fuc_first > 1 && id_k_Motor != 0) //bloqueado para armazenamento     --- lógica medonha, tu tem que visualizar o que ocorre na struct do id_k do gerador
        {
            //if(depurar_motor==1){
            IupMessagef("Aviso!", "A barra %d só permite a inserção de uma máquina síncrona!", id_x);
            //
        }




       return IUP_DEFAULT; // NÃO ENCERRA, ANTES DE FAZER A FUNÇÃO ACIMA!
       }


}








/*** NA JANELA QUE VC CRIAR QUE É REPONSÁVEL POR CAPTURAR E SALVAR OS CAMPOS DO FORMULÁRIO, DEIXE UM BOTÃO DE MEMÓRIA ...TALVEZ NEM PRECISE***/




/*****************************************(                 \FUNCTION \MEMORY \MOTOR         )********************************************

***/

static int function_memory_motor(int id_x_arg, int id_y_arg)
{
    Ihandle* ih = IupGetHandle("mdi_tag_FORM");




    int id_x = id_x_arg;
    int id_y = id_y_arg;
    int id_k_Motor = matrix_struct[id_x][id_y].motor_indices.id_k_Motor;

         //if(id_k_Motor != 0)

            /*** Isto deve estar na validação do botão load full ***/
            /*** pois somente depois de validar os status 1, 2, 3 que pode ser coletado os dados ***/


                  Ihandle *MemoryBoxValue_x_seq_pos, *MemoryBoxValue_x_seq_neg, *MemoryBoxValue_x_seq_zero, *MemoryBoxValue_x_neutro;
                  Ihandle *MemoryBoxValue_Vm_nominal, *MemoryBoxValue_Pm_nominal;


     struct motor motor_33; //ou gerador_nos_11

                  /*** EFEITO REBOTE           --- SOLUÇÃO!!! ----       ***/
                  motor_33.id_x = id_x_arg;
                  motor_33.id_y = id_y_arg;
                  motor_33.id_k_Motor = id_k_Motor;

            /*** ativando o BoxValue de tensão do motor para coleta***/

            /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

                MemoryBoxValue_Vm_nominal = IupGetDialogChild(ih, "BoxValue_Vm_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_Vm_nominal = IupGetFloat(MemoryBoxValue_Vm_nominal, "VALUE");


                motor_33.Vm_nominal = valor_Vm_nominal;



            /*** ativando o BoxValue de potência do motor para coleta***/

                MemoryBoxValue_Pm_nominal = IupGetDialogChild(ih, "BoxValue_Pm_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_Pm_nominal = IupGetFloat(MemoryBoxValue_Pm_nominal, "VALUE");

                motor_33.Pm_nominal = valor_Pm_nominal;


            /*** ativando o BoxValue de X_seq_pos do motor para coleta***/

                //Ihandle *dlg = IupGetDialog(ih); //capturou a list ou o form?
                //Ihandle *dlg = IupGetHandle("mdi_tag_FORM"); //PUTZ, TAVA CHAMANDO UMA TAG DECLARADA ERRADA mdi_Tag_FORM


                MemoryBoxValue_x_seq_pos = IupGetDialogChild(ih, "BoxValue_Xm_seq_pos_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_x_seq_pos = IupGetFloat(MemoryBoxValue_x_seq_pos, "VALUE");

                motor_33.Xm_seq_pos = valor_x_seq_pos;

            /*** ativando o BoxValue de X_seq_neg do motor para coleta***/

                //Ihandle *undo = IupGetDialogChild(ih, "mdi_tag_FORM");


                MemoryBoxValue_x_seq_neg = IupGetDialogChild(ih, "BoxValue_Xm_seq_neg_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_x_seq_neg = IupGetFloat(MemoryBoxValue_x_seq_neg, "VALUE");

                motor_33.Xm_seq_neg = valor_x_seq_neg;


            /*** ativando o BoxValue de X_seq_zero do motor para coleta***/


                MemoryBoxValue_x_seq_zero = IupGetDialogChild(ih, "BoxValue_Xm_seq_zero_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_x_seq_zero = IupGetFloat(MemoryBoxValue_x_seq_zero, "VALUE");

                motor_33.Xm_seq_zero = valor_x_seq_zero;


            /*** ativando o BoxValue de X_neutro do motor para coleta***/


                MemoryBoxValue_x_neutro = IupGetDialogChild(ih, "BoxValue_Xm_neutro_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_x_neutro = IupGetFloat(MemoryBoxValue_x_neutro, "VALUE");


                motor_33.Xm_pet = valor_x_neutro;



        char string_buffer[50];


                /*** \CRITICO \PARADIGMA - CUIDADO TEXTO MOTOR ***/
                /*** Abaixo é usado o id_toggle do motor de forma temporária para que seja possível inserir diversos motores
                     usando o mesmo frame de dados, logo o id_toggle é armazenado permanentemente na memória do motor em
                     lançamento através da struct que contém os atributos comuns, assim o id_toggle é armazenado no atributo
                     ligação esquema.
                ***/
                        if(id_toggle_MOTOR_estrela != 0){
                            motor_33.ligacao_esquema = id_toggle_MOTOR_estrela;
                            if(id_toggle_MOTOR_estrela == 1){
                                sprintf(string_buffer, "%s", "Y sem aterramento no neutro");
                            }
                            if(id_toggle_MOTOR_estrela == 2){
                                sprintf(string_buffer, "%s", "Y-at sem impedância");
                            }
                            if(id_toggle_MOTOR_estrela == 3){
                                sprintf(string_buffer, "%s", "Y-at com impedância de peterson");
                            }
                            IupMessagef("Aviso!", "O tipo de LIGAÇÃO do motor é %d = %s.", motor_33.ligacao_esquema, string_buffer);
                        }




                //marcador do numeração/quantidade de motores --- OFF
                int index_motor = 1; /*** EM STAND BY - VERIFICAR A POSSIBILIDADE DE IMPLEMENTAR A TÁTICA 1 POR EMPILHAMENTO ***/

                //Carregar_Struct_Gerador(motor_33, index_motor);
                /*** envio massivo ***/
                /*** deixar no botão load full ***/



                if(depurar_motor==1){
                //IupMessagef("Aviso!", "O valor de id_k do motor (%d:%d) é %d", id_x, id_y, id_k_Motor);
                IupMessagef("Aviso!", "O valor de X_pos do motor (%d:%d) é %.2f [%%]", id_x, id_y, motor_33.Xm_seq_pos);
                IupMessagef("Aviso!", "O valor de X_neg do motor (%d:%d) é %.2f [%%]", id_x, id_y, motor_33.Xm_seq_neg);
                IupMessagef("Aviso!", "O valor de X_zero do motor (%d:%d) é %.2f [%%]", id_x, id_y, motor_33.Xm_seq_zero);
                IupMessagef("Aviso!", "O valor de X_peterson de aterramento do motor (%d:%d) é %.2f [%%]", id_x, id_y, motor_33.Xm_pet);

                }

                /*** \depuracao

                IupMessagef("Aviso!", "O valor de X_seq do motor %d:%d é %f", id_x, id_y, matrix_struct[id_x][id_y].motor_indices.Xm_seq_pos); //PASSOU NO TESTE, NÃO HAVIA COMO CARREGAR ACIMA!
                IupMessagef("Aviso!", "O VALOR de X_neg do motor %d:%d é %f", id_x, id_y, matrix_struct[id_x][id_y].motor_indices.Xm_seq_neg);

                ***/

                Carregar_Struct_Matrix_Motor(motor_33, id_x, id_y); /*** envio massivo ***/

                //index_motor = ESTAVA EM STAND BY...!

        return IUP_DEFAULT; //ESTA FUNÇÃO SÓ SE ENCERRA QUANDO FIZER A VOID, DPS ENCERRA ESTA PARA ENTÃO ENCERRAR A FUNÇÃO LIST, diparado pelo item!
}








/*****************************************(                 \FUNCTION \CARREGAR \MEMORY \MOTOR         )********************************************

***/
void Carregar_Struct_Matrix_Motor(struct motor Motor_index, int id_x_arg, int id_y_arg)/*** recebimento massivo ***/
{

    /*** TÁTICA 3 - POR NÓS ***/
    matrix_struct[id_x_arg][id_y_arg].motor_indices = Motor_index;

                if(depurar_motor==1){
                IupMessagef("Aviso!", "REINICIANDO");
                }
                /*** \depuracao
                IupMessagef("Aviso!", "O valor de id_x e id_y do motor são %d e %d", id_x_arg, id_y_arg);

                IupMessagef("Aviso!", "O valor de X_seq do motor %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].motor_indices.Xm_seq_pos);
                IupMessagef("Aviso!", "O VALOR de X_neg do motor %d:%d é %f", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].motor_indices.Xm_seq_neg);

               //+3h peguei, EFEITO REBOTE
                IupMessagef("Aviso!", "O valor de id_k do motor %d:%d é %d - ÚLTIMA VEZ", id_x_arg, id_y_arg, matrix_struct[id_x_arg][id_y_arg].motor_indices.id_k_Motor);
                ***/
}









/************************************************************ \LIGACOES \TRAFOS *********************************************************/








/*****************************************(                 \FUNCTION \OFF         )********************************************

***/
static int button_memory_Ligacao_Trafo1(Ihandle *ih) /*** BOTÃO DE DEFINIÇÃO DA LIGAÇÃO NA JANELA TRANSFORMADOR 1***/
{
    /*** ESTA FUNÇÃO NÃO TEM A FINALIDADE DE CARREGAMENTO, MAS DE INSTRUÇÃO E VALIDAÇÃO DA MEMÓRIA DE TODOS TOGGLES ***/

    //IupMessage("Aviso!", "Função inicializada!");


    /*** \LASTRO \REATIVAR

    id_toggle_definition_tr1 é um marcador de toggle de LIGAÇÃO DO TRANSFORMADOR, entre os toggles das 11 ligações (ou 9 ligações)
    será definido um único id_toggle, e após apertar o botão definir entra aqui nesta função e fica bloqueado inserir novos trafos
    Ahhhh entendi, por isso deu comenteu o uso desta função, pq estava impossibilitando inserir ligação diferentes de novos trafos

    ***/

        if(id_toggle_TR1_nucleo == 1){//Núcleo envolvente

                if (status_memory_trafo_1==0 && id_toggle_definition_tr1 ==0){ //Note que ambos são definidos abaixo, incrementados


                    int i = 1; //Deve começar com 1

                    //rotina de aviso da ligação selecionada no instante
                    for(i = 1; i < 12; i++){ //NÃO PODE COMEÇAR EM ZERO E MENOR QUE 12
                        if(options_TR1[i].option != 0){
                          //IupMessage("Aviso!", "A LIGAÇÃO DO TRAFO 1 É A NÚMERO ! \n Minimize a janela ou encerre-a!"); ...use messageF
                          /*** \depuracao
                          IupMessagef("Aviso!","A LIGAÇÃO DO TRAFO 1 É A NÚMERO %d", options_TR1[i].option);
                          ***/
                          id_toggle_definition_tr1++;
                        }
                    }

                    //IupMessage("Aviso!", "FOR Finalizado!");



                     status_memory_trafo_1++; //IupMessage("Aviso!", "Formulário vazio!");


                     if (status_memory_trafo_1==1){

                     /*** \LISTAGEM \BINARIA \DAS \LIGACOES \DO \TR1

                     /******
                        char* string = (char*)malloc(50*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ***
                        char* string_FULL = (char*)malloc(50*12*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ***


                    //*** Rotina de buffer ******
                       //char Buffer[1]={""};
                       //strcpy(string_FULL, Buffer); //estou inicializando a variável STRING FULL





                        sprintf(string_FULL, "STATUS LIGAÇÃO %d É %d \n", 1, options_TR1[1].option);

                        for(i = 2; i < 12; i++){
                               sprintf(string, "STATUS LIGAÇÃO %d É %d \n", i, options_TR1[i].option);

                               strcat(string_FULL, string);
                        }


                               IupMessagef("Aviso!", "%s", string_FULL);


                        ***/

                        IupMessage("Aviso!", "CARREGADO LIGAÇÃO DO TRAFO DE NÚCLEO ENVOLVENTE! \n Minimize a janela ou encerre-a!");


                     }



                }//redobrar a atenção aqui, só testando que verifiquei que o primeiro clique não pega o incremento com else if, por isso if dentro de if
                else
                      IupMessage("Aviso!", "Prossiga!");
        }




        /*** \LASTRO

        id_toggle_definition_tr1 é um marcador de toggle de LIGAÇÃO DO TRANSFORMADOR, entre os toggles das 11 ligações (ou 9 ligações)
        será definido um único id_toggle, e após apertar o botão definir entra aqui nesta função e fica bloqueado inserir novos trafos
        Ahhhh entendi, por isso deu comenteu o uso desta função, pq estava impossibilitando inserir ligação diferentes de novos trafos

        ***/



        if(id_toggle_TR1_nucleo == 2){//Núcleo envolvido

                if (status_memory_trafo_1==0 && id_toggle_definition_tr1_envolvido ==0){ //Note que ambos são definidos abaixo, incrementados


                    int i = 1; //Deve começar com 1

                    //rotina de aviso da ligação selecionada no instante
                    for(i = 1; i < 4; i++){ //NÃO PODE COMEÇAR EM ZERO E MENOR QUE 12
                        if(options_TR1_envolvido[i].option != 0){
                          //IupMessage("Aviso!", "A LIGAÇÃO DO TRAFO 1 É A NÚMERO ! \n Minimize a janela ou encerre-a!"); ...use messageF
                          /*** \depuracao
                          IupMessagef("Aviso!","A LIGAÇÃO DO TRAFO 1 É A NÚMERO %d", options_TR1[i].option);
                          ***/
                          id_toggle_definition_tr1_envolvido++;
                        }
                    }

                    //IupMessage("Aviso!", "FOR Finalizado!");



                     status_memory_trafo_1++; //IupMessage("Aviso!", "Formulário vazio!");


                     if (status_memory_trafo_1==1){

                        IupMessage("Aviso!", "CARREGADO LIGAÇÃO DO TRAFO DE NÚCLEO ENVOLVIDO! \n Minimize a janela ou encerre-a!");

                     }



            }//redobrar a atenção aqui, só testando que verifiquei que o primeiro clique não pega o incremento com else if, por isso if dentro de if
            else
                  IupMessage("Aviso!", "Prossiga!");
    }




    return IUP_DEFAULT;
}





/*****************************************(          \FUNCTION \LICAGAO \TRAFO \ENVOLVENTE \TOGGLES      )********************************************

***/

static Ihandle* createForm_ligacoes_nucleo_envolvente_trafo1(void) /*** JANELA 1/2 DO TRANSFORMADOR 1 ***/
{
    Ihandle *box, *btn_Ligacao_Trafo;



    /*** Gerada após clicar no botão do frame do transformador ***/



    btn_Ligacao_Trafo = IupButton("Definir", NULL); //FUNCIONOU, DESVINCULEI O FORMULÁRIO DA CRIAÇÃO DA MDI CLIENT SOBREPOSTA
    //IupSetCallback(btn_Ligacao_Trafo,"ACTION", (Icallback)button_memory_Ligacao_Trafo1); // a função, argumento 3, recebe um Ihandle button como disparo

    /*** \LASTRO \REATIVAR

        Reativei em 14jul22 - parece que a ligação estava sem efeito, na real os toggles estava funcionando de boa
        Só reative após implementar com 100% de garantia o núcleo envolvido, a princípio
        a função do botão está bloqueando novas ligações

    ***/


    /*** QUEM DEVE DISPARAR O CARREGAMENTO DA LIGAÇÃO DO TRAFO 1 É O BT ***/


    /******************************************** TABELA COM AS LIGAÇÕES - USE SEPARADORES ***************************************/

    Ihandle *ligacao_01, *ligacao_02, *ligacao_02b, *ligacao_03, *ligacao_03b, *ligacao_04, *ligacao_04b, *ligacao_05, *ligacao_06, *ligacao_07, *ligacao_08;

    Ihandle *toggle_selection = IupToggle("SELECIONE:\n PRIMÁRIO: (\t...\t); \n SECUNDÁRIO: (\t...\t).", NULL);
    IupSetAttribute(toggle_selection, "FONTSTYLE", "Bold");

    ligacao_01 =  IupToggle("1 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: estrela aterrado.", NULL);
    ligacao_02 =  IupToggle("2 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: delta.", NULL);
    ligacao_02b =  IupToggle("3 - PRIMÁRIO: delta; \n SECUNDÁRIO: estrela aterrado.", NULL);
    ligacao_03 =  IupToggle("4 - PRIMÁRIO: estrela; \n SECUNDÁRIO: delta.", NULL);
    ligacao_03b =  IupToggle("5 - PRIMÁRIO: delta; \n SECUNDÁRIO: estrela.", NULL);
    ligacao_04 =  IupToggle("6 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: estrela.", NULL);
    ligacao_04b =  IupToggle("7 - PRIMÁRIO: estrela; \n SECUNDÁRIO: estrela aterrado.", NULL);
    ligacao_05 =  IupToggle("8 - PRIMÁRIO: delta; \n SECUNDÁRIO: delta.", NULL);
    ligacao_06 =  IupToggle("9 - PRIMÁRIO: estrela; \n SECUNDÁRIO: estrela.", NULL);
    //ligacao_07 =  IupToggle("10 - PRIMÁRIO: estrela; \n SECUNDÁRIO: estrela; \n Conexão interna entre estrelas.", NULL);
    //ligacao_08 =  IupToggle("11 - PRIMÁRIO: estrela com impedância de aterramento; \n SECUNDÁRIO: estrela com impedância de aterramento.", NULL);



            IupSetCallback(ligacao_01, "ACTION", (Icallback)function_memory_toggle_01_TR1); //Me liguei, tenho que saber qual toggle é ticado para enviar à função
            IupSetCallback(ligacao_02, "ACTION", (Icallback)function_memory_toggle_02_TR1);
            IupSetCallback(ligacao_02b, "ACTION", (Icallback)function_memory_toggle_02b_TR1);
            IupSetCallback(ligacao_03, "ACTION", (Icallback)function_memory_toggle_03_TR1);
            IupSetCallback(ligacao_03b, "ACTION", (Icallback)function_memory_toggle_03b_TR1);
            IupSetCallback(ligacao_04, "ACTION", (Icallback)function_memory_toggle_04_TR1);
            IupSetCallback(ligacao_04b, "ACTION", (Icallback)function_memory_toggle_04b_TR1);
            IupSetCallback(ligacao_05, "ACTION", (Icallback)function_memory_toggle_05_TR1);
            IupSetCallback(ligacao_06, "ACTION", (Icallback)function_memory_toggle_06_TR1);
            //IupSetCallback(ligacao_07, "ACTION", (Icallback)function_memory_toggle_07_TR1);
            //IupSetCallback(ligacao_08, "ACTION", (Icallback)function_memory_toggle_08_TR1);


        /*** CAIU A FICHA
             o toggle é equivalente ao botão, e a esse está vinculado uma ação, basta ticar que já inicia a ação!
        ***/




      Ihandle *label_Ligacao_trafo = IupLabel("Definir ligação para o transformador trifásico de 2 enrolamentos");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Ligacao_trafo, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Ligacao_trafo, "FONTSTYLE", "Bold");


      Ihandle *Field_Esquema_Ligacao = IupVbox(
                                          IupRadio(
                                                IupVbox(
                                                  toggle_selection,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_01,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_02,
                                                  ligacao_02b,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_03,
                                                  ligacao_03b,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_04,
                                                  ligacao_04b,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_05,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_06,
                                                  //IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  //ligacao_07,
                                                  //IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  //ligacao_08,
                                                  NULL
                                                )
                                           ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                           //IupHbox(BoxValue_x_seq_pos, IupLabel("%"), NULL),
                                           NULL
                                       );

     /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_1_transformador;

      /* Creating box that contains the toggles */
      barra_1_transformador = //IupHbox(
        IupFlatFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
          label_Ligacao_trafo,
            Field_Esquema_Ligacao,
            btn_Ligacao_Trafo,
          NULL)
          );//,
      //  NULL
      //);

      IupSetAttribute(IupGetChild(barra_1_transformador, 1), "TITLE", "Barra 1 - Configuração teste"); //interessante!

      //IupSetAttribute(barra_1_transformador, "BGCOLOR", "0 255 150"); //Fundo dos campos fica colorido
      IupSetAttribute(barra_1_transformador, "BGCOLOR", "255 150 114"); //Fundo dos campos fica colorido


      /************************ FIM FRAME FORMULÁRIO **************************************************************************/


    //box = IupVbox(barra_1_transformador, NULL);
    box = IupVbox(IupSetAttributes( IupScrollBox(barra_1_transformador), "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" ), NULL);
    //Agora o FORM ficou com barra de rolagem, a sacada é a usabilidade em uma tela, viabilizando o uso simultâneo dos formulários de envolvente e envolvido
    IupSetAttribute(box,"MARGIN","5x5");

    return box; //É enviado a arquitetura de uma Vbox para uma dialog em definitivo


}




/*****************************************(          \FUNCTION \LICAGAO \TRAFO \ENVOLVIDO \TOGGLES      )********************************************

***/


static Ihandle* createForm_ligacoes_nucleo_envolvido_trafo1(void) /*** JANELA 2/2 DO TRANSFORMADOR 1 ***/
{
    Ihandle *box, *btn_Ligacao_Trafo;


    btn_Ligacao_Trafo = IupButton("Definir", NULL); //FUNCIONOU, DESVINCULEI O FORMULÁRIO DA CRIAÇÃO DA MDI CLIENT SOBREPOSTA
    //IupSetCallback(btn_Ligacao_Trafo,"ACTION", (Icallback)button_memory_Ligacao_Trafo1); // a função, argumento 3, recebe um Ihandle button como disparo

    /*** \LASTRO \REATIVAR

    id_toggle_definition_tr1 é um marcador de toggle de LIGAÇÃO DO TRANSFORMADOR, entre os toggles das 11 ligações (ou 9 ligações)
    será definido um único id_toggle, e após apertar o botão definir entra aqui nesta função e fica bloqueado inserir novos trafos
    Ahhhh entendi, por isso deu comenteu o uso desta função, pq estava impossibilitando inserir ligação diferentes de novos trafos

    ***/



    /*** QUEM DEVE DISPARAR O CARREGAMENTO DA LIGAÇÃO DO TRAFO 1 É O BT ***/


    /******************************************** TABELA COM AS LIGAÇÕES - USE SEPARADORES ***************************************/

    Ihandle *ligacao_01, *ligacao_02, *ligacao_03;

    Ihandle *toggle_selection = IupToggle("SELECIONE:\n PRIMÁRIO: (\t...\t); \n SECUNDÁRIO: (\t...\t).", NULL);
    IupSetAttribute(toggle_selection, "FONTSTYLE", "Bold");

    ligacao_01 =  IupToggle("1 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: estrela aterrado.", NULL);
    ligacao_02 =  IupToggle("2 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: estrela.", NULL);
    ligacao_03 =  IupToggle("3 - PRIMÁRIO: estrela aterrado; \n SECUNDÁRIO: delta.", NULL);


            IupSetCallback(ligacao_01, "ACTION", (Icallback)function_memory_toggle_01_TR1_envolvido); //Me liguei, tenho que saber qual toggle é ticado para enviar à função
            IupSetCallback(ligacao_02, "ACTION", (Icallback)function_memory_toggle_02_TR1_envolvido);
            IupSetCallback(ligacao_03, "ACTION", (Icallback)function_memory_toggle_03_TR1_envolvido);


        /*** CAIU A FICHA
             o toggle é equivalente ao botão, e a esse está vinculado uma ação, basta ticar que já inicia a ação!
        ***/




      Ihandle *label_Ligacao_trafo = IupLabel("Definir ligação para o transformador trifásico de 2 enrolamentos");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Ligacao_trafo, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Ligacao_trafo, "FONTSTYLE", "Bold");


      Ihandle *Field_Esquema_Ligacao = IupVbox(
                                          IupRadio(
                                                IupVbox(
                                                  toggle_selection,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_01,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_02,
                                                  IupSetAttributes(IupLabel(NULL), "SEPARATOR=HORIZONTAL"),
                                                  ligacao_03,
                                                  NULL
                                                )
                                           ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                           //IupHbox(BoxValue_x_seq_pos, IupLabel("%"), NULL),
                                           NULL
                                       );

     /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_1_transformador;

      /* Creating box that contains the toggles */
      barra_1_transformador = //IupHbox(
        IupFlatFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
          label_Ligacao_trafo,
            Field_Esquema_Ligacao,
            btn_Ligacao_Trafo,
          NULL)
          );//,
      //  NULL
      //);

      IupSetAttribute(IupGetChild(barra_1_transformador, 1), "TITLE", "Barra 1 - Configuração teste"); //interessante!

      IupSetAttribute(barra_1_transformador, "BGCOLOR", "255 100 114"); //Fundo dos campos fica colorido //Verde aquário

      /************************ FIM FRAME FORMULÁRIO **************************************************************************/


    //box = IupVbox(barra_1_transformador, NULL);
    box = IupVbox(IupSetAttributes( IupScrollBox(barra_1_transformador), "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" ), NULL);
    //Agora o FORM ficou com barra de rolagem, a sacada é a usabilidade em uma tela, viabilizando o uso simultâneo dos formulários de envolvente e envolvido
    IupSetAttribute(box,"MARGIN","5x5");

    return box; //É enviado a arquitetura de uma Vbox para uma dialog em definitivo



}






/*****************************************(          \FUNCTION \NUCLEO \TRAFO \SELETOR \TOGGLES      )********************************************

***/

static int button_Ligacao_Trafo(Ihandle *ih) //rapidex! //ESTA FUNÇÃO CRIA UM DOS DOIS FORMULÁRIOS/JANELAS DE LIGAÇÃO A 01/02 ou 02/02
{
      //static int id = 1; //a princípio posso por fora da função e vincular os índices 0 a 3 ao 4 curtos
      //static int status_memory_trafo_1; --- VARIÁVEL GLOBAL ---

      Ihandle *box, *txt, *dlg, *bt;

      //note que o dlg precisa ser indexado para que vc saiba o que afinal
      //vai encerrar, pq cada vez que entra na função é um dlg novo

      if(id_toggle_TR1_nucleo != 1 && id_toggle_TR1_nucleo != 2){

            IupMessagef("Aviso!","Favor selecionar o tipo de núcleo do transformador!");

      }

      //isso foi irado, consegui criar duas janelas que podem ambas estar na tela com acionamento de apenas um botão,
      //assim reaproveito código da MDI


      if(status_memory_trafo_1 == 0 && (id_toggle_TR1_nucleo == 1 || id_toggle_TR1_nucleo == 2)) {

          /*** FORMULÁRIO

          AO CLICAR NO BOTÃO DO FRAME DO TRANSFORMADOR É CRIADO UMA DAS JANELAS DE LIGAÇÃO OU PARA O NÚCLEO ENVOLVENDO OU PARA NÚCLEO ENVOLVIDO

          ***/

          if(id_toggle_TR1_nucleo == 1){//criar um form temporário à um trafo de núcleo envolvente
            box = createForm_ligacoes_nucleo_envolvente_trafo1();
          }

          if(id_toggle_TR1_nucleo == 2){ //criar um form temporário à um trafo de núcleo envolvido
            box = createForm_ligacoes_nucleo_envolvido_trafo1();
          }

          //Me liguei, no caso preciso usar o formulário criado para inserir botões, antes de jogar para IupDialog (finalmentes)

          dlg = IupDialog(box); //captura um Vbox (FORMULÁRIO)

          if(id_toggle_TR1_nucleo == 1){
            IupSetfAttribute(dlg,"TITLE","Seleção da ligação do transformador - NÚCLEO ENVOLVENTE");//(%d) (ASPAS), id); id++;
          }
          if(id_toggle_TR1_nucleo == 2){
            IupSetfAttribute(dlg,"TITLE","Seleção da ligação do transformador - NÚCLEO ENVOLVIDO");//(%d) (ASPAS), id); id++;
          }


        //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
          IupSetAttribute(dlg,"MDICHILD","NO"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS
          IupSetAttribute(dlg,"MDIFRAME","NO");  //não gera janelas filhas //a princípio se quisesse abrir outra janela filho filho por YES
        //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via tag desta
          IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
          IupSetAttribute(dlg,"RASTERSIZE","600x600");
        //  IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");

          IupSetHandle("mdi_tag_TR1", dlg); //tag da janela
          IupSetAttribute(dlg,"PARENTDIALOG","mdi_tag_FORM"); //atribuindo a dlg à janela do Formulário via a tag desta

          IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
          IupSetAttribute(dlg, "DEFAULTESC", "quit");


          IupShow(dlg);

          IupSetAttribute(dlg,"RASTERSIZE",NULL);
      }



      if(status_memory_trafo_1 == 1)
      {
            IupMessage("Aviso!", "Formulário já foi criado!");
            //IupSetCallback(dlg, "CLOSE_CB", (Icallback)close_cb2); //mdi_closeall
            //EM CONSTRUÇÃO: use um dlg indexado e então será possível fechar o formulário
            //pelo que li, ao fechar o formulário ele também é destruído.
            //Dois gargalos o mdi_closeall não funciona e não reseta o formulário
      }
      //O MDI Close não destroy a janela em buffer, apenas fecha a existente
      //contudo isso só funcionou no iuptest.exe da versão 3.30 do iup

  return IUP_DEFAULT;
}





/*****************************************(          \MAQUINAS - \FORM \FRAMES \BOXES     )********************************************

***/






/*****************************************************(        \FORM \GERADOR     )*************************************************

***/



static Ihandle* gerador_Form_Frame(void)
{


/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/

    Ihandle *toggle1, *toggle2, *toggle3, *toggle1_estrela, *toggle2_estrela, *toggle3_estrela;

      toggle1 = IupToggle("&Reatância Subtransitória", "toggle_Xg_sub");
      toggle2 = IupToggle("&Reatância Transitória", "toggle_Xg_trans");
      toggle3 = IupToggle("&Reatância Síncrona", "toggle_Xg_sinc"); //o \n não cede exatamente a linha, mas centraliza o texto ao radio


      toggle1_estrela = IupToggle("&Y", "toggle_Y_estrela_GE"); //isso é uma tag recém criada
      toggle2_estrela = IupToggle("&Y-at", "toggle_Yat_estrela_GE");
      toggle3_estrela = IupToggle("&Y-Zn", "toggle_YZn_estrela_GE"); //o \n não cede exatamente a linha, mas centraliza o texto ao radio


      /*** POR AQUI QUE IREI SABER QUAL TIPO DE REATÂNCIA O USUÁRIO SETOU! ***/

      //FUNÇÕES DAS TAGs dos toggles

      IupSetFunction("toggle_Xg_sub", (Icallback)function_memory_toggle_Xg_sub);
      IupSetFunction("toggle_Xg_trans", (Icallback)function_memory_toggle_Xg_trans);
      IupSetFunction("toggle_Xg_sinc", (Icallback)function_memory_toggle_Xg_sinc);

      IupSetFunction("toggle_Y_estrela_GE", (Icallback)function_memory_toggle_Y_GE_estrela);
      IupSetFunction("toggle_Yat_estrela_GE", (Icallback)function_memory_toggle_Yat_GE_estrela);
      IupSetFunction("toggle_YZn_estrela_GE", (Icallback)function_memory_toggle_YZn_GE_estrela);



    /************************ TEXTOS EM LABELS - INÍCIO **************************************************************************/

    Ihandle *label_x_seq_pos, *label_x_seq_neg, *label_x_seq_zero, *label_x_neutro;



      Ihandle *label_Vg_nominal = IupLabel(NULL);
      IupSetAttribute(label_Vg_nominal, "TITLE", "Tensão nominal do gerador");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Vg_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Vg_nominal, "FONTSTYLE", "Bold");


      Ihandle *label_Pg_nominal = IupLabel(NULL);
      IupSetAttribute(label_Pg_nominal, "TITLE", "Potência nominal do gerador");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Pg_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Pg_nominal, "FONTSTYLE", "Bold");

      label_x_seq_pos = IupLabel(NULL);
      IupSetAttribute(label_x_seq_pos, "TITLE", "Reatância de Sequência Positiva");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_pos, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_pos, "FONTSTYLE", "Bold");

      label_x_seq_neg = IupLabel(NULL);
      IupSetAttribute(label_x_seq_neg, "TITLE", "Reatância de Sequência Negativa");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_neg, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_neg, "FONTSTYLE", "Bold");


      label_x_seq_zero = IupLabel(NULL);
      IupSetAttribute(label_x_seq_zero, "TITLE", "Reatância de Sequência Zero (definir)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_zero, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_zero, "FONTSTYLE", "Bold");


      label_x_neutro = IupLabel(NULL);
      IupSetAttribute(label_x_neutro, "TITLE", "Reatância de Peterson (Neutro - Zn)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_neutro, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_neutro, "FONTSTYLE", "Bold");



      /************************ TEXTOS EM LABELS - FIM **************************************************************************/

      Ihandle *label_fake;


      label_fake = IupLabel(NULL);
      IupSetAttribute(label_fake, "TITLE", " ");

      /************************ CAIXAS DE VALORES COM MEMÓRIA - INÍCIO **************************************************************************/


      Ihandle *BoxValue_Vg_nominal = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Vg_nominal, "NAME", "BoxValue_Vg_nominal_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Vg_nominal, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_Vg_nominal, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      //IupSetFloat(BoxValue_Vg_nominal, "VALUE", 15.0); //ajustei como inteiro...tolice...impreciso
      IupSetfAttribute(BoxValue_Vg_nominal, "VALUE", "%.2f", 13.8); //SHOW CONSEGUI, lembre-se do erro acima!
      //IupSetStrf(TxtPhasorIa, "VALUE", "%.lf", to_degree(arg(calc_Iphase_a)));




      Ihandle *BoxValue_Pg_nominal = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Pg_nominal, "NAME", "BoxValue_Pg_nominal_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Pg_nominal, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_Pg_nominal, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Pg_nominal, "VALUE", "%.2f", 30.0);


 //   Ihandle *MemoryBoxValue_Vg_nominal_OFF = IupGetDialogChild(NULL, "BoxValue_Vg_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
 //       float valor_Vg_nominal_OFF = IupGetFloat(MemoryBoxValue_Vg_nominal_OFF, "VALUE"); //a princípio vai exibir zero pq o forms ainda não foi criado

      //IupMessagef("Aviso!","A tensão do gerador é %f", 25.0);//valor_Vg_nominal_OFF); ---- teste útil demais
      //IupMessagef("Aviso!","A tensão do gerador é %.2f", valor_Vg_nominal_OFF);//valor_Vg_nominal_OFF); ---- teste útil demais
                                                                               //a princípio vai exibir zero pq o forms ainda não foi criado


      Ihandle *BoxValue_x_seq_pos = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_pos, "NAME", "BoxValue_Xg_seq_pos_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_pos, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_seq_pos, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_pos, "VALUE", "%.2f", 15.0);


      //Como o DialogChild não é disparado de uma função tipo Ihandle, por se corrente a codificação, recebe NULL
      //O primeiro argumento parece nitidamente um disparo de ação, só envie à memória após acionar determinado Ihandle! (botão)
      //de fato, então a memória só funcionaria com disparo de um Ihandle, coletando-se informação de um BoxValue



      Ihandle *BoxValue_x_seq_neg = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_neg, "NAME", "BoxValue_Xg_seq_neg_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_neg, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_seq_neg, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_neg, "VALUE", "%.2f", 20.0);



      Ihandle *BoxValue_x_seq_zero = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_zero, "NAME", "BoxValue_Xg_seq_zero_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_zero, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_seq_zero, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_zero, "VALUE", "%.2f", 5.0);



      Ihandle *BoxValue_x_neutro = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_neutro, "NAME", "BoxValue_Xg_neutro_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_neutro, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_neutro, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_neutro, "VALUE", "%.2f", 0.0);




      /************************ CAIXAS DE VALORES COM MEMÓRIA - FIM **************************************************************************/

                Ihandle *toggle_define = IupToggle("Definir:", NULL);
                Ihandle *toggle_define_estrela = IupToggle("Definir:", NULL); //defaine

                Ihandle *list_gerador;

                //list_gerador_OLD = function_List_gerador(); //Return do tipo Ihandle = vBox

                //list_gerador_NEW = function_List_gerador_NEW();

                list_gerador = function_List_gerador(); //ESTE CARA ESTA DENTRO DO FRAME GERADOR, E NÃO NA DEFINIÇÃO DE BARRAS


                 /* Creates zbox with two elements */
                //zbox = IupZbox (list_gerador_OLD, list_gerador_NEW, NULL);




      /************************ CAMPOS DE VALORES COM UNIDADES - INÍCIO **************************************************************************/

      Ihandle *Field_Vg_nominal = IupHbox(BoxValue_Vg_nominal, IupLabel("kV"), NULL);
      Ihandle *Field_Pg_nominal = IupHbox(BoxValue_Pg_nominal, IupLabel("MVA"), NULL);
      Ihandle *Field_x_seq_pos = IupVbox(
                                      IupRadio(
                                                IupVbox(
                                                    IupHbox(toggle_define, BoxValue_x_seq_pos, IupLabel("%"), NULL),
                                                    IupHbox(
                                                      toggle1,
                                                      toggle2,
                                                      toggle3,
                                                      NULL
                                                    ),
                                                    NULL
                                                )
                                       ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                       NULL
                                  );
      Ihandle *Field_x_seq_neg = IupHbox(BoxValue_x_seq_neg, IupLabel("%"), NULL);
      //Ihandle *Field_x_seq_zero = IupHbox(BoxValue_x_seq_zero, IupLabel("%"), NULL); //<<<OLD

      Ihandle *label_fake_horizontal_01, *label_fake_horizontal_02;

      label_fake_horizontal_01 = IupLabel("                 ");
      label_fake_horizontal_02 = IupLabel("                 ");

      Ihandle *Field_x_seq_zero = IupVbox(
                                      IupRadio(
                                                IupVbox(
                                                    IupHbox(toggle_define_estrela, BoxValue_x_seq_zero, IupLabel("%"), NULL),
                                                    IupHbox(
                                                      toggle1_estrela,
                                                      label_fake_horizontal_01,
                                                      toggle2_estrela,
                                                      label_fake_horizontal_02,
                                                      toggle3_estrela,
                                                      NULL
                                                    ),
                                                    NULL
                                                )
                                       ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                       NULL
                                  );

      Ihandle *Field_x_neutro = IupHbox(BoxValue_x_neutro, IupLabel("Ohms"), NULL);


      /************************ CAMPOS DE VALORES COM UNIDADES - FIM **************************************************************************/



/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/



      /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_1_gerador, *frame_GE;

      frame_GE = IupFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe <<<<<<<<<<<<<<<<<<<<<<<< FRAME
            list_gerador,
          IupSetAttributes(label_fake, "SIZE=75x5, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
          label_Vg_nominal,
            Field_Vg_nominal,
          label_Pg_nominal,
            Field_Pg_nominal,
          label_x_seq_pos,
            Field_x_seq_pos,
          label_x_seq_neg,
            Field_x_seq_neg,
          label_x_seq_zero,
            Field_x_seq_zero,
          label_x_neutro,
            Field_x_neutro,
          NULL)
          );

      /* Creating box that contains the toggles */
      barra_1_gerador = IupHbox(
        IupVbox(
          NULL),
        frame_GE,
        NULL);

      //IupSetAttributes(barra_1_gerador, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER");

      //IupSetAttribute(IupGetChild(barra_1_gerador, 1), "TITLE", "Dados do(s) Gerador(es)"); //interessante!



          IupSetAttributes(frame_GE, "FGCOLOR=\"0 0 255\", SIZE=EIGHTHxEIGHTH, TITLE=\"Dados do(s) Gerador(es)\"");//, MARGIN=10x10

          IupSetAttributes ( list_gerador,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");//FONTSTYLE = Bold,//FONTSIZE = \"12\",
          //Na lista ainda tem como individualizar as cores das letras no Ihandle list_motor

          IupSetAttributes ( label_Vg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Vg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_Pg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Pg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_pos,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_pos,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_neg,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_neg,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_zero,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_zero,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_neutro,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_neutro,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

      IupSetAttribute(barra_1_gerador, "BGCOLOR", "0 255 255"); //Fundo dos campos fica colorido ...azul anil - cor sóbria

      /************************ FIM FRAME FORMULÁRIO **************************************************************************/

    return barra_1_gerador; //note que saquei fora todas as especificações do gerador e estou retornando um Ihandle para a função createForm
}






/**************************************************(      \RESET \BOXES \VALUES \GERADOR     )*************************************************

***/


int run_reset_GERADOR(Ihandle *self2 ) /*** BoxValue limpeza ***/
{
    Ihandle* BoxValue_Vg = IupGetDialogChild(self2, "BoxValue_Vg_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Pg = IupGetDialogChild(self2, "BoxValue_Pg_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Xg_seq_pos = IupGetDialogChild(self2, "BoxValue_Xg_seq_pos_tag");
    Ihandle* BoxValue_Xg_seq_neg = IupGetDialogChild(self2, "BoxValue_Xg_seq_neg_tag");
    Ihandle* BoxValue_Xg_seq_zero = IupGetDialogChild(self2, "BoxValue_Xg_seq_zero_tag");
    Ihandle* BoxValue_Xg_neutro = IupGetDialogChild(self2, "BoxValue_Xg_neutro_tag");


    IupSetAttribute(BoxValue_Vg, "VALUE","");
    IupSetAttribute(BoxValue_Pg, "VALUE","");
    IupSetAttribute(BoxValue_Xg_seq_pos, "VALUE","");
    IupSetAttribute(BoxValue_Xg_seq_neg, "VALUE","");
    IupSetAttribute(BoxValue_Xg_seq_zero, "VALUE","");
    IupSetAttribute(BoxValue_Xg_neutro, "VALUE","");




  return IUP_DEFAULT;
}






/**************************************************(      \FORM \TRANSFORMADOR 1     )*************************************************

***/





static Ihandle* transformador1_Form_Frame(void)
{


/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/

    Ihandle *toggle1_tr1, *toggle2_tr1;

      toggle1_tr1 = IupToggle("&Envolvido", "tag_toggle_envolvido_tr1"); //CUIDADO, NÃO PODE TER A MESMA TAG PARA O TR1 E TR2
      toggle2_tr1 = IupToggle("&Envolvente", "tag_toggle_envolvente_tr1");




      /*** POR AQUI QUE IREI SABER QUAL TIPO DE REATÂNCIA O USUÁRIO SETOU! ***/

      IupSetFunction("tag_toggle_envolvido_tr1", (Icallback)function_memory_toggle_envolvido_TR1);
      IupSetFunction("tag_toggle_envolvente_tr1", (Icallback)function_memory_toggle_envolvente_TR1);

      /***************************************************************************************************************************/
      Ihandle *label_fake;



      label_fake = IupLabel(NULL);
      IupSetAttribute(label_fake, "TITLE", " ");




    /************************ TEXTOS EM LABELS - INÍCIO **************************************************************************/


      Ihandle *label_Vt_nominal = IupLabel(NULL); /*** Label comum às tensões do primário e secundário ***/
      IupSetAttribute(label_Vt_nominal, "TITLE", "Tensão nominal do transformador");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Vt_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Vt_nominal, "FONTSTYLE", "Bold");


      Ihandle *label_Pt_nominal = IupLabel(NULL);
      IupSetAttribute(label_Pt_nominal, "TITLE", "Potência nominal do transformador");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Pt_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Pt_nominal, "FONTSTYLE", "Bold");


      Ihandle *label_Xeq_trafo = IupLabel(NULL);
      IupSetAttribute(label_Xeq_trafo, "TITLE", "Reatância equivalente do transformador");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Xeq_trafo, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Xeq_trafo, "FONTSTYLE", "Bold");


      Ihandle *label_Esquema_Ligacao = IupLabel(NULL);
      IupSetAttribute(label_Esquema_Ligacao, "TITLE", "Esquema de Ligação (definir)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Esquema_Ligacao, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Esquema_Ligacao, "FONTSTYLE", "Bold");



      /************************ TEXTOS EM LABELS - FIM **************************************************************************/


      /************************ CAIXAS DE VALORES COM MEMÓRIA - INÍCIO **************************************************************************/

     //cuidado, achei por sorte o conflito de tags entre o TR1 e TR2

      Ihandle *BoxValue_Vt_nominal_primario = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Vt_nominal_primario, "NAME", "BoxValue_Vtr1_nominal_primario_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Vt_nominal_primario, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Vt_nominal_primario, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Vt_nominal_primario, "VALUE", "%.2f", 13.8);



      Ihandle *BoxValue_Vt_nominal_secundario = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Vt_nominal_secundario, "NAME", "BoxValue_Vtr1_nominal_secundario_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Vt_nominal_secundario, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Vt_nominal_secundario, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Vt_nominal_secundario, "VALUE", "%.2f", 69.0);



      Ihandle *BoxValue_Pt_nominal = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Pt_nominal, "NAME", "BoxValue_Ptr1_nominal_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Pt_nominal, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Pt_nominal, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Pt_nominal, "VALUE", "%.2f", 30.0);



      Ihandle *BoxValue_Xeq_trafo = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Xeq_trafo, "NAME", "BoxValue_Xeq_trafo1_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Xeq_trafo, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Xeq_trafo, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Xeq_trafo, "VALUE", "%.2f", 10.0);






      /************************ CAIXAS DE VALORES COM MEMÓRIA - FIM **************************************************************************/

                Ihandle *list_trafo;

                //list_gerador_OLD = function_List_gerador(); //Return do tipo Ihandle = vBox

                //list_gerador_NEW = function_List_gerador_NEW();

                list_trafo = function_List_TR1(); //ESTE CARA ESTA DENTRO DO FRAME GERADOR, E NÃO NA DEFINIÇÃO DE BARRAS


                 /* Creates zbox with two elements */
                //zbox = IupZbox (list_gerador_OLD, list_gerador_NEW, NULL);




      /************************ CAMPOS DE VALORES COM UNIDADES - INÍCIO **************************************************************************/
      Ihandle *toggle_define = IupToggle("Definir núcleo:", NULL);

      Ihandle *Field_Vt_nominal_primario = IupHbox(BoxValue_Vt_nominal_primario, IupLabel("kV - Primário"), NULL);
      Ihandle *Field_Vt_nominal_secundario = IupHbox(BoxValue_Vt_nominal_secundario, IupLabel("kV - Secundário"), NULL);
      Ihandle *Field_Pt_nominal = IupHbox(BoxValue_Pt_nominal, IupLabel("MVA"), NULL);
      Ihandle *Field_Xeq_trafo = IupHbox(BoxValue_Xeq_trafo, IupLabel("%"), NULL);
      Ihandle *Field_Esquema_Ligacao = IupVbox(
                                          IupRadio(
                                                IupHbox(
                                                  //IupToggle("Definir:", NULL),
                                                  toggle_define,
                                                  toggle2_tr1,
                                                  toggle1_tr1,
                                                  NULL
                                                )
                                           ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                           //IupHbox(BoxValue_x_seq_pos, IupLabel("%"), NULL),
                                           NULL
                                       );


      /************************ CAMPOS DE VALORES COM UNIDADES - FIM **************************************************************************/

      /************************ DISPARO BOTÃO LIGAÇÕES DO TRANSFORMADOR - INÍCIO **************************************************************/

      Ihandle *btn_Ligacao_Trafo;

      btn_Ligacao_Trafo = IupButton("Selecionar", NULL);
      IupSetCallback(btn_Ligacao_Trafo,"ACTION", (Icallback)button_Ligacao_Trafo); //a função (argumento 3) recebe um Ihandle (disparo do botão)...essa função deve retornar outro Ihandle tipo janela (disparar outra função com canvas options).

      /************************ DISPARO BOTÃO LIGAÇÕES DO TRANSFORMADOR - FIM **************************************************************/


      /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_1_transformador, *frame_TRAFO;

      frame_TRAFO = IupFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
            list_trafo,
          IupSetAttributes(label_fake, "SIZE=75x5, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
          label_Vt_nominal,
            Field_Vt_nominal_primario,
            Field_Vt_nominal_secundario,
          label_Pt_nominal,
            Field_Pt_nominal,
          label_Xeq_trafo,
            Field_Xeq_trafo,
          label_Esquema_Ligacao,
            Field_Esquema_Ligacao,
            btn_Ligacao_Trafo,
          NULL)
          );

      /* Creating box that contains the toggles */
      barra_1_transformador = IupHbox(
        IupVbox(
          //IupSetAttributes(IupBackgroundBox(toggle3), "BGCOLOR=\"255 0 0\""),
          //toggle3_tr, //tava usando um toggle do gerador, esqueci de por tr
          NULL),
        frame_TRAFO,
        NULL);

      //IupSetAttribute(IupGetChild(barra_1_transformador, 1), "TITLE", "Dados do(s) Transformador(es)"); //interessante!


          IupSetAttributes(frame_TRAFO, "FGCOLOR=\"0 0 255\", SIZE=EIGHTHxEIGHTH, TITLE=\"Dados do(s) Transformador(es)\", MARGIN=10x10");//

          IupSetAttributes ( list_trafo,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");//FONTSTYLE = Bold,//FONTSIZE = \"12\",

          IupSetAttributes ( label_Vt_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Vt_nominal_primario,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Vt_nominal_secundario,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_Pt_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Pt_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_Xeq_trafo,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Xeq_trafo,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_Esquema_Ligacao,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Esquema_Ligacao,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( btn_Ligacao_Trafo,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

      //IupSetAttribute(barra_1_transformador, "BGCOLOR", "255 100 114"); //Fundo dos campos fica colorido - Violeta "255 0 255" ... Lilás 255 46 114");
      IupSetAttribute(barra_1_transformador, "BGCOLOR", "255 100 114"); //Fundo dos campos fica colorido - Violeta "255 0 255" ... Lilás 255 46 114");


      /************************ FIM FRAME FORMULÁRIO **************************************************************************/

    return barra_1_transformador; //note que saquei fora todas as especificações do gerador e estou retornando um Ihandle para a função createForm
}







/**************************************************(        \RESET \BOXES \VALUES \TRAFO     )*************************************************

***/


int run_reset_TRAFO(Ihandle *self2 ) /*** BoxValue limpeza ***/
{
    Ihandle* BoxValue_Vtr1_nominal_primario = IupGetDialogChild(self2, "BoxValue_Vtr1_nominal_primario_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Vtr1_nominal_secundario = IupGetDialogChild(self2, "BoxValue_Vtr1_nominal_secundario_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Ptr1_nominal = IupGetDialogChild(self2, "BoxValue_Ptr1_nominal_tag");
    Ihandle* BoxValue_Xeq_trafo1 = IupGetDialogChild(self2, "BoxValue_Xeq_trafo1_tag");


    IupSetAttribute(BoxValue_Vtr1_nominal_primario, "VALUE","");
    IupSetAttribute(BoxValue_Vtr1_nominal_secundario, "VALUE","");
    IupSetAttribute(BoxValue_Ptr1_nominal, "VALUE","");
    IupSetAttribute(BoxValue_Xeq_trafo1, "VALUE","");




  return IUP_DEFAULT;
}








/**************************************************(      \FORM \LINHA \DE \TRANSMISSAO     )*************************************************

***/



static Ihandle* linha_LT_Form_Frame(void)
{
      Ihandle *toggle1_LT;

      //toggle1_LT = IupToggle("&Linha de Transmissão", NULL);



    /************************ TEXTOS EM LABELS - INÍCIO **************************************************************************/

    Ihandle *label_x_seq_pos_LT, *label_x_seq_neg_LT, *label_x_seq_zero_LT, *label_fake;



      label_fake = IupLabel(NULL);
      IupSetAttribute(label_fake, "TITLE", " ");


      label_x_seq_pos_LT = IupLabel(NULL);
      IupSetAttribute(label_x_seq_pos_LT, "TITLE", "Reatância de Sequência Positiva");// (definir)
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_pos_LT, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_pos_LT, "FONTSTYLE", "Bold");

    label_x_seq_neg_LT = IupLabel(NULL);
      IupSetAttribute(label_x_seq_neg_LT, "TITLE", "Reatância de Sequência Negativa");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_neg_LT, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_neg_LT, "FONTSTYLE", "Bold");


      label_x_seq_zero_LT = IupLabel(NULL);
      IupSetAttribute(label_x_seq_zero_LT, "TITLE", "Reatância de Sequência Zero");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_zero_LT, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_zero_LT, "FONTSTYLE", "Bold");


/************************ TEXTOS EM LABELS - FIM **************************************************************************/


/************************ CAIXAS DE VALORES COM MEMÓRIA - INÍCIO **************************************************************************/

      //memória está na função memory_linha_transmission()

      Ihandle *BoxValue_x_seq_pos_LT = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_pos_LT, "NAME", "BoxValue_x_seq_pos_LT_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_pos_LT, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_x_seq_pos_LT, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_pos_LT, "VALUE", "%.2f", 15.87);

      //Como o DialogChild não é disparado de uma função tipo Ihandle, por se corrente a codificação, recebe NULL
      //O primeiro argumento parece nitidamente um disparo de ação, só envie à memória após acionar determinado Ihandle! (botão)
      //de fato, então a memória só funcionaria com disparo de um Ihandle, coletando-se informação de um BoxValue


      //valor_x_seq_pos++; //uma vez armazenado na memória (após coleta) procede-se aos cálculos pertinentes

      Ihandle *BoxValue_x_seq_neg_LT = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_neg_LT, "NAME", "BoxValue_x_seq_neg_LT_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_neg_LT, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_x_seq_neg_LT, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_neg_LT, "VALUE", "%.2f", 15.87);



      Ihandle *BoxValue_x_seq_zero_LT = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_zero_LT, "NAME", "BoxValue_x_seq_zero_LT_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_zero_LT, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_x_seq_zero_LT, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_zero_LT, "VALUE", "%.2f", 47.61);



      /************************ CAIXAS DE VALORES COM MEMÓRIA - FIM **************************************************************************/

                Ihandle *list_LT;

                //list_gerador_OLD = function_List_gerador(); //Return do tipo Ihandle = vBox

                //list_gerador_NEW = function_List_gerador_NEW();

                list_LT = function_List_LT(); //ESTE CARA ESTA DENTRO DO FRAME GERADOR, E NÃO NA DEFINIÇÃO DE BARRAS


                 /* Creates zbox with two elements */
                //zbox = IupZbox (list_gerador_OLD, list_gerador_NEW, NULL);





      /************************ CAMPOS DE VALORES COM UNIDADES - INÍCIO **************************************************************************/

      Ihandle *Field_x_seq_pos_LT = IupHbox(BoxValue_x_seq_pos_LT, IupLabel("Ohms"), NULL);
      Ihandle *Field_x_seq_neg_LT = IupHbox(BoxValue_x_seq_neg_LT, IupLabel("Ohms"), NULL);
      Ihandle *Field_x_seq_zero_LT = IupHbox(BoxValue_x_seq_zero_LT, IupLabel("Ohms"), NULL);


      /************************ CAMPOS DE VALORES COM UNIDADES - FIM **************************************************************************/




/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/



      /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_2_LT, *frame_LT;

      frame_LT = IupFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
            list_LT,
          IupSetAttributes(label_fake, "SIZE=75x5, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
          label_x_seq_pos_LT,
            Field_x_seq_pos_LT,
          label_x_seq_neg_LT,
            Field_x_seq_neg_LT,
          label_x_seq_zero_LT,
            Field_x_seq_zero_LT,
          NULL)
          );

      /* Creating box that contains the toggles */
      barra_2_LT = IupHbox(
        IupVbox(
          //IupSetAttributes(IupBackgroundBox(toggle3), "BGCOLOR=\"255 0 0\""),
            //toggle1_LT,
          NULL),
        frame_LT, //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        NULL);


      //barra_2_LT = frame_LT;

          //IupSetAttributes ( lbl_6,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER");

          /* Sets frame's attributes */
          IupSetAttributes(frame_LT, "FGCOLOR=\"0 0 255\", SIZE=EIGHTHxEIGHTH, TITLE=\"Dados da(s) Linha(s) de Transmissão\", MARGIN=10x10");

          IupSetAttributes ( list_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");//FONTSTYLE = Bold,//FONTSIZE = \"12\",

          IupSetAttributes ( label_x_seq_pos_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_pos_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_neg_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_neg_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_zero_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_zero_LT,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");



      //IupSetAttributes(barra_2_LT, "SIZE=200x50, EXPAND=YES, ALIGNMENT=ACENTER");

      //IupSetAttribute(IupGetChild(barra_2_LT, 1), "TITLE", "Dados da(s) Linha(s) de Transmissão"); //interessante!
      //IupSetAttributes(IupGetChild(barra_2_LT, 1), "FGCOLOR=\"255 0 0\", SIZE=EIGHTHxEIGHTH, TITLE=\"Copyright\", MARGIN=10x10");
      //IupSetAttributes(barra_2_LT, "FGCOLOR=\"255 0 0\", SIZE=EIGHTHxEIGHTH, TITLE=\"Copyright\", MARGIN=10x10");

      IupSetAttribute(barra_2_LT, "BGCOLOR", "27 181 255"); //Fundo dos campos fica colorido - LT: verde "0 255 0"); ...azul prateado

      /************************ FIM FRAME FORMULÁRIO **************************************************************************/

    return barra_2_LT; //note que saquei fora todas as especificações do gerador e estou retornando um Ihandle para a função createForm
}







/**************************************************(        \RESET \BOXES \VALUES \LT     )*************************************************

***/


int run_reset_LT(Ihandle *self2 ) /*** BoxValue limpeza ***/
{
    Ihandle* BoxValue_x_seq_pos_LT = IupGetDialogChild(self2, "BoxValue_x_seq_pos_LT_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_x_seq_neg_LT = IupGetDialogChild(self2, "BoxValue_x_seq_neg_LT_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_x_seq_zero_LT = IupGetDialogChild(self2, "BoxValue_x_seq_zero_LT_tag");


    IupSetAttribute(BoxValue_x_seq_pos_LT, "VALUE","");
    IupSetAttribute(BoxValue_x_seq_neg_LT, "VALUE","");
    IupSetAttribute(BoxValue_x_seq_zero_LT, "VALUE","");



  return IUP_DEFAULT;
}












/**************************************************(        \FORM \MOTOR     )*************************************************

***/



static Ihandle* motor_Form_Frame(void)
{


/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/

    Ihandle *toggle1, *toggle2, *toggle3, *toggle1_estrela, *toggle2_estrela, *toggle3_estrela;

      toggle1 = IupToggle("&Reatância Subtransitória", "toggle_Xm_sub");
      toggle2 = IupToggle("&Reatância Transitória", "toggle_Xm_trans");
      toggle3 = IupToggle("&Reatância Síncrona", "toggle_Xm_sinc"); //o \n não cede exatamente linha, mas centraliza o texto ao radio


      toggle1_estrela = IupToggle("&Y", "toggle_Y_estrela_MOTOR"); //isso é uma tag recém criada
      toggle2_estrela = IupToggle("&Y-at", "toggle_Yat_estrela_MOTOR");
      toggle3_estrela = IupToggle("&Y-Zn", "toggle_YZn_estrela_MOTOR"); //o \n não cede exatamente a linha, mas centraliza o texto ao radio


      /*** POR AQUI QUE IREI SABER QUAL TIPO DE REATÂNCIA O USUÁRIO SETOU! ***/

      //FUNÇÕES DAS TAGs dos toggles

      IupSetFunction("toggle_Xm_sub", (Icallback)function_memory_toggle_Xm_sub);
      IupSetFunction("toggle_Xm_trans", (Icallback)function_memory_toggle_Xm_trans);
      IupSetFunction("toggle_Xm_sinc", (Icallback)function_memory_toggle_Xm_sinc);

      IupSetFunction("toggle_Y_estrela_MOTOR", (Icallback)function_memory_toggle_Y_MOTOR_estrela);
      IupSetFunction("toggle_Yat_estrela_MOTOR", (Icallback)function_memory_toggle_Yat_MOTOR_estrela);
      IupSetFunction("toggle_YZn_estrela_MOTOR", (Icallback)function_memory_toggle_YZn_MOTOR_estrela);


    /***************************************************************************************************************************/
      Ihandle *label_fake;



      label_fake = IupLabel(NULL);
      IupSetAttribute(label_fake, "TITLE", " ");

    /************************ TEXTOS EM LABELS - INÍCIO - MOTOR **************************************************************************/

    Ihandle *label_x_seq_pos, *label_x_seq_neg, *label_x_seq_zero, *label_x_neutro;


      Ihandle *label_Vg_nominal = IupLabel(NULL);
      IupSetAttribute(label_Vg_nominal, "TITLE", "Tensão nominal do motor");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Vg_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Vg_nominal, "FONTSTYLE", "Bold");


      Ihandle *label_Pg_nominal = IupLabel(NULL);
      IupSetAttribute(label_Pg_nominal, "TITLE", "Potência nominal do motor");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_Pg_nominal, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_Pg_nominal, "FONTSTYLE", "Bold");


      label_x_seq_pos = IupLabel(NULL);
      IupSetAttribute(label_x_seq_pos, "TITLE", "Reatância de Sequência Positiva");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_pos, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_pos, "FONTSTYLE", "Bold");

      label_x_seq_neg = IupLabel(NULL);
      IupSetAttribute(label_x_seq_neg, "TITLE", "Reatância de Sequência Negativa");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_neg, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_neg, "FONTSTYLE", "Bold");


      label_x_seq_zero = IupLabel(NULL);
      IupSetAttribute(label_x_seq_zero, "TITLE", "Reatância de Sequência Zero (definir)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_seq_zero, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_seq_zero, "FONTSTYLE", "Bold");


      label_x_neutro = IupLabel(NULL);
      IupSetAttribute(label_x_neutro, "TITLE", "Reatância de Peterson (Neutro - Zn)");
    //  IupSetAttribute(label, "RASTERSIZE", "150x70");
    //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
    //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
      IupSetAttribute(label_x_neutro, "FONT", "Helvetica, 10");
    //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
    //  IupSetAttribute(label, "FONTSIZE", "14");
    //  IupSetAttribute(label, "FONTSTYLE", "Italic");
      IupSetAttribute(label_x_neutro, "FONTSTYLE", "Bold");



      /************************ TEXTOS EM LABELS - FIM **************************************************************************/


      /************************ CAIXAS DE VALORES COM MEMÓRIA - INÍCIO **************************************************************************/



      Ihandle *BoxValue_Vg_nominal = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Vg_nominal, "NAME", "BoxValue_Vm_nominal_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Vg_nominal, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Vg_nominal, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Vg_nominal, "VALUE", "%.2f", 13.8);



      Ihandle *BoxValue_Pg_nominal = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_Pg_nominal, "NAME", "BoxValue_Pm_nominal_tag"); //tag ao texto
      IupSetAttribute(BoxValue_Pg_nominal, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_Pg_nominal, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Pg_nominal, "VALUE", "%.2f", 100.);



      Ihandle *BoxValue_x_seq_pos = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_pos, "NAME", "BoxValue_Xm_seq_pos_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_pos, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_x_seq_pos, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_pos, "VALUE", "%.2f", 13.0);

      //Como o DialogChild não é disparado de uma função tipo Ihandle, por se corrente a codificação, recebe NULL
      //O primeiro argumento parece nitidamente um disparo de ação, só envie à memória após acionar determinado Ihandle! (botão)
      //de fato, então a memória só funcionaria com disparo de um Ihandle, coletando-se informação de um BoxValue


      //valor_x_seq_pos++; //uma vez armazenado na memória (após coleta) procede-se aos cálculos pertinentes

      Ihandle *BoxValue_x_seq_neg = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_neg, "NAME", "BoxValue_Xm_seq_neg_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_neg, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      IupSetAttribute(BoxValue_x_seq_neg, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_neg, "VALUE", "%.2f", 18.0);



      Ihandle *BoxValue_x_seq_zero = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_seq_zero, "NAME", "BoxValue_Xm_seq_zero_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_seq_zero, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_seq_zero, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_seq_zero, "VALUE", "%.2f", 4.0);



      Ihandle *BoxValue_x_neutro = IupText(NULL); //doideira, começa com um IupText
      IupSetAttribute(BoxValue_x_neutro, "NAME", "BoxValue_Xm_neutro_tag"); //tag ao texto
      IupSetAttribute(BoxValue_x_neutro, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
      //IupSetInt(TextAngleIa0, "VALUE", 10);// seta o campo no valor desejado
      IupSetAttribute(BoxValue_x_neutro, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_x_neutro, "VALUE", "%.2f", 2.0);




      /************************ CAIXAS DE VALORES COM MEMÓRIA - FIM **************************************************************************/

                Ihandle *toggle_define = IupToggle("Definir:", NULL);

                Ihandle *toggle_define_estrela = IupToggle("Definir:", NULL); //defaine



                Ihandle *list_motor;

                //list_gerador_OLD = function_List_gerador(); //Return do tipo Ihandle = vBox

                //list_gerador_NEW = function_List_gerador_NEW();

                list_motor = function_List_motor(); //ESTE CARA ESTA DENTRO DO FRAME GERADOR, E NÃO NA DEFINIÇÃO DE BARRAS


                 /* Creates zbox with two elements */
                //zbox = IupZbox (list_gerador_OLD, list_gerador_NEW, NULL);



      /************************ CAMPOS DE VALORES COM UNIDADES - INÍCIO **************************************************************************/

      Ihandle *label_fake_horizontal_01, *label_fake_horizontal_02;
      label_fake_horizontal_01 = IupLabel("                 ");
      label_fake_horizontal_02 = IupLabel("                 ");

      Ihandle *Field_Vg_nominal = IupHbox(BoxValue_Vg_nominal, IupLabel("kV"), NULL);
      Ihandle *Field_Pg_nominal = IupHbox(BoxValue_Pg_nominal, IupLabel("MVA"), NULL);
      Ihandle *Field_x_seq_pos = IupVbox(
                                      IupRadio(
                                                IupVbox(
                                                    IupHbox(toggle_define, BoxValue_x_seq_pos, IupLabel("%"), NULL),
                                                    IupHbox(
                                                      toggle1,
                                                      toggle2,
                                                      toggle3,
                                                      NULL
                                                    ),
                                                    NULL
                                                )
                                       ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                       NULL
                                  );
      Ihandle *Field_x_seq_neg = IupHbox(BoxValue_x_seq_neg, IupLabel("%"), NULL);
      //Ihandle *Field_x_seq_zero = IupHbox(BoxValue_x_seq_zero, IupLabel("%"), NULL); <<< OLD
      Ihandle *Field_x_seq_zero = IupVbox(
                                      IupRadio(
                                                IupVbox(
                                                    IupHbox(toggle_define_estrela, BoxValue_x_seq_zero, IupLabel("%"), NULL),
                                                    IupHbox(
                                                      toggle1_estrela,
                                                      label_fake_horizontal_01,
                                                      toggle2_estrela,
                                                      label_fake_horizontal_02,
                                                      toggle3_estrela,
                                                      NULL
                                                    ),
                                                    NULL
                                                )
                                       ), //curioso não precisou do NULL para o Vbox ...tanto faz
                                       NULL
                                  );
      Ihandle *Field_x_neutro = IupHbox(BoxValue_x_neutro, IupLabel("Ohms"), NULL);


      /************************ CAMPOS DE VALORES COM UNIDADES - FIM **************************************************************************/





/************************ INÍCIO FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/


      /************************ INÍCIO FRAME FORMULÁRIO **************************************************************************/
      Ihandle *barra_4_motor, *frame_MOTOR;


      frame_MOTOR = IupFrame(IupVbox( //obrigatório ter um vbox ou hbox no iupframe
            list_motor,
          IupSetAttributes(label_fake, "SIZE=75x5, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
          label_Vg_nominal,
            Field_Vg_nominal,
          label_Pg_nominal,
            Field_Pg_nominal,
          label_x_seq_pos,
            Field_x_seq_pos,
          label_x_seq_neg,
            Field_x_seq_neg,
          label_x_seq_zero,
            Field_x_seq_zero,
          label_x_neutro,
            Field_x_neutro,
          NULL)
          );

      /* Creating box that contains the toggles */
      barra_4_motor = IupHbox(
        IupVbox(
          //IupSetAttributes(IupBackgroundBox(toggle3), "BGCOLOR=\"255 0 0\""),
          //toggle3,
          //toggle1_tr,
          //toggle2_tr,
          //toggle3_tr,
          NULL),
        frame_MOTOR,
        NULL);


        //IupSetAttribute(toggle_define, "ACTIVE", "NO"); //deixa bloqueado em cinza


      //IupSetAttribute(IupGetChild(barra_4_motor, 1), "TITLE", "Dados do(s) Motor(es)"); //interessante!


          IupSetAttributes(frame_MOTOR, "FGCOLOR=\"0 0 255\", SIZE=EIGHTHxEIGHTH, TITLE=\"Dados do(s) Motor(es)\"");//, MARGIN=10x10

          IupSetAttributes ( list_motor,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");//FONTSTYLE = Bold,//FONTSIZE = \"12\",
          //Na lista ainda tem como individualizar as cores das letras no Ihandle list_motor

          IupSetAttributes ( label_Vg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Vg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_Pg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_Pg_nominal,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_pos,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_pos,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_neg,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_neg,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_seq_zero,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_seq_zero,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

          IupSetAttributes ( label_x_neutro,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");
          IupSetAttributes ( Field_x_neutro,"FGCOLOR = \"0 0 0\", ALIGNMENT = ACENTER");

      IupSetAttribute(barra_4_motor, "BGCOLOR", "7 255 154"); //Violeta "255 0 255" ... Lilás 255 46 114"); ...verde prateado

      /************************ FIM FRAME FORMULÁRIO **************************************************************************/

    return barra_4_motor; //note que saquei fora todas as especificações do gerador e estou retornando um Ihandle para a função createForm
}







/**************************************************(        \RESET \BOXES \VALUES \GERADOR     )*************************************************

***/


int run_reset_MOTOR(Ihandle *self2 ) /*** BoxValue limpeza ***/
{
    Ihandle* BoxValue_Vm = IupGetDialogChild(self2, "BoxValue_Vm_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Pm = IupGetDialogChild(self2, "BoxValue_Pm_nominal_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
    Ihandle* BoxValue_Xm_seq_pos = IupGetDialogChild(self2, "BoxValue_Xm_seq_pos_tag");
    Ihandle* BoxValue_Xm_seq_neg = IupGetDialogChild(self2, "BoxValue_Xm_seq_neg_tag");
    Ihandle* BoxValue_Xm_seq_zero = IupGetDialogChild(self2, "BoxValue_Xm_seq_zero_tag");
    Ihandle* BoxValue_Xm_neutro = IupGetDialogChild(self2, "BoxValue_Xm_neutro_tag");


    IupSetAttribute(BoxValue_Vm, "VALUE","");
    IupSetAttribute(BoxValue_Pm, "VALUE","");
    IupSetAttribute(BoxValue_Xm_seq_pos, "VALUE","");
    IupSetAttribute(BoxValue_Xm_seq_neg, "VALUE","");
    IupSetAttribute(BoxValue_Xm_seq_zero, "VALUE","");
    IupSetAttribute(BoxValue_Xm_neutro, "VALUE","");




  return IUP_DEFAULT;
}






/*****************************************(          \FUNCTIONS \IN \PER \UNIT \TABS -- \ABAS     )********************************************

***/

static int btn_function_alternar_Zpu(Ihandle* ih)   /*** \TABS \ABAS \ALTERNAR \Zpu ***/
{
  //recebe o disparo do botão via sua tag

  Ihandle* tabs = (Ihandle*)IupGetAttribute(ih, "APP_TABS"); //Ihandle de manuseio coleta o Ihandle de abas original

  int count = IupGetInt(tabs, "COUNT"); //Uma vez coletado o Ihandle de origem coleta-se a informação de quantas abas possui no momento
  IupSetInt(tabs, "VALUEPOS", 0); //Uma vez definido o botão Zpu então a posição da aba passa ser a primeira dentre as 3 abas


  return IUP_DEFAULT;


}



static int btn_function_alternar_Ypu(Ihandle* ih) /*** \TABS \ABAS \ALTERNAR \Ypu ***/
{
  //recebe o disparo do botão via sua tag

  Ihandle* tabs = (Ihandle*)IupGetAttribute(ih, "APP_TABS"); //Ihandle de manuseio coleta o Ihandle de abas original

  int count = IupGetInt(tabs, "COUNT"); //Uma vez coletado o Ihandle de origem coleta-se a informação de quantas abas possui no momento
  IupSetInt(tabs, "VALUEPOS", 1); //Uma vez definido o botão Ypu então a posição da aba passa ser a segunda dentre as 3 abas
                                  //Não estando oculta uma das abas a posição é iniciada em zero! E continua sendo se estiver alguma oculta


  return IUP_DEFAULT;
}



static int btn_function_alternar_Zpu_th(Ihandle* ih) /*** \TABS \ABAS \ALTERNAR \Zth \pu ***/
{
  //recebe o disparo do botão via sua tag

  Ihandle* tabs = (Ihandle*)IupGetAttribute(ih, "APP_TABS"); //Ihandle de manuseio coleta o Ihandle de abas original

  int count = IupGetInt(tabs, "COUNT"); //Uma vez coletado o Ihandle de origem coleta-se a informação de quantas abas possui no momento
  IupSetInt(tabs, "VALUEPOS", 2); //Uma vez definido o botão Zpu_th então a posição da aba passa ser a terceira dentre as 3 abas


  return IUP_DEFAULT;
}




/*****************************************(          \JANELAS \DAS \PLANILHAS     )********************************************

***/




/*****************************************(          \button \Seq \Zero    )********************************************

***/
static int button_Seq_Zero_in_Form(Ihandle *ih) /*** OPÇÕES DE MATRIZES ZERO  ***/
{


  Ihandle *box, *dlg, *Field_load_matrix_Zpu, *bt_matrix_Zpu_pos, *bt_matrix_Ypu_pos, *bt_matrix_Zpu_th_pos;

          //label_matrix_Zpu = IupLabel("")

          bt_matrix_Zpu_pos = IupButton("MATRIZ EM PU DE SEQUÊNCIA ZERO", "btn_matrix_Zpu_zero_tag");
          IupSetAttributes(bt_matrix_Zpu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_pos,"ACTION", (Icallback)button_cb);
    IupSetFunction("btn_matrix_Zpu_zero_tag", (Icallback)btn_function_alternar_Zpu); //botão para voltar para aba 1
          IupSetAttributes(bt_matrix_Zpu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          bt_matrix_Ypu_pos = IupButton("MATRIZ DE ADMITÂNCIA DE SEQUÊNCIA ZERO", "btn_matrix_Ypu_zero_tag");
          IupSetAttributes(bt_matrix_Ypu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Ypu_pos,"ACTION", button_cb);
    IupSetFunction("btn_matrix_Ypu_zero_tag", (Icallback)btn_function_alternar_Ypu); //botão de admitância = aba 2
          IupSetAttributes(bt_matrix_Ypu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis


          bt_matrix_Zpu_th_pos = IupButton("MATRIZ DE THÉVENIN DE SEQUÊNCIA ZERO", "btn_matrix_Zpu_th_zero_tag");
          IupSetAttributes(bt_matrix_Zpu_th_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_th_pos,"ACTION", button_cb);
    IupSetFunction("btn_matrix_Zpu_th_zero_tag", (Icallback)btn_function_alternar_Zpu_th); //botão de thevenin = aba 3
          IupSetAttributes(bt_matrix_Zpu_th_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis


          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Zpu = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Zpu = IupVbox(bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);

          IupSetAttribute(Field_load_matrix_Zpu,"GAP","50"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Zpu,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP esta´acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

          //IupSetCallback(bt_matrix_Zpu_zero,"ACTION", (Icallback)button_Zpu_Zero);



//  if(status_memory_Base_SEP == 0){




  Ihandle *bt, *label_Zpu, *label_Ypu, *label_Zth_pu;

  label_Zpu = IupLabel("Esta planilha-matriz exibe os valores de impedância lançados e que foram convertidos para pu. \n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. "
                       "\n\nComplemento: \nOs dados da diagonal principal não nulos são impedância de geradores ou motores. "
                       "\nOs dados fora da diagonal principal não nulos são impedâncias de trafos ou LTs tabelados"
                       "\nde acordo com o lançamento realizado. "
                       "\n\nImpedâncias elevadas de transformadores têm como hipótese mais provável o lançamento "
                       "\nde tensões de algum transformador de forma divergente - recomendamos check list (assinalar) "
                       "\nem papel com lapiseira. ");
  label_Ypu = IupLabel("Esta planilha-matriz exibe os valores de admitâncias calculados em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
  label_Zth_pu = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");

  //IupSetAttributes(label_Zpu, "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\" ");



  Ihandle *tabs_box = IupTabs( //insano, "a aba nasce no top e se esparrama"
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_zero(1)), label_Zpu,   //o create_mat é o excel
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu0"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu0"),
                    IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                          IupVbox(IupFrame(create_mat_sequencia_zero(2)), label_Ypu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
        //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu0"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu0"),
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_zero(3)), label_Zth_pu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
           NULL);



  Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

  //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
  //IupSetAttribute(tabs_box,"GAP","5");
  //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
  //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
  IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


  /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

  IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
   //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
  //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

  Ihandle *btn;
  btn = IupButton("Button", NULL);           //ENTRA NO mat1
//  IupSetCallback(bt, "ACTION", bt_cb);
  IupSetAttribute(bt, "CANFOCUS", "NO");

  Ihandle *div_02 = IupFlatSeparator();
  IupSetAttribute(div_02, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
  IupSetAttribute(div_02, "STYLE", "FILL");
  IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta


  //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
  //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
  Ihandle *box_zero = IupHbox(Field_load_matrix_Zpu, tabs_box_scroll,div_02, NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

  IupSetAttribute(box_zero,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/





  dlg = IupDialog(
          //IupZbox(
        box_zero
        );
  //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
  IupSetAttribute(dlg,"TITLE", "Matrizes de Sequência Zero");
  //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
  //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
  //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                               //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


  IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS ***/



  //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //A PRINCÍPIO NÃO É PARA MINIMIZAR E VINCULAR A JANELA PRINCIPAL, MAS AO FORM

  IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
  IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
  //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
  //IupSetAttribute(dlg,"MENU", "mymenu");
  //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
  //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
  //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
  IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
  //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button

  IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
  IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas
  IupSetHandle("mdi_tag_PLAN_ZERO", dlg); //tag da janela
  IupSetAttribute(dlg,"PARENTDIALOG","mdi_tag_FORM"); //atribuindo a dlg à janela do Formulário via a tag desta

  IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
  IupSetAttribute(dlg, "DEFAULTESC", "quit");


  IupMap(dlg);

  //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

  //IupShow(dlg);
  IupShowXY(dlg,IUP_CENTER,IUP_CENTER);



 // }

  //else
    //{
      //  IupMessage("Aviso!", "Formulário já foi criado");
    //}


  return IUP_DEFAULT;
}







/*****************************************(          \button \Seq \Negativa    )********************************************

***/
static int button_Seq_Negativa_in_Form(Ihandle *ih) /*** OPÇÕES DE MATRIZES DE SEQUÊNCIA NEGATIVA  ***/
{

  Ihandle *box, *dlg, *Field_load_matrix_Zpu, *bt_matrix_Zpu_pos, *bt_matrix_Ypu_pos, *bt_matrix_Zpu_th_pos;

          //label_matrix_Zpu = IupLabel("")

          bt_matrix_Zpu_pos = IupButton("MATRIZ EM PU DE SEQUÊNCIA NEGATIVA", "btn_matrix_Zpu_neg_tag"); //NOTE que basta trocar a tag, economia de tempo!
          IupSetAttributes(bt_matrix_Zpu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Zpu_neg_tag", (Icallback)btn_function_alternar_Zpu); //botão para voltar para aba 1
          IupSetAttributes(bt_matrix_Zpu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          bt_matrix_Ypu_pos = IupButton("MATRIZ DE ADMITÂNCIA DE SEQUÊNCIA NEGATIVA", "btn_matrix_Ypu_neg_tag");
          IupSetAttributes(bt_matrix_Ypu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Ypu_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Ypu_neg_tag", (Icallback)btn_function_alternar_Ypu); //botão de admitância = aba 2
          IupSetAttributes(bt_matrix_Ypu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis


          bt_matrix_Zpu_th_pos = IupButton("MATRIZ DE THÉVENIN DE SEQUÊNCIA NEGATIVA", "btn_matrix_Zpu_th_neg_tag");
          IupSetAttributes(bt_matrix_Zpu_th_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_th_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Zpu_th_neg_tag", (Icallback)btn_function_alternar_Zpu_th); //botão de thevenin = aba 3
          IupSetAttributes(bt_matrix_Zpu_th_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis




          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Zpu = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Zpu = IupVbox(bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);

          IupSetAttribute(Field_load_matrix_Zpu,"GAP","50"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Zpu,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP esta´acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

          //IupSetCallback(bt_matrix_Zpu_zero,"ACTION", (Icallback)button_Zpu_Zero);



  //if(status_memory_Base_SEP == 0)


  Ihandle *label_Zpu, *label_Ypu, *label_Zth_pu;

  label_Zpu = IupLabel("Esta planilha-matriz exibe os valores de impedância lançados e que foram convertidos para pu. \n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. "
                       "\n\nComplemento: \nOs dados da diagonal principal não nulos são impedância de geradores ou motores. "
                       "\nOs dados fora da diagonal principal não nulos são impedâncias de trafos ou LTs tabelados"
                       "\nde acordo com o lançamento realizado. "
                       "\n\nImpedâncias elevadas de transformadores têm como hipótese mais provável o lançamento "
                       "\nde tensões de algum transformador de forma divergente - recomendamos check list (assinalar) "
                       "\nem papel com lapiseira. ");
  label_Ypu = IupLabel("Esta planilha-matriz exibe os valores de admitâncias calculados em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
  label_Zth_pu = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");


  Ihandle *bt;

  bt = IupButton("Button", NULL);           //ENTRA NO mat1
//  IupSetCallback(bt, "ACTION", bt_cb);
  IupSetAttribute(bt, "CANFOCUS", "NO");

  Ihandle *tabs_box = IupTabs( //insano, "a aba nasce no top e se esparrama"
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_negativa(1)), label_Zpu,   //o create_mat é o excel
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu-"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu-"),
                    IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                          IupVbox(IupFrame(create_mat_sequencia_negativa(2)), label_Ypu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
        //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu-"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu-"),
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_negativa(3)), label_Zth_pu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
        //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),

           NULL);



  Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

  //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
  //IupSetAttribute(tabs_box,"GAP","5");
  //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
  //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
  IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


  /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

  IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
   //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
  //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");



  Ihandle *div_02 = IupFlatSeparator();
  IupSetAttribute(div_02, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
  IupSetAttribute(div_02, "STYLE", "FILL");
  IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta


  //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
  //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
  Ihandle *box_negativa = IupHbox(Field_load_matrix_Zpu, tabs_box_scroll,div_02, NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

  IupSetAttribute(box_negativa,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/





  dlg = IupDialog(
          //IupZbox(
        box_negativa
        );
  //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
  IupSetAttribute(dlg,"TITLE", "Matrizes de Sequência Negativa");
  //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
  //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
  //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                               //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


  IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS ***/



  //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

  IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
  IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
  //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
  //IupSetAttribute(dlg,"MENU", "mymenu");
  //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
  //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
  //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
  IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
  //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


  IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
  IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

  IupSetHandle("mdi_tag_PLAN_NEGATIVA", dlg); //tag da janela
  IupSetAttribute(dlg,"PARENTDIALOG","mdi_tag_FORM"); //atribuindo a dlg à janela do Formulário via a tag desta

  IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
  IupSetAttribute(dlg, "DEFAULTESC", "quit");


  IupMap(dlg);

  //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

  //IupShow(dlg);
  IupShowXY(dlg,IUP_CENTER,IUP_CENTER);


 // }

  //else
    //{
      //  IupMessage("Aviso!", "Formulário já foi criado");
    //}


  return IUP_DEFAULT;
}





/*****************************************(          \button \Seq \Positiva    )********************************************

***/
static int button_Seq_Positiva_in_Form(Ihandle *ih) /*** OPÇÕES DE MATRIZES DE SEQUÊNCIA POSITIVA  ***/
{

  Ihandle *box, *dlg, *Field_load_matrix_Zpu, *bt_matrix_Zpu_pos, *bt_matrix_Ypu_pos, *bt_matrix_Zpu_th_pos;

          //label_matrix_Zpu = IupLabel("")

          bt_matrix_Zpu_pos = IupButton("MATRIZ EM PU DE SEQUÊNCIA POSITIVA", "btn_matrix_Zpu_pos_tag");
          IupSetAttributes(bt_matrix_Zpu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Zpu_pos_tag", (Icallback)btn_function_alternar_Zpu); //botão para voltar para aba 1
          IupSetAttributes(bt_matrix_Zpu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          bt_matrix_Ypu_pos = IupButton("MATRIZ DE ADMITÂNCIA DE SEQUÊNCIA POSITIVA", "btn_matrix_Ypu_pos_tag");
          IupSetAttributes(bt_matrix_Ypu_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Ypu_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Ypu_pos_tag", (Icallback)btn_function_alternar_Ypu); //botão de admitância = aba 2
          IupSetAttributes(bt_matrix_Ypu_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis


          bt_matrix_Zpu_th_pos = IupButton("MATRIZ DE THÉVENIN DE SEQUÊNCIA POSITIVA", "btn_matrix_Zpu_th_pos_tag");
          IupSetAttributes(bt_matrix_Zpu_th_pos, "SIZE=200x50, EXPAND=NO, ALIGNMENT=ACENTER");
        //IupSetCallback(bt_matrix_Zpu_th_pos,"ACTION", button_cb);
        IupSetFunction("btn_matrix_Zpu_th_pos_tag", (Icallback)btn_function_alternar_Zpu_th); //botão de thevenin = aba 3
          IupSetAttributes(bt_matrix_Zpu_th_pos,"FONTSTYLE = Bold, FONTSIZE = \"8\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis



          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Zpu = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Zpu = IupVbox(bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);

          IupSetAttribute(Field_load_matrix_Zpu,"GAP","50"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Zpu,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP esta´acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

          //IupSetCallback(bt_matrix_Zpu_zero,"ACTION", (Icallback)button_Zpu_Zero);



  //if(status_memory_Base_SEP == 0)



  Ihandle *label_Zpu, *label_Ypu, *label_Zth_pu;

  label_Zpu = IupLabel("Esta planilha-matriz exibe os valores de impedância lançados e que foram convertidos para pu. \n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. "
                       "\n\nComplemento: \nOs dados da diagonal principal não nulos são impedância de geradores ou motores. "
                       "\nOs dados fora da diagonal principal não nulos são impedâncias de trafos ou LTs tabelados"
                       "\nde acordo com o lançamento realizado. "
                       "\n\nImpedâncias elevadas de transformadores têm como hipótese mais provável o lançamento "
                       "\nde tensões de algum transformador de forma divergente - recomendamos check list (assinalar) "
                       "\nem papel com lapiseira. ");
  label_Ypu = IupLabel("Esta planilha-matriz exibe os valores de admitâncias calculados em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
  label_Zth_pu = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin em pu.\n"
                       "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                       "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                       "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");



  /*** QUEM VAI DIZER QUE CARREGOU AS PLANILHAS-MATRIZES É O create_mat_sequencia ***/

  Ihandle *tabs_box = IupTabs( //SOMENTE DA SEQUÊNCIA POSITIVA - 3 PANILHAS Zpu, Ypu e Zth_pu
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_positiva(1)), label_Zpu,   //o create_mat é o excel
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),
                    IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                          IupVbox(IupFrame(create_mat_sequencia_positiva(2)), label_Ypu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
        //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                    IupSetAttributes(
                          IupVbox(IupFrame(create_mat_sequencia_positiva(3)), label_Zth_pu,
        //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
        //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                          NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
                          //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
           NULL);



  Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

  //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
  //IupSetAttribute(tabs_box,"GAP","5");
  //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
  //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
  IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


  /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

  IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
   //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
  //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

  Ihandle *btn;
  btn = IupButton("Button", NULL);           //ENTRA NO mat1            ??? não entra em nenhum vbox
//  IupSetCallback(bt, "ACTION", bt_cb);
  IupSetAttribute(btn, "CANFOCUS", "NO");

  Ihandle *div_02 = IupFlatSeparator();
  IupSetAttribute(div_02, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
  IupSetAttribute(div_02, "STYLE", "FILL");
  IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta


  //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
  //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
  Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, tabs_box_scroll,div_02, NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

  IupSetAttribute(box_positiva,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/





  dlg = IupDialog(
          //IupZbox(
        box_positiva
        );
  //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
  IupSetAttribute(dlg,"TITLE", "Matrizes de Sequência Positiva");
  //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
  //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
  //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                               //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


  IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS ***/



  //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

  IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
  IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
  //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
  //IupSetAttribute(dlg,"MENU", "mymenu");
  //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
  //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
  //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
  IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
  //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


  IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
  IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

  IupSetHandle("mdi_tag_PLAN_POSITIVA", dlg); //tag da janela
  IupSetAttribute(dlg,"PARENTDIALOG","mdi_tag_FORM"); //atribuindo a dlg à janela do Formulário via a tag desta

  IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
  IupSetAttribute(dlg, "DEFAULTESC", "quit");


  IupMap(dlg);

  //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

  //IupShow(dlg);
  IupShowXY(dlg,IUP_CENTER,IUP_CENTER);


 // }

  //else
    //{
      //  IupMessage("Aviso!", "Formulário já foi criado");
    //}


  return IUP_DEFAULT;
}



/*******************************************************************************************************************/


/************************************************ FUNCTIONS OFF -- STAND BY ****************************************/



static char* value_CELL(Ihandle *self, int lin, int col)
{
  static char str[50];
  sprintf(str, "%d:%d", lin, col); //NOTE É UMA STRING LABEL COM DOIS PONTOS, VISANDO DETERMINAR AS COORDENADAS DA MATRIX

  return str;
}

/************************************************ FUNCTIONS OFF -- STAND BY ****************************************/


static char* value_NEW(Ihandle *self, int lin, int col)
{
  static char str[50];
  sprintf(str, "%d-%d", 1026, 1027); //NOTE É UM LABEL COM HÍFEN
  return str;
}


/*********************************************** FUNCTIONS OFF -- STAND BY ****************************************/


static char* value_NEW_zerosCells(Ihandle *self, int lin, int col)
{
  static char str[50]; //CONFLITO PODE ESTAR NO STATIC CHAR

  /*** A FINALIDADE DESTA FUNÇÃO É CRIAR UMA STRING LABEL PARA LINHA ZERO E COLUNA ZERO ***/

     //if(lin==0 && col>0){}
      sprintf(str, "Bar x:%d", col); //o único diferencial é que a string de ZerosCells impresse uma string com a palavra Bar (barra)




  return str;
}


/*******************************************************************************************************************/



/*****************************************(          \THEVENIN \Z \BARRA    )********************************************

***/



/*****************************************(          \THEVENIN \Z \BARRA \SELETOR    )********************************************

***/

void Calc_Matrix_Z_th_pu(Ihandle* disparo_load_full, int tipo)
{

	float matrix[25][25], matrix_inv[25][25], det=0;
	float ordem; //testei e carrega normalmente o int dentro do float (variável)

	int i, j;

	if(tipo == 1 || tipo == 2){
        ordem = size_SEP_bars_OLD; //OLD é a ordem menor
	}
	if(tipo == 0){
        ordem = size_SEP_bars; //implementação nova 15jul22
	}

	//IupMessagef("Aviso!","O TAMANHO DA ORDEM DA MATRIZ É %f PARA SEQUÊNCIA %d", ordem, tipo);

	/*** \CARREGAMENTO \SEQUENCIA \POSITIVA ***/
	if(tipo == 1){


        for (i = 1; i < ordem+1; i++) {

            for (j = 1; j < ordem+1; j++) {

                matrix[i][j] =  matrix_admitancia_positiva_pu[i][j]; //carregamento passível de debug...E REDUÇÃO DE CÓDIGO

                //IupMessagef("Aviso!", "O elemento %d:%d da Y_pu_pos é %2f", i, j, matrix[i][j]);

            }

        }


        det = determinante(matrix, ordem); //note o envio de matrix sem i, j

        if (det == 0){
          IupMessage("Aviso!", "A MATRIZ NÃO É INVERSÍVEL PARA SEQUÊNCIA POSITIVA");
          IupMessage("Aviso!", "O LANÇAMENTO PODE TER SIDO REALIZADO INCORRETAMENTE - PROCEDA AO CHECK LIST EM PAPEL");
        }
        else
          cofatores(matrix, ordem, tipo);

	}

	int depurar_tipo = 1;

	/*** \CARREGAMENTO \SEQUENCIA \NEGATIVA ***/
	if(tipo == 2 && depurar_tipo == 1){

        for (i = 1; i < ordem+1; i++) {

            for (j = 1; j < ordem+1; j++) {

                matrix[i][j] =  matrix_admitancia_negativa_pu[i][j]; //carregamento passível de debug...E REDUÇÃO DE CÓDIGO

                //IupMessagef("Aviso!", "O elemento %d:%d da Y_pu_neg é %2f", i, j, matrix[i][j]);

            }

        }
        det = determinante(matrix, ordem); //note o envio de matrix sem i, j

        if (det == 0){
          IupMessage("Aviso!", "A MATRIZ NÃO É INVERSÍVEL PARA SEQUÊNCIA NEGATIVA");
          IupMessage("Aviso!", "O LANÇAMENTO PODE TER SIDO REALIZADO INCORRETAMENTE - PROCEDA AO CHECK LIST EM PAPEL");
        }
        else
          cofatores(matrix, ordem, tipo);

	}



    /*** \CARREGAMENTO \SEQUENCIA \ZERO ***/
	if(tipo == 0 && depurar_tipo == 1){

        for (i = 1; i < ordem+1; i++) {

            for (j = 1; j < ordem+1; j++) {

                matrix[i][j] =  matrix_admitancia_zero_pu[i][j]; //carregamento passível de debug...E REDUÇÃO DE CÓDIGO

                //IupMessagef("Aviso!", "O elemento %d:%d da Y_pu_zero é %2f", i, j, matrix[i][j]);

            }

        }

        det = determinante(matrix, ordem); //note o envio de matrix sem i, j

        if (det == 0){
          IupMessage("Aviso!", "A MATRIZ NÃO É INVERSÍVEL PARA SEQUÊNCIA ZERO");
          IupMessage("Aviso!", "O LANÇAMENTO PODE TER SIDO REALIZADO INCORRETAMENTE - PROCEDA AO CHECK LIST EM PAPEL");
        }
        else
          cofatores(matrix, ordem, tipo);

	}





}





/*****************************************(          \DETERMINANTE    )********************************************

***/

//int contador_temporal = 0;
float determinante(float matrix[25][25], float ordem) //ordem estava float
{

	float alternador = 1, det = 0, buffer_Minor_M[25][25];

	int i, j, m, n, c;

	//printf("A ORDEM DA MATRIZ É é %2f", ordem);     //cmd
	//contador_temporal++;

	/***
	if(ordem == 14 || ordem == 15){
        IupMessagef("Aviso!", "A ORDEM DA MATRIZ É é %2f -- CARREGANDO", ordem);
        IupMessagef("Aviso!", "O contador temporal é %d -- CARREGANDO", contador_temporal);
    }
    ***/
	if (ordem == 1) {

		return (matrix[1][1]); //crítico, retorna um Minor_M 1x1 advinda da matrix 2x2...em síntese calcula o determinante de uma matrix 2x2, pós return
        //cuidado, no esgotamento matrix[1][1] é o buffer_Minor[2][2] para c=1
        //ou matrix[1][1] é o buffer_Minor[2][1] para c=2

	} else {

		det = 0;

		//ERRO ESTÚPIDO, HAVIA DEIXADO c = 0, enquanto modifiquei os demais para 1 na inicialização do laço
		for (c = 1; c < ordem+1; c++) { //laço de coeficientes da matriz para obter o determinante

			m = 1;//0;

			n = 1;//0;

			for (i = 1; i < ordem+1; i++) { //laço de Minor_M

				for (j = 1; j < ordem+1; j++) { //laço de Minor_M

					buffer_Minor_M[i][j] = 0; //O primeira elemento a carregar é o 2:2, inicialmente com zero, dps entra

					if (i != 1 && j != c) { //A primeira coluna de redução de matriz não entra, por causa do j

						buffer_Minor_M[m][n] = matrix[i][j];    //Note que ele reinicia a matriz reduzida do ponto de vista 2:2

						//ANTES O ZERO SATISFAZIA 0<1, agora deve ser 1<2, note que a condição não satisfeita reinicia o n
						//if (n < (ordem - 2)+1) %NOTE, só entra no for k>2, se operar ordem-2 dá zero, então some 1 para comparar
						if (n < (ordem - 2)+1) //Se a ordem for 2, então é carregado acima somente um elemento 1x1 e morre o laço em j==1

						       n++; else {

							n = 1;//0; se liga era zero

							m++;

						} //condicional

					} //condicional

				} //laço j

			} //laço i

			//De fato é estranho, mas de fato é um somatório dos fatores dos cofatores pelos respectivos elementos i,j da linha i = 0 da matrix.
			//cofator = alternador * determinante(buffer_Minor_M, ordem - 1)
			det = det + matrix[1][c] * alternador * determinante(buffer_Minor_M, ordem - 1); //independetemente da linha de matrix o determinante sempre será igual
                                                                                             //https://study.com/academy/lesson/laplace-expansion-equation-finding-determinants.html
                                                                                             //Livro Elementos da Matemática - Rufino, volume 3, páginas 249 a 251

            //para ordem 2x2, a conta é matrix[1][c=1]*(+1)*buffer_Minor_M[2][2]
            //para ordem 2x2, a conta é matrix[1][c=2]*(-1)*buffer_Minor_M[2][1]

            //O primeiro determinante é nulo, e o alternador 1 está atrelado ao c=1, ou seja, i+j = 2 (par)
            //Note vc montou uma matriz 14x14, enviando a ordem 15-1 para ser feito a matriz 13x13, até 1x1...recursivamente
			alternador = -1 * alternador;

		} //laço c dos cofatores para determinante

	}

	return det;

}






/*****************************************(          \COFATORES    )********************************************

***/
void cofatores(float matrix[25][25], float ordem, int tipo) //ordem estava float
{
    float buffer[25][25], cofator_C[25][25], minor_M[25][25], matrix_inv[25][25];

	int p, q, m, n, i, j;

	for (q = 1; q < ordem+1; q++) { //Laço de Minor_M e cofatores Cofator_C

		for (p = 1; p < ordem+1; p++) { //Laço de Minor_M e cofatores Cofator_C ...difere do determinante neste laço

			m = 1;//0;

			n = 1;//0;

			for (i = 1; i < ordem+1; i++) { //Laço Buffer

				for (j = 1; j < ordem+1; j++) { //Laço Buffer

					buffer[i][j] = 0;

					if (i != q && j != p) {

						buffer[m][n] = matrix[i][j];

						//if (n < (ordem - 2)+1)    %caraca, ainda tinha mais um
						if (n < (ordem - 2)+1)

						       n++;
                        else {

							n = 1;//0;

							m++;

						} //condicional

					} //condicional

				} //laço j

			} //laço i

			minor_M[q][p] = determinante(buffer, ordem - 1);
			cofator_C[q][p] = pow(-1, q + p) * minor_M[q][p];

		} //laço q

	} //laço p

	inversa(matrix, cofator_C, ordem, tipo);

}




/*****************************************(          \INVERSA    )********************************************

***/
void inversa(float matrix[25][25], float cofator_C[25][25], float ordem, int tipo) //ordem estava float
{

    int i, j, uma_vez = 0;
	float d, adjunta_T[25][25], matrix_inv[25][25];

	/*** \TRANSPOSICAO \MATRIX \DOS \COFATORES ***/

	for (i = 1; i < ordem+1; i++) {

		for (j = 1; j < ordem+1; j++) {

			adjunta_T[i][j] = cofator_C[j][i]; //carregamento de matriz transposta (adjunta é obtida pela transposição da matriz de cofatores)

		}

	}

	d = determinante(matrix, ordem);

	matrix_inv[i][j] = 0.0;

	/*** \ARREMATE \INVERSA ***/

	for (i = 1; i < ordem+1; i++) {

		for (j = 1; j < ordem+1; j++) {

			matrix_inv[i][j] = adjunta_T[i][j] / d;

		}

	}



    /*** \CARREGAMENTO \Z \THEVENIN \POSITIVA ***/

    if(tipo == 1){
        for (i = 1; i < ordem+1; i++) {

            for (j = 1; j < ordem+1; j++) {

                if(matrix_inv[i][j] != 0){
                    matrix_thevenin_positiva_pu[i][j] = -1*matrix_inv[i][j]; //carregamento passível de debug
                }
                if(matrix_inv[i][j] == 0){
                    matrix_thevenin_positiva_pu[i][j] = 0.0; //estranho deu um bug na planilha e parece que foi só isso aqui >>> 0.0
                }

                /***
                if(uma_vez == 0){
                    system("pause");
                    uma_vez++;
                }
                ***/

                /*** \INVERSA \VALIDADA ***/
                //IupMessagef("Aviso!", "O elemento %d:%d de Zth+ é %.5f", i, j, matrix_thevenin_positiva_pu[i][j]);

            }

        }
    }



    /*** \CARREGAMENTO \Z \THEVENIN \NEGATIVA ***/

    if(tipo == 2){
        for (i = 1; i < ordem+1; i++) {

            for (j = 1; j < ordem+1; j++) {

                if(matrix_inv[i][j] != 0){
                    matrix_thevenin_negativa_pu[i][j] = -1*matrix_inv[i][j]; //carregamento passível de debug
                }
                if(matrix_inv[i][j] == 0){
                    matrix_thevenin_negativa_pu[i][j] = 0.0;
                }

            }

        }
    }


    /*** \CARREGAMENTO \Z \THEVENIN \ZERO ***/

    if(tipo == 0){
        for (i = 1; i < ordem+1; i++) {
            for (j = 1; j < ordem+1; j++) {

                if(matrix_inv[i][j] != 0){
                    matrix_thevenin_zero_pu[i][j] = -1*matrix_inv[i][j]; //carregamento passível de debug
                }
                if(matrix_inv[i][j] == 0){
                    matrix_thevenin_zero_pu[i][j] = 0.0;
                }
                //A essência da função é carregar matrix_thevenin_zero_pu para acesso simultâneo
            }

        }
    }


}








/*****************************************(          \PLANILHAS    )********************************************

***/




/*****************************************(          \PLANILHAS \SEQ \POSITIVA   )********************************************

***/
static Ihandle *create_mat_sequencia_positiva(int mati)
{

/*** \TRES \PLANILHAS \SEQUENCIA \POSITIVA - \Zpu (mat(1)) \Ypu (mat(2) \Zth_pu (mat(3))***/

//id_Zbox_FULL = id_Zbox_GE + id_Zbox_LT + id_Zbox_TRAFO + id_Zbox_MOTOR; //Variável global (para - e zero)

//if__(id_Zbox_FULL != 0)

if(status_btn_home!=0 && status_memory_load_full_finish_pu == 1){


  /*** É UMA FUNÇÃO QUE RETORNA UMA Ihandle matrix ***/
  Ihandle *mat;                     //cuidado não é mati, é sem i...mati é o argumento i
  char name[30];
  sprintf(name, "mat%d", mati);                 //está concatenando mat(i) criando um tag_label,... armazenando mat1 no char name

  mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
  IupSetAttribute(mat,"UNDOREDO","Yes");

  /***
  if (mati==1)
  {
    mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
    IupSetAttribute(mat,"UNDOREDO","Yes");
  }

  else

    mat = IupMatrix(NULL);                      //Aonde nasce a matrix sem controles avançados
  ***/



  IupSetHandle(name, mat);              //tag da matriz mat ...o char name armazenou o nome mat1, mat2, mat3...

  IupSetAttribute(mat,"NUMCOL","18");           //Dimensionamento das células da matriz
  IupSetAttribute(mat,"NUMLIN","18");

  /*** Controla quantas células deseja exibir previamente ***/
  IupSetAttribute(mat,"NUMCOL_VISIBLE","5");
  IupSetAttribute(mat,"NUMLIN_VISIBLE","8");
  /*** ABAIXO VINCULADO AS CÉLULAS VISÍVEIS TEMOS A EXPANSÃO SE POSSÍVEL DAS CÉLULAS NA JANELA ***/
  IupSetAttribute(mat,"EXPAND", "NO"); //ISSO É MUITO BOM, PQ EU POSSO POR mat DENTRO DE UM HBOX OU VBOX E TER ÁREA ÚTIL PARA CRIAR FUNCIONALIDADES!
//  IupSetAttribute(mat,"SCROLLBAR", "NO");
  IupSetAttribute(mat,"RESIZEMATRIX", "YES");

  IupSetAttribute(mat,"MARKMODE", "CELL");
//  IupSetAttribute(mat,"MARKMODE", "LINCOL");
  IupSetAttribute(mat,"MARKMULTIPLE", "YES");
  IupSetAttribute(mat,"MARKAREA", "NOT_CONTINUOUS");
// IupSetAttribute(mat, "MARKAREA", "CONTINUOUS");




/*** \SUSPENSO ***/


    /***
        if(mati==1){
                      IupMessage("Aviso!", "Bem-vindo(a) à exibição em pu \n Aperte Ok para prosseguir");

                      //Matrix_struct = percentual

                      IupMessagef("Aviso!",
                        " A reatância de Z[1][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][2][%%] é %.2f [%%]"
                        "\n A reatância de Z[2][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][3][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][4][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][3][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][4][%%] é %.2f [%%]"
                        , matrix_struct[1][1].gerador_indices.Xg_seq_pos
                        , matrix_struct[1][2].trafo_indices.Xeq_trafo
                        , matrix_struct[2][1].trafo_indices.Xeq_trafo
                        , matrix_struct[1][3].trafo_indices.Xeq_trafo
                        , matrix_struct[3][1].trafo_indices.Xeq_trafo
                        , matrix_struct[3][4].LT_indices.Xeq_LT_seq_pos
                        , matrix_struct[4][3].LT_indices.Xeq_LT_seq_pos
                        , matrix_struct[4][4].motor_indices.Xm_seq_pos);


                    //Matrix_struct = por unidade = pu

                    IupMessagef("Aviso!",
                        " A reatância de Z[1][1] é %.5f [pu]"
                        "\n A reatância de Z[1][2] é %.5f [pu]"
                        "\n A reatância de Z[2][1] é %.5f [pu]"
                        "\n A reatância de Z[1][3] é %.5f [pu]"
                        "\n A reatância de Z[3][1] é %.5f [pu]"
                        "\n A reatância de Z[3][4] é %.5f [pu]"
                        "\n A reatância de Z[4][3] é %.5f [pu]"
                        "\n A reatância de Z[4][4] é %.5f [pu]"
                        , matrix_struct_pu[1][1].gerador_indices.Xg_seq_pos
                        , matrix_struct_pu[1][2].trafo_indices.Xeq_trafo
                        , matrix_struct_pu[2][1].trafo_indices.Xeq_trafo
                        , matrix_struct_pu[1][3].trafo_indices.Xeq_trafo
                        , matrix_struct_pu[3][1].trafo_indices.Xeq_trafo
                        , matrix_struct_pu[3][4].LT_indices.Xeq_LT_seq_pos
                        , matrix_struct_pu[4][3].LT_indices.Xeq_LT_seq_pos
                        , matrix_struct_pu[4][4].motor_indices.Xm_seq_pos);

                  }

        ***/
/******************************************* \AUTOMACAO \BARRA \DE \TITULO \PLANILHA \positiva - INÍCIO ****************************************/

          int max_lin_and_col = 16;
          int int_cont = 0;
          char string_cell[30] = {NULL};
          char string_name[30] = {NULL};

          do{
                  int_cont++;

                  sprintf(string_cell,  "0:%d", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar x:%d", int_cont); // Bar x:1, Bar x:2, ..., Bar x:15

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar x:1")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que usar for vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


          int_cont = 0;



          do{
                  int_cont++;

                  sprintf(string_cell,  "%d:0", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar %d:y", int_cont); // Bar 1:y, Bar 2:y, ..., Bar 15:y

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar 1:y")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


/******************************************* \AUTOMACAO \BARRA \DE \TITULO - FIM ****************************************/



/*** \BLANK ***/

        int id_maq = 0;
        int id_xy = 0;

        int id_y = 0;
        int id_x = 0;
        float sobreporsicao1 = 0;
        float sobreporsicao2 = 0;
        float sobreporsicao3 = 0;
        float sobreporsicao4 = 0;

/*** \LEMBREI - É preciso segmentar os fors por máquina senão dá conflito (com a \ideia dos 3fors+1if) ***/

/*** Lembre-se, antes havia 4 vetores de índices, por isso 4 fors ***/

/*** \>>> GERADOR + MOTOR = \DIAGONAL \<<< ***/

if(mati==1){ //PLANILHA SEQUÊNCIA POSITIVA ABA 1

        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
                                                       //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                                                       //for duplo vai sujar as células do TR e LT
                sobreporsicao1 = matrix_struct_pu[id_x][id_x].gerador_indices.Xg_seq_pos;
                sobreporsicao2 = matrix_struct_pu[id_x][id_x].motor_indices.Xm_seq_pos;
                sobreporsicao3 = sobreporsicao1 + sobreporsicao2;


                    //IupMessagef("Aviso!", "A reatância PARCIAL 1/2 de Z_pu[%d][%d][pu] é %.5f [pu]", id_x, id_x,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_x); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao3); //Plota na planilha Zpu, da janela de sequência positiva


       } //FIM FOR-1: Gerador + Motor - Seq. Positiva




/*** \>>> TRAFO + LT = \FORA \DA \DIAGONAL \<<< ***/


        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                if(id_x != id_y){ // HAVIA ESQUECIDO DISSO


                  sobreporsicao1 = matrix_struct_pu[id_x][id_y].trafo_indices.X_TR_seq_pos;
                  sobreporsicao2 = matrix_struct_pu[id_x][id_y].LT_indices.Xeq_LT_seq_pos;
                  sobreporsicao3 = sobreporsicao1 + sobreporsicao2;

                    //IupMessagef("Aviso!", "A reatância de Z_pu[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao3); //Plota na planilha Zpu, da janela de sequência positiva
                    //FUNCIONA ?



                }
            }//

       }// //FIM FOR-2: LT + TR - Seq. Positiva



}


if(mati==2){ //PLANILHA SEQUÊNCIA POSITIVA ABA 2 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \ADMITANCIA \TOTAL \<<< ***/


        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_admitancia_positiva_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A admitância Y[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat2"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//

       }// //FIM FOR-2: LT + TR - Seq. Positiva


}



/*** \Zthevenin \matriz \inversa ***/


if(mati==3){ //PLANILHA SEQUÊNCIA POSITIVA ABA 3 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \THEVENIN \CURTO \CIRCUITO \<<< ***/


        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_thevenin_positiva_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A inversa Z_th[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat3"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//FIM FOR-1: thevenin - Seq. Positiva

       }//FIM FOR-2: thevenin - Seq. Positiva


} //condicional aba 3



          IupSetAttribute(mat, "FLATSCROLLBAR", "Yes"); //MUITO SOFISTICADA, LIMPA E SUTIL
        //  IupSetAttribute(mat, "SHOWFLOATING", "Yes"); //ficou mascarado demais com barra de rolagem oculta ...atrapalha um pouco a úlima linha
        //  IupSetAttribute(mat, "SHOWTRANSPARENT", "Yes"); //não gostei


  return mat;

  }
  else return NULL;

}







/*****************************************(          \PLANILHAS \SEQ \NEGATIVA   )********************************************

***/
static Ihandle *create_mat_sequencia_negativa(int mati)            //Está recebendo um inteiro
{

/*** \SUSPENSO == 2 \CHANGE \FOR: if(status_btn_home!=0 && status_memory_load_full_finish_pu == 1) ***/
if(status_btn_home!=0 && status_memory_load_full_finish_pu == 1){


  /*** É UMA FUNÇÃO QUE RETORNA UMA Ihandle matrix ***/
  Ihandle *mat;                     //cuidado não é mati, é sem i
  char name[30];
  sprintf(name, "mat%d", mati);                 //está armazenando mat1 no char name

  mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
  IupSetAttribute(mat,"UNDOREDO","Yes");

  /***
  if (mati==1)
  {
    mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
    IupSetAttribute(mat,"UNDOREDO","Yes");
  }

  else

    mat = IupMatrix(NULL);                      //Aonde nasce a matrix sem controles avançados
  ***/



  IupSetHandle(name, mat);              //tag da matriz mat ...o char name armazenou o nome mat1, mat2, mat3...

  IupSetAttribute(mat,"NUMCOL","18");           //Dimensionamento das células da matriz
  IupSetAttribute(mat,"NUMLIN","18");

  /*** Controla quantas células deseja exibir previamente ***/
  IupSetAttribute(mat,"NUMCOL_VISIBLE","5");
  IupSetAttribute(mat,"NUMLIN_VISIBLE","8");
  /*** ABAIXO VINCULADO AS CÉLULAS VISÍVEIS TEMOS A EXPANSÃO SE POSSÍVEL DAS CÉLULAS NA JANELA ***/
  IupSetAttribute(mat,"EXPAND", "NO"); //ISSO É MUITO BOM, PQ EU POSSO POR mat DENTRO DE UM HBOX OU VBOX E TER ÁREA ÚTIL PARA CRIAR FUNCIONALIDADES!
//  IupSetAttribute(mat,"SCROLLBAR", "NO");
  IupSetAttribute(mat,"RESIZEMATRIX", "YES");

  IupSetAttribute(mat,"MARKMODE", "CELL");
//  IupSetAttribute(mat,"MARKMODE", "LINCOL");
  IupSetAttribute(mat,"MARKMULTIPLE", "YES");
  IupSetAttribute(mat,"MARKAREA", "NOT_CONTINUOUS");
// IupSetAttribute(mat, "MARKAREA", "CONTINUOUS");


/*** \SUSPENSO


        if(mati==1){
                      IupMessage("Aviso!", "Bem-vindo(a) à exibição em pu \n Aperte Ok para prosseguir");

                      //Matrix_struct = percentual

                      IupMessagef("Aviso!",
                        " A reatância de Z[1][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][2][%%] é %.2f [%%]"
                        "\n A reatância de Z[2][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][3][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][4][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][3][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][4][%%] é %.2f [%%]"
                        , matrix_struct[1][1].gerador_indices.Xg_seq_neg
                        , matrix_struct[1][2].trafo_indices.X_TR_seq_neg
                        , matrix_struct[2][1].trafo_indices.X_TR_seq_neg
                        , matrix_struct[1][3].trafo_indices.X_TR_seq_neg
                        , matrix_struct[3][1].trafo_indices.X_TR_seq_neg
                        , matrix_struct[3][4].LT_indices.Xeq_LT_seq_neg
                        , matrix_struct[4][3].LT_indices.Xeq_LT_seq_neg
                        , matrix_struct[4][4].motor_indices.Xm_seq_neg);


                    //Matrix_struct = por unidade = pu

                    IupMessagef("Aviso!",
                        " A reatância de Z[1][1] é %.5f [pu]"
                        "\n A reatância de Z[1][2] é %.5f [pu]"
                        "\n A reatância de Z[2][1] é %.5f [pu]"
                        "\n A reatância de Z[1][3] é %.5f [pu]"
                        "\n A reatância de Z[3][1] é %.5f [pu]"
                        "\n A reatância de Z[3][4] é %.5f [pu]"
                        "\n A reatância de Z[4][3] é %.5f [pu]"
                        "\n A reatância de Z[4][4] é %.5f [pu]"
                        , matrix_struct_pu[1][1].gerador_indices.Xg_seq_neg
                        , matrix_struct_pu[1][2].trafo_indices.X_TR_seq_neg
                        , matrix_struct_pu[2][1].trafo_indices.X_TR_seq_neg
                        , matrix_struct_pu[1][3].trafo_indices.X_TR_seq_neg
                        , matrix_struct_pu[3][1].trafo_indices.X_TR_seq_neg
                        , matrix_struct_pu[3][4].LT_indices.Xeq_LT_seq_neg
                        , matrix_struct_pu[4][3].LT_indices.Xeq_LT_seq_neg
                        , matrix_struct_pu[4][4].motor_indices.Xm_seq_neg);

                  }


***/


/******************************************* \AUTOMACAO \BARRA \DE \TITULO \PLANILHA \positiva - INÍCIO ****************************************/

          int max_lin_and_col = 16;
          int int_cont = 0;
          char string_cell[30] = {NULL};
          char string_name[30] = {NULL};

          do{
                  int_cont++;

                  sprintf(string_cell,  "0:%d", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar x:%d", int_cont); // Bar x:1, Bar x:2, ..., Bar x:15

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar x:1")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que usar for vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


          int_cont = 0;



          do{
                  int_cont++;

                  sprintf(string_cell,  "%d:0", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar %d:y", int_cont); // Bar 1:y, Bar 2:y, ..., Bar 15:y

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar 1:y")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


/******************************************* \AUTOMACAO \BARRA \DE \TITULO - FIM ****************************************/


/*** \BLANK ***/

        int id_y = 0;
        int id_x = 0;
        float sobreporsicao1 = 0;
        float sobreporsicao2 = 0;
        float sobreporsicao3 = 0;
        float sobreporsicao4 = 0;


/*** \>>> GERADOR + MOTOR = \DIAGONAL \<<< ***/

if(mati==1){ //PLANILHA SEQUÊNCIA NEGATIVA ABA 1

        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
                                                       //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                                                       //for duplo vai sujar as células do TR e LT
                sobreporsicao1 = matrix_impedancia_negativa_pu[id_x][id_x];

                /*** \MONITORAR \LEMBRE-SE ESTAVA USANDO STRUCT, ALGO FALHOU AINDA NA STRUCT, MAS CHEGA CERTINHO OS VALORES NO MESSAGE***/

                    //IupMessagef("Aviso!", "A reatância PARCIAL 1/2 de Z_pu[%d][%d][pu] é %.5f [pu]", id_x, id_x,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_x); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Zpu, da janela de sequência positiva


       } //FIM FOR-1: Gerador + Motor - Seq. Positiva




/*** \>>> TRAFO + LT = \FORA \DA \DIAGONAL \<<< ***/


        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                if(id_x != id_y){ // HAVIA ESQUECIDO DISSO


                  sobreporsicao1 = matrix_struct_pu[id_x][id_y].trafo_indices.X_TR_seq_neg;
                  sobreporsicao2 = matrix_struct_pu[id_x][id_y].LT_indices.Xeq_LT_seq_neg;
                  sobreporsicao3 = sobreporsicao1 + sobreporsicao2;

                    //IupMessagef("Aviso!", "A reatância de Z_pu[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao3); //Plota na planilha Zpu, da janela de sequência positiva
                    //FUNCIONA ?



                }
            }//

       }// //FIM FOR-2: LT + TR - Seq. Negativa



}


if(mati==2){ //PLANILHA SEQUÊNCIA POSITIVA ABA 2 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \ADMITANCIA \TOTAL \<<< ***/


        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_admitancia_negativa_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A admitância Y[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat2"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//

       }// //FIM FOR-2: LT + TR - Seq. Negativa


}





/*** \Zthevenin \matriz \inversa - \NEGATIVA***/


if(mati==3){ //PLANILHA SEQUÊNCIA POSITIVA ABA 3 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \THEVENIN \CURTO \CIRCUITO \<<< ***/

        for(id_x = 1; id_x < size_SEP_bars_OLD+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars_OLD+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_thevenin_negativa_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A inversa Z_th[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat3"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//FIM FOR-1: thevenin - Seq. Negativa

       }//FIM FOR-2: thevenin - Seq. Negativa


} //condicional aba 3


          IupSetAttribute(mat, "FLATSCROLLBAR", "Yes"); //MUITO SOFISTICADA, LIMPA E SUTIL
        //  IupSetAttribute(mat, "SHOWFLOATING", "Yes"); //ficou mascarado demais com barra de rolagem oculta ...atrapalha um pouco a úlima linha
        //  IupSetAttribute(mat, "SHOWTRANSPARENT", "Yes"); //não gostei


  return mat;

  }
  else return NULL;

}







/*****************************************(          \PLANILHAS \SEQ \ZERO   )********************************************

***/
static Ihandle *create_mat_sequencia_zero(int mati)            //Está recebendo um inteiro
{
/*** \SUSPENSO ==2 \CHANGE \FOR: if(status_btn_home!=0 && status_memory_load_full_finish_pu == 1) ***/
if(status_btn_home!=0 && status_memory_load_full_finish_pu == 1){


  /*** É UMA FUNÇÃO QUE RETORNA UMA Ihandle matrix ***/
  Ihandle *mat;                     //cuidado não é mati, é sem i
  char name[30];
  sprintf(name, "mat%d", mati);                 //está armazenando mat1 no char name

  mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
  IupSetAttribute(mat,"UNDOREDO","Yes");

  /***
  if (mati==1)
  {
    mat = IupMatrixEx();                        //Aonde nasce a matrix com os controles avançados de cópia, export e afins
    IupSetAttribute(mat,"UNDOREDO","Yes");
  }

  else

    mat = IupMatrix(NULL);                      //Aonde nasce a matrix sem controles avançados
  ***/



  IupSetHandle(name, mat);              //tag da matriz mat ...o char name armazenou o nome mat1, mat2, mat3...

  IupSetAttribute(mat,"NUMCOL","18");           //Dimensionamento das células da matriz
  IupSetAttribute(mat,"NUMLIN","18");

  /*** Controla quantas células deseja exibir previamente ***/
  IupSetAttribute(mat,"NUMCOL_VISIBLE","5");
  IupSetAttribute(mat,"NUMLIN_VISIBLE","8");
  /*** ABAIXO VINCULADO AS CÉLULAS VISÍVEIS TEMOS A EXPANSÃO SE POSSÍVEL DAS CÉLULAS NA JANELA ***/
  IupSetAttribute(mat,"EXPAND", "NO"); //ISSO É MUITO BOM, PQ EU POSSO POR mat DENTRO DE UM HBOX OU VBOX E TER ÁREA ÚTIL PARA CRIAR FUNCIONALIDADES!
//  IupSetAttribute(mat,"SCROLLBAR", "NO");
  IupSetAttribute(mat,"RESIZEMATRIX", "YES");

  IupSetAttribute(mat,"MARKMODE", "CELL");
//  IupSetAttribute(mat,"MARKMODE", "LINCOL");
  IupSetAttribute(mat,"MARKMULTIPLE", "YES");
  IupSetAttribute(mat,"MARKAREA", "NOT_CONTINUOUS");
// IupSetAttribute(mat, "MARKAREA", "CONTINUOUS");



/*** \SUSPENSO

        if(mati==1){
                      IupMessage("Aviso!", "Bem-vindo(a) à exibição em pu \n Aperte Ok para prosseguir");

                      //Matrix_struct = percentual

                      IupMessagef("Aviso!",
                        " A reatância de Z[1][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][2][%%] é %.2f [%%]"
                        "\n A reatância de Z[2][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[1][3][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][1][%%] é %.2f [%%]"
                        "\n A reatância de Z[3][4][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][3][%%] é %.2f [Ohms]"
                        "\n A reatância de Z[4][4][%%] é %.2f [%%]"
                        , matrix_struct[1][1].gerador_indices.Xg_seq_zero
                        , matrix_struct[1][2].trafo_indices.X_TR_seq_zero
                        , matrix_struct[2][1].trafo_indices.X_TR_seq_zero
                        , matrix_struct[1][3].trafo_indices.X_TR_seq_zero
                        , matrix_struct[3][1].trafo_indices.X_TR_seq_zero
                        , matrix_struct[3][4].LT_indices.Xeq_LT_seq_zero
                        , matrix_struct[4][3].LT_indices.Xeq_LT_seq_zero
                        , matrix_struct[4][4].motor_indices.Xm_seq_zero);


                    //Matrix_struct = por unidade = pu

                    IupMessagef("Aviso!",
                        " A reatância de Z[1][1] é %.5f [pu]"
                        "\n A reatância de Z[1][2] é %.5f [pu]"
                        "\n A reatância de Z[2][1] é %.5f [pu]"
                        "\n A reatância de Z[1][3] é %.5f [pu]"
                        "\n A reatância de Z[3][1] é %.5f [pu]"
                        "\n A reatância de Z[3][4] é %.5f [pu]"
                        "\n A reatância de Z[4][3] é %.5f [pu]"
                        "\n A reatância de Z[4][4] é %.5f [pu]"
                        , matrix_struct_pu[1][1].gerador_indices.Xg_seq_zero
                        , matrix_struct_pu[1][2].trafo_indices.X_TR_seq_zero
                        , matrix_struct_pu[2][1].trafo_indices.X_TR_seq_zero
                        , matrix_struct_pu[1][3].trafo_indices.X_TR_seq_zero
                        , matrix_struct_pu[3][1].trafo_indices.X_TR_seq_zero
                        , matrix_struct_pu[3][4].LT_indices.Xeq_LT_seq_zero
                        , matrix_struct_pu[4][3].LT_indices.Xeq_LT_seq_zero
                        , matrix_struct_pu[4][4].motor_indices.Xm_seq_zero);

                  }


        ***/



/******************************************* \AUTOMACAO \BARRA \DE \TITULO \PLANILHA \positiva - INÍCIO ****************************************/

          int max_lin_and_col = 16;
          int int_cont = 0;
          char string_cell[30] = {NULL};
          char string_name[30] = {NULL};

          do{
                  int_cont++;

                  sprintf(string_cell,  "0:%d", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar x:%d", int_cont); // Bar x:1, Bar x:2, ..., Bar x:15

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar x:1")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que usar for vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


          int_cont = 0;



          do{
                  int_cont++;

                  sprintf(string_cell,  "%d:0", int_cont); //(linha,coluna) = "lin:col"

                  sprintf(string_name,  "Bar %d:y", int_cont); // Bar 1:y, Bar 2:y, ..., Bar 15:y

                  IupSetStrf(mat, string_cell, "%s", string_name); //envio: (matrix, "x:y", "Bar 1:y")

                  //primeira vez me dei conta da necessidade de utilizar o do-while...note que vai imprimir de 1 a 15 sob a mesma célula, até que sai a última impressão que é 15
                  //com do-while funcionou de primeira!

          }while(int_cont<max_lin_and_col-1); //ainda é feito um último laço se houver desigualdade, por isso o -1


/******************************************* \AUTOMACAO \BARRA \DE \TITULO - FIM ****************************************/


/*** \BLANK ***/


        int id_y = 0;
        int id_x = 0;
        float sobreporsicao1 = 0;
        float sobreporsicao2 = 0;
        float sobreporsicao3 = 0;
        float sobreporsicao4 = 0;


/*** \>>> GERADOR + MOTOR = \DIAGONAL \<<< ***/

if(mati==1){ //PLANILHA SEQUÊNCIA ZERO ABA 1 - Zpu é mais seletiva


        /*** Zpu diagonal ***/
        for(id_x = 1; id_x < size_SEP_bars+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
                                                       //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                                                       //for duplo vai sujar as células do TR e LT
                sobreporsicao1 = matrix_impedancia_zero_pu[id_x][id_x];

                //AQUI JÁ HAVIA SE RESOLVIDO, O PROBLEMA É 1:1 DA ADMITÂNCIA Y


                    //IupMessagef("Aviso!", "A reatância PARCIAL 1/2 de Z_pu[%d][%d][pu] é %.5f [pu]", id_x, id_x,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_x); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Zpu, da janela de sequência positiva


       } //FIM FOR-1: Gerador + Motor - Seq. Positiva




/*** \>>> TRAFO + LT = \FORA \DA \DIAGONAL \<<< ***/

        /*** Zpu fora da diagonal ***/
        for(id_x = 1; id_x < size_SEP_bars+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero
                if(id_x != id_y){ // HAVIA ESQUECIDO DISSO


                  sobreporsicao1 = matrix_struct_pu[id_x][id_y].trafo_indices.X_TR_seq_zero;
                  sobreporsicao2 = matrix_struct_pu[id_x][id_y].LT_indices.Xeq_LT_seq_zero;
                  sobreporsicao3 = sobreporsicao1 + sobreporsicao2;

                    //IupMessagef("Aviso!", "A reatância de Z_pu[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao);
                    sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                    IupSetStrf(IupGetHandle("mat1"), string_cell, "%.5f", sobreporsicao3); //Plota na planilha Zpu, da janela de sequência positiva
                    //FUNCIONA ?



                }
            }//

       }// //FIM FOR-2: LT + TR - Seq. Zero



}


if(mati==2){ //PLANILHA SEQUÊNCIA ZERO ABA 2 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \ADMITANCIA \TOTAL  - \ZERO \<<< ***/

        /*** Ypu É MENOS SELETIVA QUE Zpu ***/
        for(id_x = 1; id_x < size_SEP_bars+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_admitancia_zero_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A admitância Y[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat2"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//

       }// //FIM FOR-2: LT + TR - Seq. Zero

}



/*** \Zthevenin \matriz \inversa ***/


if(mati==3){ //PLANILHA SEQUÊNCIA ZERO ABA 3 >>>>>>>>> TROQUE mat1 para mat2 no IupGetHandle


/*** \>>>  \THEVENIN \CURTO \CIRCUITO - \ZERO \<<< ***/

        /*** Zth_pu É MENOS SELETIVA QUE Zpu ***/
        for(id_x = 1; id_x < size_SEP_bars+1; id_x++){ //antes ia de 0 a 4, e o único gerador dessa matriz era o 0:0
            for(id_y = 1; id_y < size_SEP_bars+1; id_y++){ //lá no cálculo de pu já foi adaptado para iniciar em 1, e não mas em zero


                sobreporsicao1 = matrix_thevenin_zero_pu[id_x][id_y];

                //IupMessagef("Aviso!", "A inversa Z_th[%d][%d] é %.5f [pu]", id_x, id_y,sobreporsicao1);
                sprintf(string_cell,  "%d:%d", id_x, id_y); //(linha,coluna) = "lin:col", já casou os pares, antes era i+1
                IupSetStrf(IupGetHandle("mat3"), string_cell, "%.5f", sobreporsicao1); //Plota na planilha Ypu, da janela de sequência positiva, aba 2

            }//FIM FOR-1: thevenin - Seq. Zero

       }//FIM FOR-2: thevenin - Seq. Zero


} //condicional aba 3


          IupSetAttribute(mat, "FLATSCROLLBAR", "Yes"); //MUITO SOFISTICADA, LIMPA E SUTIL
        //  IupSetAttribute(mat, "SHOWFLOATING", "Yes"); //ficou mascarado demais com barra de rolagem oculta ...atrapalha um pouco a úlima linha
        //  IupSetAttribute(mat, "SHOWTRANSPARENT", "Yes"); //não gostei


  return mat;

  }
  else return NULL;

}






/***************************** CRIAÇÃO DE LISTAS DE PARES ORDENADOS - FUNCTIONS STRING FULL AND TAGs *********************************/
/*****************************************(          \LISTAS \DINAMICAS \STRING \FULL \IN \TAGS   )********************************************
        >>> CARREGAMENTO EM CASCATA
***/




/*****************************************(       \CARREGAR \LISTA \DINAMICA \GERADOR   )********************************************

***/
void function_INDEX_Zbox_Gerador(Ihandle* disparo){ //dispara em seguida Zbox_Trafo, Zbox_LT e Zbox_Motor

    /*********** LASTRO

    1) A função function_List_gerador() cria o frame na função gerador(), e a função acima atualiza a lista do frame criado
    2) Não é possível atualizar a lista antes de definir o número de barras via botão button_Size_bars da função function_size_SEP_bars
    2.1) Quebrar a função function_size_SEP_bars em duas, uma para gerar o vetor de inteiros e outra para criar o vetor char de indexs gerador

    *************/

    if(id_size_bars==0)
    {
         IupMessagef("Aviso!", "Favor definir o número de barras!\nClique no Botão Definir.");
    }

    if(id_size_bars !=0 )
    {
          int ret = IupAlarm("Aviso!", "Deseja limpar o Formulário", "Yes", "No", NULL);
          if (ret == 1) /* Yes Option*/
          {
            run_reset_MOTOR(disparo);
            run_reset_GERADOR(disparo);
            run_reset_TRAFO(disparo);
            run_reset_LT(disparo);
          }
          else
            printf("continua");
    }

    if(id_size_bars!=0) //AGORA O BOTÃO DE INDEXAÇÃO TRABALHA
    {
           //Ihandle *list_NEW = IupGetHandle ("list_tag_GE");  //LIMPAR LISTA - N APÓS A 3a VEZ ... pois eu defini um conteúdo INDEX_OFF
           //IupSetAttributes(list_NEW, indexs_conj_GERADOR_FULL); // LISTA RENEW != LISTA RENEW --- ADEMAIS IF ABAIXO


           //a tag do frame é a 1:1 ... CAPTURAR O BOTÃO OU INDIRETAMENTE A DLG?! EM SEGUIDA VAI EM BUSCA DA TAG DO FRAME

           /***** NOTE QUE A STRING FULL PRECISA TER SIDO CRIADA >>> id_Zbox++; //CRÍTICO ***/

            if(id_Zbox_GE != 0){                                                               //NOVA LISTA

                    Ihandle *list_NEW = IupGetHandle("list_tag_GE");

                    //frame = IupFrame(IupSetAttributes(IupList(NULL), "DROPDOWN=YES, 1=Test, 2=APROVADO, VALUE=1"));
                    //IupSetAttributes(frame, "DROPDOWN=NO, 1=Test, 2=APROVADO, VALUE=1"); //SÓ PRECISO PEGAR O FRAME CAPTURADO E ATUALIZAR A LISTA


                    //IupSetAttributes(lista_FOR_tag, "DROPDOWN=NO, 1=\"Banana\", 2=\"Apple\", 3=\"Orange\", 4=\"Strawberry\", 5=\"Grape\","
                      //     "VALUE=1, XXX_BGCOLOR=\"192 64 192\"");


                    //IupSetAttributes(list_NEW, "");
                    IupSetAttributes(list_NEW, indexs_conj_GERADOR_FULL);
                    //NOTE QUE ESTOU USANDO CERTO = SET = AJUSTAR...

                    /*************** ATUALIZA A LISTA DE INDEXAÇÃO DO GERADOR COM A STRING FULL DO GERADOR *****************/

                          int i = 1;

                          i++;
                          i = 10 + i;

                          //IupMessagef("Aviso!", "A indexação da STRING FULL do GE é %s", indexs_conj_GERADOR_FULL);

                          //IupMessagef("Aviso!", "A indexação de barras/nós foi criada.\nProssiga ao preenchimento do formulário! - GE");

                          function_INDEX_Zbox_Trafo(1); //dispara a criação da indexação do trafo

                    //return IUP_DEFAULT; //ACHO QUE NÃO PODERIA DEIXAR ISSO AQUI, SOMENTE NO FINAL DA CASCATA ?!
                    //FUNCIONOU TRANQUILÃO, no caso o botão drop list *button_Zbox de índices finaliza a função Carregar function_INDEX_Zbox_Gerador
                    //após o return do final da cascata, na function_INDEX_Zbox_Motor
            }



    }


}





/*****************************************(       \CARREGAR \LISTA \DINAMICA \TRAFO   )********************************************

***/
void function_INDEX_Zbox_Trafo(int GE_Zbox_function){ //dispara em seguida Zbox_LT e Zbox_Motor

    if(id_size_bars==0)
    {
         IupMessagef("Aviso!", "Favor definir o número de barras!\nClique no Botão Definir - TRAFO.");
    }

    if(id_size_bars!=0) //AGORA O BOTÃO DE INDEXAÇÃO TRABALHA
    {

            if(id_Zbox_TRAFO != 0){                                                               //NOVA LISTA

                    Ihandle *list_NEW = IupGetHandle("list_tag_TRAFO"); //captaura a lista "zerada" = ativada com index_ON

                    IupSetAttributes(list_NEW, indexs_conj_TRAFO_FULL); //Atualiza a lista com a STRING FULL do trafo

                    /*************** ATUALIZA A LISTA DE INDEXAÇÃO DO GERADOR COM A STRING FULL DO GERADOR *****************/

                          int i = 1;

                          i++;
                          i = 10 + i;

                          //IupMessagef("Aviso!", "A indexação de barras/nós foi criada.\nProssiga ao preenchimento do formulário! - TRAFO");

                          function_INDEX_Zbox_LT(2); //dispara a criação da indexação da LT

                    //return IUP_DEFAULT;
            }

    }

}




/*****************************************(       \CARREGAR \LISTA \DINAMICA \LT   )********************************************

***/
void function_INDEX_Zbox_LT(int Trafo_Zbox_function){ //dispara em seguida Zbox_Motor --- fim da cascata

    if(id_size_bars==0)
    {
         IupMessagef("Aviso!", "Favor definir o número de barras!\nClique no Botão Definir - LT.");
    }

    if(id_size_bars!=0) //AGORA O BOTÃO DE INDEXAÇÃO TRABALHA
    {

            if(id_Zbox_LT != 0){                                                               //NOVA LISTA

                    Ihandle *list_NEW = IupGetHandle("list_tag_LT"); //captaura a lista "zerada" = ativada com index_ON

                    IupSetAttributes(list_NEW, indexs_conj_LT_FULL); //Atualiza a lista com a STRING FULL do trafo

                    /*************** ATUALIZA A LISTA DE INDEXAÇÃO DO GERADOR COM A STRING FULL DO GERADOR *****************/

                          int i = 1;

                          i++;
                          i = 10 + i;

                          //IupMessagef("Aviso!", "A indexação de barras/nós foi criada.\nProssiga ao preenchimento do formulário! - LT");

                          function_INDEX_Zbox_Motor(3); //dispara a criação da indexação do motor

                    //return IUP_DEFAULT;
            }

    }

}








/*****************************************(       \CARREGAR \LISTA \DINAMICA \MOTOR   )********************************************

***/
static int function_INDEX_Zbox_Motor(int LT_Zbox_function){//Encerra a cascata e inicializa as variáveis nulas id_k

    if(id_size_bars==0)
    {
         IupMessagef("Aviso!", "Favor definir o número de barras!\nClique no Botão Definir - MOTOR.");
    }

    if(id_size_bars!=0) //AGORA O BOTÃO DE INDEXAÇÃO TRABALHA
    {

            if(id_Zbox_MOTOR != 0){                                                               //NOVA LISTA

                    Ihandle *list_NEW = IupGetHandle("list_tag_MOTOR"); //captaura a lista "zerada" = ativada com index_ON

                    IupSetAttributes(list_NEW, indexs_conj_MOTOR_FULL); //Atualiza a lista com a STRING FULL do trafo

                    /*************** ATUALIZA A LISTA DE INDEXAÇÃO DO GERADOR COM A STRING FULL DO GERADOR *****************/

                          int i = 1;

                          i++;
                          i = 10 + i;

                          //IupMessagef("Aviso!", "A indexação de barras/nós foi criada.\nProssiga ao preenchimento do formulário! - MOTOR");
                          if(depurar_motor==1){
                          IupMessagef("Aviso!", "A indexação de barras/nós foi criada.\nProssiga ao preenchimento do formulário!");
                          }


            /********************************************* INICIALIZAÇÃO DAS VARIÁVEIS DE ID_K DAS STRUCTS ***********************************/
            /***
            for(id_x = 0; id_x < size_SEP_bars+1; id_x++){
                for(id_y = 0;id_y < size_SEP_bars+1; id_y++){

                    matrix_struct[id_x][id_y].gerador_indices.id_k_Motor = 0;

                }

            }
            ***/



                    return IUP_DEFAULT;
            }

    }

}







/******************** STAND BY **********************************************************************/

int string_comprimento(int* string) //Função genérica de suporte - Stand By (não setá sendo utilizada)
{
    //Função que retorna o comprimento de uma string - código C puro

    int comprimento = 0;

    //Agora que me dei conta que o fórum tinha publicado um código errado, e como ninguém questionou ficou parecendo certo, mas estava errado!
    while (*(indexs_conj_SEP + comprimento) != '\0') { //confere o valor da casa, se não for \0 prossegue

       // IupMessagef("Aviso!", "A posição do vetor indexs_conj_SEP é %d", (indexs_conj_SEP + comprimento));
       // IupMessagef("Aviso!", "O valor do vetor indexs_conj_SEP é %d", *(indexs_conj_SEP + comprimento));
        comprimento++;
        indexs_conj_SEP + comprimento; //avança a casa ...acesso global à variável
    }

    //IupMessagef("Aviso!", "O comprimento do vetor é %d", comprimento);

    return comprimento;
}







/*****************************************(       \CARREGAR \BARRAS \INICIALIZAR \LISTAS \DINAMICAS   )********************************************

***/
static int function_size_SEP_bars(Ihandle *button_Size_bars) //Cálculos de indexação do gerador <<<<<< QUEBRAR FUNÇÃO EM 2
{


id_size_bars++; //identificador que foi criado a indexação das barras
/************************************* ATIVAÇÃO DO BOX VALUE BAR SIZE **********************************/
/************************************* CRIAÇÃO DO VETOR INDEX DO TIPO INT **********************************/
/************************************* CRIAÇÃO DO VETOR INDEX DO TIPO CHAR PARA O GERADOR **********************************/

    /*** ativando o BoxValue de BoxValue_size_SEP_bars do Form para coleta***/

    Ihandle *MemoryBoxValue_size_SEP_bars = IupGetDialogChild(button_Size_bars, "BoxValue_size_SEP_bars_tag"); //disparar por um botão button_Size_bars e pela tag colega o número de barras
    int valor_size_SEP_bars = IupGetInt(MemoryBoxValue_size_SEP_bars, "VALUE"); //Variável global
                                                                            //Tem que armazenar o inteiro numa variável global

    /*** CUIDADO É UM GET_INT ***/

    if(depurar_SEP == 1){
    IupMessagef("Aviso!", "O número de barras coletas é %d", valor_size_SEP_bars);
    }


    /****** CUIDADO A VARIÁVEL VALOR ESTÁ COMO STATIC INT = 4 *******/
    //Coleta de variável global
    size_SEP_bars = valor_size_SEP_bars; //Não tem como fazer uma função que depende do botão, tem que coletar de uma variável global

    size_SEP_bars_OLD = size_SEP_bars;//inicialização

    status_memory_size_SEP_bars++; //Serve para o botão do Form Base, e fica visível o status de dimensionamento do SEP


    function_STRING_FULL_GERADOR(1);
    function_STRING_FULL_TRAFO(2);
    function_STRING_FULL_LT(3);
    function_STRING_FULL_MOTOR(4);


    return IUP_DEFAULT; //Não tem como retornar um inteiro, pois é um botão;
}









/*****************************************(       \CRIAR \LISTA \DINAMICA \STRING \GERADOR   )********************************************

***/

void function_STRING_FULL_GERADOR(int disparo)
{

/****************************************** CARREGAMENTO DO CONJUNTO DE CARACTERES DAS BARRAS DO GERADOR **********************************/

    /*************************************** CONVERTANDO O VETOR INDEX_CONJUT INT PARA CHAR - DECLARAÇÕES ************************/

    //int size_string = MAX_STRING_FULL*size_SEP_bars;



    /*** OBSERVAÇÕES CRÍTICAS: 1 - static char indexs_conj_GERADOR_FULL[50] deve ser assim senão vai bugar a impressão ou use malloc ***/
                        /***   2 - o indexs_conj_GERADOR_FULL não vai zerar as strings se tu não zerar ao mudar o número de barras: não pode ficar static ***/

    //char indexs_conj_GERADOR[50]; //Se eu insiro diretamente um tamanho a impressão da string FULL fica também com caracteres zuados na primeira quantidade de barras
    char* indexs_conj_GERADOR = (char*)malloc(50*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ****/

    //char indexs_conj_GERADOR_FULL[50];
    indexs_conj_GERADOR_FULL = (char*)malloc(MAX_STRING_FULL*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA - VAR GLOBAL ****/

    //char Teste[]= {"Teste: "}; --- GARGALO NÃO SEI COMO SAIR DISSO, está alocado e inicializado, pq não faz a concatenagem
    //char Teste[50]= {""};
    //indexs_conj_GERADOR_FULL = Teste; //inicializa olhando para Teste[0]


    /*** Rotina de buffer ***/
        char Buffer[1]={""}; /*** de fato é um buffer, pq vai ficar somente na função e não globalmente ***/
        //strcpy(indexs_conj_GERADOR_FULL, Buffer);
       strcpy(indexs_conj_GERADOR_FULL, Buffer); //estou inicializando a variável STRING FULL
        //strcat(indexs_conj_GERADOR_FULL, Buffer); ///naõ testei sobreposto

        //O strcpy vai copiar um conteúdo de uma var para outra var
        //O strcat vai integrar um conteúdo de uma var em outra var




    //static int MAX_size_SEP_bars = 0; //Variável global

    //LIMPAR STRING CHAR DA LISTA - PRIMEIRA VEZ
  /***
    sprintf(indexs_conj_GERADOR_FULL,"DROPDOWN=NO, 1=\"index_ON\", "
            "VALUE=1, BGCOLOR=\"100 255 0\"");
***/

    sprintf(indexs_conj_GERADOR_FULL,"Carregamento de índices para o gerador."); //PROBLEMA NÃO É APAGAR A STRING EM SI, ELA APAGA, O PROBLEMA É APAGAR A LISTA!

    //    strcpy(indexs_conj_GERADOR_FULL, Buffer); - erro 1 - repetir e não limpa
    //IupMessagef("Aviso!", "%s", indexs_conj_GERADOR_FULL); // IMPRINDO A STRING LIMPA - TELA VAZIA





    id_Zbox_GE++; //CRÍTICO --- PRIMEIRA VEZ QUE FOI CRIADO A STRING FULL --- NÃO VAI TER ACESSO SIMULTÂNEO PQ A OUTRA FUNÇÃO DEPENDE DE DISPARO
               //O ACESSO A LIST_TAG AQUI DEPENDE DO DISPARO DO BOTÃO SIZE BARS
               //O ACESSO A LIST_TAG EM OUTRO CASO DEPENDE DO DISPARO DO BOTÃO DE INDEXAÇÃO ...QUE CONTUDO DEPENDE DA STRING DO BOTÃO SIZE

/************************* CAGADA ABSURDA: CONSEGUI LIMPAR TODOS OS ITENS FAZENDO TESTE TOSCO **************************/

/********************************************** LIMPAR LISTA FULL ******************************************************/

//1 bug = só não apagou esta lista uma vez 11mai22 17h12

        Ihandle *list_RENEW = IupGetHandle("list_tag_GE");         //LIMPAR LISTA - PRIMEIRA VEZ ... pois eu defini um conteúdo para primeira linha
        //list_RENEW = IupList(NULL);
        //IupSetHandle ("list_tag", list_RENEW);



        Ihandle *list_RENEW_itens = IupGetDialogChild(list_RENEW, NULL); //A princípio era para ativar uma tag de item, mas pegando a pegando toda lista
        IupSetAttribute(list_RENEW, "REMOVEITEM", IupGetAttribute(list_RENEW_itens, "VALUE")); //Uma vez armazenado todos os itens da lista, removo

/********************************************** LIMPAR LISTA FULL ******************************************************/

            sprintf(indexs_conj_GERADOR_FULL,"DROPDOWN=NO, 1=\"index_ON\", "
            "VALUE=1, BGCOLOR=\"100 255 0\""); //Verde = habilitado

        IupSetAttributes(list_RENEW, indexs_conj_GERADOR_FULL); //carrega a string char "zerada" à lista


      //  Ihandle *list_RENEW = IupGetHandle ("list_tag");         //LIMPAR LISTA - PRIMEIRA VEZ ... pois eu defini um conteúdo para primeira linha
       // IupSetAttributes(list_RENEW, indexs_conj_GERADOR_FULL); //carrega a string char "zerada" à lista


    //LIMPAR STRING CHAR DA LISTA -


    /*************************************** CONVERTENDO O VETOR INDEX_CONJUT INT PARA CHAR  - FOR ************************/


//cuidado, tava gerando só o número 1 e assim a lista só vai criar um elemento

    for(int i = 0; i <size_SEP_bars_OLD+1; i++){ //+1 é por causa do selecionar (Barra:Barra)

        //A LIMPEZA DA STRING FULL OCORRE DENTRO DO FOR!!! NÃO É O BUFFER QUE INICIALIZA É O STRING FULL
        if(i==0){

            sprintf(indexs_conj_GERADOR_FULL, "%d=\"Barra:Barra \",", i+1);
            //strcat(indexs_conj_GERADOR_FULL, indexs_conj_GERADOR);

            //sprintf(indexs_conj_GERADOR, "%d=\" (%d:%d) \", ", *(indexs_conj_SEP+i), *(indexs_conj_SEP+i), *(indexs_conj_SEP+i));
            //strcat(indexs_conj_GERADOR_FULL, indexs_conj_GERADOR);

            //IupMessagef("Aviso!", "%s", indexs_conj_GERADOR_FULL);
        }

        if(i>0){
            sprintf(indexs_conj_GERADOR, "%d=\" (%d:%d) \", ", i+1, i, i); //aqui tu tem que concatenar filho
            /*** Rotina copia letra por letra
            while(indexs_conj_GERADOR[j] != '\0'){
            *(indexs_conj_GERADOR_FULL2+j) = indexs_conj_GERADOR[j];
            j++;
            }
            ***/

            strcat(indexs_conj_GERADOR_FULL, indexs_conj_GERADOR); //incrementa ao conteúdo antigo de indexs_conj_GERADOR_FULL o apêndice indexs_conj_GERADOR
                                                                   //a aa aaa aaa ...a cada interação
            //IupMessagef("Aviso!", "%s", indexs_conj_GERADOR_FULL); //a aa aaa aaa ...a cada interação
            //IupMessagef("Aviso!", "%s", indexs_conj_GERADOR_FULL);

                matrix_struct[i][i].gerador_indices.id_k_Gerador = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                matrix_struct[i][i].gerador_indices.id_x = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                matrix_struct[i][i].gerador_indices.id_y = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO


        }


    }


/****************************************** GERANDO A STRING FULL DE CARACTERES DO GERADOR *******************************************************/


    strcat(indexs_conj_GERADOR_FULL, "VALUE=1, BGCOLOR=\"0 255 255\""); //azul anil fundo do gerador
    //IupMessagef("Aviso!", "%s", indexs_conj_GERADOR_FULL); //PREENCHIMENTO FINAL DISPONÍVEL EM VARIÁVEL GLOBAL

    //IupMessagef("Aviso!", "%s", "Favor carregar índices."); //PREENCHIMENTO FINAL DISPONÍVEL EM VARIÁVEL GLOBAL

    /************** LISTA ATUALIZADA PARA USO ************/


    //free(indexs_conj_GERADOR); //Liberar memória, pois este vetor não é permanente



/************************ CONJUNTO DE ÍNDICES - FIM **************************************************************************/

    /************* LASTRO

    1) function_INDEX_Zbox_Gerabor
    2) list_tag


    **************/

}









/*****************************************(       \CRIAR \LISTA \DINAMICA \STRING \TRAFO   )********************************************

***/

void function_STRING_FULL_TRAFO(int disparo)
{

/****************************************** CARREGAMENTO DO CONJUNTO DE CARACTERES DAS BARRAS DO GERADOR **********************************/

    /*************************************** CONVERTANDO O VETOR INDEX_CONJUT INT PARA CHAR - DECLARAÇÕES ************************/

    //int size_string = MAX_STRING_FULL*size_SEP_bars; //MAX_STRING_FULL = 200 - fator

    char* indexs_conj_TRAFO = (char*)malloc(50*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ****/

    indexs_conj_TRAFO_FULL = (char*)malloc(MAX_STRING_FULL*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA - VAR GLOBAL ****/



    /*** Rotina de buffer ***/
       char Buffer[1]={""}; /*** de fato é um buffer, pq vai ficar somente na função e não globalmente ***/
       strcpy(indexs_conj_TRAFO_FULL, Buffer); //estou inicializando a variável STRING FULL





    sprintf(indexs_conj_TRAFO_FULL,"Carregamento de índices para o transformador."); //PROBLEMA NÃO É APAGAR A STRING EM SI, ELA APAGA, O PROBLEMA É APAGAR A LISTA!

    //IupMessagef("Aviso!", "%s", indexs_conj_TRAFO_FULL); // IMPRINDO A STRING LIMPA - TELA VAZIA




    id_Zbox_TRAFO++; //CRÍTICO --- PRIMEIRA VEZ QUE FOI CRIADO A STRING FULL --- NÃO VAI TER ACESSO SIMULTÂNEO PQ A OUTRA FUNÇÃO DEPENDE DE DISPARO
               //O ACESSO A LIST_TAG AQUI DEPENDE DO DISPARO DO BOTÃO SIZE BARS
               //O ACESSO A LIST_TAG EM OUTRO CASO DEPENDE DO DISPARO DO BOTÃO DE INDEXAÇÃO ...QUE CONTUDO DEPENDE DA STRING DO BOTÃO SIZE


        Ihandle *list_RENEW = IupGetHandle ("list_tag_TRAFO");         //LIMPAR LISTA - PRIMEIRA VEZ ... pois eu defini um conteúdo para primeira linha


/********************************************** LIMPAR LISTA FULL ******************************************************/

        Ihandle *list_RENEW_itens = IupGetDialogChild(list_RENEW, NULL); //A princípio era para ativar uma tag de item, mas pegando a pegando toda lista
        IupSetAttribute(list_RENEW, "REMOVEITEM", IupGetAttribute(list_RENEW_itens, "VALUE")); //Uma vez armazenado todos os itens da lista, removo

/********************************************** LIMPAR LISTA FULL ******************************************************/

            sprintf(indexs_conj_TRAFO_FULL,"DROPDOWN=NO, 1=\"index_ON\", "
            "VALUE=1, BGCOLOR=\"100 255 0\""); //Verde = habilitado

        IupSetAttributes(list_RENEW, indexs_conj_TRAFO_FULL); //carrega a string char "zerada" à lista


    /*************************************** CONVERTENDO O VETOR INDEX_CONJUT INT PARA CHAR  - FOR ************************/
    //MAX_STRING_FULL = 200 - fator             //SÓ VAI QUEBRAR A STRING SE O FATOR FOR BAIXO
    //*(indexs_conj_SEP+i)
    int n = 0;
    int k = 0;
    int i = 0;
    int j = 0;
    int g = 0;
        //for(i = 0, j=2; i <size_SEP_bars_OLD;j++, i++){
        for(i = 0; i < size_SEP_bars_OLD;i++){
            for(j=0; j < size_SEP_bars_OLD; j++){
            //A LIMPEZA DA STRING FULL OCORRE DENTRO DO FOR!!! NÃO É O BUFFER QUE INICIALIZA É O STRING FULL

                g = 0;

                if(k == 0 && j == 1){ //Este if é apenas para inicializar
                    n++; //funciona de jeito nenhum como argumento!
                    //sprintf(indexs_conj_LT_FULL, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    sprintf(indexs_conj_TRAFO_FULL, "%d=\"Barra primária:Barra Secundária\",", n); //n é o elemento 1 da lista


                    n++;
                    sprintf(indexs_conj_TRAFO, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    //-IupMessagef("Aviso!", "%s", indexs_conj_LT_FULL);

                    strcat(indexs_conj_TRAFO_FULL, indexs_conj_TRAFO);

                    matrix_struct[i+1][j+1].trafo_indices.id_k_Trafo = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                    matrix_struct[i+1][j+1].trafo_indices.id_x = 0;
                    matrix_struct[i+1][j+1].trafo_indices.id_y = 0;

                    k++;
                    g++;
                }

                if(k != 0 && i != j && g == 0){ //precisa do g por causa do k++ valida acima por 1 vez
                     n++;
                    sprintf(indexs_conj_TRAFO, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    //IupMessagef("Aviso!", "%s", indexs_conj_TRAFO);

                    strcat(indexs_conj_TRAFO_FULL, indexs_conj_TRAFO); //é difícil "enxergar isso", mas é preciso que A
                                                                         //STRING FULL fique cheia corretamente no primeiro if para concatenar ...
                                                                         //as duas variáveis precisam estar cheias para entrar no segundo if
                    //-IupMessagef("Aviso!", "%s", indexs_conj_TRAFO_FULL);

                    matrix_struct[i+1][j+1].trafo_indices.id_k_Trafo = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                    matrix_struct[i+1][j+1].trafo_indices.id_x = 0;
                    matrix_struct[i+1][j+1].trafo_indices.id_y = 0;
                }
            }

        }



/****************************************** GERANDO A STRING FULL DE CARACTERES DO TRAFO *******************************************************/


    strcat(indexs_conj_TRAFO_FULL, "VALUE=1, BGCOLOR=\"255 100 114\""); //lilás sóbrio - Trafo geral

}








/*****************************************(       \CRIAR \LISTA \DINAMICA \STRING \LT   )********************************************

***/

void function_STRING_FULL_LT(int disparo)
{

/****************************************** CARREGAMENTO DO CONJUNTO DE CARACTERES DAS BARRAS DO GERADOR **********************************/

    /*************************************** CONVERTANDO O VETOR INDEX_CONJUT INT PARA CHAR - DECLARAÇÕES ************************/

    //int size_string = MAX_STRING_FULL*size_SEP_bars; //MAX_STRING_FULL = 200 - fator

    char* indexs_conj_LT = (char*)malloc(50*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ****/

    indexs_conj_LT_FULL = (char*)malloc(MAX_STRING_FULL*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA - VAR GLOBAL ****/



    /*** Rotina de buffer ***/
        char Buffer[1]={""}; /*** de fato é um buffer, pq vai ficar somente na função e não globalmente ***/

       strcpy(indexs_conj_LT_FULL, Buffer); //estou inicializando a variável STRING FULL





    sprintf(indexs_conj_LT_FULL,"Carregamento de índices para a linha de transmissão"); //PROBLEMA NÃO É APAGAR A STRING EM SI, ELA APAGA, O PROBLEMA É APAGAR A LISTA!

    //IupMessagef("Aviso!", "%s", indexs_conj_LT_FULL); // IMPRINDO A STRING LIMPA - TELA VAZIA





    id_Zbox_LT++; //CRÍTICO --- PRIMEIRA VEZ QUE FOI CRIADO A STRING FULL --- NÃO VAI TER ACESSO SIMULTÂNEO PQ A OUTRA FUNÇÃO DEPENDE DE DISPARO
               //O ACESSO A LIST_TAG AQUI DEPENDE DO DISPARO DO BOTÃO SIZE BARS
               //O ACESSO A LIST_TAG EM OUTRO CASO DEPENDE DO DISPARO DO BOTÃO DE INDEXAÇÃO ...QUE CONTUDO DEPENDE DA STRING DO BOTÃO SIZE


        Ihandle *list_RENEW = IupGetHandle ("list_tag_LT");         //LIMPAR LISTA - PRIMEIRA VEZ ... pois eu defini um conteúdo para primeira linha


/********************************************** LIMPAR LISTA FULL ******************************************************/

        Ihandle *list_RENEW_itens = IupGetDialogChild(list_RENEW, NULL); //A princípio era para ativar uma tag de item, mas pegando a pegando toda lista
        IupSetAttribute(list_RENEW, "REMOVEITEM", IupGetAttribute(list_RENEW_itens, "VALUE")); //Uma vez armazenado todos os itens da lista, removo

/********************************************** LIMPAR LISTA FULL ******************************************************/

            sprintf(indexs_conj_LT_FULL,"DROPDOWN=NO, 1=\"index_ON\", "
            "VALUE=1, BGCOLOR=\"100 255 0\""); //verde de ativação index_ON

        IupSetAttributes(list_RENEW, indexs_conj_LT_FULL); //carrega a string char "zerada" à lista


    /*************************************** CONVERTENDO O VETOR INDEX_CONJUT INT PARA CHAR  - FOR ************************/
    //MAX_STRING_FULL = 200 - fator             //SÓ VAI QUEBRAR A STRING SE O FATOR FOR BAIXO
    //*(indexs_conj_SEP+i)
    int n = 0;
    int k = 0;
    int i = 0;
    int j = 0;
    int g = 0;
        //for(i = 0, j=2; i <size_SEP_bars_OLD;j++, i++){
        for(i = 0; i < size_SEP_bars_OLD;i++){
            for(j=0; j < size_SEP_bars_OLD; j++){
            //A LIMPEZA DA STRING FULL OCORRE DENTRO DO FOR!!! NÃO É O BUFFER QUE INICIALIZA É O STRING FULL

                g = 0;

                if(k == 0 && j == 1){ //Este if é apenas para inicializar
                    n++; //funciona de jeito nenhum como argumento!
                    //sprintf(indexs_conj_LT_FULL, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    sprintf(indexs_conj_LT_FULL, "%d=\"Barra:Barra\",", n); //n é o elemento 1 da lista


                    n++;
                    sprintf(indexs_conj_LT, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    //-IupMessagef("Aviso!", "%s", indexs_conj_LT_FULL);

                    strcat(indexs_conj_LT_FULL, indexs_conj_LT);


                    matrix_struct[i+1][j+1].LT_indices.id_k_LT = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                    matrix_struct[i+1][j+1].LT_indices.id_x = 0;
                    matrix_struct[i+1][j+1].LT_indices.id_y = 0;

                    k++;
                    g++;
                    //Inicialização do carregamento de forma correta
                }

                if(k != 0 && i != j && g == 0){ //precisa do g por causa do k++ valida acima por 1 vez
                     n++;
                    //sprintf(indexs_conj_LT, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    sprintf(indexs_conj_LT, "%d=\" (%d:%d) \", ", n, i+1, j+1);
                    //IupMessagef("Aviso!", "%s", indexs_conj_LT);

                    strcat(indexs_conj_LT_FULL, indexs_conj_LT); //é difícil "enxergar isso", mas é preciso que A
                                                                         //STRING FULL fique cheia corretamente no primeiro if para concatenar ...
                                                                         //as duas variáveis precisam estar cheias para entrar no segundo if
                    //-IupMessagef("Aviso!", "%s", indexs_conj_LT_FULL);

                    matrix_struct[i+1][j+1].LT_indices.id_k_LT = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
                    matrix_struct[i+1][j+1].LT_indices.id_x = 0;
                    matrix_struct[i+1][j+1].LT_indices.id_y = 0;
                }
            }

        }



/****************************************** GERANDO A STRING FULL DE CARACTERES DO TRAFO *******************************************************/


    strcat(indexs_conj_LT_FULL, "VALUE=1, BGCOLOR=\"27 181 255\""); //azul prata - LT

}







/*****************************************(       \CRIAR \LISTA \DINAMICA \STRING \MOTOR   )********************************************

***/

void function_STRING_FULL_MOTOR(int disparo)
{

/****************************************** CARREGAMENTO DO CONJUNTO DE CARACTERES DAS BARRAS DO MOTOR **********************************/

    /*************************************** CONVERTANDO O VETOR INDEX_CONJUT INT PARA CHAR - DECLARAÇÕES ************************/

    //int size_string = MAX_STRING_FULL*size_SEP_bars;



    char* indexs_conj_MOTOR = (char*)malloc(50*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA ****/
    indexs_conj_MOTOR_FULL = (char*)malloc(MAX_STRING_FULL*sizeof(char)); /*** ALOCAÇÃO DE MEMÓRIA É OBRIGATÓRIA - VAR GLOBAL ****/


    /*** Rotina de buffer ***/
       char Buffer[1]={""};
       strcpy(indexs_conj_MOTOR_FULL, Buffer); //estou inicializando a variável STRING FULL


    sprintf(indexs_conj_MOTOR_FULL,"Carregamento de índices para o motor.");

    //IupMessagef("Aviso!", "%s", indexs_conj_MOTOR_FULL); // IMPRINDO A STRING LIMPA - TELA VAZIA





    id_Zbox_MOTOR++; //CRÍTICO --- PRIMEIRA VEZ QUE FOI CRIADO A STRING FULL --- NÃO VAI TER ACESSO SIMULTÂNEO PQ A OUTRA FUNÇÃO DEPENDE DE DISPARO
               //O ACESSO A LIST_TAG AQUI DEPENDE DO DISPARO DO BOTÃO SIZE BARS
               //O ACESSO A LIST_TAG EM OUTRO CASO DEPENDE DO DISPARO DO BOTÃO DE INDEXAÇÃO ...QUE CONTUDO DEPENDE DA STRING DO BOTÃO SIZE

/************************* CAGADA ABSURDA: CONSEGUI LIMPAR TODOS OS ITENS FAZENDO TESTE TOSCO **************************/

/********************************************** LIMPAR LISTA FULL ******************************************************/


        Ihandle *list_RENEW = IupGetHandle ("list_tag_MOTOR");         //LIMPAR LISTA - PRIMEIRA VEZ ... pois eu defini um conteúdo para primeira linha


        Ihandle *list_RENEW_itens = IupGetDialogChild(list_RENEW, NULL); //A princípio era para ativar uma tag de item, mas pegando a pegando toda lista
        IupSetAttribute(list_RENEW, "REMOVEITEM", IupGetAttribute(list_RENEW_itens, "VALUE")); //Uma vez armazenado todos os itens da lista, removo

/********************************************** LIMPAR LISTA FULL ******************************************************/

            sprintf(indexs_conj_MOTOR_FULL,"DROPDOWN=NO, 1=\"index_ON\", "
            "VALUE=1, BGCOLOR=\"100 255 0\""); //verde de ativação index_ON

        IupSetAttributes(list_RENEW, indexs_conj_MOTOR_FULL); //carrega a string char "zerada" à lista


    /*************************************** CONVERTENDO O VETOR INDEX_CONJUT INT PARA CHAR  - FOR ************************/


//cuidado, tava gerando só o número 1 e assim a lista só vai criar um elemento

    for(int i = 0; i <size_SEP_bars_OLD+1; i++){ //+1 é por causa do selecionar

        //A LIMPEZA DA STRING FULL OCORRE DENTRO DO FOR!!! NÃO É O BUFFER QUE INICIALIZA É O STRING FULL
        if(i==0){

            sprintf(indexs_conj_MOTOR_FULL, "%d=\"Barra:Barra \",", i+1);
            //strcat(indexs_conj_GERADOR_FULL, indexs_conj_GERADOR);

            //sprintf(indexs_conj_GERADOR, "%d=\" (%d:%d) \", ", *(indexs_conj_SEP+i), *(indexs_conj_SEP+i), *(indexs_conj_SEP+i));
            //strcat(indexs_conj_GERADOR_FULL, indexs_conj_GERADOR);

            //IupMessagef("Aviso!", "%s", indexs_conj_MOTOR_FULL);
        }

        if(i>0){
            sprintf(indexs_conj_MOTOR, "%d=\" (%d:%d) \", ", i+1, i, i); //aqui tu tem que concatenar filho

            strcat(indexs_conj_MOTOR_FULL, indexs_conj_MOTOR); //incrementa ao conteúdo antigo de indexs_conj_MOTOR_FULL o apêndice indexs_conj_GERADOR

            //IupMessagef("Aviso!", "%s", indexs_conj_MOTOR_FULL);

            matrix_struct[i][i].motor_indices.id_k_Motor = 0; //DEVE INICIALIZAR AS VARIÁVEIS PQ HÁ VAZAMENTO
            matrix_struct[i][i].motor_indices.id_x = 0;
            matrix_struct[i][i].motor_indices.id_y = 0;

        }


    }


/****************************************** GERANDO A STRING FULL DE CARACTERES DO GERADOR *******************************************************/


    strcat(indexs_conj_MOTOR_FULL, "VALUE=1, BGCOLOR=\"7 255 154\""); //verde prateado

    if(depurar_SEP==1){
    IupMessagef("Aviso!", "%s", "Favor carregar índices."); //PREENCHIMENTO FINAL DISPONÍVEL EM VARIÁVEL GLOBAL
    }

    /************** LISTA ATUALIZADA PARA USO ************/


    //free(indexs_conj_GERADOR); //Liberar memória, pois este vetor não é permanente



/************************ CONJUNTO DE ÍNDICES - FIM **************************************************************************/

    /************* LASTRO

    1) function_INDEX_Zbox_Gerabor
    2) list_tag


    **************/

}








/*****************************************(         \FRAMES \LISTAS \IN \FORM       )********************************************

***/





/*****************************************(       \FRAME \LISTA \GERADOR \IN \FORM  )********************************************

***/

static Ihandle* function_List_gerador(void){ //BOX Ihandle - Estrutura da lista de indexação do gerador



/****************************************************** BOTÃO DROP LIST **************************************/
  Ihandle *button;
  button = IupDropButton(NULL);
  IupSetStrAttribute(button, "TITLE", "Barras");


  /***** ATRIBUTOS DO BOTÃO ****/

  IupSetCallback(button, "FLAT_ACTION", (Icallback)function_message_sincrona);
  //IupAppend(frm_box2, button);
  IupSetAttribute(button, "DROPCHILD_HANDLE", (char*)CreateList_Gerador()); //ELE RECEBE A LISTA POW ... SOMENTE ESTA LINHA É CAPAZ DE FAZER O BOTÃO LISTA

/*************************************************************************************************************/

    /*** Criação do Frame contendo o drop_button_list e um Label instrutivo ***/
    Ihandle *drop_Lists_in_Box;

    drop_Lists_in_Box = IupFrame(IupHbox(
                          IupLabel("Selecione as barras dos geradores"), //Label do frame
                          button,
                          //button_Zbox,
                          NULL
                        ));

    //IupSetAttribute(drop_Lists_in_Box, "SHOWDRAGDROP", "Yes");


    IupSetAttributes(drop_Lists_in_Box, "TITLE=Index_GE");


    return drop_Lists_in_Box;
}










/*****************************************(       \FRAME \LISTA \TRAFO \IN \FORM  )********************************************

***/

static Ihandle* function_List_TR1(void)
{ //BOX Ihandle - Estrutura da lista de indexação do gerador



/****************************************************** BOTÃO DROP LIST DO TRAFO **************************************/
  Ihandle *button;
  button = IupDropButton(NULL);
  IupSetStrAttribute(button, "TITLE", "Barras");


  /***** ATRIBUTOS DO BOTÃO ****/

  IupSetCallback(button, "FLAT_ACTION", (Icallback)function_message_trafo);
  //IupAppend(frm_box2, button);
  IupSetAttribute(button, "DROPCHILD_HANDLE", (char*)CreateList_Trafo()); //ELE RECEBE A LISTA POW ... SOMENTE ESTA LINHA É CAPAZ DE FAZER O BOTÃO LISTA

/*************************************************************************************************************/


    /*** Criação do Frame contendo o drop_button_list e um Label instrutivo ***/
    Ihandle *drop_Lists_in_Box;

    drop_Lists_in_Box = IupFrame(IupHbox(
                          IupLabel("Selecione as barras dos transformadores"),
                          button,
                          //button_Zbox,
                          NULL
                        ));

    //IupSetAttribute(drop_Lists_in_Box, "SHOWDRAGDROP", "Yes");


    IupSetAttributes(drop_Lists_in_Box, "TITLE=Index_Trafo");


    return drop_Lists_in_Box;
}









/*****************************************(       \FRAME \LISTA \LT \IN \FORM  )********************************************

***/

static Ihandle* function_List_LT(void)
{ //BOX Ihandle - Estrutura da lista de indexação do gerador



/****************************************************** BOTÃO DROP LIST DA LT **************************************/
  Ihandle *button;
  button = IupDropButton(NULL);
  IupSetStrAttribute(button, "TITLE", "Barras"); //Verificar se essa tag impacta sobre os outros botões


  /***** ATRIBUTOS DO BOTÃO ****/

  IupSetCallback(button, "FLAT_ACTION", (Icallback)function_message_LT);
  //IupAppend(frm_box2, button);
  IupSetAttribute(button, "DROPCHILD_HANDLE", (char*)CreateList_LT()); //ELE RECEBE A LISTA POW ... SOMENTE ESTA LINHA É CAPAZ DE FAZER O BOTÃO LISTA

/*************************************************************************************************************/

    /*** Criação do Frame contendo o drop_button_list e um Label instrutivo ***/
    Ihandle *drop_Lists_in_Box;

    drop_Lists_in_Box = IupFrame(IupHbox(
                          IupLabel("Selecione as barras das linhas de transmissão"),
                          button,
                          //button_Zbox,
                          NULL
                        ));

    //IupSetAttribute(drop_Lists_in_Box, "SHOWDRAGDROP", "Yes"); //não identifiquei o que faz


    IupSetAttributes(drop_Lists_in_Box, "TITLE=Index_LT");


    return drop_Lists_in_Box;

}








/*****************************************(       \FRAME \LISTA \MOTOR \IN \FORM  )********************************************

***/

static Ihandle* function_List_motor(void)
{ //BOX Ihandle - Estrutura da lista de indexação do gerador



/****************************************************** BOTÃO DROP LIST DO MOTOR **************************************/
  Ihandle *button;
  button = IupDropButton(NULL);
  IupSetStrAttribute(button, "TITLE", "Barras");


  /***** ATRIBUTOS DO BOTÃO ****/

  IupSetCallback(button, "FLAT_ACTION", (Icallback)function_message_sincrona);
  //IupAppend(frm_box2, button);
  IupSetAttribute(button, "DROPCHILD_HANDLE", (char*)CreateList_Motor()); //ELE RECEBE A LISTA POW ... SOMENTE ESTA LINHA É CAPAZ DE FAZER O BOTÃO LISTA

/*************************************************************************************************************/


    /*** Criação do Frame contendo o drop_button_list e um Label instrutivo ***/
    Ihandle *drop_Lists_in_Box;

    drop_Lists_in_Box = IupFrame(IupHbox(
                          IupLabel("Selecione as barras dos motores"),
                          button,
                          //button_Zbox,
                          NULL
                        ));

    //IupSetAttribute(drop_Lists_in_Box, "SHOWDRAGDROP", "Yes");


    IupSetAttributes(drop_Lists_in_Box, "TITLE=Index_Motor");


    return drop_Lists_in_Box;
}










/************************************************ CRIAR UMA LISTA ESTÁTICA DE START PARA CADA MÁQUINA ***************************************/

/*****************************************(       \CRIAR \LISTAS \ESTATICAS \IN \FORM  )********************************************

***/






/*****************************************(       \LISTA \ESTATICA \GERADOR \IN \FORM  )********************************************

***/

static Ihandle* CreateList_Gerador(void) //Ele é disparado por um botão drop, parece estranho pq os botões que disparam funções via o Ihandle deles mesmos
{

  Ihandle *lista_FOR_tag = IupList(NULL);

  /****************** ETAPA 2 ***************/
    //IupSetAttributes(lista_FOR_tag, string_tag_FULL);         /**** <<<<<<<<<<<<<<<<<<<< APAGAR??? sim, nem existe mais a var string_tag_FULL****/

    //criar um for com mesmo atributo

  IupSetAttributes(lista_FOR_tag, "DROPDOWN=NO, 1=\"index_OFF\","
                   "VALUE=1, BGCOLOR=\"0 255 255\""); //azul anil - gerador
  //IupSetAttribute (frame, "TITLE", "List");

  char str[]="Hello \
              world. This is \
              a string";

              /*** \The \K&R \book ***/


  IupSetHandle ("list_tag_GE", lista_FOR_tag); //CRÍTICO


  IupSetAttribute(lista_FOR_tag, "VISIBLEITEMS", "20");
  //  IupSetAttribute(list, "VISIBLECOLUMNS", "7");
  IupSetAttribute(lista_FOR_tag, "VISIBLELINES", "4");
  //IupSetCallback(list, "ACTION", (Icallback)list_cb2);
  //IupSetCallback(list, "ACTION", (Icallback)list_cb); //chega a entrar na list, mas o Zbox não funciona

  /******************** ETAPA FINAL ********************/
  IupSetCallback (lista_FOR_tag, "ACTION", (Icallback) function_memory_gerador_id_k); //Neste caso cada item da lista virou um botão de disparo

  return lista_FOR_tag; //Return do botão do frame gerador
}






/*****************************************(       \LISTA \ESTATICA \TRAFO \IN \FORM  )********************************************

***/

static Ihandle* CreateList_Trafo(void) //Ele é disparado por um botão drop, parece estranho pq os botões que disparam funções via o Ihandle deles mesmos
{

  Ihandle *lista_FOR_tag = IupList(NULL);

  /****************** ETAPA 3 ***************/
  //IupSetAttributes(lista_FOR_tag, string_tag_FULL);         /**** <<<<<<<<<<<<<<<<<<<< APAGAR??? ****/

    //criar um for com mesmo atributo

  IupSetAttributes(lista_FOR_tag, "DROPDOWN=NO, 1=\"index_OFF\","
                   "VALUE=1, BGCOLOR=\"255 100 114\""); //TR - Lilás sóbrio
  //IupSetAttribute (frame, "TITLE", "List");


  IupSetHandle ("list_tag_TRAFO", lista_FOR_tag); //CRÍTICO, tag de rastreabilidade


  IupSetAttribute(lista_FOR_tag, "VISIBLEITEMS", "20");
  //  IupSetAttribute(list, "VISIBLECOLUMNS", "7");
  IupSetAttribute(lista_FOR_tag, "VISIBLELINES", "4");
  //IupSetCallback(list, "ACTION", (Icallback)list_cb2);
  IupSetCallback(lista_FOR_tag, "ACTION", (Icallback)function_memory_transformador1_id_k); //Aqui fica a rotina da lista, ela é concebida em sua raiz numerada de 1 a n, então ao
                                                                                           //acionar a lista clicando em qualquer item é disparado uma função com a informação do item clicado

  //chega a entrar na list, mas o Zbox não funciona <<< OLD

  return lista_FOR_tag; //Return do botão do frame transformador
}







/*****************************************(       \LISTA \ESTATICA \LT \IN \FORM  )********************************************

***/

static Ihandle* CreateList_LT(void) //Ele é disparado por um botão drop, parece estranho pq os botões que disparam funções via o Ihandle deles mesmos
{

  Ihandle *lista_FOR_tag = IupList(NULL);

  /****************** ETAPA 3 ***************/
  //IupSetAttributes(lista_FOR_tag, string_tag_FULL);         /**** <<<<<<<<<<<<<<<<<<<< APAGAR??? ****/

    //criar um for com mesmo atributo

  IupSetAttributes(lista_FOR_tag, "DROPDOWN=NO, 1=\"index_OFF\","
                   "VALUE=1, BGCOLOR=\"27 181 255\""); //LT - azul prata
  //IupSetAttribute (frame, "TITLE", "List");


  IupSetHandle ("list_tag_LT", lista_FOR_tag); //CRÍTICO


  IupSetAttribute(lista_FOR_tag, "VISIBLEITEMS", "20");
  //  IupSetAttribute(list, "VISIBLECOLUMNS", "7");
  IupSetAttribute(lista_FOR_tag, "VISIBLELINES", "4");
  //IupSetCallback(list, "ACTION", (Icallback)list_cb2);
  IupSetCallback(lista_FOR_tag, "ACTION", (Icallback)function_memory_LT_id_k); //chega a entrar na list, mas o Zbox não funciona

  return lista_FOR_tag; //Return do botão do frame LT
}









/*****************************************(       \LISTA \ESTATICA \MOTOR \IN \FORM  )********************************************

***/

static Ihandle* CreateList_Motor(void) //Ele é disparado por um botão drop, parece estranho pq os botões que disparam funções via o Ihandle deles mesmos
{

  Ihandle *lista_FOR_tag = IupList(NULL);

  /****************** ETAPA 3 ***************/
  //IupSetAttributes(lista_FOR_tag, string_tag_FULL);         /**** <<<<<<<<<<<<<<<<<<<< APAGAR??? ****/

    //criar um for com mesmo atributo

  IupSetAttributes(lista_FOR_tag, "DROPDOWN=NO, 1=\"index_OFF\","
                   "VALUE=1, BGCOLOR=\"7 255 154\""); //Motor - verde prateado

                   //"255 0 255");
  //IupSetAttribute (frame, "TITLE", "List");


  IupSetHandle ("list_tag_MOTOR", lista_FOR_tag); //CRÍTICO


  IupSetAttribute(lista_FOR_tag, "VISIBLEITEMS", "20");
  //  IupSetAttribute(list, "VISIBLECOLUMNS", "7");
  IupSetAttribute(lista_FOR_tag, "VISIBLELINES", "4");
  //IupSetCallback(list, "ACTION", (Icallback)list_cb2);
  //IupSetCallback(list, "ACTION", (Icallback)list_cb); //chega a entrar na list, mas o Zbox não funciona

  /******************** ETAPA FINAL ********************/
  IupSetCallback (lista_FOR_tag, "ACTION", (Icallback)function_memory_motor_id_k);
  //IupSetCallback (lista_FOR_tag, "ACTION", (Icallback) function_memory_motor_id_k);




  return lista_FOR_tag; //Return do botão do frame motor
}







/********************************************** FORMULÁRIO INPUT DE DADOS - INÍCIO ********************************/

/*****************************************(     \FORMULARIO \FORM \SHOT \C )********************************************

***/





static Ihandle* createForm(void) //o tipo e argumento é bem específico aqui
{
    //Crie de forma generalizada, visando a inserção de várias barras


      Ihandle *box, *label_sistema, *bt; /***APESAR DA FUNÇÃO SER DO TIPO VOID, O RETURN DEVE SER DO TIPO IHANDLE ***/
      Ihandle *label_txt, *BoxValue_txt;   /***Com progresso salve automaticamente, e no final do preenchimento deixe um button save***/
      Ihandle *btn_load_full;


      Ihandle *label_matrix_Zpu;
      Ihandle *bt_matrix_Zpu_zero, *bt_matrix_Zpu_neg, *bt_matrix_Zpu_pos;


      /**FORMULÁRIO**/



          /**********************************************************************************************/

          Ihandle *Field_load_matrix_Zpu;

          label_matrix_Zpu = IupLabel("Visualizar matrizes em pu");

          bt_matrix_Zpu_zero = IupButton("SEQUÊNCIA ZERO", "btn_matrix_Zpu_zero_tag");
          IupSetAttributes(bt_matrix_Zpu_zero, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER"); /*** JÁ ESTÁ EXPANSÍVEL O BOTÃO ***/
          //IupSetCallback(bt_matrix_Zpu_zero,"ACTION", (Icallback)button_cb);
          IupSetAttributes(bt_matrix_Zpu_zero,"FONTSTYLE = Bold, FONTSIZE = \"7.7\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          bt_matrix_Zpu_neg = IupButton("SEQUÊNCIA NEGATIVA", "btn_matrix_Zpu_neg_tag");
          IupSetAttributes(bt_matrix_Zpu_neg, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER");
          //IupSetCallback(bt_matrix_Zpu_neg,"ACTION", button_cb);
          IupSetAttributes(bt_matrix_Zpu_neg,"FONTSTYLE = Bold, FONTSIZE = \"7.7\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          bt_matrix_Zpu_pos = IupButton("SEQUÊNCIA POSITIVA", "btn_matrix_Zpu_pos_tag");
          IupSetAttributes(bt_matrix_Zpu_pos, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER");
          //IupSetCallback(bt_matrix_Zpu_pos,"ACTION", button_cb);
          IupSetAttributes(bt_matrix_Zpu_pos,"FONTSTYLE = Bold, FONTSIZE = \"7.7\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");
          IupSetAttribute(div_01, "STYLE", "LINE");
          IupSetAttribute(div_01, "COLOR", "255 0 0"); //Divisória vermelha
          IupSetAttribute(div_01, "NAME", "divisoria_tag_red"); //PRIMEIRA VEZ QUE CRIA UM IHANDLE É ASSIM QUE ATRIBUI A TAG



          Field_load_matrix_Zpu = IupVbox(label_matrix_Zpu, div_01, bt_matrix_Zpu_zero, bt_matrix_Zpu_neg, bt_matrix_Zpu_pos, NULL);


          IupSetCallback(bt_matrix_Zpu_zero,"ACTION", (Icallback)button_Seq_Zero_in_Form); //CUIDADO, ESTES BOTÕES SÃO DO FORMS
          IupSetCallback(bt_matrix_Zpu_neg,"ACTION", (Icallback)button_Seq_Negativa_in_Form);
          IupSetCallback(bt_matrix_Zpu_pos,"ACTION", (Icallback)button_Seq_Positiva_in_Form);





          /**********************************************************************************************/
          Ihandle *Field_load_txt, *Field_BoxText;

          label_txt = IupLabel("Insira um título de identificação para o arquivo .txt");
          //IupSetAttribute(label_x_neutro, "TITLE", "Reatância de Peterson (Neutro - Zn)");

          //Veja como aumentar essa BoxValue
          BoxValue_txt = IupText(NULL); //acho que é NULL por padrão, que nem o canvas ...confirmando que IupText é BoxValue
          //veja o frame colorido lá tem um texto que fica na caixa já digitado
          //não é esse caso, aqui basta digitar! (não é preciso a princípio de mecanismos para digitação)
          IupSetAttributes(BoxValue_txt, "SIZE=5x5, EXPAND=YES");//, ALIGNMENT=ACENTER");

          bt = IupButton("Gerar .txt", "btn_gerar_txt_tag"); //FUNCIONOU, DESVINCULEI O FORMULÁRIO DA CRIAÇÃO DA MDI CLIENT SOBREPOSTA
          IupSetAttributes(bt, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER");
          //IupSetCallback(bt,"ACTION", (Icallback)button_cb); //button_cb, função monitorável pelo prompt, deletado

          /*** CARREGAR TODOS OS VALORES COLETADOS ***/
          btn_load_full = IupButton("Gravar", "btn_load_full_tag");
          IupSetCallback(btn_load_full,"ACTION", (Icallback)button_load_full_memory);

          /************************************ INÍCIO FRAME BOTÃO CARREGAR FORMULÁRIO ********************************************/
         Ihandle *frame_btn_load_full;
         Ihandle *label_load_full;

         //Botão 1 está dentro deste frame 1

         label_load_full = IupLabel("Carregar Formulário");

         frame_btn_load_full = IupFlatFrame
              (
                IupVbox
                (
                 //label_load_full,//IupSetAttributes(label_load_full, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER"),
                 IupSetAttributes(label_load_full, "SIZE=5x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                 //btn_load_full,//IupSetAttributes(btn_load_full, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER"), //box_mdi = btn_1
                 //
                 IupSetAttributes(btn_load_full, "SIZE=5x30, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                 //lbl,
                  NULL
                )
              );
          //IupSetAttribute( frame_btn_load_full, "MARGIN", "5x5");

          //IupSetAttributes(frame_btn_load_full, "SIZE=20x20, EXPAND=YES, ALIGNMENT=ACENTER");

          IupSetAttributes ( label_load_full,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\" ");
          //IupSetAttribute( lbl, "MARGIN", "100x");

          IupSetHandle("frame_btn_load_full_tag", frame_btn_load_full);


          IupSetAttribute(frame_btn_load_full, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_1, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_1, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_btn_load_full, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_btn_load_full, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_btn_load_full, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_btn_load_full, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_btn_load_full, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_btn_load_full, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_btn_load_full, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_btn_load_full, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_btn_load_full, "FRAMESPACE", "15"); //área frame bottom - ÁREA

    /************************************ FIM FRAME BOTÃO CARREGAR FORMULÁRIO ********************************************/




    /************************************ INÍCIO BOTÃO DEFINIR BASE ********************************************/
         Ihandle *frame_btn_definir_base;
         Ihandle *label_definir_base;
         Ihandle *btn_definir_base;

         btn_definir_base = IupButton("Base do SEP", "btn_definir_base_tag");
         //IupSetCallback(btn_definir_base, "ACTION", (Icallback)btn_1_call); //Este call back é imediato
         //IupSetAttribute(btn_definir_base, "EXPAND", "YES"); //já está sendo expandido dentro do frame
         //IupSetAttribute(btn_definir_base, "ACTIVE", "NO");
         //IupSetHandle("btn_definir_base_tag", btn_definir_base);
         IupSetFunction("btn_definir_base_tag", (Icallback)button_Base_SEP); //A primeira maneira tbm é válida
         //IupSetFunction("btn_definir_base_tag", (Icallback)mdi_new); //A primeira maneira tbm é válida
         //IupSetCallback(btn_definir_base, "ACTION", (Icallback)button_Base_SEP);

      /************************************ FIM BOTÃO DEFINIR BASE ********************************************/




      /************************************ INÍCIO FRAME DO BOTÃO DEFINIR BASE ********************************************/

         label_definir_base = IupLabel("Definir Base");

         frame_btn_definir_base = IupFlatFrame
              (
                IupVbox
                (
                 //IupSetAttributes(label_definir_base, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER"),
                 //IupSetAttributes(btn_definir_base, "SIZE=5x5, EXPAND=YES, ALIGNMENT=ACENTER"), //box_mdi = btn_1
                 //
                 IupSetAttributes(label_definir_base, "SIZE=5x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                 IupSetAttributes(btn_definir_base, "SIZE=5x30, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                  NULL
                )
              );

          IupSetAttributes ( label_definir_base,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\" ");
          //IupSetAttribute( lbl, "MARGIN", "100x");

          IupSetHandle("frame_btn_load_full_tag", frame_btn_definir_base);


          IupSetAttribute(frame_btn_definir_base, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_1, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_1, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_btn_definir_base, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_btn_definir_base, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_btn_definir_base, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_btn_definir_base, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_btn_definir_base, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_btn_definir_base, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_btn_definir_base, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_btn_definir_base, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          //IupSetAttribute(frame_btn_definir_base, "FRAMESPACE", "20"); //área frame bottom - ÁREA <<<< OLD
          IupSetAttribute(frame_btn_definir_base, "FRAMESPACE", "15"); //área frame bottom - ÁREA

    /************************************ FIM FRAME DO BOTÃO CARREGAR FORMULÁRIO ********************************************/



/************************ CONJUNTO DE ÍNDICES - INÍCIO **************************************************************************/

    Ihandle *label_size_bars, *button_Size_bars;

    //list_gerador = IupList(NULL);
    //Não pode ser conteúdo numérico para listas, mas tem como contornar...mas tenha em mente é char
    //Mais elemente ainda filho! Pega o tamanho da ordem do sistema = até 15 barras, e daí tu gera automaticamente o vetor de índices

    label_size_bars = IupLabel("Insira o número de barras do SEP: ");
    //IupSetAttribute(label_x_neutro, "TITLE", "Reatância de Peterson (Neutro - Zn)");


/********************************************* NÚMERO DE BARRAS E CÁLCULO DE ÍNDICES - INÍCIO ********************************************************/





    button_Size_bars = IupButton("Definir", "button_Size_bars_tag"); //FUNCIONOU, DESVINCULEI O FORMULÁRIO DA CRIAÇÃO DA MDI CLIENT SOBREPOSTA
        IupSetAttributes(button_Size_bars, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER");
        IupSetCallback(button_Size_bars,"ACTION", (Icallback)function_size_SEP_bars); //BOTÃO DE DEFINIÇÃO DE BARRAS E CÁLCULO DE INDEXS GERADOR




/********************************************* NÚMERO DE BARRAS E CÁLCULO DE ÍNDICES - FIM ********************************************************/

    //button_Size_bars = IupButton(NULL, NULL); // isso pode ser útil demais
    //Field_NUM_bars_SEP = IupVbox(label_size_bars, IupHbox(BoxValue_size_SEP_bars, NULL), NULL);

    Ihandle *BoxValue_size_SEP_bars = IupText(NULL); //doideira, começa com um IupText
    IupSetAttributes(BoxValue_size_SEP_bars, "SIZE=10x10, EXPAND=YES");//, ALIGNMENT=ACENTER");
    IupSetAttribute(BoxValue_size_SEP_bars, "NAME", "BoxValue_size_SEP_bars_tag"); //tag ao texto
    IupSetAttribute(BoxValue_size_SEP_bars, "READONLY", "NO"); //estranho, não faz sentido a caixa de valor dar origem aqui...agora faz!
    IupSetAttribute(BoxValue_size_SEP_bars, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
    IupSetfAttribute(BoxValue_size_SEP_bars, "VALUE", "%d", 2); //SHOW CONSEGUI, lembre-se do erro acima!


 /****************************************************** LANTERNA CARREGAMENTO SIZE BARS **********************/

        Ihandle *frame_lanterna = IupFrame(IupVbox(IupLabel(">"), NULL));
        IupSetHandle("frame_lanterna_tag", frame_lanterna);


        IupSetAttributes(frame_lanterna, "SIZE=8x8, EXPAND=YES, ALIGNMENT=ACENTER");

        //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
        IupSetAttribute(frame_lanterna, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          //IupSetAttribute(frame_lanterna, "FRAMECOLOR", "255 255 255"); //bordas frame
          //IupSetAttribute(frame_lanterna, "TITLELINECOLOR", "255 255 0");//divisória line frame

          //IupSetAttribute(frame_lanterna, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          //IupSetAttribute(frame_lanterna, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_lanterna, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_lanterna, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_lanterna, "FRAMESPACE", "8"); //área frame bottom - ÁREA


 /****************************************************** BOTÃO DROP LIST **************************************/
  Ihandle *button_Zbox;
  button_Zbox = IupButton(NULL, NULL);
  IupSetStrAttribute(button_Zbox, "TITLE", "Carregar índices XY");
  IupSetCallback(button_Zbox, "ACTION", (Icallback)function_INDEX_Zbox_Gerador); //TAVA MANDANDO O BOTAO ERRADO, CERTO É ESTE: button_Zbox
                                                                                //ETAPA 2: o botão dispara a reinicialização da lista gerador
                                                                                //DEU CERTO - lista atualizada

                                                                                //O Icallback não recebe return da function_INDEX_Zbox_Gerador, mas da
                                                                                //function_INDEX_Zbox_Motor, sistema está em cascata
                                                                                //Em camada seria o mesmo que fazer com Calc_X e String_FULL
  IupSetAttributes(button_Zbox, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER");


  /**************STAND BY*******************/












/*************************************************************************************************************/




    //Para coincidir na variável global também ficou 4 --- int valor_size_SEP_bars = 4;

      Ihandle *Field_NUM_bars_SEP;

      Field_NUM_bars_SEP = IupVbox(label_size_bars, IupHbox(BoxValue_size_SEP_bars, button_Size_bars,frame_lanterna, button_Zbox, NULL), NULL);


      /**** DEIXE A FUNÇÃO gerador() se encarregar de exibir a List INDEXs do gerador ***/


















    /************************************** INÍCIO MÁQUINAS FORM ********************************************************/

          Field_BoxText = IupHbox(BoxValue_txt, bt, NULL);

          //STAND BY
          //Field_load_txt = IupVbox(label_txt, Field_BoxText, frame_btn_definir_base, frame_btn_load_full, NULL);

          Field_load_txt = IupVbox(frame_btn_definir_base, frame_btn_load_full, NULL); //<<<< #OLD2

          //Field_load_txt = IupVbox(frame_btn_definir_base, NULL);



          /**********************************************************************************************/




      Ihandle *barra_1_gerador, *barra_1_transformador, *barra_2_Linha_Transmissao, *barra_3_transformador2, *barra_4_motor;
      Ihandle *maquinas_sincronas, *maquinas_nao_sincronas, *maquinas_load_base_e_load_full, *maquinas_barra_1;
      Ihandle *maquinas_barra_2e3, *maquinas, *maquinas_barra_4_Fields;

      barra_1_gerador = gerador_Form_Frame();
      //barra_1_gerador2 = gerador();
      barra_1_transformador = transformador1_Form_Frame(); //Você aciona uma função com retorno Ihandle, assim é recebido um Vbox ou Hbox para construir o Form

      barra_2_Linha_Transmissao = linha_LT_Form_Frame();

      //barra_3_transformador2 = transformador2(); <<<< #OLD2

      //barra_3_transformador2 = frame_btn_load_full; //somente transferindo Ihandles


      barra_4_motor = motor_Form_Frame();

      maquinas_sincronas = IupVbox(barra_1_gerador, barra_4_motor, NULL);
      maquinas_nao_sincronas = IupVbox(barra_2_Linha_Transmissao, barra_1_transformador, NULL);

      maquinas_load_base_e_load_full = IupVbox(Field_load_txt, Field_load_matrix_Zpu, NULL);

      maquinas_barra_1 = IupHbox(maquinas_nao_sincronas, maquinas_sincronas, maquinas_load_base_e_load_full, NULL);
      IupSetAttribute(maquinas_barra_1,"MARGIN","3x3");
      //maquinas_barra_2e3 = IupVbox( NULL); /*** COLOQUE OS BOTÕES DE THEVENIN AQUI ***/
      //maquinas_barra_4_Fields = IupHbox(, barra_3_transformador2, , NULL);

      //maquinas = IupHbox(maquinas_barra_1, IupVbox(maquinas_barra_2e3, maquinas_barra_4_Fields, NULL), NULL);
      maquinas = maquinas_barra_1;






/******************************************* FORMULÁRIO START BUTTON HOME - INÍCIO ********************************/



/************************ FIM FRAME GERADOR - BARRA 1 - FORMULÁRIO **************************************************************************/


       label_sistema = IupLabel("Sistema unifilar de até N barras"); /****************************** TOPO DO FORMULÁRIO **************/
        //  IupSetAttribute(label, "RASTERSIZE", "150x70");
        //  IupSetAttribute(label, "ALIGNMENT", "ACENTER:ACENTER");
        //    IupSetAttribute(label, "TEXTALIGNMENT", "ACENTER");
          IupSetAttribute(label_sistema, "FONT", "Helvetica, 14");
        //  IupSetAttribute(label, "FONT", "Helvetica, Underline 14");
        //  IupSetAttribute(label, "FONTSIZE", "14");
        //  IupSetAttribute(label, "FONTSTYLE", "Italic");
          IupSetAttribute(label_sistema, "FONTSTYLE", "Bold");
          IupSetAttribute(label_sistema, "BGCOLOR", "255 255 0");
          IupSetAttribute(label_sistema, "FGCOLOR", "0 0 255");


      Ihandle *_vbox_maquinas;

      _vbox_maquinas = IupVbox(label_sistema, Field_NUM_bars_SEP, maquinas, NULL);


      //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
      //box = IupVbox(IupSetAttributes( IupScrollBox(_vbox_maquinas), "RASTERSIZE=200x300" ), NULL);
      box = IupVbox(IupSetAttributes( IupScrollBox(_vbox_maquinas), "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" ), NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse
      IupSetAttribute(box,"MARGIN","5x5"); //SE NÃO DEIXAR ISSO FICA UM LIXO O FORMULA´RIO

      //NÃO FICOU PERFEITO, MAS MITIGA AS QUEIXAS A NAVEGABILIDADE DO FORMULÁRIO...É PRECISO MAPEAR A JANELA AO REDIMENSIONAR


      //Exatamente isto, como comentado no start button abaixo, tu precisa criar tudo que vai no form e inserir na box (janela)
 //     box = IupVbox(label_sistema, maquinas, NULL);//barra_1_gerador2, NULL);
 //     IupSetAttribute(box,"MARGIN","5x5");



      return box; //É enviado a arquitetura de uma Vbox para uma dialog em definitivo
}














/******************************************* FORMULÁRIO INPUT DE DADOS - FIM ********************************/

                /**** O FORMULÁRIO INICIA-SE COM DISPARO DO BOTÃO 1 ****/
                /*** Passo 1: disparo do botão 1 da janela principal (curto fase-terra), dando início a criação da janela do formulário ***/
                /*** Passo 2: disparo da criação de um formulário do tipo IupVbox: gerador, transformador, LT ***/
                /*** Passo 3: o return da função createForm retorna a IupVbox do tipo Ihandle, então é carregado numa variável Ihandle que por sua vez é jogada na janela dialog ***/



/*****************************************(     \BUTTON \HOME \FORM \SHOT \C )********************************************

***/



static int btn_HOME_call(Ihandle *btn)
{
  static int id = 0; //a princípio posso por fora da função e vincular os índices 0 a 3 ao 4 curtos

  Ihandle *box, *txt, *dlg, *bt;

  //note que o dlg precisa ser indexado para que vc saiba o que afinal
  //vai encerrar, pq cada vez que entra na função é um dlg novo

  if(id == 0){

      //static int status_btn_home; //Variável global
      status_btn_home++;
      /**FORMULÁRIO
          txt = IupText(NULL);

          bt = IupButton("Test", NULL);
          IupSetCallback(bt,"ACTION", button_cb);

      box = IupVbox(IupHbox(bt, NULL), txt, NULL);
      IupSetAttribute(box,"MARGIN","5x5");
      **/
      box = createForm();

      //Me liguei, no caso preciso usar o formulário criado para inserir botões, antes de jogar para IupDialog (finalmentes)

      dlg = IupDialog(box); //captura um Vbox (FORMULÁRIO)
      IupSetfAttribute(dlg,"TITLE","Formulário de dados - curto-circuito");//(%d), (aspas) id);

      //pendência_01 o btn_home não permite reabrir o formulário, em caso de acidente do usuário não ter preenchido.
      id++; /*** É um marcador de contagem e referencial, é possível abrir vários formulários (se desejado), ao minimizar o formulário ele fica na tela principal do software e não do windows - SE MAXIMIZAR, SENÃO FICA NO CANTO INFERIOR ESQUERDO DO WINDOWS ***/

      //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                               //SEQUER PRECISA DA CRIAÇÃO DO CANVAS

      IupSetHandle("mdi_tag_FORM", dlg); //tag da janela
      IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo o Formulário à janela principal
      //IupSetAttribute(dlg,"PARENTDIALOG","mdi_Form"); //atribuindo a dlg à janela do Formulário via a tag desta

      IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
      IupSetAttribute(dlg,"RASTERSIZE","600x600");
    //  IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");


      IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
      IupSetAttribute(dlg,"MDIFRAME","YES"); //GERA janelas filhas


      IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
      IupSetAttribute(dlg, "DEFAULTESC", "quit");



      //EXATAMENTE ISSO! SE TU NÃO TIVER ISSO O SCROLL BAR NÃO É MAPEADO NA ABERTURA DO FORM CREATE
      IupMap(dlg); //INSERIDO DIA 04/mai ACREDITO QUE FALTAVA ISSO PARA MAPEAR O FORM ...COLOQUE NAS LIGAÇÕES DOS TRAFOS



      IupShow(dlg);

      IupSetAttribute(dlg,"RASTERSIZE",NULL);
  }

  else
    {
        IupMessage("Aviso!", "Formulário já foi criado ou está minimizado!");
        //IupSetCallback(dlg, "CLOSE_CB", (Icallback)close_cb2); //mdi_closeall
        //EM CONSTRUÇÃO: use um dlg indexado e então será possível fechar o formulário
        //pelo que li, ao fechar o formulário ele também é destruído.
        //Dois gargalos o mdi_closeall não funciona e não reseta o formulário
    }
  //O MDI Close não destroy a janela em buffer, apenas fecha a existente
  //contudo isso só funcionou no iuptest.exe da versão 3.30 do iup

  return IUP_DEFAULT;
}






/******************************************* FORMULÁRIO START BUTTON HOME - FIM ********************************/




/*****************************************(     \CALCULADORA \CURRENTS \SHOT \C )********************************************

***/

/********************************* DADOS DE CÁLCULO DE CORRENTES DE CURTO-CIRCUITO MONOFÁSICO ***********************/
//function_Curto_Circuito_Monofasico
static int function_Curto_Circuito_Correntes(Ihandle *self){

    struct dados_falta coleta;

    ///analisar_barra_de_falta //memória não gravou
    //int  i = coleta.Barra_V_Falta;
    //float tension_Fault = coleta.V_Falta;
    //float phasor_tension_Fault = coleta.phasor_V_Falta;

    /*****************************************************************************************/
    Ihandle *MemoryBoxValue_Barra_V_Falta;
    MemoryBoxValue_Barra_V_Falta = IupGetDialogChild(self, "BoxValue_Barra_de_Falta_tag");
    int valor_Barra_V_Falta = IupGetInt(MemoryBoxValue_Barra_V_Falta, "VALUE");

    int  i = valor_Barra_V_Falta;
    /*****************************************************************************************/

    Ihandle* Module = IupGetDialogChild(self, "BoxValue_V_Falta_tag"); //ATIVANDO O BOX VALUE IupText
    float valorModule = IupGetFloat(Module, "VALUE");//...outro jeito é da coleta


    Ihandle* Phasor = IupGetDialogChild(self, "BoxValue_phasor_V_Falta_tag"); //ATIVANDO O BOX VALUE IupText
    float valorPhasor = IupGetFloat(Phasor, "VALUE");//...outro jeito é da coleta

    //complex<double>
    //double complex
    complex<double> Tension_Fault_Complex_fault;

    float valorPhasor_radians = to_radians(valorPhasor);

    float valorModule_x = valorModule*cos(valorPhasor_radians); //Aqui ocorre a conversão de valorModule e valorPhasor  para retangular
    float valorModule_y = valorModule*sin(valorPhasor_radians);

    Tension_Fault_Complex_fault = valorModule_x + valorModule_y*I;

    printf("O valor do modulo eh %.lf\n", valorModule);
    printf("O valor do x eh %.lf\n", valorModule_x);
    printf("O valor do y eh %.lf\n", valorModule_y);

    IupMessagef("Aviso!","O módulo da tensão de falta na barra %d é %.5f", i, abs(Tension_Fault_Complex_fault));
    IupMessagef("Aviso!","O fasor da tensão de falta na barra %d é %.5f", i, to_degree(arg(Tension_Fault_Complex_fault)));

    /*****************************************************************************************/

    float Znn_1 = matrix_thevenin_positiva_pu[i][i];
    float Znn_2 = matrix_thevenin_negativa_pu[i][i];
    float Znn_0 = matrix_thevenin_zero_pu[i][i];
    /*****************************************************************************************/
    complex<double> Complex_Znn_1, Complex_Znn_2, Complex_Znn_0;

    Complex_Znn_1 = Znn_1*I;
    Complex_Znn_2 = Znn_2*I;
    Complex_Znn_0 = Znn_0*I;

    IupMessagef("Aviso!","A impedância equivalente de Thevenin capturada de Z%d%d_1 é j%.5f", i, i, abs(Complex_Znn_1));
    IupMessagef("Aviso!","A impedância equivalente de Thevenin capturada de Z%d%d_2 é j%.5f", i, i, abs(Complex_Znn_2));
    IupMessagef("Aviso!","A impedância equivalente de Thevenin capturada de Z%d%d_0 é j%.5f", i, i, abs(Complex_Znn_0));
    /*****************************************************************************************/
    //current_fault_phase_GND
    complex<double> Complex_Ia1, Complex_Ia2, Complex_Ia0;

    if(btn_n_call == 1){ //CURTO-CIRCUITO MONOFÁSICO
        //IupMessagef("Aviso!","Identificador de falta é btn_n_call = %d", btn_n_call);

        Complex_Ia1 = Tension_Fault_Complex_fault/(Complex_Znn_1+Complex_Znn_2+Complex_Znn_0);
        Complex_Ia2 = Complex_Ia1;
        Complex_Ia0 = Complex_Ia1;

        //IupMessagef("Aviso!","O módulo da corrente de falta na barra %d é %.5f", i, abs(Complex_Ia1));
        //IupMessagef("Aviso!","O fasor da corrente de falta na barra %d é %.5f", i, to_degree(arg(Complex_Ia1)));

    }

    if(btn_n_call == 2){ //CURTO-CIRCUITO BIFÁSICO
        IupMessagef("Aviso!","Identificador de falta é btn_n_call = %d", btn_n_call);

        Complex_Ia1 = Tension_Fault_Complex_fault/(Complex_Znn_1+Complex_Znn_2);
        Complex_Ia2 = -Complex_Ia1;
        Complex_Ia0 = 0;
    }

    if(btn_n_call == 3){ //CURTO-CIRCUITO BIFÁSICO-TERRA
        IupMessagef("Aviso!","Identificador de falta é btn_n_call = %d", btn_n_call);

        Complex_Ia1 = Tension_Fault_Complex_fault/(Complex_Znn_1+((Complex_Znn_2*Complex_Znn_0)/(Complex_Znn_2+Complex_Znn_0)));
        Complex_Ia2 = -Complex_Ia1*(Complex_Znn_0/(Complex_Znn_0+Complex_Znn_2));
        Complex_Ia0 = -Complex_Ia1*(Complex_Znn_2/(Complex_Znn_0+Complex_Znn_2));
    }
    if(btn_n_call == 4){ //CURTO-CIRCUITO TRIFÁSICO
        IupMessagef("Aviso!","Identificador de falta é btn_n_call = %d", btn_n_call);

        Complex_Ia1 = Tension_Fault_Complex_fault/Complex_Znn_1;
        Complex_Ia2 = 0;
        Complex_Ia0 = 0;
    }

    /************************************** NÃO VAI PRECISAR DISSO ... POR ENQUANTO**********************************/
    float MODULE_Complex_Ia1, MODULE_Complex_Ia2, MODULE_Complex_Ia0;
    float PHASOR_Complex_Ia1, PHASOR_Complex_Ia2, PHASOR_Complex_Ia0;

    MODULE_Complex_Ia1 = abs(Complex_Ia1);
    PHASOR_Complex_Ia1 = to_degree(arg(Complex_Ia1));

    MODULE_Complex_Ia2 = abs(Complex_Ia2);
    PHASOR_Complex_Ia2 = to_degree(arg(Complex_Ia2));

    MODULE_Complex_Ia0 = abs(Complex_Ia0);
    PHASOR_Complex_Ia0 = to_degree(arg(Complex_Ia0));


    matrix_current_seq_positiva_pu[i][i].a.module = MODULE_Complex_Ia1; //reconverter e capturar mais facilmente
    matrix_current_seq_positiva_pu[i][i].a.phasor = PHASOR_Complex_Ia1;

    matrix_current_seq_negativa_pu[i][i].a.module = MODULE_Complex_Ia2; //reconverter e capturar mais facilmente
    matrix_current_seq_negativa_pu[i][i].a.phasor = PHASOR_Complex_Ia2;

    matrix_current_seq_zero_pu[i][i].a.module = MODULE_Complex_Ia0; //reconverter e capturar mais facilmente
    matrix_current_seq_zero_pu[i][i].a.phasor = PHASOR_Complex_Ia0;
    /*********************************************************************************************************/
                       /***                     \SEQUENCIA \POSITIVA                      ***/

    //Complex_Ia1                       /*** Página 42 Kindermann 2018 ***/
    complex<double>  Complex_Ib1 = Complex_Ia1*T[1][1]; //ATENÇÃO
    complex<double>  Complex_Ic1 = Complex_Ia1*T[1][2];

    //T[1][1] = cpow(OPERADOR_A, 2);
    //T[1][2] = OPERADOR_A;
    double module_Operador_a = abs(T[1][2]);

    double angulo_Operador_a = arg(T[1][2]);
    angulo_Operador_a = to_degree(angulo_Operador_a);

    double module_Operador_quadratico = abs(T[1][1]);

    double angulo_Operador_quadratico = arg(T[1][1]);
    angulo_Operador_quadratico = to_degree(angulo_Operador_quadratico);


        //IupMessagef("Aviso!","O módulo do operador a_dot é %.lf", module_Operador_a);
        //IupMessagef("Aviso!","O fasor do operador a_dot é %.lf", angulo_Operador_a);

        //IupMessagef("Aviso!","O módulo do operador a_dot^2 é %.5f", abs(T[1][1]));
        //IupMessagef("Aviso!","O fasor do operador a_dot^2 é %.5f graus", to_degree(arg(T[1][1])));

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ia1 = IupGetDialogChild(self, "BoxValue_tag_Ia1"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ia1, "VALUE", "%.5lf", abs(Complex_Ia1));

    Ihandle* BoxValue_PHASOR_Ia1 = IupGetDialogChild(self, "BoxValue_tag_AngleIa1");
    IupSetStrf(BoxValue_PHASOR_Ia1, "VALUE", "%.lf", to_degree(arg(Complex_Ia1)));

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ib1 = IupGetDialogChild(self, "BoxValue_tag_Ib1"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ib1, "VALUE", "%.5lf", abs(Complex_Ib1));

    Ihandle* BoxValue_PHASOR_Ib1 = IupGetDialogChild(self, "BoxValue_tag_AngleIb1");
    IupSetStrf(BoxValue_PHASOR_Ib1, "VALUE", "%.lf", to_degree(arg(Complex_Ib1)));

    /*********************************************************************************************************/

    Ihandle* BoxValue_MODULE_Ic1 = IupGetDialogChild(self, "BoxValue_tag_Ic1"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ic1, "VALUE", "%.5lf", abs(Complex_Ic1));

    Ihandle* BoxValue_PHASOR_Ic1 = IupGetDialogChild(self, "BoxValue_tag_AngleIc1");
    IupSetStrf(BoxValue_PHASOR_Ic1, "VALUE", "%.lf", to_degree(arg(Complex_Ic1)));

    /*********************************************************************************************************/

                       /***                     \SEQUENCIA \NEGATIVA                      ***/

    //Complex_Ia2                       /*** Página 43 Kindermann 2018 ***/
    complex<double>  Complex_Ib2 = Complex_Ia2*T[1][2];
    complex<double>  Complex_Ic2 = Complex_Ia2*T[1][1]; //ATENÇÃO

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ia2 = IupGetDialogChild(self, "BoxValue_tag_Ia2"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ia2, "VALUE", "%.5lf", abs(Complex_Ia2));

    Ihandle* BoxValue_PHASOR_Ia2 = IupGetDialogChild(self, "BoxValue_tag_AngleIa2");
    IupSetStrf(BoxValue_PHASOR_Ia2, "VALUE", "%.lf", to_degree(arg(Complex_Ia2)));

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ib2 = IupGetDialogChild(self, "BoxValue_tag_Ib2"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ib2, "VALUE", "%.5lf", abs(Complex_Ib2));

    Ihandle* BoxValue_PHASOR_Ib2 = IupGetDialogChild(self, "BoxValue_tag_AngleIb2");
    IupSetStrf(BoxValue_PHASOR_Ib2, "VALUE", "%.lf", to_degree(arg(Complex_Ib2)));

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ic2 = IupGetDialogChild(self, "BoxValue_tag_Ic2"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ic2, "VALUE", "%.5lf", abs(Complex_Ic2));

    Ihandle* BoxValue_PHASOR_Ic2 = IupGetDialogChild(self, "BoxValue_tag_AngleIc2");
    IupSetStrf(BoxValue_PHASOR_Ic2, "VALUE", "%.lf", to_degree(arg(Complex_Ic2)));

    /*********************************************************************************************************/

                       /***                     \SEQUENCIA \ZERO                      ***/

    //Complex_Ia0                       /*** Página 44 Kindermann 2018 ***/
    complex<double> Complex_Ib0 = Complex_Ia0; //ATENÇÃO!!
    complex<double> Complex_Ic0 = Complex_Ia0; //ATENÇÃO!!


    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ia0 = IupGetDialogChild(self, "BoxValue_tag_Ia0"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ia0, "VALUE", "%.5lf", abs(Complex_Ia0));

    Ihandle* BoxValue_PHASOR_Ia0 = IupGetDialogChild(self, "BoxValue_tag_AngleIa0");
    IupSetStrf(BoxValue_PHASOR_Ia0, "VALUE", "%.lf", to_degree(arg(Complex_Ia0)));

    /*********************************************************************************************************/
    Ihandle* BoxValue_MODULE_Ib0 = IupGetDialogChild(self, "BoxValue_tag_Ib0"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ib0, "VALUE", "%.5lf", abs(Complex_Ib0));

    Ihandle* BoxValue_PHASOR_Ib0 = IupGetDialogChild(self, "BoxValue_tag_AngleIb0");
    IupSetStrf(BoxValue_PHASOR_Ib0, "VALUE", "%.lf", to_degree(arg(Complex_Ib0)));

    /*********************************************************************************************************/

    Ihandle* BoxValue_MODULE_Ic0 = IupGetDialogChild(self, "BoxValue_tag_Ic0"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ic0, "VALUE", "%.5lf", abs(Complex_Ic0));

    Ihandle* BoxValue_PHASOR_Ic0 = IupGetDialogChild(self, "BoxValue_tag_AngleIc0");
    IupSetStrf(BoxValue_PHASOR_Ic0, "VALUE", "%.lf", to_degree(arg(Complex_Ic0)));

    /*********************************************************************************************************/

    /******************************************* \CORRENTE \DE \BASE *****************************************/
    complex<double> Complex_Ibase;

    float Z_base = 0;
    float V_base = base_SEP_coleta[i].V_base;
    V_base = V_base*pow(10.0,3.0);              //Note input real
    float S_base = base_SEP_coleta[0].P_base;
    S_base = S_base*pow(10.0,6.0);              //Note input real

    //Z_base = pow(V_base, 2.0)/S_base;   //Note output real

        Complex_Ibase = S_base/(sqrt(3.0)*V_base) + 0*I;  //Note output real


    Ihandle* BoxValue_MODULE_Ibase = IupGetDialogChild(self, "BoxValue_tag_Ibase"); //Capturar o campo para trocar o valor ou inicializar
    IupSetStrf(BoxValue_MODULE_Ibase, "VALUE", "%.5lf", abs(Complex_Ibase));

    Ihandle* BoxValue_PHASOR_Ibase = IupGetDialogChild(self, "BoxValue_tag_AngleIbase");
    IupSetStrf(BoxValue_PHASOR_Ibase, "VALUE", "%.lf", to_degree(arg(Complex_Ibase)));


    /*********************************************************************************************************/

    /******************************************* \CORRENTES \REAIS *****************************************/
    complex<double> Complex_Ia_pu, Complex_Ib_pu, Complex_Ic_pu, Complex_Ia, Complex_Ib, Complex_Ic;

    Complex_Ia_pu = (Complex_Ia0*T[0][0])+(Complex_Ia1*T[0][1])+(Complex_Ia2*T[0][2]); //Como a matriz T está em retangular, opero a corrente de fase retangular com o índice da matriz T, obtendo a componente simétrica
    Complex_Ib_pu = (Complex_Ia0*T[1][0])+(Complex_Ia1*T[1][1])+(Complex_Ia2*T[1][2]);
    Complex_Ic_pu = (Complex_Ia0*T[2][0])+(Complex_Ia1*T[2][1])+(Complex_Ia2*T[2][2]);


    Complex_Ia = Complex_Ia_pu * Complex_Ibase;
    Complex_Ib = Complex_Ib_pu * Complex_Ibase;
    Complex_Ic = Complex_Ic_pu * Complex_Ibase;

    /******************************************************************************************/

    Ihandle* TxtIa = IupGetDialogChild(self, "BoxValue_tag_Ia");//TAG TEXTOPhaseA
    IupSetStrf(TxtIa, "VALUE", "%.5lf", abs(Complex_Ia));


    Ihandle* TxtPhasorIa = IupGetDialogChild(self, "BoxValue_tag_AngleIa");
    IupSetStrf(TxtPhasorIa, "VALUE", "%.lf", to_degree(arg(Complex_Ia)));

    /******************************************************************************************/

    Ihandle* TxtIb = IupGetDialogChild(self, "BoxValue_tag_Ib");
    IupSetStrf(TxtIb, "VALUE", "%.5lf", abs(Complex_Ib));


    Ihandle* TxtPhasorIb = IupGetDialogChild(self, "BoxValue_tag_AngleIb");
    IupSetStrf(TxtPhasorIb, "VALUE", "%.lf", to_degree(arg(Complex_Ib)));

    /******************************************************************************************/

    Ihandle* TxtIc = IupGetDialogChild(self, "BoxValue_tag_Ic");
    IupSetStrf(TxtIc, "VALUE", "%.5lf", abs(Complex_Ic));


    Ihandle* TxtPhasorIc = IupGetDialogChild(self, "BoxValue_tag_AngleIc");
    IupSetStrf(TxtPhasorIc, "VALUE", "%.lf", to_degree(arg(Complex_Ic)));

    /************************************************************************************************/

    status_memory_Fault_phase_GND_SEP++;

    return IUP_DEFAULT;

}






/*****************************************(     \BUTTON \CALCULAR \CURRENTS \MONOFASICO \SHOT \C )********************************************

***/
static int button_calc_curto_circuito_monofasico(Ihandle *ih){

    printf("criar uma função que processe os dados coletados de tensão de falta e barra de falta e possa ser acionada remotamente a qualquer instante");


    //condicional final: status_memory_load_full_finish>0
    if(status_memory_load_full_finish>-1){

      /*** Desbloqueia assim que botão full load for acionado ***/
      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues no form SHOT-C BTN_1 ***********************************************/

        function_Curto_Circuito_Correntes(ih);/// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        //condicional final: status_memory_Tension_Fault_SEP==1
        if (status_memory_Tension_Fault_SEP>=1){
             IupMessage("Aviso!", "CALCULADO AS CORRENTES DO CURTO-CIRCUITO MONOFÁSICO À TERRA NA BARRA DE FALTA DO SEP! \n"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");


    return IUP_DEFAULT;



}







/*****************************************(     \BUTTON \CALCULAR \CURRENTS \BIFASICO \SHOT \C )********************************************

***/

static int button_calc_curto_circuito_bifasico(Ihandle *ih){

    printf("criar uma função que processe os dados coletados de tensão de falta e barra de falta e possa ser acionada remotamente a qualquer instante");


    //condicional final: status_memory_load_full_finish>0
    if(status_memory_load_full_finish>-1){

      /*** Desbloqueia assim que botão full load for acionado ***/
      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues no form SHOT-C BTN_1 ***********************************************/

        function_Curto_Circuito_Correntes(ih);/// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        //condicional final: status_memory_Tension_Fault_SEP==1
        if (status_memory_Tension_Fault_SEP>=1){
             IupMessage("Aviso!", "CALCULADO AS CORRENTES DO CURTO-CIRCUITO BIFÁSICO NA BARRA DE FALTA DO SEP! \n"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");


    return IUP_DEFAULT;



}






/*****************************************(     \BUTTON \CALCULAR \CURRENTS \BIFASICO \TERRA \SHOT \C )********************************************

***/

static int button_calc_curto_circuito_bifasico_terra(Ihandle *ih){

    printf("criar uma função que processe os dados coletados de tensão de falta e barra de falta e possa ser acionada remotamente a qualquer instante");


    //condicional final: status_memory_load_full_finish>0
    if(status_memory_load_full_finish>-1){

      /*** Desbloqueia assim que botão full load for acionado ***/
      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues no form SHOT-C BTN_1 ***********************************************/

        function_Curto_Circuito_Correntes(ih); /// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        //condicional final: status_memory_Tension_Fault_SEP==1
        if (status_memory_Tension_Fault_SEP>=1){
             IupMessage("Aviso!", "CALCULADO AS CORRENTES DO CURTO-CIRCUITO BIFÁSICO À TERRA NA BARRA DE FALTA DO SEP! \n"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");


    return IUP_DEFAULT;



}






/*****************************************(     \BUTTON \CALCULAR \CURRENTS \TRIFASICO \SHOT \C )********************************************

***/


static int button_calc_curto_circuito_trifasico(Ihandle *ih){

    printf("criar uma função que processe os dados coletados de tensão de falta e barra de falta e possa ser acionada remotamente a qualquer instante");


    //condicional final: status_memory_load_full_finish>0
    if(status_memory_load_full_finish>-1){

      /*** Desbloqueia assim que botão full load for acionado ***/
      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues no form SHOT-C BTN_1 ***********************************************/

        function_Curto_Circuito_Correntes(ih); /// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        //condicional final: status_memory_Tension_Fault_SEP==1
        if (status_memory_Tension_Fault_SEP>=1){
             IupMessage("Aviso!", "CALCULADO AS CORRENTES DO CURTO-CIRCUITO TRIFÁSICO NA BARRA DE FALTA DO SEP! \n"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");


    return IUP_DEFAULT;



}





/*****************************************(     \BUTTON \MEMORY \TENSION \FAULT )********************************************

***/
//analisar esta função nem sequer usei
static int function_memory_Tension_Fault(Ihandle *ih){

            /*** ACESSO ÚNICO PELO BOTÃO definir tensão de falta ***/

                  Ihandle *MemoryBoxValue_V_Falta, *MemoryBoxValue_phasor_V_Falta, *MemoryBoxValue_Barra_V_Falta;
                  struct dados_falta coleta;


            /*** ativando o BoxValue de tensão de falta para coleta***/

            /*** cuidado, o IupGetDialogChild não pode ser NULL, o que justifica inclusive o motivo do encapasulamento em funções, use o ih do botão load full memory ***/

                MemoryBoxValue_V_Falta = IupGetDialogChild(ih, "BoxValue_V_Falta_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_V_Falta = IupGetFloat(MemoryBoxValue_V_Falta, "VALUE");

                coleta.V_Falta = valor_V_Falta;


            /*** ativando o BoxValue de potência de base para coleta***/

                MemoryBoxValue_phasor_V_Falta = IupGetDialogChild(ih, "BoxValue_phasor_V_Falta_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  float valor_phasor_V_Falta = IupGetFloat(MemoryBoxValue_phasor_V_Falta, "VALUE");

                coleta.phasor_V_Falta = valor_phasor_V_Falta;


            /*** ativando o BoxValue de região de base para coleta***/

                MemoryBoxValue_Barra_V_Falta = IupGetDialogChild(ih, "BoxValue_Barra_de_Falta_tag"); //a referência só entra aqui, abaixo pega o valor VALUE
                  //float valor_Regiao_base = IupGetFloat(MemoryBoxValue_Regiao_base, "VALUE");

                int valor_Barra_V_Falta = IupGetInt(MemoryBoxValue_Barra_V_Falta, "VALUE");

                coleta.Barra_V_Falta = valor_Barra_V_Falta;



               /*** \STAND \BY***/

               if(valor_Barra_V_Falta > size_SEP_bars_OLD || valor_Barra_V_Falta < 1)
               {
                   IupMessage("Aviso!", "Digite um valor válido!");
               }
               else{
                   status_memory_Tension_Fault_SEP++;
                   return IUP_DEFAULT;
               }





               return IUP_DEFAULT;

}




/*****************************************(     \BUTTON \DEFINIR \TENSION \FAULT )********************************************

***/
static int button_memory_Tension_Fault(Ihandle *ih) /*** BOTÃO DE DEFINIÇÃO DA TENSÃO DE FALTA NA JANELA BTN_1 ***/
{

    printf("criar uma função que armazene a tensão de falta e possa ser acionar remotamente a qualquer instante");


    //condicional final: status_memory_load_full_finish>0
    if(status_memory_load_full_finish>-1){

      /*** Desbloqueia assim que botão full load for acionado ***/
      /************************************************ DISPARAR FUNÇÃO CAPTURA BoxValues no form SHOT-C BTN_1 ***********************************************/

        function_memory_Tension_Fault(ih);

        //condicional final: status_memory_Tension_Fault_SEP==1
        if (status_memory_Tension_Fault_SEP>=1){
             IupMessage("Aviso!", "CARREGADO OS DADOS DA FALTA DO SEP! \nContinue!"); //Ihandle *info_Base_SEP1 = IupMessage(...)//o IupMessage não requer esse Ihandle, ele é do tipo void
        }
    }
    else
          IupMessage("Aviso!", "Prossiga!");


    return IUP_DEFAULT;

}





/*****************************************(     \VALUES \BOXES \CORRENTES \SEQ \POSITIVA )********************************************

***/
static Ihandle* Function_Box_Currents_Seq_Pos(void){

    Ihandle *hboxFildIa1;
    Ihandle *Label_CurrentIa1, *BoxValue_TextIa1, *Label_anglePhasorIa1, *BoxValue_TextAnglePhasorIa1;
    Ihandle *Label_SymbolsDegreeIa1_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIb1;
    Ihandle *Label_CurrentIb1, *BoxValue_TextIb1, *Label_anglePhasorIb1, *BoxValue_TextAnglePhasorIb1;
    Ihandle *Label_SymbolsDegreeIb1_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIc1;
    Ihandle *Label_CurrentIc1, *BoxValue_TextIc1, *Label_anglePhasorIc1, *BoxValue_TextAnglePhasorIc1;
    Ihandle *Label_SymbolsDegreeIc1_Amper; //individualize tudo para não sobrecarregar!



    Ihandle *Label_Corrente_Seq_Positiva = IupLabel("Correntes de sequência positiva:");

    /**********************************************************************************************************/

    Label_CurrentIa1  = IupMglLabel("\\overset I{\\bullet}a1 =");
    IupSetAttribute(Label_CurrentIa1, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIa1, "LABELFONTSIZE", "12");

        BoxValue_TextIa1 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIa1 , "NAME", "BoxValue_tag_Ia1");
        IupSetAttribute(BoxValue_TextIa1 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa1, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIa1, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIa1 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIa1, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIa1, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIa1 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIa1, "NAME", "BoxValue_tag_AngleIa1");
        IupSetAttribute(BoxValue_TextAnglePhasorIa1, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa1, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIa1, "ALIGNMENT", "ARIGHT");


    //Label_SymbolsDegreeIa1_Amper = IupLabel("° \t [pu]");//IupLabel(title1);
    //IupSetAttribute(Label_SymbolsDegreeIa1_Amper, "FONTSIZE", "14");
    //IupSetAttribute(Label_SymbolsDegreeIa1_Amper, "FONTSTYLE", "Bold");

    Label_SymbolsDegreeIa1_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIa1_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIa1_Amper, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Label_CurrentIb1  = IupMglLabel("\\overset I{\\bullet}b1 =");
    IupSetAttribute(Label_CurrentIb1, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIb1, "LABELFONTSIZE", "12");

        BoxValue_TextIb1 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIb1 , "NAME", "BoxValue_tag_Ib1");
        IupSetAttribute(BoxValue_TextIb1 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa1, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIb1, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIb1 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIb1, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIb1, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIb1 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIb1, "NAME", "BoxValue_tag_AngleIb1");
        IupSetAttribute(BoxValue_TextAnglePhasorIb1, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa1, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIb1, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIb1_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIb1_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIb1_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/
    Label_CurrentIc1  = IupMglLabel("\\overset I{\\bullet}c1 =");
    IupSetAttribute(Label_CurrentIc1, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIc1, "LABELFONTSIZE", "12");

        BoxValue_TextIc1 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIc1 , "NAME", "BoxValue_tag_Ic1");
        IupSetAttribute(BoxValue_TextIc1 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIc1, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIc1, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIc1 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIc1, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIc1, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIc1 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIc1, "NAME", "BoxValue_tag_AngleIc1");
        IupSetAttribute(BoxValue_TextAnglePhasorIc1, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIc1, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIc1, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIc1_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIc1_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIc1_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/

    hboxFildIa1 = IupHbox(
                   Label_CurrentIa1,

                        BoxValue_TextIa1,

                   Label_anglePhasorIa1,

                        BoxValue_TextAnglePhasorIa1,

                   Label_SymbolsDegreeIa1_Amper,

                   NULL);

    IupSetAttribute(hboxFildIa1, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIa1, "GAP", "0");
    /************************************************************************************************************/



    hboxFildIb1 = IupHbox(
                   Label_CurrentIb1,

                        BoxValue_TextIb1,

                   Label_anglePhasorIb1,

                        BoxValue_TextAnglePhasorIb1,

                   Label_SymbolsDegreeIb1_Amper,

                   NULL);

    IupSetAttribute(hboxFildIb1, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIb1, "GAP", "0");

    /**************************************************************************************************************/



    hboxFildIc1 = IupHbox(
                   Label_CurrentIc1,

                        BoxValue_TextIc1,

                   Label_anglePhasorIc1,

                        BoxValue_TextAnglePhasorIc1,

                   Label_SymbolsDegreeIc1_Amper,

                   NULL);

    IupSetAttribute(hboxFildIc1, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIc1, "GAP", "0");

    /**************************************************************************************************************/
    Ihandle *vboxFildIa;

    vboxFildIa = IupVbox(
                          Label_Corrente_Seq_Positiva,

                          hboxFildIa1,

                          hboxFildIb1,

                          hboxFildIc1,

                          NULL);

    return vboxFildIa;

}




/*****************************************(     \VALUES \BOXES \CORRENTES \SEQ \NEGATIVA )********************************************

***/
static Ihandle* Function_Box_Currents_Seq_Neg(void){

    Ihandle *hboxFildIa2;
    Ihandle *Label_CurrentIa2, *BoxValue_TextIa2, *Label_anglePhasorIa2, *BoxValue_TextAnglePhasorIa2;
    Ihandle *Label_SymbolsDegreeIa2_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIb2;
    Ihandle *Label_CurrentIb2, *BoxValue_TextIb2, *Label_anglePhasorIb2, *BoxValue_TextAnglePhasorIb2;
    Ihandle *Label_SymbolsDegreeIb2_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIc2;
    Ihandle *Label_CurrentIc2, *BoxValue_TextIc2, *Label_anglePhasorIc2, *BoxValue_TextAnglePhasorIc2;
    Ihandle *Label_SymbolsDegreeIc2_Amper; //individualize tudo para não sobrecarregar!



    Ihandle *Label_Corrente_Seq_Positiva = IupLabel("Correntes de sequência negativa:");

    /**********************************************************************************************************/
    Label_CurrentIa2  = IupMglLabel("\\overset I{\\bullet}a2 =");
    IupSetAttribute(Label_CurrentIa2, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIa2, "LABELFONTSIZE", "12");

        BoxValue_TextIa2 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIa2 , "NAME", "BoxValue_tag_Ia2");
        IupSetAttribute(BoxValue_TextIa2 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa2, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIa2, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIa2 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIa2, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIa2, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIa2 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIa2, "NAME", "BoxValue_tag_AngleIa2");
        IupSetAttribute(BoxValue_TextAnglePhasorIa2, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa2, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIa2, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIa2_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIa2_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIa2_Amper, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Label_CurrentIb2  = IupMglLabel("\\overset I{\\bullet}b2 =");
    IupSetAttribute(Label_CurrentIb2, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIb2, "LABELFONTSIZE", "12");

        BoxValue_TextIb2 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIb2 , "NAME", "BoxValue_tag_Ib2");
        IupSetAttribute(BoxValue_TextIb2 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIb2, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIb2, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIb2 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIb2, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIb2, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIb2 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIb2, "NAME", "BoxValue_tag_AngleIb2");
        IupSetAttribute(BoxValue_TextAnglePhasorIb2, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIb2, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIb2, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIb2_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIb2_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIb2_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/
    Label_CurrentIc2  = IupMglLabel("\\overset I{\\bullet}c2 =");
    IupSetAttribute(Label_CurrentIc2, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIc2, "LABELFONTSIZE", "12");

        BoxValue_TextIc2 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIc2 , "NAME", "BoxValue_tag_Ic2");
        IupSetAttribute(BoxValue_TextIc2 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIc2, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIc2, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIc2 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIc2, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIc2, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIc2 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIc2, "NAME", "BoxValue_tag_AngleIc2");
        IupSetAttribute(BoxValue_TextAnglePhasorIc2, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIc2, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIc2, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIc2_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIc2_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIc2_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/

    hboxFildIa2 = IupHbox(
                   Label_CurrentIa2,

                        BoxValue_TextIa2,

                   Label_anglePhasorIa2,

                        BoxValue_TextAnglePhasorIa2,

                   Label_SymbolsDegreeIa2_Amper,

                   NULL);

    IupSetAttribute(hboxFildIa2, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIa2, "GAP", "0");
    /************************************************************************************************************/



    hboxFildIb2 = IupHbox(
                   Label_CurrentIb2,

                        BoxValue_TextIb2,

                   Label_anglePhasorIb2,

                        BoxValue_TextAnglePhasorIb2,

                   Label_SymbolsDegreeIb2_Amper,

                   NULL);

    IupSetAttribute(hboxFildIb2, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIb2, "GAP", "0");

    /**************************************************************************************************************/



    hboxFildIc2 = IupHbox(
                   Label_CurrentIc2,

                        BoxValue_TextIc2,

                   Label_anglePhasorIc2,

                        BoxValue_TextAnglePhasorIc2,

                   Label_SymbolsDegreeIc2_Amper,

                   NULL);

    IupSetAttribute(hboxFildIc2, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIc2, "GAP", "0");

    /**************************************************************************************************************/
    Ihandle *vboxFildIa;

    vboxFildIa = IupVbox(
                          Label_Corrente_Seq_Positiva,

                          hboxFildIa2,

                          hboxFildIb2,

                          hboxFildIc2,

                          NULL);

    return vboxFildIa;

}




/*****************************************(     \VALUES \BOXES \CORRENTES \SEQ \ZERO )********************************************

***/
static Ihandle* Function_Box_Currents_Seq_Zero(void){

    Ihandle *hboxFildIa0;
    Ihandle *Label_CurrentIa0, *BoxValue_TextIa0, *Label_anglePhasorIa0, *BoxValue_TextAnglePhasorIa0;
    Ihandle *Label_SymbolsDegreeIa0_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIb0;
    Ihandle *Label_CurrentIb0, *BoxValue_TextIb0, *Label_anglePhasorIb0, *BoxValue_TextAnglePhasorIb0;
    Ihandle *Label_SymbolsDegreeIb0_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIc0;
    Ihandle *Label_CurrentIc0, *BoxValue_TextIc0, *Label_anglePhasorIc0, *BoxValue_TextAnglePhasorIc0;
    Ihandle *Label_SymbolsDegreeIc0_Amper; //individualize tudo para não sobrecarregar!



    Ihandle *Label_Corrente_Seq_Positiva = IupLabel("Correntes de sequência zero:");

    /**********************************************************************************************************/
    Label_CurrentIa0  = IupMglLabel("\\overset I{\\bullet}a0 =");
    IupSetAttribute(Label_CurrentIa0, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIa0, "LABELFONTSIZE", "12");

        BoxValue_TextIa0 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIa0 , "NAME", "BoxValue_tag_Ia0");
        IupSetAttribute(BoxValue_TextIa0 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa0, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIa0, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIa0 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIa0, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIa0, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIa0 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIa0, "NAME", "BoxValue_tag_AngleIa0");
        IupSetAttribute(BoxValue_TextAnglePhasorIa0, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa0, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIa0, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIa0_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIa0_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIa0_Amper, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Label_CurrentIb0  = IupMglLabel("\\overset I{\\bullet}b0 =");
    IupSetAttribute(Label_CurrentIb0, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIb0, "LABELFONTSIZE", "12");

        BoxValue_TextIb0 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIb0 , "NAME", "BoxValue_tag_Ib0");
        IupSetAttribute(BoxValue_TextIb0 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIb0, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIb0, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIb0 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIb0, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIb0, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIb0 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIb0, "NAME", "BoxValue_tag_AngleIb0");
        IupSetAttribute(BoxValue_TextAnglePhasorIb0, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIb0, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIb0, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIb0_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIb0_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIb0_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/
    Label_CurrentIc0  = IupMglLabel("\\overset I{\\bullet}c0 =");
    IupSetAttribute(Label_CurrentIc0, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIc0, "LABELFONTSIZE", "12");

        BoxValue_TextIc0 = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIc0 , "NAME", "BoxValue_tag_Ic0");
        IupSetAttribute(BoxValue_TextIc0 , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIc0, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIc0, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIc0 = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIc0, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIc0, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIc0 = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIc0, "NAME", "BoxValue_tag_AngleIc0");
        IupSetAttribute(BoxValue_TextAnglePhasorIc0, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIc0, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIc0, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIc0_Amper = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIc0_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIc0_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/

    hboxFildIa0 = IupHbox(
                   Label_CurrentIa0,

                        BoxValue_TextIa0,

                   Label_anglePhasorIa0,

                        BoxValue_TextAnglePhasorIa0,

                   Label_SymbolsDegreeIa0_Amper,

                   NULL);

    IupSetAttribute(hboxFildIa0, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIa0, "GAP", "0");
    /************************************************************************************************************/



    hboxFildIb0 = IupHbox(
                   Label_CurrentIb0,

                        BoxValue_TextIb0,

                   Label_anglePhasorIb0,

                        BoxValue_TextAnglePhasorIb0,

                   Label_SymbolsDegreeIb0_Amper,

                   NULL);

    IupSetAttribute(hboxFildIb0, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIb0, "GAP", "0");

    /**************************************************************************************************************/



    hboxFildIc0 = IupHbox(
                   Label_CurrentIc0,

                        BoxValue_TextIc0,

                   Label_anglePhasorIc0,

                        BoxValue_TextAnglePhasorIc0,

                   Label_SymbolsDegreeIc0_Amper,

                   NULL);

    IupSetAttribute(hboxFildIc0, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIc0, "GAP", "0");

    /**************************************************************************************************************/
    Ihandle *vboxFildIa;

    vboxFildIa = IupVbox(
                          Label_Corrente_Seq_Positiva,

                          hboxFildIa0,

                          hboxFildIb0,

                          hboxFildIc0,

                          NULL);

    return vboxFildIa;

}




/*****************************************(     \VALUES \BOXES \CORRENTES \REAIS )********************************************

***/
static Ihandle* Function_Box_Currents_real(void){

    Ihandle *hboxFildIa;
    Ihandle *Label_CurrentIa, *BoxValue_TextIa, *Label_anglePhasorIa, *BoxValue_TextAnglePhasorIa;
    Ihandle *Label_SymbolsDegreeIa_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIb;
    Ihandle *Label_CurrentIb, *BoxValue_TextIb, *Label_anglePhasorIb, *BoxValue_TextAnglePhasorIb;
    Ihandle *Label_SymbolsDegreeIb_Amper; //individualize tudo para não sobrecarregar!

    Ihandle *hboxFildIc;
    Ihandle *Label_CurrentIc, *BoxValue_TextIc, *Label_anglePhasorIc, *BoxValue_TextAnglePhasorIc;
    Ihandle *Label_SymbolsDegreeIc_Amper; //individualize tudo para não sobrecarregar!


    Ihandle *Label_Correntes_Reais = IupLabel("Correntes de fase:");

    /**********************************************************************************************************/
    Label_CurrentIa  = IupMglLabel("\\overset I{\\bullet}a =");
    IupSetAttribute(Label_CurrentIa, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIa, "LABELFONTSIZE", "12");

        BoxValue_TextIa = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIa , "NAME", "BoxValue_tag_Ia");
        IupSetAttribute(BoxValue_TextIa , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIa, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIa = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIa, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIa, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIa = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIa, "NAME", "BoxValue_tag_AngleIa");
        IupSetAttribute(BoxValue_TextAnglePhasorIa, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIa, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIa_Amper = IupMglLabel("\\degree \t[A]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIa_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIa_Amper, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Label_CurrentIb  = IupMglLabel("\\overset I{\\bullet}b =");
    IupSetAttribute(Label_CurrentIb, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIb, "LABELFONTSIZE", "12");

        BoxValue_TextIb = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIb , "NAME", "BoxValue_tag_Ib");
        IupSetAttribute(BoxValue_TextIb , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIa, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIb, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIb = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIb, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIb, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIb = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIb, "NAME", "BoxValue_tag_AngleIb");
        IupSetAttribute(BoxValue_TextAnglePhasorIb, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIa, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIb, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIb_Amper = IupMglLabel("\\degree\t [A]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIb_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIb_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/
    Label_CurrentIc  = IupMglLabel("\\overset I{\\bullet}c =");
    IupSetAttribute(Label_CurrentIc, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIc, "LABELFONTSIZE", "12");

        BoxValue_TextIc = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIc , "NAME", "BoxValue_tag_Ic");
        IupSetAttribute(BoxValue_TextIc , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIc, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIc, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIc = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIc, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIc, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIc = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIc, "NAME", "BoxValue_tag_AngleIc");
        IupSetAttribute(BoxValue_TextAnglePhasorIc, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIc, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIc, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIc_Amper = IupMglLabel("\\degree\t [A]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIc_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIc_Amper, "LABELFONTSIZE", "12");
    /*******************************************************************************************************/

    hboxFildIa = IupHbox(
                   Label_CurrentIa,

                        BoxValue_TextIa,

                   Label_anglePhasorIa,

                        BoxValue_TextAnglePhasorIa,

                   Label_SymbolsDegreeIa_Amper,

                   NULL);

    IupSetAttribute(hboxFildIa, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIa, "GAP", "0");
    /************************************************************************************************************/



    hboxFildIb = IupHbox(
                   Label_CurrentIb,

                        BoxValue_TextIb,

                   Label_anglePhasorIb,

                        BoxValue_TextAnglePhasorIb,

                   Label_SymbolsDegreeIb_Amper,

                   NULL);

    IupSetAttribute(hboxFildIb, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIb, "GAP", "0");

    /**************************************************************************************************************/



    hboxFildIc = IupHbox(
                   Label_CurrentIc,

                        BoxValue_TextIc,

                   Label_anglePhasorIc,

                        BoxValue_TextAnglePhasorIc,

                   Label_SymbolsDegreeIc_Amper,

                   NULL);

    IupSetAttribute(hboxFildIc, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIc, "GAP", "0");

    /**************************************************************************************************************/
    Ihandle *vboxFildIabc;

    vboxFildIabc = IupVbox(
                          Label_Correntes_Reais,

                          hboxFildIa,

                          hboxFildIb,

                          hboxFildIc,

                          NULL);

    return vboxFildIabc;

}





/*****************************************(     \VALUE \BOX \CORRENTE \BASE )********************************************

***/
static Ihandle* Function_Box_Current_base(void){

    Ihandle *hboxFildIbase;
    Ihandle *Label_CurrentIbase, *BoxValue_TextIbase, *Label_anglePhasorIbase, *BoxValue_TextAnglePhasorIbase;
    Ihandle *Label_SymbolsDegreeIbase_Amper; //individualize tudo para não sobrecarregar!


    Ihandle *Label_Corrente_Base = IupLabel("Corrente de base:");

    /**********************************************************************************************************/
    Label_CurrentIbase  = IupMglLabel("I_{base} =");
    IupSetAttribute(Label_CurrentIbase, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_CurrentIbase, "LABELFONTSIZE", "12");

        BoxValue_TextIbase = IupText(NULL);                                                //950->1350: crtl+g
        IupSetAttribute(BoxValue_TextIbase , "NAME", "BoxValue_tag_Ibase");
        IupSetAttribute(BoxValue_TextIbase , "READONLY", "YES"); //máscara 1 : bloqueia ou não novos valores
        //IupSetInt(BoxValue_TextIbase, "VALUE", NULL);// seta o campo no valor desejado
        IupSetAttribute(BoxValue_TextIbase, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER

    Label_anglePhasorIbase = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasorIbase, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasorIbase, "LABELFONTSIZE", "12");

        BoxValue_TextAnglePhasorIbase = IupText(NULL);
        IupSetAttribute(BoxValue_TextAnglePhasorIbase, "NAME", "BoxValue_tag_AngleIbase");
        IupSetAttribute(BoxValue_TextAnglePhasorIbase, "READONLY", "YES");
        //IupSetInt(BoxValue_TextAnglePhasorIbase, "VALUE", 10);
        IupSetAttribute(BoxValue_TextAnglePhasorIbase, "ALIGNMENT", "ARIGHT");

    Label_SymbolsDegreeIbase_Amper = IupMglLabel("\t [A]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegreeIbase_Amper, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegreeIbase_Amper, "LABELFONTSIZE", "12");
    /**********************************************************************************************************/
    hboxFildIbase = IupHbox(
                   Label_CurrentIbase,

                        BoxValue_TextIbase,

                   //Label_anglePhasorIbase,

                        //BoxValue_TextAnglePhasorIbase,

                   Label_SymbolsDegreeIbase_Amper,

                   NULL);

    IupSetAttribute(hboxFildIbase, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFildIbase, "GAP", "0");
    /**************************************************************************************************************/
    Ihandle *vboxFildIbase;

    vboxFildIbase = IupVbox(
                          Label_Corrente_Base,

                          hboxFildIbase,

                          NULL);

    return vboxFildIbase;

}



/*************************************************************************************************************************************/





/*****************************************(     \FORM \BTN \ONE \SHOT \C  )********************************************

***/






/******************************************* FORMULÁRIO START BUTTON 1 - INÍCIO ********************************/



static int createForm_Shot_C_1fase_1_terra(void) /*** JANELA DE DADOS EM PU E OPÇÕES DE CÁLCULOS ***/
{
     btn_n_call = 1; //Função btn_1_call
     LongProcessing();
/*
     static int status_btn1 = 0;
     static int janela_dados_coletados = 0;

     status_btn1 = status_memory_Base_SEP + status_memory_trafo_1 + status_memory_trafo_2 + status_memory_load_full_finish;

     if(status_btn_home==0)
          IupMessage("Aviso!", "Favor preencher e carregar o formulário");
     if(status_btn_home!=0 && status_memory_Base_SEP==0)
          IupMessage("Aviso!", "Favor preencher e definir a base do SEP");
     if(status_btn_home!=0 && status_memory_trafo_1==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 1");
     if(status_btn_home!=0 && status_memory_trafo_2==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 2");
     if(status_btn_home!=0 && status_memory_load_full_finish==0)
          IupMessage("Aviso!", "Favor carregar o formulário");
     if(status_btn_home!=0 && status_btn1 == 4) {
          IupMessage("Aviso!", "Bem-vindo(a) ao cálculo de curto-circuito fase-terra \n Aperte Ok para prosseguir");
          janela_dados_coletados++;
     }
     janela_dados_coletados++; //Implementação
*/


    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_V_Falta;
    //Botão para carregar a tensão de falta.
    button_V_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Tension_Fault); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Barra_de_Falta;
    //Botão para carregar a tensão de falta.
    button_Barra_de_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    //IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Base_SEP); // a função, argumento 3, recebe um Ihandle button como disparo
    IupSetCallback(button_Barra_de_Falta,"ACTION", (Icallback)button_memory_Tension_Fault);

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Calcular_Correntes_Sequencia;
    //Botão para carregar a tensão de falta.
    button_Calcular_Correntes_Sequencia = IupButton("Calcular", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_Calcular_Correntes_Sequencia,"ACTION", (Icallback)button_calc_curto_circuito_monofasico); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    Ihandle *Label_Tensao_V_Falta =  IupLabel("Tensão de Falta:");
    Ihandle *Label_arrow_Tensao_Falta;

    Label_arrow_Tensao_Falta = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Tensao_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Tensao_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/

    /**********************************************************************************/
    Ihandle *Label_Barra_de_Falta =  IupLabel("Barra de Falta:");
    Ihandle *Label_arrow_Barra_de_Falta;

    Label_arrow_Barra_de_Falta= IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Barra_de_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Barra_de_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/
      Ihandle *BoxValue_Barra_de_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_Barra_de_Falta, "NAME", "BoxValue_Barra_de_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_Barra_de_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_Barra_de_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Barra_de_Falta, "VALUE", "%d", 1);

    /**********************************************************************************************************/
    Ihandle *Label_Tension_VF;
    Label_Tension_VF  = IupMglLabel("\\overset V{\\bullet}_F =");
    IupSetAttribute(Label_Tension_VF, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_Tension_VF, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_V_Falta, "NAME", "BoxValue_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_V_Falta, "VALUE", "%.2f", 1.0);

    Ihandle *Label_anglePhasor_V_Falta;
    Label_anglePhasor_V_Falta = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasor_V_Falta, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasor_V_Falta, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_phasor_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_phasor_V_Falta, "NAME", "BoxValue_phasor_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_phasor_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_phasor_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_phasor_V_Falta, "VALUE", "%.2f", 0);


    Ihandle *Label_SymbolsDegree_V_Falta_Volt;
    Label_SymbolsDegree_V_Falta_Volt = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Ihandle *hboxFild_V_Falta;

    hboxFild_V_Falta = IupHbox(
                   Label_Tension_VF,

                        BoxValue_V_Falta,

                   Label_anglePhasor_V_Falta,

                        BoxValue_phasor_V_Falta,

                   Label_SymbolsDegree_V_Falta_Volt,

                   NULL);

    IupSetAttribute(hboxFild_V_Falta, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFild_V_Falta, "GAP", "0");


    /**********************************************************************************/
    Ihandle *Label_Corrente_Sequencia = IupLabel("Correntes de sequência");
    Ihandle *Label_arrow_Corrente_Sequencia;

    Label_arrow_Corrente_Sequencia = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "LABELFONTSIZE", "12");

    /**********************************************************************************/
                                    /***** \correntes \sequencia *****/
    Ihandle *vboxFildIseq_pos;
    Ihandle *vboxFildIseq_neg;
    Ihandle *vboxFildIseq_zero;

    vboxFildIseq_pos = Function_Box_Currents_Seq_Pos(); //invocar uma função box sequência positiva
    vboxFildIseq_neg = Function_Box_Currents_Seq_Neg(); //invocar uma função box sequência positiva
    vboxFildIseq_zero = Function_Box_Currents_Seq_Zero(); //invocar uma função box sequência positiva

    /**********************************************************************************/
                                    /***** \correntes \reais *****/
    Ihandle *vboxFildIreal;

    vboxFildIreal = Function_Box_Currents_real(); //invocar uma função box sequência positiva


    /**********************************************************************************/
                                    /***** \correntes \base *****/
    Ihandle *vboxFildIbase;

    vboxFildIbase = Function_Box_Current_base(); //invocar uma função box sequência positiva


    /******************************************************************************************************/
    Ihandle *Field_load_matrix_Currents_Sequence;


          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Currents_Sequence = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          //Field_load_matrix_Currents_Sequence = IupVbox(label_INFO_Dados, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Currents_Sequence = IupVbox(//
                                          div_01,
                                          IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          hboxFild_V_Falta,
                                          IupHbox(Label_arrow_Barra_de_Falta, Label_Barra_de_Falta, BoxValue_Barra_de_Falta, button_Barra_de_Falta, NULL),
                                          IupHbox(Label_arrow_Corrente_Sequencia,  Label_Corrente_Sequencia, button_Calcular_Correntes_Sequencia, NULL),
                                          vboxFildIseq_pos,
                                          vboxFildIseq_neg,
                                          vboxFildIseq_zero,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Sequence,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Sequence,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP está acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Currents_Real;

          Field_load_matrix_Currents_Real = IupVbox(//
                                          //div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIreal,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Real,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Real,"MARGIN","10x10");


      /*************************************************************************************************************/

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Current_Base;


          Ihandle *div_02 = IupFlatSeparator();
          IupSetAttribute(div_02, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_02, "STYLE", "FILL");
          IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta

          Field_load_matrix_Current_Base = IupVbox(//
                                          div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIbase,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Current_Base,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Current_Base,"MARGIN","10x10");


      /*************************************************************************************************************/


      Ihandle *label_Zth_pu_pos, *label_Zth_pu_neg, *label_Zth_pu_zero;

      label_Zth_pu_pos = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência positiva em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_neg = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência negativa  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_zero = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência zero  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");


      /*** QUEM VAI DIZER QUE CARREGOU AS PLANILHAS-MATRIZES É O create_mat_sequencia ***/

      Ihandle *tabs_box = IupTabs( //SOMENTE DA SEQUÊNCIA POSITIVA - 3 PANILHAS Zpu, Ypu e Zth_pu
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_positiva(3)), label_Zth_pu_pos,   //o create_mat é o excel
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),
                        IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                              IupVbox(IupFrame(create_mat_sequencia_negativa(3)), label_Zth_pu_neg,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_zero(3)), label_Zth_pu_zero,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
               NULL);



      Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

      //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
      //IupSetAttribute(tabs_box,"GAP","5");
      //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
      //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
      IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


      /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

      IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
       //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
      //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

      Ihandle *div_03 = IupFlatSeparator();
      IupSetAttribute(div_03, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
      IupSetAttribute(div_03, "STYLE", "FILL");
      IupSetAttribute(div_03, "COLOR", "0 0 0"); //Divisória preta


      //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
      //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
      Ihandle *box_positiva = IupHbox(Field_load_matrix_Currents_Sequence,

                                      tabs_box_scroll,

                                      IupVbox(Field_load_matrix_Current_Base, Field_load_matrix_Currents_Real, NULL),

                                      div_03,
                                       NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

      IupSetAttribute(box_positiva,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/


      Ihandle *box_positiva_box_scroll = IupScrollBox(box_positiva);

      IupSetAttributes(box_positiva_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );




      Ihandle *dlg;


      dlg = IupDialog(
              //IupZbox(
            box_positiva_box_scroll
            );
      //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
      IupSetAttribute(dlg,"TITLE", "Correntes de curto-circuito fase-terra");
      //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
      //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
      //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


      IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS - ATRAVÉS DISSO É POSSÍVEL ALTERNAR ABAS ***/

      //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

      IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
      IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
      //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
      //IupSetAttribute(dlg,"MENU", "mymenu");
      //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
      //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
      //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
      IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
      //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


      IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
      IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

      //IupSetHandle("mdiFrame", dlg); //A tag mdiFrame, ou seja, a janela principal/primeira ou HOME tem a tag de rastreio mdiFrame
      IupSetHandle("mdi_tag_PLAN_CURRENTS_btn_1", dlg); //tag da janela
      IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via a tag desta


      IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
      IupSetAttribute(dlg, "DEFAULTESC", "quit");


      IupMap(dlg);

      //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

      //IupShow(dlg);
      IupShowXY(dlg,IUP_CENTER,IUP_CENTER);



      //else
        //chave-abre
          //  IupMessage("Aviso!", "Formulário já foi criado");
        //chave-fecha


      return IUP_DEFAULT;

}


/******************************************* FORMULÁRIO START BUTTON 1 - FIM ********************************/






/*****************************************(     \FORM \BTN \TWO \SHOT \C  )********************************************

***/





/******************************************* FORMULÁRIO START BUTTON 2 - INÍCIO ********************************/



static int createForm_Shot_C_2fase_2(void) /*** JANELA DE DADOS EM PU E OPÇÕES DE CÁLCULOS ***/
{


/*
   static int status_btn2 = 0;
   static int id = 0;

     status_btn2 = status_memory_Base_SEP + status_memory_trafo_1 + status_memory_trafo_2 + status_memory_load_full_finish;

     if(status_btn_home==0)
          IupMessage("Aviso!", "Favor preencher e carregar o formulário");
     if(status_btn_home!=0 && status_memory_Base_SEP==0)
          IupMessage("Aviso!", "Favor preencher e definir a base do SEP");
     if(status_btn_home!=0 && status_memory_trafo_1==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 1");
     if(status_btn_home!=0 && status_memory_trafo_2==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 2");
     if(status_btn_home!=0 && status_memory_load_full_finish==0)
          IupMessage("Aviso!", "Favor carregar o formulário");
     if(status_btn_home!=0 && status_btn2 == 4 && id == 0){
          IupMessage("Aviso!", "Bem-vindo(a) ao cálculo de curto-circuito bifásico \n Aperte Ok para prosseguir");

*/


    btn_n_call = 2; //Função btn_2_call
    LongProcessing();

    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_V_Falta;
    //Botão para carregar a tensão de falta.
    button_V_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Tension_Fault); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Barra_de_Falta;
    //Botão para carregar a tensão de falta.
    button_Barra_de_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    //IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Base_SEP); // a função, argumento 3, recebe um Ihandle button como disparo
    IupSetCallback(button_Barra_de_Falta,"ACTION", (Icallback)button_memory_Tension_Fault);

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Calcular_Correntes_Sequencia;
    //Botão para carregar a tensão de falta.
    button_Calcular_Correntes_Sequencia = IupButton("Calcular", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_Calcular_Correntes_Sequencia,"ACTION", (Icallback)button_calc_curto_circuito_bifasico); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    Ihandle *Label_Tensao_V_Falta =  IupLabel("Tensão de Falta:");
    Ihandle *Label_arrow_Tensao_Falta;

    Label_arrow_Tensao_Falta = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Tensao_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Tensao_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/

    /**********************************************************************************/
    Ihandle *Label_Barra_de_Falta =  IupLabel("Barra de Falta:");
    Ihandle *Label_arrow_Barra_de_Falta;

    Label_arrow_Barra_de_Falta= IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Barra_de_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Barra_de_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/
      Ihandle *BoxValue_Barra_de_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_Barra_de_Falta, "NAME", "BoxValue_Barra_de_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_Barra_de_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_Barra_de_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Barra_de_Falta, "VALUE", "%d", 1);

    /**********************************************************************************************************/
    Ihandle *Label_Tension_VF;
    Label_Tension_VF  = IupMglLabel("\\overset V{\\bullet}_F =");
    IupSetAttribute(Label_Tension_VF, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_Tension_VF, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_V_Falta, "NAME", "BoxValue_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_V_Falta, "VALUE", "%.2f", 1.0);

    Ihandle *Label_anglePhasor_V_Falta;
    Label_anglePhasor_V_Falta = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasor_V_Falta, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasor_V_Falta, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_phasor_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_phasor_V_Falta, "NAME", "BoxValue_phasor_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_phasor_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_phasor_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_phasor_V_Falta, "VALUE", "%.2f", 0);


    Ihandle *Label_SymbolsDegree_V_Falta_Volt;
    Label_SymbolsDegree_V_Falta_Volt = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Ihandle *hboxFild_V_Falta;

    hboxFild_V_Falta = IupHbox(
                   Label_Tension_VF,

                        BoxValue_V_Falta,

                   Label_anglePhasor_V_Falta,

                        BoxValue_phasor_V_Falta,

                   Label_SymbolsDegree_V_Falta_Volt,

                   NULL);

    IupSetAttribute(hboxFild_V_Falta, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFild_V_Falta, "GAP", "0");


    /**********************************************************************************/
    Ihandle *Label_Corrente_Sequencia = IupLabel("Correntes de sequência");
    Ihandle *Label_arrow_Corrente_Sequencia;

    Label_arrow_Corrente_Sequencia = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "LABELFONTSIZE", "12");

    /**********************************************************************************/
                                    /***** \correntes \sequencia *****/
    Ihandle *vboxFildIseq_pos;
    Ihandle *vboxFildIseq_neg;
    Ihandle *vboxFildIseq_zero;

    vboxFildIseq_pos = Function_Box_Currents_Seq_Pos(); //invocar uma função box sequência positiva
    vboxFildIseq_neg = Function_Box_Currents_Seq_Neg(); //invocar uma função box sequência positiva
    vboxFildIseq_zero = Function_Box_Currents_Seq_Zero(); //invocar uma função box sequência positiva

    /**********************************************************************************/
                                    /***** \correntes \reais *****/
    Ihandle *vboxFildIreal;

    vboxFildIreal = Function_Box_Currents_real(); //invocar uma função box sequência positiva


    /**********************************************************************************/
                                    /***** \correntes \base *****/
    Ihandle *vboxFildIbase;

    vboxFildIbase = Function_Box_Current_base(); //invocar uma função box sequência positiva


    /******************************************************************************************************/
    Ihandle *Field_load_matrix_Currents_Sequence;


          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Currents_Sequence = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          //Field_load_matrix_Currents_Sequence = IupVbox(label_INFO_Dados, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Currents_Sequence = IupVbox(//
                                          div_01,
                                          IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          hboxFild_V_Falta,
                                          IupHbox(Label_arrow_Barra_de_Falta, Label_Barra_de_Falta, BoxValue_Barra_de_Falta, button_Barra_de_Falta, NULL),
                                          IupHbox(Label_arrow_Corrente_Sequencia,  Label_Corrente_Sequencia, button_Calcular_Correntes_Sequencia, NULL),
                                          vboxFildIseq_pos,
                                          vboxFildIseq_neg,
                                          vboxFildIseq_zero,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Sequence,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Sequence,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP está acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Currents_Real;

          Field_load_matrix_Currents_Real = IupVbox(//
                                          //div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIreal,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Real,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Real,"MARGIN","10x10");


      /*************************************************************************************************************/

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Current_Base;


          Ihandle *div_02 = IupFlatSeparator();
          IupSetAttribute(div_02, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_02, "STYLE", "FILL");
          IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta

          Field_load_matrix_Current_Base = IupVbox(//
                                          div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIbase,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Current_Base,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Current_Base,"MARGIN","10x10");


      /*************************************************************************************************************/


      Ihandle *label_Zth_pu_pos, *label_Zth_pu_neg, *label_Zth_pu_zero;

      label_Zth_pu_pos = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência positiva em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_neg = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência negativa  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_zero = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência zero  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");


      /*** QUEM VAI DIZER QUE CARREGOU AS PLANILHAS-MATRIZES É O create_mat_sequencia ***/

      Ihandle *tabs_box = IupTabs( //SOMENTE DA SEQUÊNCIA POSITIVA - 3 PANILHAS Zpu, Ypu e Zth_pu
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_positiva(3)), label_Zth_pu_pos,   //o create_mat é o excel
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),
                        IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                              IupVbox(IupFrame(create_mat_sequencia_negativa(3)), label_Zth_pu_neg,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_zero(3)), label_Zth_pu_zero,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
               NULL);



      Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

      //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
      //IupSetAttribute(tabs_box,"GAP","5");
      //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
      //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
      IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


      /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

      IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
       //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
      //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

      Ihandle *div_03 = IupFlatSeparator();
      IupSetAttribute(div_03, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
      IupSetAttribute(div_03, "STYLE", "FILL");
      IupSetAttribute(div_03, "COLOR", "0 0 0"); //Divisória preta


      //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
      //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
      Ihandle *box_positiva = IupHbox(Field_load_matrix_Currents_Sequence,

                                      tabs_box_scroll,

                                      IupVbox(Field_load_matrix_Current_Base, Field_load_matrix_Currents_Real, NULL),

                                      div_03,
                                       NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

      IupSetAttribute(box_positiva,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/


      Ihandle *box_positiva_box_scroll = IupScrollBox(box_positiva);

      IupSetAttributes(box_positiva_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );




      Ihandle *dlg;


      dlg = IupDialog(
              //IupZbox(
            box_positiva_box_scroll
            );
      //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
      IupSetAttribute(dlg,"TITLE", "Correntes de curto-circuito bifásico");
      //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
      //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
      //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


      IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS - ATRAVÉS DISSO É POSSÍVEL ALTERNAR ABAS ***/

      //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

      IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
      IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
      //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
      //IupSetAttribute(dlg,"MENU", "mymenu");
      //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
      //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
      //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
      IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
      //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


      IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
      IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

      //IupSetHandle("mdiFrame", dlg); //A tag mdiFrame, ou seja, a janela principal/primeira ou HOME tem a tag de rastreio mdiFrame
      IupSetHandle("mdi_tag_PLAN_CURRENTS_btn_1", dlg); //tag da janela
      IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via a tag desta


      IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
      IupSetAttribute(dlg, "DEFAULTESC", "quit");


      IupMap(dlg);

      //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

      //IupShow(dlg);
      IupShowXY(dlg,IUP_CENTER,IUP_CENTER);



      //else
        //chave-abre
          //  IupMessage("Aviso!", "Formulário já foi criado");
        //chave-fecha


      return IUP_DEFAULT;

}



/******************************************* FORMULÁRIO START BUTTON 2 - FIM ********************************/







/*****************************************(     \FORM \BTN \THREE \SHOT \C  )********************************************

***/






/******************************************* FORMULÁRIO START BUTTON 3 - INÍCIO ********************************/



static int createForm_Shot_C_2fase_3_terra(void) /*** JANELA DE DADOS EM PU E OPÇÕES DE CÁLCULOS ***/
{
     btn_n_call = 3; //Função btn_3_call
     LongProcessing();

/*
     static int status_btn1 = 0;

     status_btn1 = status_memory_Base_SEP + status_memory_trafo_1 + status_memory_trafo_2 + status_memory_load_full_finish;

     if(status_btn_home==0)
          IupMessage("Aviso!", "Favor preencher e carregar o formulário");
     if(status_btn_home!=0 && status_memory_Base_SEP==0)
          IupMessage("Aviso!", "Favor preencher e definir a base do SEP");
     if(status_btn_home!=0 && status_memory_trafo_1==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 1");
     if(status_btn_home!=0 && status_memory_trafo_2==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 2");
     if(status_btn_home!=0 && status_memory_load_full_finish==0)
          IupMessage("Aviso!", "Favor carregar o formulário");
     if(status_btn_home!=0 && status_btn1 == 4)
          IupMessage("Aviso!", "Bem-vindo(a) ao cálculo de curto-circuito bifásico-terra \n Aperte Ok para prosseguir");

*/

    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_V_Falta;
    //Botão para carregar a tensão de falta.
    button_V_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Tension_Fault); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Barra_de_Falta;
    //Botão para carregar a tensão de falta.
    button_Barra_de_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    //IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Base_SEP); // a função, argumento 3, recebe um Ihandle button como disparo
    IupSetCallback(button_Barra_de_Falta,"ACTION", (Icallback)button_memory_Tension_Fault);

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Calcular_Correntes_Sequencia;
    //Botão para carregar a tensão de falta.
    button_Calcular_Correntes_Sequencia = IupButton("Calcular", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_Calcular_Correntes_Sequencia,"ACTION", (Icallback)button_calc_curto_circuito_bifasico_terra); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    Ihandle *Label_Tensao_V_Falta =  IupLabel("Tensão de Falta:");
    Ihandle *Label_arrow_Tensao_Falta;

    Label_arrow_Tensao_Falta = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Tensao_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Tensao_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/

    /**********************************************************************************/
    Ihandle *Label_Barra_de_Falta =  IupLabel("Barra de Falta:");
    Ihandle *Label_arrow_Barra_de_Falta;

    Label_arrow_Barra_de_Falta= IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Barra_de_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Barra_de_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/
      Ihandle *BoxValue_Barra_de_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_Barra_de_Falta, "NAME", "BoxValue_Barra_de_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_Barra_de_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_Barra_de_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Barra_de_Falta, "VALUE", "%d", 1);

    /**********************************************************************************************************/
    Ihandle *Label_Tension_VF;
    Label_Tension_VF  = IupMglLabel("\\overset V{\\bullet}_F =");
    IupSetAttribute(Label_Tension_VF, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_Tension_VF, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_V_Falta, "NAME", "BoxValue_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_V_Falta, "VALUE", "%.2f", 1.0);

    Ihandle *Label_anglePhasor_V_Falta;
    Label_anglePhasor_V_Falta = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasor_V_Falta, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasor_V_Falta, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_phasor_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_phasor_V_Falta, "NAME", "BoxValue_phasor_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_phasor_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_phasor_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_phasor_V_Falta, "VALUE", "%.2f", 0);


    Ihandle *Label_SymbolsDegree_V_Falta_Volt;
    Label_SymbolsDegree_V_Falta_Volt = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Ihandle *hboxFild_V_Falta;

    hboxFild_V_Falta = IupHbox(
                   Label_Tension_VF,

                        BoxValue_V_Falta,

                   Label_anglePhasor_V_Falta,

                        BoxValue_phasor_V_Falta,

                   Label_SymbolsDegree_V_Falta_Volt,

                   NULL);

    IupSetAttribute(hboxFild_V_Falta, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFild_V_Falta, "GAP", "0");


    /**********************************************************************************/
    Ihandle *Label_Corrente_Sequencia = IupLabel("Correntes de sequência");
    Ihandle *Label_arrow_Corrente_Sequencia;

    Label_arrow_Corrente_Sequencia = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "LABELFONTSIZE", "12");

    /**********************************************************************************/
                                    /***** \correntes \sequencia *****/
    Ihandle *vboxFildIseq_pos;
    Ihandle *vboxFildIseq_neg;
    Ihandle *vboxFildIseq_zero;

    vboxFildIseq_pos = Function_Box_Currents_Seq_Pos(); //invocar uma função box sequência positiva
    vboxFildIseq_neg = Function_Box_Currents_Seq_Neg(); //invocar uma função box sequência positiva
    vboxFildIseq_zero = Function_Box_Currents_Seq_Zero(); //invocar uma função box sequência positiva

    /**********************************************************************************/
                                    /***** \correntes \reais *****/
    Ihandle *vboxFildIreal;

    vboxFildIreal = Function_Box_Currents_real(); //invocar uma função box sequência positiva


    /**********************************************************************************/
                                    /***** \correntes \base *****/
    Ihandle *vboxFildIbase;

    vboxFildIbase = Function_Box_Current_base(); //invocar uma função box sequência positiva


    /******************************************************************************************************/
    Ihandle *Field_load_matrix_Currents_Sequence;


          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Currents_Sequence = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          //Field_load_matrix_Currents_Sequence = IupVbox(label_INFO_Dados, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Currents_Sequence = IupVbox(//
                                          div_01,
                                          IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          hboxFild_V_Falta,
                                          IupHbox(Label_arrow_Barra_de_Falta, Label_Barra_de_Falta, BoxValue_Barra_de_Falta, button_Barra_de_Falta, NULL),
                                          IupHbox(Label_arrow_Corrente_Sequencia,  Label_Corrente_Sequencia, button_Calcular_Correntes_Sequencia, NULL),
                                          vboxFildIseq_pos,
                                          vboxFildIseq_neg,
                                          vboxFildIseq_zero,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Sequence,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Sequence,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP está acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Currents_Real;

          Field_load_matrix_Currents_Real = IupVbox(//
                                          //div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIreal,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Real,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Real,"MARGIN","10x10");


      /*************************************************************************************************************/

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Current_Base;


          Ihandle *div_02 = IupFlatSeparator();
          IupSetAttribute(div_02, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_02, "STYLE", "FILL");
          IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta

          Field_load_matrix_Current_Base = IupVbox(//
                                          div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIbase,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Current_Base,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Current_Base,"MARGIN","10x10");


      /*************************************************************************************************************/


      Ihandle *label_Zth_pu_pos, *label_Zth_pu_neg, *label_Zth_pu_zero;

      label_Zth_pu_pos = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência positiva em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_neg = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência negativa  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_zero = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência zero  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");


      /*** QUEM VAI DIZER QUE CARREGOU AS PLANILHAS-MATRIZES É O create_mat_sequencia ***/

      Ihandle *tabs_box = IupTabs( //SOMENTE DA SEQUÊNCIA POSITIVA - 3 PANILHAS Zpu, Ypu e Zth_pu
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_positiva(3)), label_Zth_pu_pos,   //o create_mat é o excel
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),
                        IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                              IupVbox(IupFrame(create_mat_sequencia_negativa(3)), label_Zth_pu_neg,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_zero(3)), label_Zth_pu_zero,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
               NULL);



      Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

      //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
      //IupSetAttribute(tabs_box,"GAP","5");
      //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
      //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
      IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


      /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

      IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
       //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
      //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

      Ihandle *div_03 = IupFlatSeparator();
      IupSetAttribute(div_03, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
      IupSetAttribute(div_03, "STYLE", "FILL");
      IupSetAttribute(div_03, "COLOR", "0 0 0"); //Divisória preta


      //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
      //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
      Ihandle *box_positiva = IupHbox(Field_load_matrix_Currents_Sequence,

                                      tabs_box_scroll,

                                      IupVbox(Field_load_matrix_Current_Base, Field_load_matrix_Currents_Real, NULL),

                                      div_03,
                                       NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

      IupSetAttribute(box_positiva,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/


      Ihandle *box_positiva_box_scroll = IupScrollBox(box_positiva);

      IupSetAttributes(box_positiva_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );




      Ihandle *dlg;


      dlg = IupDialog(
              //IupZbox(
            box_positiva_box_scroll
            );
      //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
      IupSetAttribute(dlg,"TITLE", "Correntes de curto-circuito bifásico-terra");
      //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
      //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
      //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


      IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS - ATRAVÉS DISSO É POSSÍVEL ALTERNAR ABAS ***/

      //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

      IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
      IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
      //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
      //IupSetAttribute(dlg,"MENU", "mymenu");
      //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
      //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
      //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
      IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
      //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


      IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
      IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

      //IupSetHandle("mdiFrame", dlg); //A tag mdiFrame, ou seja, a janela principal/primeira ou HOME tem a tag de rastreio mdiFrame
      IupSetHandle("mdi_tag_PLAN_CURRENTS_btn_1", dlg); //tag da janela
      IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via a tag desta


      IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
      IupSetAttribute(dlg, "DEFAULTESC", "quit");


      IupMap(dlg);

      //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

      //IupShow(dlg);
      IupShowXY(dlg,IUP_CENTER,IUP_CENTER);



      //else
        //chave-abre
          //  IupMessage("Aviso!", "Formulário já foi criado");
        //chave-fecha


      return IUP_DEFAULT;

}




/******************************************* FORMULÁRIO START BUTTON 3 - FIM ********************************/









/*****************************************(     \FORM \BTN \FOUR \SHOT \C  )********************************************

***/






/******************************************* FORMULÁRIO START BUTTON 4 - INÍCIO ********************************/



static int createForm_Shot_C_3fase_4(void) /*** JANELA DE DADOS EM PU E OPÇÕES DE CÁLCULOS ***/
{
    btn_n_call = 4; //Função btn_4_call
    LongProcessing();

/*
   static int status_btn1 = 0;


     status_btn1 = status_memory_Base_SEP + status_memory_trafo_1 + status_memory_trafo_2 + status_memory_load_full_finish;

     if(status_btn_home==0)
          IupMessage("Aviso!", "Favor preencher e carregar o formulário");
     if(status_btn_home!=0 && status_memory_Base_SEP==0)
          IupMessage("Aviso!", "Favor preencher e definir a base do SEP");
     if(status_btn_home!=0 && status_memory_trafo_1==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 1");
     if(status_btn_home!=0 && status_memory_trafo_2==0)
          IupMessage("Aviso!", "Favor preencher e definir a ligação do transformador 2");
     if(status_btn_home!=0 && status_memory_load_full_finish==0)
          IupMessage("Aviso!", "Favor carregar o formulário");
     if(status_btn_home!=0 && status_btn1 == 4)
          IupMessage("Aviso!", "Bem-vindo(a) ao cálculo de curto-circuito trifásico \n Aperte Ok para prosseguir");


*/




    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_V_Falta;
    //Botão para carregar a tensão de falta.
    button_V_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Tension_Fault); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Barra_de_Falta;
    //Botão para carregar a tensão de falta.
    button_Barra_de_Falta = IupButton("Definir", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    //IupSetCallback(button_V_Falta,"ACTION", (Icallback)button_memory_Base_SEP); // a função, argumento 3, recebe um Ihandle button como disparo
    IupSetCallback(button_Barra_de_Falta,"ACTION", (Icallback)button_memory_Tension_Fault);

    /**********************************************************************************/
    /**********************************************************************************/
    //Ihandle *label;
    Ihandle *button_Calcular_Correntes_Sequencia;
    //Botão para carregar a tensão de falta.
    button_Calcular_Correntes_Sequencia = IupButton("Calcular", NULL);
    //Implementar a função de armazenamento de memória da tensão de falta
    IupSetCallback(button_Calcular_Correntes_Sequencia,"ACTION", (Icallback)button_calc_curto_circuito_trifasico); // a função, argumento 3, recebe um Ihandle button como disparo

    /**********************************************************************************/
    Ihandle *Label_Tensao_V_Falta =  IupLabel("Tensão de Falta:");
    Ihandle *Label_arrow_Tensao_Falta;

    Label_arrow_Tensao_Falta = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Tensao_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Tensao_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/

    /**********************************************************************************/
    Ihandle *Label_Barra_de_Falta =  IupLabel("Barra de Falta:");
    Ihandle *Label_arrow_Barra_de_Falta;

    Label_arrow_Barra_de_Falta= IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Barra_de_Falta, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Barra_de_Falta, "LABELFONTSIZE", "12");

    /**********************************************************************************/
      Ihandle *BoxValue_Barra_de_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_Barra_de_Falta, "NAME", "BoxValue_Barra_de_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_Barra_de_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_Barra_de_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_Barra_de_Falta, "VALUE", "%d", 1);

    /**********************************************************************************************************/
    Ihandle *Label_Tension_VF;
    Label_Tension_VF  = IupMglLabel("\\overset V{\\bullet}_F =");
    IupSetAttribute(Label_Tension_VF, "RASTERSIZE", "60x30");
    IupSetAttribute(Label_Tension_VF, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_V_Falta, "NAME", "BoxValue_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_V_Falta, "VALUE", "%.2f", 1.0);

    Ihandle *Label_anglePhasor_V_Falta;
    Label_anglePhasor_V_Falta = IupMglLabel("\\angle");//("\\utf2220");
    IupSetAttribute(Label_anglePhasor_V_Falta, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_anglePhasor_V_Falta, "LABELFONTSIZE", "12");

      Ihandle *BoxValue_phasor_V_Falta = IupText(NULL);
      IupSetAttribute(BoxValue_phasor_V_Falta, "NAME", "BoxValue_phasor_V_Falta_tag"); //tag vinculado ao box text
      IupSetAttribute(BoxValue_phasor_V_Falta, "READONLY", "NO");
      IupSetAttribute(BoxValue_phasor_V_Falta, "ALIGNMENT", "ARIGHT"); //opções ALEFT, ACENTER
      IupSetfAttribute(BoxValue_phasor_V_Falta, "VALUE", "%.2f", 0);


    Ihandle *Label_SymbolsDegree_V_Falta_Volt;
    Label_SymbolsDegree_V_Falta_Volt = IupMglLabel("\\degree\t [pu]");//IupLabel(title1);
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "RASTERSIZE", "40x25");
    IupSetAttribute(Label_SymbolsDegree_V_Falta_Volt, "LABELFONTSIZE", "12");

    /******************************************************************************************************/
    Ihandle *hboxFild_V_Falta;

    hboxFild_V_Falta = IupHbox(
                   Label_Tension_VF,

                        BoxValue_V_Falta,

                   Label_anglePhasor_V_Falta,

                        BoxValue_phasor_V_Falta,

                   Label_SymbolsDegree_V_Falta_Volt,

                   NULL);

    IupSetAttribute(hboxFild_V_Falta, "MARGIN", "2x2"); //afastamento das bordas direita e esquera x topo e embaixo
    IupSetAttribute(hboxFild_V_Falta, "GAP", "0");


    /**********************************************************************************/
    Ihandle *Label_Corrente_Sequencia = IupLabel("Correntes de sequência");
    Ihandle *Label_arrow_Corrente_Sequencia;

    Label_arrow_Corrente_Sequencia = IupMglLabel("\\bullet");
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "RASTERSIZE", "10x10"); //se não tiver isso nada feito
    IupSetAttribute(Label_arrow_Corrente_Sequencia, "LABELFONTSIZE", "12");

    /**********************************************************************************/
                                    /***** \correntes \sequencia *****/
    Ihandle *vboxFildIseq_pos;
    Ihandle *vboxFildIseq_neg;
    Ihandle *vboxFildIseq_zero;

    vboxFildIseq_pos = Function_Box_Currents_Seq_Pos(); //invocar uma função box sequência positiva
    vboxFildIseq_neg = Function_Box_Currents_Seq_Neg(); //invocar uma função box sequência positiva
    vboxFildIseq_zero = Function_Box_Currents_Seq_Zero(); //invocar uma função box sequência positiva

    /**********************************************************************************/
                                    /***** \correntes \reais *****/
    Ihandle *vboxFildIreal;

    vboxFildIreal = Function_Box_Currents_real(); //invocar uma função box sequência positiva


    /**********************************************************************************/
                                    /***** \correntes \base *****/
    Ihandle *vboxFildIbase;

    vboxFildIbase = Function_Box_Current_base(); //invocar uma função box sequência positiva


    /******************************************************************************************************/
    Ihandle *Field_load_matrix_Currents_Sequence;


          //exibir em txt se possível para permitir copiar e colar

          Ihandle *div_01 = IupFlatSeparator();
          IupSetAttribute(div_01, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_01, "STYLE", "FILL");
          IupSetAttribute(div_01, "COLOR", "0 0 0"); //Divisória preta

          //STYLE=FILL
          //COLOR="255 0 128"



          //Field_load_matrix_Currents_Sequence = IupVbox(div_01, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          //Field_load_matrix_Currents_Sequence = IupVbox(label_INFO_Dados, bt_matrix_Zpu_pos, bt_matrix_Ypu_pos, bt_matrix_Zpu_th_pos, NULL);
          Field_load_matrix_Currents_Sequence = IupVbox(//
                                          div_01,
                                          IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          hboxFild_V_Falta,
                                          IupHbox(Label_arrow_Barra_de_Falta, Label_Barra_de_Falta, BoxValue_Barra_de_Falta, button_Barra_de_Falta, NULL),
                                          IupHbox(Label_arrow_Corrente_Sequencia,  Label_Corrente_Sequencia, button_Calcular_Correntes_Sequencia, NULL),
                                          vboxFildIseq_pos,
                                          vboxFildIseq_neg,
                                          vboxFildIseq_zero,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Sequence,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Sequence,"MARGIN","10x10"); //agora clareou, só não sei como por gap horizontal diretamente
          //A hierarquia do GAP está acima do MARGIN, então mesmo que leia depois o MARGIN, o GAP se sobrepõe

          //No caso vc precisa criar um IupHbox daí entre os elementos do Hbox aplica-se o gap, no caso horizontalmente!

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Currents_Real;

          Field_load_matrix_Currents_Real = IupVbox(//
                                          //div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIreal,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Currents_Real,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Currents_Real,"MARGIN","10x10");


      /*************************************************************************************************************/

      /******************************************************************************************************/
      Ihandle *Field_load_matrix_Current_Base;


          Ihandle *div_02 = IupFlatSeparator();
          IupSetAttribute(div_02, "ORIENTATION", "HORIZONTAL");     //HORIZONTAL entre elementos verticias
          IupSetAttribute(div_02, "STYLE", "FILL");
          IupSetAttribute(div_02, "COLOR", "0 0 0"); //Divisória preta

          Field_load_matrix_Current_Base = IupVbox(//
                                          div_02,
                                          //IupHbox(Label_arrow_Tensao_Falta, Label_Tensao_V_Falta, button_V_Falta, NULL),
                                          vboxFildIbase,
                                          //
                                          NULL);

          IupSetAttribute(Field_load_matrix_Current_Base,"GAP","5"); //aqui permitiu por um gap vertical em cada botão acima (argumentos do Field)
          IupSetAttribute(Field_load_matrix_Current_Base,"MARGIN","10x10");


      /*************************************************************************************************************/


      Ihandle *label_Zth_pu_pos, *label_Zth_pu_neg, *label_Zth_pu_zero;

      label_Zth_pu_pos = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência positiva em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_neg = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência negativa  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");
      label_Zth_pu_zero = IupLabel("Esta planilha-matriz exibe os valores de impedância de thévenin de sequência zero  em pu.\n"
                           "\nA exibição de matrizes de ordens maiores que 5x5 requer navegar usando as barras de rolagem. "
                           "\nÉ possível exportar a planilha-matriz para as extensões de texto (.txt), LaTeX (.tex) e Web (.html). "
                           "\nAo salvar o nome do arquivo digite a extensão desejada. O acesso à exportação é via contra-click. ");


      /*** QUEM VAI DIZER QUE CARREGOU AS PLANILHAS-MATRIZES É O create_mat_sequencia ***/

      Ihandle *tabs_box = IupTabs( //SOMENTE DA SEQUÊNCIA POSITIVA - 3 PANILHAS Zpu, Ypu e Zth_pu
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_positiva(3)), label_Zth_pu_pos,   //o create_mat é o excel
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),     //o gap de 10 ou 100 vai definir a exibição ou não da barra de rolagem na maximização da janela
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Z_pu+"),
                        IupSetAttributes(           //GAP entre elementos da aba ...entre elementos na vertical
                              IupVbox(IupFrame(create_mat_sequencia_negativa(3)), label_Zth_pu_neg,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu-"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Y_pu+"),
                        IupSetAttributes(
                              IupVbox(IupFrame(create_mat_sequencia_zero(3)), label_Zth_pu_zero,
            //                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"),
            //                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"),
                              NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu0"),
                              //NULL), "FONT=\"HELVETICA_BOLD_12\", FGCOLOR=\"0 0 255\", FONTSIZE=\"12\", FONTSTYLE=\"Bold\", BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=100, TABTITLE=Zth_pu+"),
               NULL);



      Ihandle *tabs_box_scroll = IupScrollBox(tabs_box);

      //IupSetAttribute(tabs_box_scroll,"MARGIN","50x50");
      //IupSetAttribute(tabs_box,"GAP","5");
      //IupSetAttributes(tabs_box_scroll, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ARIGHT");
      //IupSetAttributes(tabs_box, "SIZE=500x400, EXPAND=YES, ALIGNMENT=ACENTER");
      IupSetAttributes(tabs_box, "SIZE=300x300, EXPAND=NO, ALIGNMENT=ACENTER");


      /*** cuidado por size aqui no tabs_box_scroll parece que o desativa ***/

      IupSetAttributes(tabs_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );
       //_vbox_2 = IupVbox(IupSetAttributes(IupScrollBox(_vbox_1), "RASTERSIZE=200x300"), NULL); //No caso delimita a barra de rolagem com tamanho que desejar ...se o valor for alto, então vai exibir somente dps de redimensionar manualmente
      //IupSetAttribute(tabs_box_scroll,"MARGIN","20x20");

      Ihandle *div_03 = IupFlatSeparator();
      IupSetAttribute(div_03, "ORIENTATION", "VERTICAL");                   //VERTICAL entre elementos horizontais
      IupSetAttribute(div_03, "STYLE", "FILL");
      IupSetAttribute(div_03, "COLOR", "0 0 0"); //Divisória preta


      //Ihandle *box_positiva = IupHbox(btn, Field_load_matrix_Zpu, tabs_box_scroll, NULL);
      //Ihandle *box_positiva = IupHbox(Field_load_matrix_Zpu, div_01, tabs_box_scroll, NULL);
      Ihandle *box_positiva = IupHbox(Field_load_matrix_Currents_Sequence,

                                      tabs_box_scroll,

                                      IupVbox(Field_load_matrix_Current_Base, Field_load_matrix_Currents_Real, NULL),

                                      div_03,
                                       NULL); //Se o layout de arraste for NO só atualiza dps de soltar o click do mouse

      IupSetAttribute(box_positiva,"GAP","30"); /*** GAP horizontal entre os elementos do Hbox ***/


      Ihandle *box_positiva_box_scroll = IupScrollBox(box_positiva);

      IupSetAttributes(box_positiva_box_scroll, "NAME=SCROLLBOXTEST, LAYOUTDRAG=YES" );




      Ihandle *dlg;


      dlg = IupDialog(
              //IupZbox(
            box_positiva_box_scroll
            );
      //IupSetfAttribute(dlg,"TITLE","MDI Child (%d)", id); id++;
      IupSetAttribute(dlg,"TITLE", "Correntes de curto-circuito trifásico");
      //IupSetfAttribute(dlg,"TITLE","Exibição de matrizes de sequência positiva");//(%d) (ASPAS), id);
      //id++; //é possível indexar a janela pelo título, caso contrário coloque o contador para não permitir a reabertura
      //IupSetAttribute(dlg,"MDICHILD","YES"); //MANO PARA SOBREPOR AO IUP_BOX ERA SÓ COMENTAR ESSA LINHA
                                                   //SEQUER PRECISA DA CRIAÇÃO DO CANVAS


      IupSetAttribute(dlg, "APP_TABS", (char*)tabs_box); /*** TAG UNIVERSAL PARA O IHANDLE ABAS - ATRAVÉS DISSO É POSSÍVEL ALTERNAR ABAS ***/

      //IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame");

      IupSetCallback(dlg,"MDIACTIVATE_CB",(Icallback)mdi_activate);
      IupSetAttribute(dlg,"RASTERSIZE","800x600"); //HxV
      //IupSetAttribute(dlg, "PLACEMENT", "MAXIMIZED");
      //IupSetAttribute(dlg,"MENU", "mymenu");
      //IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
      //IupSetAttribute(dlg,"BGCOLOR", "0 0 0");
      //IupSetAttribute(dlg, "FONT", "Helvetica, 24");
      IupSetAttribute(dlg, "FONT", "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
      //IupSetAttribute(dlg, "FGCOLOR", "255 0 0");//Fica vermelho somente o nome do frame >>> nesse cenário ficou o label e o text_button


      IupSetAttribute(dlg,"MDICHILD","NO"); //sobreposição
      IupSetAttribute(dlg,"MDIFRAME","NO"); //não gera janelas filhas

      //IupSetHandle("mdiFrame", dlg); //A tag mdiFrame, ou seja, a janela principal/primeira ou HOME tem a tag de rastreio mdiFrame
      IupSetHandle("mdi_tag_PLAN_CURRENTS_btn_1", dlg); //tag da janela
      IupSetAttribute(dlg,"PARENTDIALOG","mdiFrame"); //atribuindo a dlg à janela principal via a tag desta


      IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
      IupSetAttribute(dlg, "DEFAULTESC", "quit");


      IupMap(dlg);

      //IupSetAttribute(dlg,"RASTERSIZE", NULL); //isso tá errado, fará a janela ficar pitoca

      //IupShow(dlg);
      IupShowXY(dlg,IUP_CENTER,IUP_CENTER);



      //else
        //chave-abre
          //  IupMessage("Aviso!", "Formulário já foi criado");
        //chave-fecha


      return IUP_DEFAULT;

}



/******************************************* FIM - FORMULÁRIO START BUTTON 4 - FIM ********************************/









/******************************* INÍCIO - VARIÁVEIS GLOBAIS/GLOBAL e LOCAIS/LOCAL - INÍCIO ***************************************/

                /*** Variável global - basta inserir static que já é o suficiente, nada externamente à função ***/


/*****************************************(     \ICON \SHOT \C  )********************************************

***/




/********************************** INÍCIO - Ícone do SHOT-C - INÍCIO *****************************************/

static unsigned char img[] =
{
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,5,6,6,6,6,6,6,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,5,6,6,6,6,6,6,5,5,4,2,
1,3,5,5,5,5,6,6,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,6,6,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,6,6,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,6,6,5,5,6,6,5,5,6,6,5,5,6,6,5,5,5,5,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,6,6,6,6,6,6,6,5,5,6,6,5,5,6,6,5,5,6,6,6,6,6,6,6,6,5,5,5,5,6,6,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,2,
1,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,
1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};//imagem 32x43 (só expandiu horizontalmente) - último número sem vírgula!

/* defines icon's image */
//imagem 32x32 - removido - atenuar linhas

/******************************************* FIM - Ícone do SHOT-C - FIM *****************************************/




/*****************************************(     \OPEN \TXT \FILE \SHOT \C  )********************************************

***/





/********************************** INÍCIO - Utilitários - abertura de arquivos txt - INÍCIO *****************************************/

//estrutura para abertura de arquivo
char* read_file(const char* filename)
{
  int size;
  char* str;
  FILE* file = fopen(filename, "rb");
  if (!file)
  {
    IupMessagef("Error", "Can't open file: %s", filename);
    return NULL;
  }

  /* calculate file size */
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  /* allocate memory for the file contents + nul terminator */
  str = (char*)malloc(size + 1);
  /* read all data at once */
  fread(str, size, 1, file);
  /* set the nul terminator */
  str[size] = 0;

  if (ferror(file))
    IupMessagef("Error", "Fail when reading from file: %s", filename);

  fclose(file);
  return str;
}


/********************************** FIM - Utilitários - abertura de arquivos txt - FIM *****************************************/





/*****************************************(     \IUP \CLOSE \SHOT \C  )********************************************

***/





/********************************** INÍCIO - Utilitários - encerramento do SHOT-C - INÍCIO *****************************************/

static int close_cb_OLD(Ihandle *ih) /*** ENCERRA JANELA ***/
{
    /* Executes IupMessage */
    IupMessage("Encerramento!","Finalizando janelas");

    return IUP_CLOSE;
}


static int close_cb(Ihandle* ih)
{
  int ret = IupAlarm("Encerramento!", "Encerrar o SHOT-C?", "Yes", "No", NULL);
  if (ret == 1) /* Yes Interrupt */
  {
    return IUP_CLOSE;
    printf("Encerrando...");
    //LongProcessing();

  }
  else
    return IUP_CONTINUE;
}



int quit_cb(void) /*** ENCERRA JANELA ***/
{
  return IUP_CLOSE;
}



/********************************** FIM - Utilitários - encerramento do SHOT-C - FIM *****************************************/









/*****************************************(     \INT \MAIN \DO \SHOT \C  )********************************************

***/








/********************************** Main ******************************************************************************************/

/*comentar aqui
    IupOpen(&argc, &argv); //aqui ele abre pela primeira vez, mas tu precisa mandar abrir novamente dps
    // CreateMainDialog();
    //me liguei como obter a próxima janela, a ideia é fazer entrar no loop, e travar com if,
    //permitindo assim entrar na janela principal

    LongProcessing();

    IupMainLoop();

    counter_release();

    //IupClose(); //é aqui que entra ...

*/ //comentar aqu
/********************************** Main ********************************************************************************************/

int main(int argc, char **argv)
{

    Ihandle *dlg, *button, *text, *hbox, *box;

    Ihandle *vbox, *multitext, *menu, *canvas; //note que o menu é um Ihandle, assim como os submenus e itens_menu
    Ihandle *sub_menu_file, *file_menu, *item_exit, *item_open, *item_saveas, *btn_open, *btn_save;
    Ihandle *sub_menu_edit, *edit_menu, *item_find, *item_goto, *btn_find;
    Ihandle *sub_menu_format, *format_menu, *item_font;
    Ihandle *sub_menu_about, *about_menu, *item_about, *item_license;
    Ihandle *lbl_statusbar, *toolbar_hb, *recent_menu;
    Ihandle *config, *button_close;
    Ihandle *frame, *label, *label2, *label3, *label4;
    Ihandle *button_run_simetric, *icon, *plot, *vboxSimetricas; //se liga o ícone da janela precisa ser declarado
    Ihandle *quit_bt, *item_undo;
    Ihandle *hboxFild1, *hboxFild2, *hboxFild3;
    Ihandle *frame2; //é daf matriz T
    Ihandle *hboxFild4, *hboxFild5, *hboxFild6, *vboxSimetricas2, *frame3;
    Ihandle *SymbolsDegree4, *SymbolsDegree5, *SymbolsDegree6;
    Ihandle *SymbolsDegree1, *SymbolsDegree2, *SymbolsDegree3;
    Ihandle *Ia0, *Ia1, *Ia2, *IgualText, *linha1, *linha2, *linha3, *plot_matrix;
    Ihandle *Ia, *Ib, *Ic, *plot2, *fracaoTerco, *Symbol_dot;
    Ihandle *separa1, *separa2, *separa3, *separa4, *separa5, *separa6;
    Ihandle *CurrentPhaseA, *CurrentPhaseB, *CurrentPhaseC, *anglePhasorIa, *anglePhasorIb, *anglePhasorIc;
    Ihandle *TextAnglePhasorIa, *TextAnglePhasorIb, *TextAnglePhasorIc, *TextIPhaseA, *TextIPhaseB, *TextIPhaseC;
    Ihandle *button_unlock, *button_run_phase, *button_reset, *hboxPhase, *hboxSimetricas2, *hboxSimetric_buttons;

    //Variáveis em 2022
    Ihandle *item_reset, *reset_menu, *sub_menu_reset;

    setlocale(LC_ALL, "Portuguese"); //funcionou 21abr22 22h

    IupOpen(&argc, &argv);
    IupImageLibOpen(); //INICIALIZA A BIBLIOTECA COM OS ÍCONES DO IUP = abrir, salvar, procurar ...ícones sobre controles especiais da matrix
    IupGLCanvasOpen(); //deve ser chamado após o IupOpen
    IupGLControlsOpen();
    IupControlsOpen();
    IupMglPlotOpen();     /* init IupMGLPlot library - coloquei pra pegar simbol TeX angle */

    /*INCIALIZAÇÃO DE OPERADORES*/
    init_matrix_T(); //Esta é a matriz complexa Matriz T

    IupSetGlobal("MGLFONTS", "../etc/mglfonts"); //na dúvida coloca, já que está perto da inicialização

    //canvas = IupGLCanvas(NULL); //importante, se tu não declarou lá embaixo contendo frames, tu precisa declarar aqui
    canvas = IupCanvas(NULL);
      //IupSetAttribute(canvas,"BGCOLOR","128 255 128"); //--- //As cores só estão funcionando sobre a IupDialog
      //IupSetAttribute(canvas,"SCROLLBAR","YES");
      //IupSetAttribute(canvas,"EXPAND","HORIZONTAL");
      //IupSetAttribute(canvas,"RASTERSIZE","x100");
      //IupSetAttribute(_cnv_1,"CANFOCUS","NO");
      //set_callbacks(canvas);
    IupSetAttribute(canvas,"MDICLIENT","YES"); //ATRIBUTO PARA VINCULAR A JANELA PRINCIPAL
                                               //IMPORTANTE SALIENTAR QUE NÃO É UMA NOVA JANELA, MAS O FUNDO DA JANELA PRINCIPAL
    //IupSetAttribute(canvas,"MDIMENU",NULL);

    //olha as atribuições lá embaixo

    config = IupConfig();
    IupSetAttribute(config, "APP_NAME", "simple_notepad"); //dá continuidade lá embaixo, ainda não sei pra que serve isso
    IupConfigLoad(config);

    /***************************************** INÍCIO DA IMAGEM/ÍCONE JANELA ************************************************/


    /* Creating dialog's icon */
  //icon = IupImage(32, 32, img); //ícone IUP é 32x32
  icon = IupImage(43, 32, img); //Temporário dps descobrir pq as letras estão segmentadas
  //icon = IupImage(32, 40, img);
  IupSetAttribute (icon, "1", "255 255 255");
  IupSetAttribute (icon, "2", "000 000 000");
  IupSetAttribute (icon, "3", "226 226 226");
  //IupSetAttribute (icon, "3", "255 00 0");
  //IupSetAttribute (icon, "3", "0 226 226");
  //IupSetAttribute (icon, "4", "128 128 128");
  IupSetAttribute (icon, "4", "255 000 000");
  //IupSetAttribute (icon, "5", "192 192 192");
  IupSetAttribute (icon, "5", "255 255 255");
  IupSetAttribute (icon, "6", "000 000 255");
  IupSetHandle ("icon_tag", icon); //Atenção, tag do ícone

  /* Creating dialog's content */
  quit_bt = IupButton("Quit", NULL); //note que quit_BT declarou-se agora, já a quit_CB já tá lá em cima!
  IupSetCallback(quit_bt, "ACTION", (Icallback)quit_cb); //tu pode chamar indiretamente usando Icallback na estrutura lá de cima
  IupSetHandle("quit", quit_bt); //intermediação para que seja possível atribuir à janela via char





    /*                                         MENU                                                  */
    /************************************ INÍCIO DO MENU ********************************************/

    //declarando os itens menu --- cuidado tu pode por lado a lado, tipo submenu = IupSubmenu("File", options);, options é outra coisa.

    //item_open = IupItem("Open...\tCtrl+O", NULL); //lembre-se disso, as opções que vão em cada botão do menu se chama IupItem
    //IupSetAttribute(item_open, "KEY", "O");

    item_open = IupItem ("Open", NULL);
    IupSetAttribute(item_open, "KEY", "O");
    IupSetCallback(item_open, "ACTION", (Icallback)blank_text);

    item_saveas = IupItem("Save As...\tCtrl+S", NULL);
    IupSetAttribute(item_saveas, "KEY", "S");
    IupSetCallback(item_saveas, "ACTION", (Icallback)blank_text);

    item_exit = IupItem("&Exit", NULL);
    //options = IupMenu(IupItem("Exit","quit_cb"),NULL); ...acima está sem função! (não está, o exemplo não é funcional)
    //item_exit = IupItem("&Exit", quit_bt); --- não funciona assim
   // item_exit = IupItem("&Exit", "quit_cb");//NÃO DÁ ERRO E NEM FUNCIONA COM "quit_cb"
    IupSetAttribute(item_exit, "KEY", "x"); //estava certo, é NULL mesmo, o atalho está na tecla
    //IupSetCallback(item_exit, "ACTION", (Icallback)quit_cb); //funcionou!
    IupSetCallback(item_exit, "ACTION", (Icallback)close_cb); //parece mais estável
    //IupSetCallback(item_exit, "ACTION", (Icallback)mdi_closeall);//precisa estar dentro do canvas??




    item_find = IupItem("&Find...\tCtrl+F", NULL);
    IupSetCallback(item_find, "ACTION", (Icallback)blank_text);


    item_goto = IupItem("&Go To...\tCtrl+G", NULL);
    IupSetCallback(item_goto, "ACTION", (Icallback)blank_text);


    item_font = IupItem("&Font...", NULL);
    IupSetCallback(item_font, "ACTION", (Icallback)blank_text);


    item_reset = IupItem("Close All Forms", "mdi_closeall_tag"); //tag
    //IupItem("Close All", "mdi_closeall"),
    //ENCERRAR OS FORMULÁRIOS MDI CHILD WINDOWS (DEVERIA)
    //IupSetFunction("mdi_closeall_tag", (Icallback)mdi_closeall);
    //IupSetCallback(item_reset, "ACTION", (Icallback)mdi_closeall);
    //NÃO VAI FUNCIONAR, PQ PRECISA ESTAR DENTRO DO CANVAS
    //NO CASO DESCOMENTAR A LINHA NO MDICHILD IMPEDIRIA A SOBREPOSIÇÃO DE JANELAS
    //ESTÁ TUDO SOB CONTROLE, MENOS MAU QUE DESCOBRI O MOTIVO
    IupSetCallback(item_reset, "ACTION", (Icallback)blank_text);


    item_about = IupItem("&UTFPR - TCC2...", NULL);
    IupSetCallback(item_about, "ACTION", (Icallback)about_text);

    item_license = IupItem("&Licenses...", NULL);
    IupSetCallback(item_license, "ACTION", (Icallback)about_licenses);

    item_undo = IupItem ("Undo", NULL);
    IupSetAttribute(item_undo, "KEY", "U");
    IupSetAttribute(item_undo, "ACTIVE", "NO");

    recent_menu = IupMenu(NULL);


    //APÓS DECLARADOS OS ITENS, TU PODE DECIDIR DISTRIBUIR EM MENUS E SUBMENUS!

    file_menu = IupMenu(
                    item_open,
                    item_saveas,
                    IupSeparator(),//SEPARADOR
                    IupSubmenu("Recent &Files", recent_menu),//note que acima o recente menu foi declarado como menu tipo NULL, daí vai aparecer uma seta
                    //item_undo,
                    item_exit,
                    NULL);

    edit_menu = IupMenu(
                    item_find,
                    item_goto,
                    NULL);

    format_menu = IupMenu(
                      item_font,
                      NULL);

    reset_menu = IupMenu(
                      item_reset,
                      NULL);
    about_menu = IupMenu(
                    item_about,
                    item_license,
                    NULL);


// FORMALIZANDO O MENU, DANDO NOME AOS SUBMENUS
    sub_menu_file = IupSubmenu("&File", file_menu); //IupSubmenu é o conteiner que recebe os menus, que doido
    sub_menu_edit = IupSubmenu("&Edit", edit_menu);
    sub_menu_format = IupSubmenu("&Format", format_menu);
    sub_menu_reset = IupSubmenu("&Reset", reset_menu);
    sub_menu_about = IupSubmenu("&About", about_menu);

//TESTE
  //  options = IupMenu(IupItem("Exit","quit_cb"),NULL); //o Exit recebe a função quit_cb

// FINALIZNDO O MENU COLOCANDO OS SUBMENUS NUM MESMO CONTAINER
    menu = IupMenu(
               sub_menu_file,
               sub_menu_edit,
               sub_menu_format,
               sub_menu_reset, //--- a curto prazo não tem utilidade, não fecha como um destroy, é só um x-close
               sub_menu_about,
               NULL);

//RASTREABILIDADE DO MENU
    IupSetHandle("menu", menu); //O de azul que é atribuido o menu acima

    //fim da declaração do menu, nada disso entra no vbox!


    /************************************ FIM DO MENU ********************************************/









    /*************************** JANELA PRINCIPAL - FRAME BOTÃO 1 - CURTO-CIRCUITO FASE-TERRA  **********************/
         Ihandle* btn_1;
         //Ihandle *box_mdi;


         //dlg = IupDialog(IupVbox(box, cnv, NULL));

         //btn_1 = IupButton("Calcular", NULL);
         btn_1 = IupButton("Calcular", "btn_1_tag"); //mesmo princípio de vinculação do IupItem
         //IupSetCallback(btn_1, "ACTION", (Icallback)btn_1_call); //Este call back é imediato
         //IupSetAttribute(bt2, "EXPAND", "YES");
         //IupSetAttribute(bt2, "ACTIVE", "NO");
         //IupSetHandle("btn_1_tag", btn_1);
         //IupSetFunction("btn_1_tag", (Icallback)btn_1_call); //A primeira maneira tbm é válida
         IupSetFunction("btn_1_tag", (Icallback)createForm_Shot_C_1fase_1_terra); //A primeira maneira tbm é válida
         //IupSetFunction("btn_1_tag", (Icallback)mdi_new); //A primeira maneira tbm é válida
         //IupSetCallback(btn_1, "ACTION", (Icallback)btn_1_call);
         //IupSetCallback(btn_1, "ACTION", (Icallback)btn_1_call);

         //SE LIGA, nos dois cenários, com ACTION e Function entra na função
         //o problema é outro (problema oculto)

         //IupSetCallback(button_reset, "ACTION", (Icallback) btn_run_reset);

         //box_mdi = IupHbox(bt_mdi, box_4, NULL); ...algum conflito aqui
         //box_mdi = IupHbox(btn_1, NULL);
         //IupSetAttribute(box_mdi,"MARGIN","5x5");

    /************************************ FIM BOTÃO 1 CURTO-CIRCUITO ********************************************/






    /*********************************** INÍCIO BOTÃO 2  CURTO-CIRCUITO ********************************************/
         Ihandle *btn_2; //É necessário porque a princípio serão formulários diferentes

         btn_2 = IupButton("Calcular", NULL);
         IupSetCallback(btn_2, "ACTION", (Icallback)createForm_Shot_C_2fase_2);
         //IupSetAttribute(bt2, "EXPAND", "YES");
         //IupSetAttribute(bt2, "ACTIVE", "NO");
         //IupSetHandle("btn_2_tag", btn_2);


    /************************************ FIM BOTÃO 2 CURTO-CIRCUITO ********************************************/







    /*********************************** INÍCIO BOTÃO 3  CURTO-CIRCUITO ********************************************/
         Ihandle *btn_3;

         btn_3 = IupButton("Calcular", NULL);
         IupSetCallback(btn_3, "ACTION", (Icallback)createForm_Shot_C_2fase_3_terra);
         //IupSetAttribute(bt2, "EXPAND", "YES");
         //IupSetAttribute(bt2, "ACTIVE", "NO");
         IupSetHandle("btn_3_tag", btn_3);


    /************************************ FIM BOTÃO 3 CURTO-CIRCUITO ********************************************/











    /*********************************** INÍCIO BOTÃO 4  CURTO-CIRCUITO ********************************************/
         Ihandle *btn_4;

         btn_4 = IupButton("Calcular", NULL);
         IupSetCallback(btn_4, "ACTION", (Icallback)createForm_Shot_C_3fase_4);
         //IupSetAttribute(bt2, "EXPAND", "YES");
         //IupSetAttribute(bt2, "ACTIVE", "NO");
         IupSetHandle("btn_4_tag", btn_4);


    /************************************ FIM BOTÃO 4 CURTO-CIRCUITO ********************************************/




    /*********************************** INÍCIO BOTÃO HOME  CURTO-CIRCUITO ********************************************/
         Ihandle *btn_home;

         btn_home = IupButton("PREENCHER FORMULÁRIO", NULL);
         IupSetCallback(btn_home, "ACTION", (Icallback)btn_HOME_call);
         //IupSetAttribute(bt2, "EXPAND", "YES");
         //IupSetAttribute(bt2, "ACTIVE", "NO");
         IupSetHandle("btn_home_tag", btn_home);
         IupSetAttributes(btn_home, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER");
         IupSetAttributes(btn_home,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\" "); //ficou combinando demais letras azuis


    /************************************ FIM BOTÃO HOME CURTO-CIRCUITO ********************************************/






    /************************************ ÍNICIO - JANELA PRINCIPAL - INÍCIO ***************************************/






    /************************************ INÍCIO FRAME 1 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_1;
         Ihandle *lbl_1;

         //Botão 1 está dentro deste frame 1

         lbl_1 = IupLabel("fase-terra");

         frame_1 = IupFlatFrame
              (
                IupVbox
                (
                 //IupSetAttributes(lbl, "EXPAND=YES, ALIGNMENT=ACENTER"),
                 //IupSetAttributes(lbl_1, "SIZE=15x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                 IupSetAttributes(lbl_1, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                 IupSetAttributes(btn_1, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"), //box_mdi = btn_1
                 //lbl,
                  NULL
                )
              );

          IupSetAttributes ( lbl_1,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\" ");
          //IupSetAttribute( lbl, "MARGIN", "100x");

          IupSetHandle("frame_1_tag", frame_1);


          IupSetAttribute(frame_1, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_1, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_1, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_1, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_1, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_1, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_1, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_1, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_1, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_1, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_1, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_1, "FRAMESPACE", "20"); //área frame bottom - ÁREA

    /************************************ FIM FRAME 1 CURTO-CIRCUITO ********************************************/





        /************************************ INÍCIO FRAME 2 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_2;
         Ihandle *lbl_2;

         lbl_2 = IupLabel("bifásico");

         frame_2 = IupFlatFrame
              (
                IupVbox
                (
                  //IupSetAttributes(lbl_2, "EXPAND=YES, ALIGNMENT=ACENTER"),
                  //IupSetAttributes(lbl_2, "SIZE=15x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                  IupSetAttributes(lbl_2, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  IupSetAttributes(btn_2, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  NULL
                )
              );

          IupSetAttributes ( lbl_2,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER");

          IupSetAttribute(frame_2, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_1, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_1, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_2, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_2, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_2, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_2, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_2, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_2, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_2, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_2, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_2, "FRAMESPACE", "20"); //área frame bottom - ÁREA


    /************************************ FIM FRAME 2 CURTO-CIRCUITO ********************************************/




    /************************************ INÍCIO FRAME 3 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_3;
         Ihandle *lbl_3;

         lbl_3 = IupLabel("bifásico-terra");

         frame_3 = IupFlatFrame
              (
                IupVbox
                (
                  //IupSetAttributes(lbl_2, "EXPAND=YES, ALIGNMENT=ACENTER"),
                  //IupSetAttributes(lbl_3, "SIZE=15x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                  IupSetAttributes(lbl_3, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  IupSetAttributes(btn_3, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  NULL
                )
              );

          IupSetAttributes ( lbl_3,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER");

          IupSetAttribute(frame_3, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_1, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_1, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_3, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_1, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_3, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_3, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_3, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_3, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_3, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_3, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_3, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_3, "FRAMESPACE", "20"); //área frame bottom - ÁREA


    /************************************ FIM FRAME 3 CURTO-CIRCUITO ********************************************/

    /************************************ INÍCIO FRAME 3 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_4;
         Ihandle *lbl_4;

         lbl_4 = IupLabel("trifásico");

         frame_4 = IupFlatFrame
              (
                IupVbox
                (
                  //IupSetAttributes(lbl_4, "EXPAND=YES, ALIGNMENT=ACENTER"),
                  //IupSetAttributes(lbl_4, "SIZE=15x15, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),
                  IupSetAttributes(lbl_4, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  IupSetAttributes(btn_4, "SIZE=10x10, EXPAND=YES, ALIGNMENT=ACENTER"),
                  NULL
                )
              );

          IupSetAttributes ( lbl_4,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER");

          IupSetAttribute(frame_4, "TITLE", "Curto-Circuito");
   //       IupSetAttribute(frame_4, "FGCOLOR", "0 0 0"); //vermelho letra
   //       IupSetAttribute(frame_4, "FONTSTYLE", "Bold");
          IupSetAttribute(frame_4, "FONTSIZE", "10"); //ainda bem que fica somente sob o título, poderia ser sob ambos
          //IupSetAttribute(frame_4, "BGCOLOR", "0 128 0"); //verde
          IupSetAttribute(frame_4, "BGCOLOR", "64 192 255"); //azul anil...estranho não funciona no lbl direto
          IupSetAttribute(frame_4, "FRAMECOLOR", "255 255 255"); //bordas frame
          IupSetAttribute(frame_4, "TITLELINECOLOR", "255 255 0");//divisória line frame

          IupSetAttribute(frame_4, "TITLEBGCOLOR", "64 128 255");//back ground abaixo da letra frame title, azul marinho
          IupSetAttribute(frame_4, "TITLECOLOR", "255 255 255");//título color frame letra - branca, padrão é preta
        //  IupSetAttribute(frame_1, "TITLELINE", "No");
          IupSetAttribute(frame_4, "TITLELINEWIDTH", "5"); //espessura linha divisória
          IupSetAttribute(frame_4, "FRAMEWIDTH", "5"); //espessura bordas linhas frame
          IupSetAttribute(frame_4, "FRAMESPACE", "20"); //área frame bottom - ÁREA


    /************************************ FIM FRAME 4 CURTO-CIRCUITO ********************************************/

    /************************************ INÍCIO FRAME 5 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_5;
         Ihandle *lbl_5;

         lbl_5 = IupLabel("Calculadora de curtos-circuitos simétricos e assimétricos no SEP"); // de obtenção

         /* Creates frame with a label */
         frame_5 = IupFrame
          (
            IupHbox
            (
              IupFill(),
              lbl_5,
              IupFill(),
              NULL
            )
          );
          //IupSetAttributes(lbl_4, "SIZE=30x30, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),


          IupSetAttributes ( lbl_5,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER");

          /* Sets frame's attributes */
          IupSetAttributes(frame_5, "FGCOLOR=\"255 0 0\", SIZE=EIGHTHxEIGHTH, TITLE=\"Software\", MARGIN=10x10");

          //Ihandle *label_text_1;
          //label_text_1 = IupLabel("Calculadora de exibição gráfica de modelos de sequência");
          //IupSetAttributes(label_text_1, "EXPAND=YES, ALIGNMENT=ACENTER");
          //IupSetAttribute(label_text_1, "MARGIN", "10x10");



    /************************************ FIM FRAME 5 CURTO-CIRCUITO ********************************************/


    /************************************ INÍCIO FRAME 6 CURTO-CIRCUITO ********************************************/
         Ihandle *frame_6;
         Ihandle *lbl_6;

         lbl_6 = IupLabel("Software de engenharia elétrica \n UTFPR - Todos direitos reservados");

         /* Creates frame with a label */
         frame_6 = IupFrame
          (
            IupHbox
            (
              IupFill(),
              lbl_6,
              IupFill(),
              NULL
            )
          );
          //IupSetAttributes(lbl_4, "SIZE=30x30, EXPAND=HORIZONTAL, ALIGNMENT=ACENTER"),


          IupSetAttributes ( lbl_6,"FONTSTYLE = Bold, FONTSIZE = \"12\", FGCOLOR = \"0 0 255\", ALIGNMENT = ACENTER"); //cuidado, as cores das letras devem ser editadas linha por linha

          /* Sets frame's attributes */
          IupSetAttributes(frame_6, "FGCOLOR=\"255 0 0\", SIZE=EIGHTHxEIGHTH, TITLE=\"Copyright\", MARGIN=10x10");


    /************************************ FIM FRAME 6 CURTO-CIRCUITO ********************************************/



    /**** \REMOVIDO - REMOÇÃO DE ALGUNS FRAMES
                      REMOÇÃO OBRIGATÓRIA SENÃO O PROGRAMA NÃO COMPILA!
    *****/



    /************************************ INÍCIO JANELA PRINCIPAL NEW (modelo 2) ********************************************/

    //box = IupVbox(label, NULL);
    box = IupVbox(NULL);
    IupSetAttribute(box, "MARGIN", "5x5");



    Ihandle *box_2, *box_3, *box_4;

    box_2 = IupHbox(frame_1, frame_2, NULL);
    IupSetAttribute(box_2, "MARGIN", "10x10"); //meio doido isso aqui, bug o tamnho dos frames... x10 é igual a 0x10
    IupSetAttribute(box_2, "GAP", "10");
    //IupSetAttribute(box_2, "ALIGNMENT ", "ACENTER");
    //IupSetAttributes ( box_2,"ALIGNMENT = ACENTER"); //funcionou nem no singular nem no plural
    //IupSetAttributes ( box_2,"SIZE=300x100, TITLE=\"Componentes Simétricas\", MARGIN=10x10");

    //monitorar aqui, pq se tu altera o conteiner ele muda aqui na exibição final

    box_3 = IupHbox(frame_3, frame_4, NULL);
    IupSetAttribute(box_3, "MARGIN", "10x10");
    IupSetAttribute(box_3, "GAP", "10");


    //box_4 = IupVbox(box_mdi, frame_5, box_2, box_3, frame_6, NULL);
    box_4 = IupVbox(frame_5, box_2, btn_home, box_3, frame_6, NULL);
    IupSetAttribute(box_4, "MARGIN", "5x5");
    IupSetAttribute(box_4, "GAP", "10");
    //não coloque abaixo pq senão não é exibido o botão bt_mdi



    /* Creating main dialog */
    //dlg = IupDialog(IupVbox(quit_bt,NULL)); //Está é outra maneira de criar uma janela vazia

    //canvas = IupGLCanvas(NULL); //ISSO AQUI É OBRIGATÓRIO - ESTILO AUTOCAD, CASO CONTRÁRIO USE UMA VBOX
                              //IupGLCanvas foi declarado lá em cima após definir Ihandle* canvas.
                              //AGORA QUE DEI FÉ, SE TU DECLARAR NOVAMENTE AQUI, TU MEIO QUE ZERA TUDO E CRIA UM AUTOCAD 2D...agora pq

    //CUIDADO, VC NÃO PRECISA DO CANVAS PARA GERAR FORMULÁRIOS, BOTÕES E FRAMES, EXCETO PARA MDI E DRAW
    //dlg = IupDialog(box); //neste caso para box = IupVbox(NULL); não é recebido um janela intermediária IupCanvas ou IupGLCanvas
    //dlg = IupDialog(IupVbox(quit_bt,NULL));
    //dlg = IupDialog(IupCanvas(""));//é equivalente ao IupCanvas (NULL)...vai estar vazio a janela, com padrão em branco...exceto se atribuir BGCOLOR à janela principal
    //dlg = IupDialog(canvas);      //A FUNÇÃO REDRAW LOGO ABAIXO QUE DESENHA OS CIRCUITOS...desfazer o comentário logo acima do canvasGL
    //dlg = IupDialog(label);         //AGORA CONSEGUI DESENHAR NUMA GL CANVAS E DEFINIR UMA POSIÇÃO NA JANELA PRINCIPAL USANDO O VBOX
    //dlg = IupDialog(label2);
    //dlg = IupDialog(IupSetAttributes(IupHbox(frame1, frame2, frame3, frame4, NULL), "NMARGIN=10x10"));
    //dlg = createFrame();
    dlg = IupDialog(box_4);
    //dlg = IupDialog(IupVbox(box_mdi, box_4, NULL));
    // IupDialog(IupVbox(quit_bt,NULL));
    //IupSetAttribute(dlg, "TITLE", "CURTO CIRCUITO :: HYAN");
    IupSetAttribute(dlg, "TITLE", "SHOT-C :: HYAN"); //Short-C ou Shot-C: tão leve quanto um flaming shot, e tão impactante quanto! (SE NÃO FOSSE O MGL...)
    IupSetAttribute(dlg,"MDIFRAME","YES"); //ATRIBUTO PARA CRIAÇÃO DE OUTRAS JANELAS
                                           //O GARGALO É QUE SÓ GERA A JANELA SE CRIAR UM CANVAS, OU SEJA, UM CANVAS DRAW INDIRETAMENTE
    //IupSetAttribute(dlg, "SIZE", "FULLxFULL");
    IupSetAttribute(dlg, "RASTERSIZE", "800x700"); //RASTER_SIZE
    IupSetAttributeHandle(dlg, "MENU", menu); //note que é Handle...aqui a janela recebe o menu...ou tu põe menu ou "menu"...em azul é definido pela tecgraf

    //IupSetHandle("mdiFrame_rasta", dlg); //RASTREABILIDADE
    IupSetHandle("mdiFrame", dlg); //ENTENDI!!! Aqui é uma tag mdiFrame, ou seja, a janela princiapal/primeira ou HOME tem a tag de rastreio mdiFrame

    //IupSetAttribute(dlg, "MARGIN", "10x10");
    //IupSetAttribute(dlg, "BGCOLOR", "121 154 183"); //peguei um exemplo do github e descobri como trocar a cor do fundo
    //IupSetAttribute(dlg,"BGCOLOR","255 255 128"); //As cores só estão funcionando sobre a IupDialog
    //IupSetAttribute(dlg,"BGCOLOR","0 255 128"); //Acima ficou fundão amarelo, agora ficou um verde limão, cuidado, aqui tu não está alterando a cor do canvas não fi
    //IupSetAttribute(dlg,"BGCOLOR","121 154 183");
    IupSetAttribute(dlg, "RESIZE", "YES");
    IupSetAttribute(dlg, "BORDER", "YES"); //Fica mais parecido com softwares modernos...estranho não está exibindo as bordas
    IupSetAttribute(dlg, "CURSOR", "CROSS"); //exibe um cursor cruz
    IupSetAttribute(dlg, "ICON", "icon_tag"); //definido lá no image icon ...TAG do ícone
    IupSetAttribute(dlg, "DEFAULTESC", "quit"); //o ESC está acionando um botão com a função quit, precisa ser intermediário char

    //IupSetAttribute(dlg,"SCROLLBAR","YES"); //não apareceu, nem as bordas
    //IupSetAttribute(dlg,"EXPAND","HORIZONTAL");
    //IupSetAttribute(dlg,"RASTERSIZE","x100");


    IupMap(dlg); //Mapear a janela principal para iniciar ações e configurações

    //Note ainda é SetAttribute
    IupSetAttribute(dlg, "CONFIG", (char*)config); //aqui vc transfere as definições do config para o dialog-windows

                                                  //depois de um tempão assimilei, ele pega o a atribuição config de font lá em cima,
                                                  //transforma numa string e joga para configuração da dlg

    /************************************ FIM JANELA ********************************************/



    //lembrar de voltar aqui após construir a função para descomentar

    /**** \CUIDADO \CRITICO - É OBRIGATÓRIO A REMOÇÃO DOS IUPSETCALLBACK S SENÃO O CÓDIGO NÃO COMPILA
                              NÃO ADIANTA ATENUAR CÓDIGO, REMOVER FRAMES, SE NÃO COMENTAR OU REMOVER NÃO COMPILA
    ****/


    /* parent for pre-defined dialogs in closed functions (IupMessage) */
    //IupSetAttributeHandle(NULL, "PARENTDIALOG", dlg); //assim tu zera os parentes


    /*****************************************************************/

          //  cdInitContextPlus();
          //  cdUseContextPlus(1);

    /************************************ INÍCIO CONSTRUÇÃO GEOMÉTRICA CIRCUITOS SEP ********************************************/
                                                /*** suprimido em 19abr22 ***/
    /************************************ FIM CONSTRUÇÃO GEOMÉTRICA CIRCUITOS SEP ***********************************************/

    //TRÊS ESTRUTURAS ABAIXO SÃO PADRONIZADAS
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER); //altere o nome do ponteiro janela...
    //IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    //IupConfigDialogShow(config, dlg, "MainWindow"); //isso é um Show e deixa a tela maximizada...transfere as definições do config para o dialog-windows
    IupMainLoop();
    IupClose();

    //CRIE UM WHILE QUE SEJA CAPAZ DE REINICIAR TODO O SOFTWARE
    //ACREDITO QUE COM UM CÓDIGO POR FUNÇÕES QUE NEM O DO MDI
    //EVITANDO-SE O CONSTRANGIMENTO DE TER QUE FECHAR E REABRIR O SOFTWARE
    return EXIT_SUCCESS;
}






/*****************************************(     \TOGGLES \ALTERNANCE  )********************************************

***/


void function_zerar_options_esquema_ligacao(int num_disparo)
{
    int i;
            for(i = 1; i < 12; i++){ //NÃO PODE COMEÇAR EM ZERO E MENOR QUE 12
               options_TR1[i].option = 0;
            }


}


void function_zerar_options_esquema_ligacao_envolvido(int num_disparo)
{
    int i;
            for(i = 1; i < 4; i++){ //NÃO PODE COMEÇAR EM ZERO E MENOR QUE 4
               options_TR1_envolvido[i].option = 0;
            }


}







static int function_memory_toggle_01_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle)
{
    //toggle_envolvido somente dispara, não é reutilizado, contudo é crítico, ele carrega a tag da ligação

    /*** \LASTRO \REATIVAR

    id_toggle_definition_tr1_envolvido é um marcador de toggle de LIGAÇÃO DO TRANSFORMADOR, entre os toggles das 3 ligações
    será definido um único id_toggle, e após apertar o botão definir entra na função do botão definir e fica bloqueado inserir novos trafos
    Ahhhh entendi, por isso deu comentei o uso desta função, pq estava impossibilitando inserir ligação diferentes de novos trafos

    ***/



    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido == 0){ //Esse id_toggle_definition é global de múltiplos acessos
        function_zerar_options_esquema_ligacao_envolvido(1);
        options_TR1_envolvido[1].option = 1;
        //id_toggle_esquema_TR1 = options_TR1[1].option;
        IupMessage("Aviso","Opção 1 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido != 0){ //Está temporariamente inativo, enquanto o botão definir estiver sem função
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1_envolvido == 0) //CONSEGUI!!!
        options_TR1_envolvido[1].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_02_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido == 0){
        function_zerar_options_esquema_ligacao_envolvido(1);
        options_TR1_envolvido[2].option = 2;
        //id_toggle_esquema_TR1 = options_TR1[2].option;
        IupMessage("Aviso","Opção 2 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1_envolvido == 0)
        options_TR1_envolvido[2].option = 0;

    return IUP_DEFAULT;
}



static int function_memory_toggle_03_TR1_envolvido(Ihandle *toggle_envolvido, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido == 0){
        function_zerar_options_esquema_ligacao_envolvido(1);
        options_TR1_envolvido[4].option = 4;
        //id_toggle_esquema_TR1 = options_TR1[4].option;
        IupMessage("Aviso","Opção 4 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1_envolvido != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1_envolvido == 0)
        options_TR1_envolvido[4].option = 0;

    return IUP_DEFAULT;
}




static int function_memory_toggle_01_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[1].option = 1;
        //id_toggle_esquema_TR1 = options_TR1[1].option;
        IupMessage("Aviso","Opção 1 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0) //CONSEGUI!!!
        options_TR1[1].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_02_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[2].option = 2;
        //id_toggle_esquema_TR1 = options_TR1[2].option;
        IupMessage("Aviso","Opção 2 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[2].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_02b_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[3].option = 3;
       // id_toggle_esquema_TR1 = options_TR1[3].option;
        IupMessage("Aviso","Opção 3 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[3].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_03_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[4].option = 4;
        //id_toggle_esquema_TR1 = options_TR1[4].option;
        IupMessage("Aviso","Opção 4 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[4].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_03b_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[5].option = 5;
        //id_toggle_esquema_TR1 = options_TR1[5].option;
        IupMessage("Aviso","Opção 5 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[5].option = 0;

    return IUP_DEFAULT;
}



static int function_memory_toggle_04_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[6].option = 6;
        //id_toggle_esquema_TR1 = options_TR1[6].option;
        IupMessage("Aviso","Opção 6 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[6].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_04b_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[7].option = 7;
        //id_toggle_esquema_TR1 = options_TR1[7].option;
        IupMessage("Aviso","Opção 7 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[7].option = 0;

    return IUP_DEFAULT;
}



static int function_memory_toggle_05_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[8].option = 8;
        //id_toggle_esquema_TR1 = options_TR1[8].option;
        IupMessage("Aviso","Opção 8 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[8].option = 0;

    return IUP_DEFAULT;
}



static int function_memory_toggle_06_TR1(Ihandle *toggle, int boolean_toggle)
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[9].option = 9;
        //id_toggle_esquema_TR1 = options_TR1[9].option;
        IupMessage("Aviso","Opção 9 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[9].option = 0;

    return IUP_DEFAULT;
}



static int function_memory_toggle_07_TR1(Ihandle *toggle, int boolean_toggle) //Ligação Y-Y //LIGAÇÃO EM STAND-BY
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[10].option = 10;
        //id_toggle_esquema_TR1 = options_TR1[10].option;
        IupMessage("Aviso","Opção 10 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[10].option = 0;

    return IUP_DEFAULT;
}


static int function_memory_toggle_08_TR1(Ihandle *toggle, int boolean_toggle) //Ligação Y-reator:Y-reator //LIGAÇÃO EM STAND-BY
{
    if(boolean_toggle == 1 && id_toggle_definition_tr1 == 0){
        function_zerar_options_esquema_ligacao(1);
        options_TR1[11].option = 11;
        //id_toggle_esquema_TR1 = options_TR1[11].option;
        IupMessage("Aviso","Opção 11 selecionada. Antes de prosseguir defina a ligação!");
    }
    if(boolean_toggle == 1 && id_toggle_definition_tr1 != 0){
        IupMessage("Aviso","Prossiga, ligação já foi definida!");
    }
    if(boolean_toggle == 0 && id_toggle_definition_tr1 == 0)
        options_TR1[11].option = 0;

    return IUP_DEFAULT;
}






static int function_memory_toggle_envolvente_TR1(Ihandle *toggle1_tr, int boolean_toggle, int status)//, int boolean_toggle)
{

//Ficou bem amarrado!

    /***

    Quando você clica para escolher o núcleo envolvente é criado o id_toggle_TR1 = 1 para que assim seja possível diferenciar
    qual formulário criar com as respectivas ligações do núcleo envolvente

    E somente depois de clicar no botão do frame do transformador que é gerado o formulário, então a função pega o marcador e decide

    ***/

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_TR1_nucleo = 1;
        IupMessagef("Aviso!","O tipo de núcleo do trafo é envolvente! value[%d].", id_toggle_TR1_nucleo); // value[%d]
    }

    return IUP_DEFAULT;
}


static int function_memory_toggle_envolvido_TR1(Ihandle *toggle1_tr, int boolean_toggle, int status)//, int boolean_toggle)
{

/*** Não tem outro jeito, os toggles no modo rádio não trabalham em conjunto, deve ter funções individualizadas ***/

//Ficou bem amarrado!

    /***

    Quando você clica para escolher o núcleo envolvido é criado o id_toggle_TR1 = 2 para que assim seja possível diferenciar
    qual formulário criar com as respectivas ligações do núcleo envolvido

    E somente depois de clicar no botão do frame do transformador que é gerado o formulário, então a função pega o marcador e decide

    ***/


    if(boolean_toggle==1){ //isso não é depuração...
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 1; ...daí eu carrego numa função de memória todos os atributos das ligações
        id_toggle_TR1_nucleo = 2; //variável é um marcador de status da ligação, poderia inclusiva compor um elemento da struct, não é o toggle em si
        IupMessagef("Aviso!","O tipo de núcleo do trafo é envolvido! value[%d].", id_toggle_TR1_nucleo); //value[%d]
    }

    return IUP_DEFAULT;
}






static int function_memory_toggle_Xg_sub(Ihandle *toggle_Xg_sub, int boolean_toggle, int status) /*** GERADOR X_subtransitoria ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xg = 1;
        IupMessagef("Aviso!","A reatância do gerador é a subtransitória X''! value[%d]", id_toggle_Xg);
    }

    return IUP_DEFAULT;
}




static int function_memory_toggle_Xg_trans(Ihandle *toggle_Xg_sub, int boolean_toggle, int status) /*** GERADOR X_transitoria ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xg = 2;
        IupMessagef("Aviso!","A reatância do gerador é a transitória X'! value[%d]", id_toggle_Xg);
    }

    return IUP_DEFAULT;
}



static int function_memory_toggle_Xg_sinc(Ihandle *toggle_Xg_sub, int boolean_toggle, int status) /*** GERADOR X_sincrona***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xg = 3;
        IupMessagef("Aviso!","A reatância do gerador é a síncrona Xs! value[%d]", id_toggle_Xg);
    }

    return IUP_DEFAULT;
}


static int function_memory_toggle_Y_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y puro ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_GE_estrela = 1;
        IupMessagef("Aviso!","O esquema de ligação do gerador é estrela sem neutro aterrado! value[%d]", id_toggle_GE_estrela);
    }

    return IUP_DEFAULT;
}

static int function_memory_toggle_Yat_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y-at ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_GE_estrela = 2;
        IupMessagef("Aviso!","O esquema de ligação do gerador é estrela com neutro aterrado! value[%d]", id_toggle_GE_estrela);
    }

    return IUP_DEFAULT;
}

static int function_memory_toggle_YZn_GE_estrela(Ihandle *toggle_GE_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y-Zn ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_GE_estrela = 3;
        IupMessagef("Aviso!","O esquema de ligação do gerador é estrela de um neutro aterrado com reator! value[%d]", id_toggle_GE_estrela);
    }

    return IUP_DEFAULT;
}


static int function_memory_toggle_Xm_sub(Ihandle *toggle_Xm_sub, int boolean_toggle, int status) /*** MOTOR X_subtransitoria ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xm = 1;
        IupMessagef("Aviso!","A reatância do motor é a subtransitória X''! value[%d]", id_toggle_Xm);
    }

    return IUP_DEFAULT;
}





static int function_memory_toggle_Xm_trans(Ihandle *toggle_Xm_sub, int boolean_toggle, int status) /*** MOTOR X_transitoria ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xm = 2;
        IupMessagef("Aviso!","A reatância do motor é a transitória X'! value[%d]", id_toggle_Xm);
    }

    return IUP_DEFAULT;
}



static int function_memory_toggle_Xm_sinc(Ihandle *toggle_Xm_sub, int boolean_toggle, int status) /*** MOTOR X_sincrona***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_Xm = 3;
        IupMessagef("Aviso!","A reatância do motor é a síncrona Xs! value[%d]", id_toggle_Xm);
    }

    return IUP_DEFAULT;
}




static int function_memory_toggle_Y_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y puro --- IMPORTANTE, o toggle só alterna se o Ihandle for igual***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_MOTOR_estrela = 1;
        IupMessagef("Aviso!","O esquema de ligação do motor é estrela sem neutro aterrado! value[%d]", id_toggle_MOTOR_estrela);
    }

    return IUP_DEFAULT;
}

static int function_memory_toggle_Yat_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y-at ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_MOTOR_estrela = 2;
        IupMessagef("Aviso!","O esquema de ligação do motor é estrela com neutro aterrado! value[%d]", id_toggle_MOTOR_estrela);
    }

    return IUP_DEFAULT;
}

static int function_memory_toggle_YZn_MOTOR_estrela(Ihandle *toggle_MOTOR_estrela, int boolean_toggle, int status) /*** LIGAÇÃO Y-Zn ***/
{

    if(boolean_toggle==1){
        //matrix_struct[0][1].trafo_indices.ligacao_nucleo = 2;
        id_toggle_MOTOR_estrela = 3;
        IupMessagef("Aviso!","O esquema de ligação do motor é estrela de um neutro aterrado com reator! value[%d]", id_toggle_MOTOR_estrela);
    }

    return IUP_DEFAULT;
}



