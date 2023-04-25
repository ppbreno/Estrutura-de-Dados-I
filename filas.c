#include <stdio.h>
#define MAX 10
#define true 1
#define false 0


typedef struct Fila{
    int inicio;
    int fim;
    int vFila[MAX];
}Fila;

int inicializacao(Fila *fila){
    fila->inicio = 0;
    fila->fim = 0;
}

int vazia(Fila *fila){
    if(fila->inicio == fila->fim){
        return true;
    }else{
        return false;
    }
}

int cheia(Fila *fila){
    if(fila->fim == MAX){
        return true;
    }else{
        return false;
    }
}

void inserir(Fila *fila, int elemento){
    if(cheia(fila)){
        printf("Fila cheia!");
    }else{
        fila->vFila[fila->fim] = elemento;
        fila->fim++;
    }
}

void remover(Fila *fila, int *elemento){
    if(vazia(fila)){
        printf("Fila vazia - Não ha elementos na fila para remocao");
    }else{
        *elemento = fila->vFila[fila->inicio];
        fila->inicio++;
    }
}

void obterInicioFila(Fila *fila, int *elemento){
    if(vazia(fila)){
        printf("Fila vazia - Não ha elementos na fila para remocao");
    }else{
        *elemento = fila->vFila[fila->inicio];
    }
}

int main(){
    int elem;
    Fila teste;
    inicializacao(&teste);

    printf("Digite um numero para ser inserido na fila: ");
    scanf("%d", &elem);
    inserir(&teste, elem);
    printf("%d", teste.vFila[0]);

}
