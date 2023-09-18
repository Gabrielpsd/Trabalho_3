#include <math.h> /* pow()*/
#include <string.h> /* strtok */
#include <stdlib.h> /* realloc, atof, free*/
#include <stdio.h>

#include "validador.h"

/* ------------------------- adicionaespacos ----------------------------------
    OBS: Chamar a funcao removeAllSpaces antes dessa para garantir consistencia

    a funcao ira adicionar um espacos entre um operador e os numeros.
*/
void adicionaEspacos(char *String)
{
    char *tempString, auxiliar;
    
    int contString = 0,contTemp = 0;

    tempString = (char *) malloc(sizeof(char) * 1);

    while (String[contString]!= '\0')
    {
       auxiliar = String[contString];
       
       /* sempre verificadno se o caratere anterior ja eh um espaco para garatir consistencia 
       (que havera somente 1 espaco entre operador e operando)*/
        if(ehOperador(auxiliar) && tempString[contTemp-1] != ESPACE)
        {
                tempString = (char *)realloc(tempString, (sizeof(char)) * (contTemp+4));
                tempString[contTemp] = ESPACE;
                contTemp++;
                tempString[contTemp] = auxiliar;
                contString++;
                contTemp++;
                tempString[contTemp] = ESPACE;
                contTemp++;

        }else
            if(ehOperador(auxiliar) && tempString[contTemp-1] == ESPACE)
            {
                tempString = (char *)realloc(tempString, (sizeof(char)) * (contTemp+3)); 
                tempString[contTemp] =auxiliar;
                contString++;
                contTemp++;
                tempString[contTemp] = ESPACE;
                contTemp++;
            }
            else            
            {
                tempString = realloc(tempString,sizeof(char) * (contTemp+2));
                tempString[contTemp] = auxiliar;
                contString++;
                contTemp++;
            }

    }
    
    tempString[contTemp] = '\0';

    strcpy(String,tempString);
    
    free(tempString);

}

