#include <string.h> /* strlen() */
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

    while (cont < strlen(string) - 1)
    {
        if(string[cont] > 57 || string[cont] < 40)
            return FALSE;
              
        cont++;
    }

    return TRUE;
}


void removeAllSpaces(char *String){
    char tempString[strlen(String)];

    int contString = 0,contTemp = 0;

    while (contString < strlen(String) - 1)
    {
        if(String[contString] != ESPACE){
                tempString[contTemp++] = String[contString];
        }
            
        contString++;
    }
    
    contString = 0;

    while (contString < contTemp)
    {
        String[contString] = tempString[contString];
        ++contString;
    }

    String[contTemp +1 ] = '\0';
 
}

void imprimePilha(PILHA pilha){
    int i;

    i = 0;

    if(pilha.topo == 0 ){
        printf("pilha vazia !! \n");
    }else{
        printf("pilha: \n");

        for (i = 0 ; i < pilha.topo; i++)
        {
            printf("%c ,",pilha.elemento[i]);
        }
    }
}