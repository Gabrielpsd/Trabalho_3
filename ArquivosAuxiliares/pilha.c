#include "pilha.h"
#include <stdio.h>

int Push(Pilha *P, int elemento)
{
    if (P->topo == TAMANHO_PILHA) return 0;
    else
    {
        P->elementos[P->topo] = elemento;
        P->topo++;
        return 1;
    }
}

int Pop(Pilha *P, int *elemento)
{
    if (P->topo == 0) return 0;
    else
    {
        P->topo--;
        *elemento = P->elementos[P->topo];
        return 1;
    }
}

void InitPilha(Pilha *P)
{
     P->topo = 0;
}