/* ----------------------------- calcPosFixa ----------------------------
    ira realizar o calculo de uma equcao pos fixa, será feita percorrendo o elemento elemento por elemento 
    assim que encontrar um operador, ele pega os dois ultimos operados executa a operação 
    e coloca o resultado novamente na pilha, e assim vai indo ate percorrer toda a equacao pos fixa 

    ao final sobrara apenas o resultado e basta retorna-lo 

*/
float calcPosFixa(char *equacao)
{
    /* variaveis utilizadas */
    int i;
    char operador, *pt;
    float Result[TAMANHO], elemento1 , elemento2, resultado; 

    /* inicialização das variaveis */
    i = 0;
    /* setando o token de separacao dos elementos*/
    pt = strtok(equacao, " ");

    while(pt)
    {   
        /* se for operando apenas o coloca vo vetor de saida */
        if(ehOperador(pt[0]) == FALSE)
        {  
            /**/
            Result[i] = atof(pt);
            ++i;
        }
        else
        {   
        
        /* ira pegar os dois ultimos elementos do vetor*/
            elemento1 = Result[--i];

            resultado = elemento1;

            elemento2 = Result[--i];

            operador = pt[0];

            switch (operador)
            {
                case '+':
                    resultado = elemento1 + elemento2;

                    break;
                case '-':
                    resultado = elemento2 - elemento1;

                    break;
                case '*':
                    resultado = elemento1 * elemento2;

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
           
            Result[i++] = resultado;
        }

        pt = strtok(NULL," ");
    }

    /* na ultima posicao ira sobrar apenas o resultado, entao armazena para retorno da funcao 
    e assim livramos o ponteiro alocado para poder o limpar da memoria
    */
    resultado = Result[0];

    return resultado;
}

/* ---------------- Concatena--------------------------------
        recebe duas strings e concatena as duas, e a string do parametro 1 ficara concatenada 
        com a string do segundo parametro 
----------------------------------------------------------------
*/
void concatena(char *dest , char *scr, int lastScr,unsigned int tamanhoDest)
{
    int tamanho, auxiliar, i;

    tamanho = strlen(scr);

    auxiliar = lastScr;
    i = 0;

    /* ira armazenar ate que o destino não tenha mais espaco ou o a string scr seja passada por inteiro */
    if(strlen(dest) < tamanhoDest)

        while (scr[i] !='\0' && i < tamanho)
        {
             dest[auxiliar++] = scr[i++];
        }

}


/* ------------------------ converte para infixa ------------------
        Essa funcao ira recer uma string no formato infixa e converterá para o formado pos fixo
    ela recebe um ponteiro char, e o resultado da equação ela armazena no proprio 
    parametro passado como referencia. 
*/
void converteInfixa(char *equacao)
{

    /* variaveis utilizadas na funcao */
    PILHA pilha;
    char saida[TAMANHO], auxiliar, *pt;
    int j;

    /*iniciando as variaveis*/
    saida[0] = ' ';
    init(&pilha);
    j = 0;

    /*o separador dos elementos da funcao é o caractere espaco*/
    pt = strtok(equacao, " ");

    while (pt)
    {            
        /*Se não for operador que dizer que é operado */
        if (ehOperador(pt[0]) == FALSE)
        { 

            concatena(saida , pt,j, TAMANHO);
            j += strlen(pt);

            saida[j++] = ' ';

        } 
        else
        {   
            
            /* caso o elemento se um fechar parensetis ele ira retirar todos operadores da pilha ate 
            encontrar um abre parentesis*/
            if(pt[0] == ')')
            {   
                Pop(&pilha,&auxiliar);
                /* vai retirando todos os elementos da pilha */
                while(auxiliar != '(')
                {   
                    /* coloca um operador mais um token (" ") */
                    saida[j] = auxiliar;
                    j++;
                    saida[j] = ' ';
                    j++;
                    Pop(&pilha,&auxiliar);
                }

            }
            else
            {
                /* se entrou aqui significa que o elemento trabalhado 
                eh um operador e difrente de ) ent~çao precisamor trabalhar com ele 
                para verificar a ordem de precedencia entre o elemento trabalhado e 
                o que esta no topo da pilha*/
                    if (pilha.topo != 0 && PilhaPrioidade(pt[0], returnTop(pilha)))
                    {
                        /* se entrou aqui significa que o elemento que esta no topo da pilha tem maior
                        prioridade e por isso o jogamos na sting de saída*/
                        Pop(&pilha,&auxiliar);
                        saida[j++] = auxiliar;
                        saida[j++] = ' ';

                    }

                /* emilhamos o elemento que estamos analizando da equacao infixa novamente*/
                Push(&pilha,pt[0]);
            }

   
        }

        /* avanca para o proximo token da string */
        pt = strtok(NULL ," ");
    }
    j = j - 1;

    /*desempilha os operadores restantes na pilha (caso haja)*/    
    while (pilha.topo > 0)
    {   
        saida[j++] = ' ';
        Pop(&pilha,&auxiliar);
        saida[j++] = auxiliar;
        
    }
    
    /* coloca o operador de final de string na ultima posicao*/
    saida[j] = '\0';

    /* passa a saida para a string que entrou como parametro*/
    strcpy(equacao,saida);

}

/* ---------------------- ehOperador -----------------------------
        Verifica se o elemento passado como parametro eh um operando e assim o sendo retorna TRUE 
        caso contrario FALSE
    -----------------------------------------------------------
*/
Boolean ehOperador(char Valor){

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

/* ----------------- init pilha-----------------------
    Ao chamar essa funcao o programa setara o 
 o topo da pilha para a posicao zero onde sera armazenado
 o primeiro elemento    
 --------------------------------------------------------
*/
void init(PILHA *Pilha)
{
   /* coloca o topo da pilha no inicio */
    Pilha->topo = 0;
}


/* ------------------- PilhaPrioridade --------------------------------- 
caso o elemento que esteja na minha pilha tenha mais prioridade do que o elemento que 
tem na minha equaçaõ, logo preciso colocar ele na string de saída pois na na hora de resolver a equacao pos-fixa 
ele precisa aprecer primeiro

a funcao avalia se o char do primeiro parametro tem mais prioridade que o char do segundo parametro 
se sim retorna TRUE se não FALSE
-------------------------------------------------------------------------
*/
Boolean PilhaPrioidade(char string1,char string2){
    switch (string1)
    {
            case '+':
                switch (string2)
                 { 
                         case '+':
                         case '-': 
                         case '*':
                         case '/': 
                         case '$':
                            return TRUE;
                        default:
                            return FALSE;
                 }
            case '-':
                switch (string2)
                 { 
                        case '+':
                         case '-': 
                         case '*':
                         case '/': 
                         case '$':
                            return TRUE;
                        default:
                            return FALSE;
   
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
    return FALSE;
}

/* ---------------------- POP-----------------
        retira o elemento no topo da pilha, e o armazena no segundo parametro da funcao, 
    e retorna um Booleano TRUE (se conseguir empilhar) ou false (se não coseguir desempilhar)
-----------------------------------------------
*/
Boolean Pop(PILHA *pilha,char *element)
{

    /*  se o topo for ) entao a pilha esta vazia */
    if(pilha->topo == 0 ) return FALSE;
    else
    {
        /* armazena o elemento do topo e retorna TRUE*/
        *element = pilha->elemento[--pilha->topo];
        return TRUE;
    }
}

/* ----------------------------PUSH-------------------------------------------------
        Recebe o ponteiro de uma pilha e o elemento a colocar na pilha 
    se o push for bem sucedido então o programa retorna TRUE (conseguiu empilhar)
    ou false (não conseguiu empilhar)
--------------------------------------------------------------------------------------
*/
Boolean Push(PILHA *pilha, char element)
{

    /* se o topo for igual ao tamanho da pilha então esta cheia*/
    if(pilha->topo == TAMANHO) return FALSE;
    else
    {
        /* se tiver espaco na pilha ele ira empilhar */
        pilha->elemento[pilha->topo] = element;
        pilha->topo++;

        return TRUE;
    }

}

/* ---------------------- remoeAllspaces----------------------
        Como o pograma utiliza o caratere espaco como separador dos operadores e operandos, então 
        precimaos garantir que todos estão uniformes, pois o ususario pode digitar dois (ou mais) espacos seguidos 
        o que pode gerar erros de calculo, então sera removido todos os espaços para garantir uniformidade

    O funciomento é bem simples, ele vai copiando o valor da string da chamada da funcao digito a digito para uma string 
    auxiliar porem se o digito for igual a espaco ele ignora-o e segue para o proximo digito da string
---------------------------------------------------------------
*/
void removeAllSpaces(char *String)
{
    char *tempString;
    int contString = 0,contTemp = 0, size;

    size = strlen(String);

    tempString = (char *) malloc(size * (sizeof(char)));

    while (String[contString] != '\0')
    {
        if(String[contString] != ESPACE)
        {
                tempString[contTemp] = String[contString];
                contTemp++;
        }
            
        contString++;
    }
    
    /* colocando o carater fim de string apenas para não gerar erros na funcao strcpy */
    tempString[contTemp] = '\0';

    strcpy(String,tempString);
    
    free(String);
}


/* ------------------- return top --------------------------
    como não podemos saber qual elemento esta no topo da pilha ate desempilharmo-no
    entao a funcao ira dar um pop na pilha, e armazenar o elemento em uma variavel para retorna-la 
    e depois ira dar um push novamente nesse elemento
    ----------------------------------------------------------
*/
char returnTop(PILHA pilha)
{
    char auxiliar;
    Pop(&pilha,&auxiliar);
    Push(&pilha,auxiliar);
    return auxiliar;
}


/* ----------------------- validate digits ----------------------------
    recebe uma string e verifica se ha na string algum caratere não permitido no programa
    retoran FALSE caso encontre algum elemento incorreto
*/
Boolean validateDigits(char *string)
{

    int cont = 0;

    /* percorre a string */
    while (string[cont] != '\0')
    {
        
        /* caso nao seja um operador pode ser que seja um espaco ou um numero ainda 
        então para cada digito precisamos fazer tres validacoes*/
        if(!ehOperador(string[cont]))
            if(!(string[cont] == ESPACE))    
                if(string[cont] < 48 || string[cont] > 57)     
                    return FALSE;

        cont++;
    }

    /* caso não tenha encontrato nenhuma inconsistencia então retorna true */
    return TRUE;
}


/*--------------------------- Verifica arbertura--------------------------------------
        o programa recebe uma string e vai varrendo digito a digito, quando encontra
    um abre parentesis ele empilha-o e quando encontra o fecha parentesis ele desempilha oque esta no topo 
    que para esse caso precisa ser um abre parentesis para fechar o par () 
    se ao desempilhar for diferente de abre parentesis ou ao final de tudo sobrar elemento na pilha 
    então a expressão esta mal formada
---------------------------------------------------------------------------------------
*/

Boolean verificaAberturas(char *expressao)
{

    /* variaveis utilizadas na função */
    PILHA pilha;
    unsigned int i;
    char auxiliar;

    /* inicia a pilha */
    init(&pilha);
    
    /* ira percorrer toda a string de entrada */
    for(i =0; i< strlen(expressao)- 1; ++i )
    {
        
        if (expressao[i] == '(' )
        {   
            /* achou um abre parentesis e empilha-o*/
            if(Push(&pilha,expressao[i]) == FALSE)
                return FALSE;
        }
        else 
        {
            /*encontrou um fecha parentesis e entao desempilha o que esta no topo */
            if(expressao[i] == ')')
            {
                if(Pop(&pilha,&auxiliar) == FALSE)
                {
                    /*entra aqui se houver erro ao desempilhar (pilha vazia)*/
                    return FALSE;
                }
                else
                {
                    /* se o elemento desempilhado for diferente do esperado então 
                    esta mal formada a equação*/
                    if (auxiliar != '(')
                        return FALSE;
                }

            }
        }
    }

    /* se não achou nenhum erro retorna verdadeiro por padrão */
    return TRUE;
}
