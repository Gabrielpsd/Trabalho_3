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
    char saida[TAMANHO], auxiliar, *pt;
    int i, j;

    //iniciando as variaveis
    saida[0] = '\0';

    init(&pilha);
    i = j = 0;

    pt = strtok(equacao, " ");

    while (pt)
    {  

        /* printf("inicio elemento: \n");
        printf("pt: %s\n",pt);
        printf("tamanho PT: %d \n",strlen(pt)); */

        if (ehOperando(pt[0]) == FALSE)
        {   
            
        //printf("concatenando: %s com %s \n", saida,pt);
            //strcat(saida,pt);
        concatena(saida , pt,j, TAMANHO);
        //printf("concatenada: %s\n",saida);
            //printf(" saida: %s\n",saida); 
            j += strlen(pt);
            /* printf("tamanho saida: %d \n",strlen(saida));
            printf("tamanho j : %d  \n",j); */
            saida[j++] = ' ';
        } 
        else
        {   
            
            if(pt[0] == ')')
            {   
                Pop(&pilha,&auxiliar);
                while(auxiliar != '(')
                {   

                    saida[j++] = auxiliar;
                    saida[j++] = ' ';
                    Pop(&pilha,&auxiliar);
                }

                ++i;

            }
            else
            {

            // printf("to aqui (1)\n");
                    if (pilha.topo != 0 && PilhaPrioidade(pt[0], returnTop(pilha))){
                        Pop(&pilha,&auxiliar);
                        saida[j++] = auxiliar;
                        saida[j++] = ' ';
                        //printf("to aqui (2)\n");
                    }

                Push(&pilha,pt[0]);
            }

            /* printf("Topo pilha: %c \n", returnTop(pilha)); */
        }

        pt = strtok(NULL ," ");
       /*  printf("tamanho de j apos espaco: %d ",j);
        printf("------------------\n"); */
    }

    /* printf("tamanho saida: %d ", strlen(saida));
    printf("saida:%st", saida); */
    
    j = j - 1;
    
    while (pilha.topo > 0)
    {   
        saida[j++] = ' ';
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
bool PilhaPrioidade(char string1,char string2){

    switch (string1)
    {
            case '+':
                 switch (string2)
                 { 
                        
                        default:
                            return TRUE;
                 }
            case '-':
                 switch (string2)
                 {  
                        default: TRUE; 
                 }
            case '*':
                 switch (string2)
                 { 
                         case '+':
                         case '-': return TRUE;
                         case '*':
                         case '/': 
                         case '$':
                            return FALSE;
                        
                 }
            case '/':
                 switch (string2)
                 { 
                         case '+':
                         case '-': return TRUE; 
                         case '*':
                         case '/': 
                         case '$':
                            return FALSE;

                 }
            case '$':
                 switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': 
                         case '$': return TRUE;
                 }
            case '(':
                return FALSE;
    }
}

char returnTop(PILHA pilha){
    char auxiliar;
    Pop(&pilha,&auxiliar);
    Push(&pilha,auxiliar);
    return auxiliar;
}

float calcPosFixa(char *equacao)
{
    int i,j;
    char operador, *pt;
    float *Result, elemento1 , elemento2, resultado; 

    i = 0;
    pt = strtok(equacao, " ");

    Result = (float *) realloc(Result, sizeof(float) * (i + 1));

    while(pt)
    {   
        if(ehOperando(pt[0]) == FALSE)
        {  
            Result = (float *) realloc(Result, sizeof(float) * (i + 1));
            Result[i] = atof(pt);
            ++i;
        }
        else
        {   
             j = 0;
            printf("\n---------------\n");
            printf("Atualmente: \n");
            while (j < i)
            {
                printf("%.2f ", Result[j]);
                j++;
            }
            printf("Valor de i: %d ", i);
            printf("Operador: %c ",pt[0]);
            printf("\n---------------\n") ; 
           elemento1 = Result[--i];

                 resultado = elemento1;
              //printf("number: %.2f \t",elemento1);
                elemento2 = Result[--i];
                //printf("number: %.2f \t\n",elemento2);
                operador = pt[0];

           
                switch (operador)
                {
                case '+':
                    resultado = elemento1 + elemento2;
                printf("Resultado soma: %.2f\n",resultado);
                    break;
                case '-':
                    resultado = elemento2 - elemento1;
                printf("Resultado sub: %.2f\n",resultado);
                    break;
                case '*':
                    resultado = elemento1 * elemento2;
                printf("Resultado multi: %.2f\n",resultado);
                    break;
                case '/':
                    if (elemento2 == 0)
                    {
                        printf("Ocorreu alguma divisão por ZERO");
                        exit(1);
                    }
                    resultado = elemento2 / elemento1;
                    break;
                case '$':
                    resultado = pow(elemento2 ,elemento1);
                    break;

                default:
                    break;
                }
           

            //printf("Atribuindo a posicao: %d ", i);
            Result[i++] = resultado;
        }

        pt = strtok(NULL," ");
    }

    return Result[0];
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

void concatena(char *dest , char *scr, int lastScr, int tamanhoDest)
{
    int tamanho, auxiliar, i;

    tamanho = strlen(scr);

    auxiliar = lastScr;
    i = 0;

    if(strlen(dest) < tamanhoDest)
        while (scr[i] !='\0' && i < tamanho)
        {
            //printf("Passado %c para %s ",scr[i], dest);
            dest[auxiliar++] = scr[i++];
        }

}