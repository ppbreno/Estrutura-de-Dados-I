#include <stdio.h>

typedef struct Lista
{
    int elem;
    struct Lista prox;
    struct Lista ant;
};

void insercao (struct Lista *lista, int valor){
    struct Lista *aux, *aux2, *analisado, *anterior;
    analisado = lista;
    aux = (struct Lista*) malloc (sizeof(struct Lista));
    aux->elem = valor;
    aux->prox = NULL;
    aux->ant = NULL;

    while(analisado->elem < valor && analisado->prox != NULL){
        anterior = analisado; //anterior passa a ser o atual analisado
        analisado = analisado->prox; //analisado passa a ser a próxima posição
    }

    //ao sair do laço, se mantém a descrição acima

    if(analisado != NULL){ //inserindo no meio da lista
        if(anterior != NULL){ //inserção no meio da lista
            anterior->prox = aux2; //salva em qual posição o proximo estava apontando
            anterior->prox = aux;
            aux->ant = anterior;
            aux->prox = aux2; //utiliza o valor salvo
        }else{ //inserção na primeira posição
            anterior->ant = aux;
            aux->prox = anterior;
            aux->ant = NULL;
        }
    }else{ //o valor será inserido na ultima posição da lista
        if(anterior == NULL){ //primeiro elemento da lista
            aux = lista;
        }else{

        }
        analisado = aux;
        aux->ant = analisado;
        aux->prox = NULL;
    }
}