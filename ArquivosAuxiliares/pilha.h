
#ifndef PILHA

#define PILHA
#define TAMANHO_PILHA 10

typedef struct{
               int topo;
               int elementos[TAMANHO_PILHA];
              }Pilha; 

int Push(Pilha *, int);
int Pop(Pilha *, int *);
void InitPilha(Pilha *);

#endif

