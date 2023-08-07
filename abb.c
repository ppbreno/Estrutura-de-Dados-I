#include <stdio.h>

typedef struct Arvore{
    int info;
    struct Arvore *esq;
    struct Arvore *dir;
}Arvore;

int buscar_ordenada(Arvore *a, int num){
    int direita, esquerda;
    if(a==NULL)
        printf("numero nao encontrado\n");
        return 0;
    if(a->info==num){
        printf("numero encontrado\n");
        return 1;
    }
    if(num<a->info){
        esquerda=buscar_ordenada(a->esq,num);
    }else{
        direita=buscar_ordenada(a->dir,num);
    }
    return esquerda+direita;
}

Arvore * inserir_noh(Arvore *a, int num){
    if(a==NULL){
        a = (Arvore *) malloc(sizeof(Arvore)); //cria
        a->info=num; //Insere o valor
        a->esq=NULL; //Cria filho esquerdo
        a->dir=NULL; //Cria filho direito
        printf("Inserido\n");
    }else if(num < a->info){ //Se o numero for menor do que a raiz, percorre a esquerda.
        a->esq = inserir_noh(a->esq,num);
    }else{
        a->dir = inserir_noh(a->dir,num);
    }
    return a;
}

int main(){
    Arvore *r;
    int busca;
    inserir_noh(&r,10);
    buscar_ordenada(&r, 20);
}
