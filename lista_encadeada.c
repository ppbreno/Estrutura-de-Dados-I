#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *proximo;
}No;

typedef struct {
    No *inicio;
    int tam;
}Lista;

void inserirInicio(Lista *lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tam++;
}

void imprimir(Lista *lista){
    No *inicio = lista->inicio;
    printf("Tamanho da lista: %d\n", lista->tam);
    while(inicio != NULL){
        printf("%d ", inicio->valor);
        inicio = inicio->proximo;
    }
    printf("\n\n");
}

void inserirFim(Lista *lista, int valor){
    No *no, *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;

    if(lista->inicio == NULL){
        lista->inicio = novo;
    }else{
        no = lista->inicio;
        while(no->proximo != NULL){
            no = no->proximo;
        }
        no->proximo = novo;
    }
    lista->tam++;
}

int main(){
    Lista lista;

    lista.inicio = NULL;
    lista.tam = 0;

    int opcao, valor;

    do{
        printf("1- Inserir no inicio \n2- Imprimir \n3- Inserir no final \n4- Sair \n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            printf("Digite um valor a ser inserido: ");
            scanf("%d", &valor);
            inserirInicio(&lista, valor);
            break;
        case 2:
            imprimir(&lista);
            break;
        case 3:
            printf("Digite um valor a ser inserido: ");
            scanf("%d", &valor);
            inserirFim(&lista, valor);
            break;
        case 4:
            printf("Finalizando...");
            break;
        default:
            printf("Opcao invalida\n");
        }
    }while(opcao != 4);

    return 0;
}
