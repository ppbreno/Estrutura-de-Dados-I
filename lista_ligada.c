#include <stdio.h>
#define MAX 50

typedef enum { false, true } bool;

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO reg;
    int prox;
}ELEMENTO;

typedef struct{
    ELEMENTO A[MAX];
    int inicio;
    int dispo;
}LISTA;

void inicializarLista(LISTA *l){
    int i;
    for(i = 0; i < MAX-1; i++){
        l->A[i].prox = i+1;
    }
    l->A[MAX-1].prox = -1;
    l->inicio = -1;
    l->dispo = 0;
}

int tamanho(LISTA *l){
    int i = l->inicio;
    int tam = 0;
    while(i != -1){
        tam++;
        i = l->A[i].prox;
    }
    return tam;
}

void exibirLista(LISTA *l){
    int i = l->inicio;
    printf("LISTA: \" ");
    while(i != -1){
        printf("%d ", l->A[i].reg.chave);
        i = l->A[i].prox;
    }
    printf("\"\n");
}

int buscaSequencial(LISTA *l, int ch){
    int i = l->inicio;
    while(i != -1 && l->A[i].reg.chave < ch){
        i = l->A[i].prox;
    }
    if(i != -1 && l->A[i].reg.chave == ch){
        return i;
    }else{
        return -1;
    }
}

int obterNo(LISTA *l){
    int resultado = l->dispo;
    if(l->dispo != -1){
        l->dispo = l->A[l->dispo].prox;
    }
    return resultado;
}

bool inserirElemListaOrd(LISTA *l, int valor){
    REGISTRO reg;
    reg.chave = valor;
    if(l->dispo == -1){
        return false;
    }else{
        int ant = -1;
        int i = l->inicio;
        int ch = reg.chave;
        while((i != -1) && (l->A[i].reg.chave < ch)){
            ant = i;
            i = l->A[i].prox;
        }
        if((i != -1) && (l->A[i].reg.chave == ch)){
            return false;
        }else{
            i = obterNo(l);
            l->A[i].reg = reg;
            if(ant == -1){
                l->A[i].prox = l->inicio;
                l->inicio = i;
            }else{
                l->A[i].prox = l->A[ant].prox;
                l->A[ant].prox = i;
            }
            return true;
        }
    }
}

void devolverNo(LISTA *l, int j){
    l->A[j].prox = l->dispo;
    l->dispo = j;
}

bool excluirElemLista(LISTA *l, int ch){
    int ant = -1;
    int i = l->inicio;
    while((i != -1) && (l->A[i].reg.chave < ch)){
        ant = i;
        i = l->A[i].prox;
    }
    if(i == -1 || l->A[i].reg.chave != ch){
        return false;
    }
    if(ant == -1){
        l->inicio = l->A[i].prox;
    }else{
        l->A[ant].prox = l->A[i].prox;
    }
    devolverNo(l, i);
    return true;
}

int main(){
    LISTA lista;

    inicializarLista(&lista);
    inserirElemListaOrd(&lista, 10);
    inserirElemListaOrd(&lista, 80);
    inserirElemListaOrd(&lista, 30);
    inserirElemListaOrd(&lista, 45);
    inserirElemListaOrd(&lista, 20);
    exibirLista(&lista);
    excluirElemLista(&lista, 20);
    exibirLista(&lista);
}
