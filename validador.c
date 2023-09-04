#include <math.h> /* pow()*/
#include <string.h>
#include <stdlib.h>

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
        
        //imprimePilha(pilha);

        if (expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{')
        {
            if(Push(&pilha,expressao[i]) == FALSE)
                return FALSE;
        }
        else 
        {
            if(expressao[i] == ')' || expressao[i] == '}' || expressao[i] == ']'){
                if(Pop(&pilha,&auxiliar)){
                    switch (expressao[i])
                    {

                    case ')':
                        if(auxiliar != '(')
                            return FALSE;
                        else 
                            return TRUE;
                        break;

                    case '}':

                        if(auxiliar != '{')
                            return FALSE;
                        else 
                            return TRUE;
                        break;

                    case '[':

                        if(auxiliar != ']')
                            return FALSE;
                        else 
                            return TRUE;
                        break;
                    }
                }else 
                    return FALSE;
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
        //printf("to aqui (0)");
        if (equacao[i] < '9' && equacao[i] > '0') saida[j++] = equacao[i++];
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
    
        //printf("to aqui (3)\n");
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
                         case '-': return 1; 
                         case '*':
                         case '/': return 0; 
                 }
            case '-':
                 switch (string2)
                 { 
                         case '+':
                         case '-': return 1; 
                         case '*':
                         case '/': return 0; 
                 }
            case '*':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                 }
            case '/':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                 }
            case '$':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                 }
            case '(':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 1;
                 }
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
            prinf("char em char: %d \n",elemento1);
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

            Push(&pilha,(char)resultado);
        }
    }
    
    return resultado;
}