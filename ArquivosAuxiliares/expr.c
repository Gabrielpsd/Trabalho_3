#include <stdio.h> /* printf(); scanf() */
#include "pilha.h" /* push(); pop() */

int main(int argc, char **argv)
{
    char expr[15];
    int digito, i;
    char operador;
    int operando1, operando2, resultado;
    Pilha P;

    printf("Digite a string de entrada em notacao posfixa: ");
    scanf("%s", expr);
    i = 0;
    InitPilha(&P);
    while (expr[i])
    {
           if (expr[i] >= '0' && expr[i] <= '9')
           {
               digito = expr[i] - '0';
               Push(&P, digito);
           }
           else
           {
               operador = expr[i];
               Pop(&P, &operando2);
               Pop(&P, &operando1);
               switch (operador)
               {
                       case '+': Push(&P, operando1 + operando2); break;
                       case '-': Push(&P, operando1 - operando2); break;
                       case '*': Push(&P, operando1 * operando2); break;
                       case '/': Push(&P, operando1 / operando2); break;
                       default: printf("\nOperador invalido!");
               }
           }
           i++;
    }

    Pop(&P, &resultado);
    printf("\nExpressao entrada (posfixa): %s", expr);
    printf("\nResultado expressao: %i", resultado);

	return 0;
}



