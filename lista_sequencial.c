#include <stdio.h>
#define MAX 50

typedef int TIPOCHAVE;

typedef enum { false, true } bool;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct{
    REGISTRO A[MAX];
    int nroElem;
}LISTA;

void inicializarLista(LISTA *l){
    l->nroElem = 0;
}

int tamanho(LISTA *l){
    return l->nroElem;
}

void exibirLista(LISTA *l){
    int i;
    printf("Lista: \" ");
    for(i = 0; i < l->nroElem; i++){
        printf("%d ", l->A[i].chave);
    }
    printf("\"\n");
}

int buscaSequencial(LISTA *l, TIPOCHAVE ch){
    int i = 0;
    while(i < l->nroElem){
        if(ch == l->A[i].chave){
            return i;
        }else{
            i++;
        }
    }
    return -1;
}

bool inserirElemLista(LISTA *l, int valor, int i){
    REGISTRO reg;
    reg.chave = valor;
    int j;
    if((l->nroElem == MAX) || (i < 0) || (i > l->nroElem)){
        return false;
    }else{
        for(j = l->nroElem; j > i; j--){
            l->A[j] = l->A[j-1];
        }
        l->A[i] = reg;
        l->nroElem++;
        return true;
    }
}

bool excluirElemLista(TIPOCHAVE ch, LISTA *l){
    int pos, j;
    pos = buscaBinaria(l, ch);
    if(pos == -1){
        return false;
    }else{
        for(j = pos; j < l->nroElem-1; j++){
            l->A[j] = l->A[j+1];
        }
        l->nroElem--;
        return true;
    }
}

int buscaSentinela(LISTA *l, TIPOCHAVE ch){
    int i = 0;
    l->A[l->nroElem].chave = ch;
    while(l->A[i].chave != ch){
        i++;
    }
    if(i == l->nroElem){
        return -1;
    }else{
        return i;
    }
}

bool inserirElemListaOrd(LISTA *l, int valor){
    REGISTRO reg;
    reg.chave = valor;
    if(l->nroElem >= MAX){
        return false;
    }else{
        int pos = l->nroElem;
        while(pos > 0 && l->A[pos-1].chave > reg.chave){
            l->A[pos] = l->A[pos-1];
            pos--;
        }
        l->A[pos] = reg;
        l->nroElem++;
        return true;
    }
}

int buscaBinaria(LISTA *l, TIPOCHAVE ch){
    int esq = 0, dir = l->nroElem-1, meio;
    while(esq <= dir){
        meio = (esq + dir) / 2;
        if(l->A[meio].chave == ch){
            return meio;
        }else{
            if(l->A[meio].chave < ch){
                esq = meio +1;
            }else{
                dir = meio - 1;
            }
        }
    }
    return -1;
}

int main(){
    LISTA lista;

    inicializarLista(&lista);
    inserirElemLista(&lista, 20, 0);
    inserirElemLista(&lista, 30, 1);
    inserirElemLista(&lista, 10, 0);
    exibirLista(&lista);
    excluirElemLista(20, &lista);
    exibirLista(&lista);

    inserirElemListaOrd(&lista, 25);
    inserirElemListaOrd(&lista, 20);
    inserirElemListaOrd(&lista, 15);
    exibirLista(&lista);
}
