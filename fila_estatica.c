#include <stdio.h>
#define MAX 50

typedef enum { false, true } bool;

typedef struct {
    int chave;
}Registro;

typedef struct{
    Registro A[MAX];
    int inicio;
    int nroElem;
}Fila;

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->nroElem = 0;
}

int tamanho(Fila *f){
    return f->nroElem;
}

void exibirFila(Fila *f){
    printf("Fila: \" ");
    int i = f->inicio;
    int temp;
    for(temp = 0; temp < f->nroElem; temp++){
        printf("%i ", f->A[i].chave);
        i = (i + 1) % MAX; //retorna para o começo do vetor, caso exista valor validos (fila circular)
    }
    printf("\"\n");
}

void inserirElementoFila(Fila *f, int valor){
    Registro novo;
    novo.chave = valor;
    if(f->nroElem >= MAX){
        return false;
    }else{
        int posicao = (f->inicio + f->nroElem) % MAX;
        f->A[posicao] = novo;
        f->nroElem++;
        return true;
    }
}

void excluirElementoFila(Fila *f, Registro *reg){
    if(f->nroElem == 0){
        return false;
    }else{
        *reg = f->A[f->inicio];
        f->inicio = (f->inicio+1) % MAX;
        f->nroElem--;
        return true;
    }
}

int main (){
    Fila fila;
    Registro removido;

    inicializarFila(&fila);
    inserirElementoFila(&fila, 10);
    inserirElementoFila(&fila, 20);
    inserirElementoFila(&fila, 30);
    exibirFila(&fila);
    excluirElementoFila(&fila, &removido);
    exibirFila(&fila);
}
