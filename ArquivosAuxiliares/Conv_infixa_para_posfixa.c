/* Programa que lê uma string em formato infixo do usuário e transforma para o formato posfixo 
   Ex.: 
      Entrada: 3+5
      Saida: 35+
   Obs.: a string de entrada deve conter somente números com 1 dígito e sem separação de espaço entre os operadores e operandos
*/

#include<stdio.h> /* printf() */


#define MAX_ELEMENTOS 5 /* Número máximo de elementos que a minha pilha comporta */
#define VAZIA ' '       /* indicar pilha vazia */  
#define SIMBOLO_DESCONHECIDO 1  /* indicar que foi digitado um operador desconhecido */

typedef char vetor[MAX_ELEMENTOS];
typedef struct {
                 int topo;
                 vetor Elementos;
               } Pilha;

void Push(Pilha *, char); /* Empilhar */
char Pop(Pilha *);        /* Desempilhar */
char StackTopElement(Pilha);    /* Desempilha um elemento da pilha e torna a colocá-lo de volta */
int Comp(char, char);     /* Comparar precedência entre 2 operadores */


int main(int argc, char **argv)
{
  Pilha P;
  char str1[20];             /* Expressão no formato infixo */
  char str2[20];             /* String que conterá a expressão no formato posfixo */
  char symbol_pilha, symbol_str;

  int i = 0, j = 0;
  
  printf("Digite a string a ser analisada (ex. 3+5*2+1*7): ");
  scanf("%s", str1);
  
  P.topo = 0; /* Inicializar a pilha */
  while (str1[i]) /* varrer a string de entrada enquanto for diferente de '\0' */
  {
      if (str1[i] >= '0' && str1[i] <= '9') str2[j] = str1[i], j++; /* se o caracter for um dígito, então colocar ele na string de saída */
      else
      {
          symbol_pilha = StackTopElement(P); /* Pegar operador do topo da pilha */
          symbol_str = str1[i];       /* Pegar operador da string de entrada */
          /* comparar operadores: se operador da string tiver menor precedência que um operador que já estiver no topo da pilha, 
             então COLOCAR NA STRING DE SAÍDA, TODOS OS OPERADORES ARMAZENADOS NA PILHA, CUJA PRECEDÊNCIA SEJA MAIOR QUE O OPERADOR 
             ATUAL QUE TENHO EM MÃOS DA STRING */
          while (symbol_pilha != VAZIA && !Comp(StackTopElement(P), symbol_str)) 
          {
                 symbol_pilha = Pop(&P); /* desempilhar operador da pilha que tem maior precedência que o operador atual que está sendo analisado da string de entrada */
                 str2[j] = symbol_pilha; /* colocar esse operador na string de saída */
                 j++;
          }
          Push(&P, symbol_str); /* Empilhar operador atual, que tenho em mãos, da string */
      }
      i++; /* "andar" na string de entrada */
  } /* fim do while */


  /* Colocar na string de saída todos os operadores que porventura ainda estejam empilhados na pilha */
  do{
      symbol_pilha = Pop(&P);
      str2[j] = symbol_pilha;      
      j++;
  } while (symbol_pilha != VAZIA);
  str2[j] = '\0';


  printf("\n"); 
  printf("String de entrada (infixa): %s\n", str1);
  printf("String de saida (posfixa): %s\n", str2);

  return 0;
}

void Push(Pilha *pilha, char elemento)
{
  if (pilha->topo < MAX_ELEMENTOS)
  {
      pilha->Elementos[pilha->topo] = elemento;
      pilha->topo++;
  }

}
char Pop(Pilha *pilha)
{
  char elemento = VAZIA;
  if (pilha->topo != 0)
  {
      pilha->topo--;
      elemento = pilha->Elementos[pilha->topo];
  }
  return elemento;
}

char StackTopElement(Pilha P)
{
     int topo;
     topo = P.topo - 1;
     return(P.Elementos[topo]);
}


int Comp(char Elem1, char Elem2)
{
    switch (Elem1)
    {
            case VAZIA:
                 switch (Elem2)
                 { 
                         case '+':
                         case '-':
                         case '*':
                         case '/': return 1;
                 }
            case '+':
                 switch (Elem2)
                 { 
                         case '+':
                         case '-': return 0; /* '+' e '-' à direita tem menor precedência que o '+' à esquerda */
                         case '*':
                         case '/': return 1; /* '*' e '/' tem maior precedência que o '+' à esquerda */
                 }
            case '-':
                 switch (Elem2)
                 { 
                         case '+':
                         case '-': return 0; /* '+' e '-' à direita tem menor precedência que o '-' à esquerda */ 
                         case '*':
                         case '/': return 1; /* '*' e '/' tem maior precedência que o '-' à esquerda */
                 }
            case '*':
                 switch (Elem2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 0; /* '+' e '-' e '*' e '/' tem menor precedência que o '*' à esquerda */
                 }
            case '/':
                 switch (Elem2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': return 0; /* '+' e '-' e '*' e '/' tem menor precedência que o '/' à esquerda */
                 }
    }
	return SIMBOLO_DESCONHECIDO;
}
