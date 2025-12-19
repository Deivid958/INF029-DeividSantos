#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct estrutura{
    int valor;
    int tamEstruturaAux;
    int qtdEstruturaAux;
    int *p;
}estrutura;

estrutura vetorPrincipal[TAM];

int ehPosicaoValida(int posicao);

void troca(int * a,int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
int partQuick(int vetorAux[],int inicio,int fim){
    int pivo = fim;
    int j = inicio-1;

    for(int i = inicio;i < fim;i++){
        if(vetorAux[i] <= vetorAux[fim]){
            j++;
            troca(&vetorAux[j],&vetorAux[i]);
        }
    }
    troca(&vetorAux[j+1],&vetorAux[fim]);
    return j+1;
}
void quick(int vetorAux[],int inicio,int fim){
    if(inicio < fim){
        int p = partQuick(vetorAux,inicio,fim);
        quick(vetorAux,inicio,p-1);
        quick(vetorAux,p+1,fim);
    }
}

int estruturaVazia(int posicao){
    if(vetorPrincipal[posicao].qtdEstruturaAux == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    return 0;
}
int temEspacoValor(int posicao){
    if(vetorPrincipal[posicao].qtdEstruturaAux == vetorPrincipal[posicao].tamEstruturaAux)
        return SEM_ESPACO;
    else
        return SUCESSO;
}
int temEspacoEstrutura(int tamanho){
    int * alocado = (int *)malloc(sizeof(int)*tamanho);
    if(alocado == NULL){
        free(alocado);
        return SEM_ESPACO;
    }
    else{
        free(alocado);
        return SUCESSO;
    }
}
/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/

int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int posicaoReal = posicao-1;
    int retorno = 0;
    // se posição é um valor válido {entre 1 e 10}
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    // a posicao pode já existir estrutura auxiliar
    else if(vetorPrincipal[posicaoReal].p != NULL){
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    }
    
    // o tamanho nao pode ser menor que 1
    else if(tamanho < 1){
        retorno = TAMANHO_INVALIDO;
    }

    // o tamanho ser muito grande
    else if(temEspacoEstrutura(tamanho) == SEM_ESPACO){
        retorno = SEM_ESPACO_DE_MEMORIA;
    }
    
    
    // deu tudo certo, crie
    else{
        int * novo = (int *)malloc(tamanho*sizeof(int));
        vetorPrincipal[posicaoReal].p = novo;
        vetorPrincipal[posicaoReal].qtdEstruturaAux = 0;
        vetorPrincipal[posicaoReal].tamEstruturaAux = tamanho;

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{

    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    int posicaoReal = posicao-1;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        posicao_invalida = 1;
    }
    if(vetorPrincipal[posicaoReal].p != NULL){
        existeEstruturaAuxiliar = 1;
    }
    if(temEspacoValor(posicaoReal) != SEM_ESPACO){
        temEspaco = 1;
    }
    
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar)
        {
            if (temEspaco)
            {
                //insere
                int qtd = vetorPrincipal[posicaoReal].qtdEstruturaAux;
                int *insere = vetorPrincipal[posicaoReal].p;

                insere[qtd] = valor;
                vetorPrincipal[posicaoReal].qtdEstruturaAux++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int posicaoReal = posicao-1;
    int retorno = SUCESSO;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetorPrincipal[posicaoReal].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if(estruturaVazia(posicaoReal) == ESTRUTURA_AUXILIAR_VAZIA){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else{
        vetorPrincipal[posicaoReal].qtdEstruturaAux--;
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int posicaoReal = posicao-1;
    int retorno;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetorPrincipal[posicaoReal].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if(estruturaVazia(posicaoReal) == ESTRUTURA_AUXILIAR_VAZIA){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else{
        int achei = 0,aux;
        int * EstruturaAux = vetorPrincipal[posicaoReal].p;
        int qtd = vetorPrincipal[posicaoReal].qtdEstruturaAux;
        for(int i = 0;i < qtd;i++){
            if(valor == EstruturaAux[i]){
                achei = 1;
                aux = EstruturaAux[i];
                EstruturaAux[i] = EstruturaAux[qtd-1];
                EstruturaAux[qtd-1] = aux;
                vetorPrincipal[posicaoReal].qtdEstruturaAux--;
                break;
            }
        }
        if(achei){
            retorno = SUCESSO;
        }
        else{
            retorno = NUMERO_INEXISTENTE;
        }
    }
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int posicaoReal = posicao-1;
    int* EstruturaAux = vetorPrincipal[posicaoReal].p;
    int qtd = vetorPrincipal[posicaoReal].qtdEstruturaAux;
    int retorno = SUCESSO;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetorPrincipal[posicaoReal].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        for(int i = 0;i < qtd;i++){
            vetorAux[i] = EstruturaAux[i];
        }
    }
  
    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int qtd = vetorPrincipal[posicao-1].qtdEstruturaAux;
    int retorno = SUCESSO;
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetorPrincipal[posicao-1].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        quick(vetorAux,0,qtd);
    }
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int qtd,j=0,k;
    int* EstruturaAux;
    int retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    for(int i = 0;i < TAM;i++){
        qtd = vetorPrincipal[i].qtdEstruturaAux;

        if(vetorPrincipal[i].p != NULL && qtd > 0){
            EstruturaAux = vetorPrincipal[i].p;
            for(k = 0;k < qtd;k++){
                vetorAux[j] = EstruturaAux[k];
                j++;
            }
            retorno = SUCESSO;
        }
    }
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    int qtd,count = 0;
    
    for(int i = 0;i < TAM;i++){
        qtd = vetorPrincipal[i].qtdEstruturaAux;
        if(vetorPrincipal[i].p != NULL && qtd > 0){
            retorno = SUCESSO;
            count += qtd;
        }
    }
    if(retorno == SUCESSO){
        getDadosDeTodasEstruturasAuxiliares(vetorAux);
        quick(vetorAux,0,count-1);
    }
    
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    int retorno = SUCESSO;
    int tamEstrutura = vetorPrincipal[posicao-1].tamEstruturaAux;
    int posicaoReal = posicao-1;
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    // a posicao pode já existir estrutura auxiliar
    else if(vetorPrincipal[posicaoReal].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    
    // o tamanho nao pode ser menor que 1
    else if((novoTamanho+tamEstrutura) < 1){
        retorno = NOVO_TAMANHO_INVALIDO;
    }

    // o tamanho ser muito grande
    else if(temEspacoEstrutura(novoTamanho+tamEstrutura) == SEM_ESPACO){
        retorno = SEM_ESPACO_DE_MEMORIA;
    }
    else{
        int *ptr = vetorPrincipal[posicaoReal].p;
        int *temp = realloc(ptr,(novoTamanho+tamEstrutura)*sizeof(int));
        vetorPrincipal[posicaoReal].tamEstruturaAux = novoTamanho+tamEstrutura;
        if(vetorPrincipal[posicaoReal].qtdEstruturaAux > tamEstrutura+novoTamanho){
            vetorPrincipal[posicaoReal].qtdEstruturaAux += novoTamanho;
        }

    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else if(vetorPrincipal[posicao-1].p == NULL){
        retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else if(estruturaVazia(posicao-1) == ESTRUTURA_AUXILIAR_VAZIA){
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else{
        retorno = vetorPrincipal[posicao-1].qtdEstruturaAux;
    }

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int totalTam;
    No *head = malloc(sizeof(No));
    if(head == NULL){
        return NULL;
    }
    head->prox = NULL;
    
    for(int i = 0;i < TAM;i++){
        if(vetorPrincipal[i].p!=NULL){
            totalTam+=vetorPrincipal[i].qtdEstruturaAux;
        }
    }
    int* vet = malloc(totalTam*sizeof(int));

    if (getDadosDeTodasEstruturasAuxiliares(vet) == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS){
        free(head);
        return NULL;
    } 
    else{
        No * atual = head;
        for(int i = 0;i < 10;i++){
            No* novo = malloc(sizeof(No));
            novo->conteudo = vet[i];
            novo->prox = NULL;
            if(novo == NULL){
                return NULL;
            }
            atual->prox = novo;
            atual = atual->prox;
        }
        
        return head;
    }
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No* atual = inicio->prox;
    while(atual != NULL){
        vetorAux[i] = atual->conteudo;
        i++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No * teste = *inicio;
    No * atual = *inicio;
    No* aux;
    atual = atual->prox;
    while(atual != NULL){
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for(int i = 0;i<TAM;i++){
        vetorPrincipal[i].p = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar()
{   
    for(int i = 0;i<TAM;i++){
        free(vetorPrincipal[i].p);
    }
}
