#ifndef validador.
#define validador

#define TAMANHO 100 /* um tamnho maximo definido para a string de entrada*/
#define ESPACE 32 /* caractere espaco*/

/* enumerador que armazenara valores "logicos" */
typedef enum 
{ 
   FALSE = 0 , 
   TRUE = 1 
} Boolean;

/* definicao de uma estrutrutura do tipo PILHA*/
typedef struct _pilha
{
   int topo;
   char elemento[TAMANHO];
}PILHA;

/* **************************   FUNCTIONS *******************************************/


 /*	|------------ adiciona espacos  ----------------------|
	|		adiciona os espacos corretamente 		       |
    |    Recebe: char  referente a equacao digitada       |
    |    pelo usuario;                                    |
    |    retorna: VOID                                    |
    |-----------------------------------------------------|
*/

void adicionaEspacos(char *);

/* |--------------- CalcPosFixa  --------------------------------|
	|		realiza o calculo de uma equacao pos-fixa              |
   |    Recebe: ponteiro char que armazena a equcacão infixa    |
   |    retorna: Float com o resultado                          |
   |-----------------------------------------------------------|
*/
float calcPosFixa(char *);

/* |--------------- concatena  --------------------------------|
	|		Realiza a concatenacao de duas strings                |
   |    Recebe: um ponteiro char destino, um ponteiro          |
         para char origem, um inteiro que sera a ultima posicao| 
         do destino e um inteiro com o tamanho do destino      |
   |    retorna: void;                                         |
   |-----------------------------------------------------------|
*/
void concatena(char * , char *, int ,unsigned int );

/* |--------------- Pop  --------------------------------|
	|		Transforma uma equacao infixa para pos fixa     |
   |    Recebe: ponteiro char referente a string         |
   |   digitada pelo usuario                             |
   |    retorna: VOID                                    |
   |-----------------------------------------------------|
*/
void converteInfixa(char *);

 /* |--------------- Init  -------------------------------|
	 |		   inicia uma pilha, colocando o topo        |
    |    Recebe: ponteiro de uma pilha                    |
    |    retorna: void                                 |
    |-----------------------------------------------------|
*/
void init(PILHA *);

/* |--------------- ehOperador  --------------------------------|
	|		verifica se o elemento passado é um operador           |
   |    Recebe: char                                             |
   |    retorna: Boolean                                        |
   |-----------------------------------------------------------|
*/
Boolean ehOperador(char);


/* |--------------- PilhaPrioridade  --------------------|
	|		Verifica a ordem de prioridade de dois elementos|
   |    Recebe: dois char, cada um contento um operador  |
   |    retorna: Boolean                                |
   |----------------------------------------------------|
*/
Boolean PilhaPrioidade(char ,char );

 /* |--------------- Pop  -------------------------------|
	 |		Remove um elemento ao topo da pilha            |
    |    Recebe: ponteiro de uma pilha                    |
    |    retorna: Boolean                                 |
    |-----------------------------------------------------|
*/
Boolean Pop(PILHA *, char *);

 /* |--------------- Push  -------------------------------|
	 |		Adiciona um elemento ao topo da pilha            |
    |    Recebe: ponteiro de uma pilha                    |
    |    retorna: Boolean                                 |
    |-----------------------------------------------------|
*/
Boolean Push(PILHA *, char);


 /*	|------------ Remove all spaces ----------------------|
	|		remove os espacos da string de entrada 		  |
    |    Recebe: char  referente a equacao digitada       |
    |    pelo usuario;                                    |
    |    retorna: VOID                                    |
    |-----------------------------------------------------|
*/
void removeAllSpaces(char *);

/* |--------------- returnTop  --------------------------------|
	|		retorna o elemento no topo da pilha                   |
   |    Recebe: PILHA                                         |
   |    retorna: char refereten ao elemento                    |
   |-----------------------------------------------------------|
*/
char returnTop(PILHA );

 /*	|------------ Validate digits ----------------------|
	|		verifica se ha carateres irregulares		|
    |    Recebe: char  referente a equacao digitada      |
    |    pelo usuario;                                   |
    |    retorna: um Booleano FALSE ou TRUE              |
    |---------------------------------------------------|
*/
Boolean validateDigits(char *);

/* |--------------- Pop  --------------------------------|
	|		Verifica os fechamentos e aberturas dos         | 
   | parentesis                                         |
   |    Recebe: ponteiro char referente a string         |
   |   digitada pelo usuario                              |
   |    retorna: Boolean                                |
   |----------------------------------------------------|
*/
Boolean verificaAberturas(char *);

#endif /* Validador.h */