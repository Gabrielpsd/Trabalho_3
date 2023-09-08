#ifndef validador
#define validador

#define TAMANHO 255

typedef struct 
{
   int topo;
   char elemento[TAMANHO];
}PILHA;

typedef enum {FALSE, TRUE} bool;


/* **************************   FUNCTIONS *******************************************/
void init(PILHA *);

bool Push(PILHA *, char);

bool Pop(PILHA *, char *);

bool verificaAberturas(char *);

void converteInfixa(char *);

bool definePrioridade(char string1,char string2);

char returnTop(PILHA );

bool ehOperando(char);
#endif /* quadradoAnimado */ 