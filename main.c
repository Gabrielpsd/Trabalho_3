/* 

	programa: Quadrado animado 
	Descrição: O programa é uma janela que abre no prompt de comando do computador, essa janela sera interativa e  o usuario podera mudar sua cor e seu tamanho
	dentro dessa janela havera um quadrado que ficara se movimentando esse quadrado pode ter suas propriedade de direção e velocidade alteradas pelo usuario caso ele 
	assim dejesar e entrar com as teclas corretas;
	Programador: Gabriel Pereira dos Santos Dias
	data de modificação: 01/05/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe  validador.c preProcessamento.c conio_v3.2.4.c 
	
	
	 -Wall -Werror -Wextra -pedantic -lwinmm  
	
	link do repositorio: https://github.com/Gabrielpsd
	
*/

#include <stdio.h>
#include <string.h>

#include "conio_v3.2.4.h"
#include "validador.h"
#include "preProcessamento.h"


int main(int argc, char **argv){

	argc = argc;
	argv = argv;

	char inputString[TAMANHO], secString[TAMANHO];
	char c[TAMANHO],element[TAMANHO];
	int i,resultado;

	printf("Digite um elemento: ");
	fgets(c, TAMANHO-1, stdin);
	c[strlen(c) - 1 ] = '\0';
	/*
	printf("Antes da FORMATACAO\n ");
	printf("%s ", c);
	printf("Tamanho: %d \n",strlen(c));
	*/

	//removeAllSpaces(c);

	/*
	printf("apos da FORMATACAO\n ");
	printf("%s ", c);
	printf("Tamanho: %d \n",strlen(c));
	*/
	strcpy(element,c);

	if(validateDigits(c))
		concatena(element,c,0,TAMANHO);
	else
	{
		printf("ha carateres incalculaveis no sistema \n");
	}
	
	printf("trabalhar com essa: ");
	printf("%s \n", element);
	printf("Tamanho: %d \n",strlen(element));
	

	if(verificaAberturas(element)){
		printf("expressao bem formada !!\n");
		converteInfixa(element);
		i = 0;
		printf("String final: ");
		while (element[i] != '\0')
		{
			putchar(element[i]);
			i++;
		}

		calcPosFixa(element);
			
	}else 
		printf("a elementos incorretos");
		
return 0 ;
}