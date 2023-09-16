/* 

	programa: Quadrado animado 
	Descrição: O programa é uma janela que abre no prompt de comando do computador, essa janela sera interativa e  o usuario podera mudar sua cor e seu tamanho
	dentro dessa janela havera um quadrado que ficara se movimentando esse quadrado pode ter suas propriedade de direção e velocidade alteradas pelo usuario caso ele 
	assim dejesar e entrar com as teclas corretas;
	Programador: Gabriel Pereira dos Santos Dias
	data de modificação: 01/05/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe  validador.c -Wall -Werror -Wextra -pedantic


	
	link do repositorio: https://github.com/Gabrielpsd
	
*/

#include <stdio.h> /*fgets, printf, putchar*/
#include <string.h> /* strcpy , */

#include "validador.h"

int main(int argc, char **argv)
{
	/*declaração das variaveis utilizadas na função */
	char entrada[TAMANHO],element[TAMANHO];
	int i;

	/* artificio para remover Warning */
	argc = argc;
	argv = argv;
	
	/* entrada de dados do usuario */
	printf("Digite um elemento: ");
	fgets(entrada, TAMANHO-1, stdin);
	entrada[strlen(entrada) - 1 ] = '\0';

	/* é bom manter os dados originais digitado pelo usuario, então
	armazenamo-os em uma variavel auxiliar*/ 
	strcpy(element,entrada);
	
	/* removemos todos os espacos*/
	removeAllSpaces(element);
	printf("aqui (0) %s \n",element);
	/* adicionamo-os novamente*/
	adicionaEspacos(element);
	printf("aqui (1) %s \n",element);
	/* validamos os digitos da entrada para garantir que não há erro algum*/
	if(!validateDigits(element))
	{	
		/* se tiver erro caira aqui*/	
		printf("ha carateres incalculaveis no sistema \n");
	}
	else
	{
		/* se não tiver erro vem para ca
		verificamos os pares de parentesis antes de prosseguir*/
		if(verificaAberturas(element))
		{
			/* se as aberturar e fechamentos dos parentesis estiverem ok, caimos aqui*/
			/* se estiver ok podemos passa-la para infixa sem problema */
			converteInfixa(element);
				printf("aqui (2)\n");
			i = 0;
			printf("String pos fixa: ");
			/* imrpimimos a funcao pos fixa, digito a digito*/
			while (element[i] != '\0')
			{
				putchar(element[i]);
				i++;
			}


			printf("\n");			
			printf("Resultado: %.2f",calcPosFixa(element));
		}
		else 
			/* se o fechamento dos parentesis estiverem incorretos cairemos aqui*/
			printf("a elementos incorretos");
	}

	return 0 ;
}