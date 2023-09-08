#include <math.h> /* pow()*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "validador.h"
#include "preProcessamento.h"

void init(PILHA *Pilha){
    Pilha->topo = 0;
}

bool Push(PILHA *pilha, char element){

    if(pilha->topo == TAMANHO) return FALSE;
    else
    {
        pilha->elemento[pilha->topo] = element;
        pilha->topo++;

        return TRUE;
    }

}


bool Pop(PILHA *pilha,char *element){

    if(pilha->topo == 0 ) return FALSE;
    else{
        
        *element = pilha->elemento[--pilha->topo];
        return TRUE;
    }
}

bool verificaAberturas(char *expressao){
    PILHA pilha;
    int i;
    char auxiliar;

    init(&pilha);
    
    for(i =0; i< strlen(expressao)- 1; ++i ){
        
        if (expressao[i] == '(' )
        {
            if(Push(&pilha,expressao[i]) == FALSE)
                return FALSE;
        }
        else 
        {
            if(expressao[i] == ')')
            {
                if(Pop(&pilha,&auxiliar) == FALSE)
                {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

void converteInfixa(char *equacao){

    PILHA pilha;
    char saida[TAMANHO], auxiliar;
    int i, j;

    //iniciando as variaveis
    
    init(&pilha);
    i = j = 0;

    while (equacao[i])
    {
        if (ehOperando(equacao[i]) == FALSE)
        {
            saida[j++] = equacao[i++];
        } 
        else
        {   

            if(equacao[i] == ')')
            {   
                Pop(&pilha,&auxiliar);
                while(auxiliar != '(')
                {   

                    saida[j++] = auxiliar;

                    Pop(&pilha,&auxiliar);
                }

                ++i;

            }
            else
            {
            // printf("to aqui (1)\n");
                    if (pilha.topo != 0 && definePrioridade(equacao[i], returnTop(pilha))){
                        Pop(&pilha,&auxiliar);
                        saida[j++] = auxiliar;
                        //printf("to aqui (2)\n");
                    }

                Push(&pilha,equacao[i++]);
            }
        }

        saida[j++] = ' ';
    }


    while (pilha.topo > 0)
    {   

        Pop(&pilha,&auxiliar);
        saida[j++] = auxiliar;
        //printf("to aqui (4)\ntopo: %d",pilha.topo);
    }
    
    saida[j] = '\0';

    strcpy(equacao,saida);

}

/* caso o elemento que esteja na minha pilha tenha mais prioridade do que o elemento que 
tem na minha equaçaõ, logo preciso colocar ele na string de saída pois na na hora de resolver a equacao pos-fixa 
ele precisa aprecer primeiro*/
bool definePrioridade(char string1,char string2){

    switch (string1)
    {
            case ' ':
                 switch (string2)
                 { 
                         case '+':
                         case '-':
                         case '*':
                         case '/': return 1;
                 }
            case '+':
                 switch (string2)
                 { 
                         case '+':
                         case '-': return 0; 
                         case '*':
                         case '/': return 1; 
                 }
            case '-':
                 switch (string2)
                 { 
                         case '+':
                         case '-': return 0; 
                         case '*':
                         case '/': return 1; 
                 }
            case '*':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                         default:
                            return 0;
                 }
            case '/':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                         default: 
                            return 0;
                 }
            case '$':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': 
                         case '$': return 1;
                         default: return 0;
                 }
            case '(':
                return 0;
    }
}

char returnTop(PILHA pilha){
    char auxiliar;
    Pop(&pilha,&auxiliar);
    Push(&pilha,auxiliar);
    return auxiliar;
}

int calcPosFixa(char *equacao)
{
    int i, elemento1, elemento2,resultado;
    PILHA pilha;
    char operador;

    i = 0;
    while (equacao[i])
    {
        if(equacao[i] >=  '0' && equacao[i] < '9'){
            Push(&pilha,equacao[i]);
        }
        else
        {
            Pop(&pilha,&operador);
            elemento1 = atoi(&operador);

            Pop(&pilha,&operador);
            elemento2 = atoi(&operador);

            operador = equacao[i];

            switch (operador)
            {
            case '+':
                resultado = elemento1 + elemento2;
                break;
            case '-':
                resultado = elemento1 - elemento2;
                break;
            case '*':
                resultado = elemento1 * elemento2;
                break;
            case '/':
                resultado = elemento1 / elemento2;
                break;
            case '$':
                resultado = pow(elemento1 ,elemento2);
                break;

            default:
                break;
            }

            Push(&pilha,resultado + '0');
        }

        ++i;
    }

    return pilha.elemento[pilha.topo] - '0';
}

bool ehOperando(char Valor){

    switch (Valor)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '$': 
    case '(':
    case ')':
        return TRUE;
    default:
        return FALSE;
    }
}