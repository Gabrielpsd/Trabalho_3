#include <string.h> /* strlen() */
#include <stdlib.h>
#include <stdio.h>

#include "validador.h"

#define ESPACE 32 


int countString(char *String){

    int size = 0; 

    while (String[size] != '\0')
    {
        size++;
    }

    return size;

}

//se retorno =0 há caracteres incalculaveis

bool validateDigits(char *string){

    int cont = 0;

    while (string[cont] != '\0')
    {
        if(!ehOperando(string[cont]))
            if(string[cont] < 48 || string[cont] > 57)
                return FALSE;
              
        cont++;
    }

    return TRUE;
}


void removeAllSpaces(char *String){
    char tempString[strlen(String)];

    int contString = 0,contTemp = 0;

    while (String[contString] != '\0')
    {
        if(String[contString] != ESPACE){
                tempString[contTemp] = String[contString];
                contTemp++;
        }
            
        contString++;
    }
    
    tempString[contTemp] = '\0';

    strcpy(String,tempString);

    /*
    contString = 0;

    while (contString < contTemp)
    {
        String[contString] = tempString[contString];
        ++contString;
    }
    */
    String[contTemp + 1 ] = '\0';
 
}

void imprimePilha(PILHA pilha){
    int i;

    i = 0;
    printf("imprimindo a pilha: ");
    if(pilha.topo == 0 ){
        printf("pilha vazia !! \n");
    }else{
        printf("pilha: \n");

        for (i = 0 ; i < pilha.topo; i++)
        {
            putchar(pilha.elemento[i]);
        }
    }
}

/* funcao que ira adicoinar espacos entre os caracteres para que possa-se trabalhar com caracteres de mais de um digito*/
void adicionaEspacos(char *String)
{
    printf("Tamanho do vetor alocado: %d \n",strlen(String));

    char *tempString;
    printf("Entrei com essa string: %s!\n",String);

    int contString = 0,contTemp = 0;

    tempString = (char *) malloc(sizeof(int) * 1);

    printf("dentro da funcao: ");
    while (String[contString]!= '\0')
    {
        if (String[contString] == '(' || String[contString] == ')')
        {
            tempString = (char *)realloc(tempString, (sizeof(char)) * (contTemp+3));
                tempString[contTemp] = ' ';
                printf("%c", tempString[contTemp]);
                contTemp++;
                tempString[contTemp] = String[contString];
                printf("%c", tempString[contTemp]);
                contString++;
                contTemp++;
                tempString[contTemp] = ' ';
                printf("%c", tempString[contTemp]);
                contTemp++;
        }
        else
        {

            if(ehOperando(String[contString]) && tempString[contString-1] != ESPACE){
                tempString = (char *)realloc(tempString, (sizeof(char)) * (contTemp+3));
                tempString[contTemp] = ' ';
                printf("%c", tempString[contTemp]);
                contTemp++;
                tempString[contTemp] = String[contString];
                printf("%c", tempString[contTemp]);
                contString++;
                contTemp++;
                tempString[contTemp] = ' ';
                printf("%c", tempString[contTemp]);
                contTemp++;
        }else{
            tempString = realloc(tempString,sizeof(char) * (contTemp+1));
                tempString[contTemp] = String[contString];
                printf("%c", tempString[contTemp]);
                contString++;
                contTemp++;
        }
        }
        
        
    }
    
    tempString[contTemp] = '\0';

    printf("\ntamnho da string de saida: %d ", contTemp);
    printf("String saida: %s!\n",tempString);

    String =(char *) calloc(contTemp,sizeof(char));

    contTemp = 0;
    String = tempString;
    /*
    while (tempString[contTemp] != '\0')
    {
        String[contTemp] = tempString[contTemp];
        ++contTemp;
    }
    */
    String[contTemp] = '\0';
}
