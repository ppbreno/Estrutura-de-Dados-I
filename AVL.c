typedef struct NO* ArvAvl;

#include <stdio.h>
#include <stdlib.h>

struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

int alt_NO(struct NO* no){
    if(no == NULL){
        return -1;
    }else{
        return no->alt;
    }
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(alt_NO(no->esq) - alt_NO(no->dir));
}

int maior(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

//Rotação Simples à Esquerda - Rotação RR
void RSE(ArvAvl *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    no->alt = maior(alt_NO(no->dir), (*raiz)->alt) + 1;
    (*raiz) = no;
}

//Rotação Simples à Direita - Rotação LL
void RSD(ArvAvl *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    no->alt = maior(alt_NO(no->esq), (*raiz)->alt) + 1;
    *raiz = no;
}

//Rotação Dupla à Esquerda - Rotação RL
void RDE(ArvAvl *raiz){
    RSE(&(*raiz)->esq);
    RSD(raiz);
}

//Rotação Dupla à Direita - Rotação LR
void RDD(ArvAvl *raiz){
    RSD(&(*raiz)->dir);
    RSE(raiz);
}

int insere_ArvAvl(ArvAvl *raiz, int valor){
    int res;
    if(raiz == NULL){//árvore vazia ou nó folhas
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            return 0;
        }
        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        raiz = novo;
        printf("Inserido\n");
        return 1;
    }
    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_ArvAvl(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info){
                    RSD(raiz);
                }else{
                    RDD(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = insere_ArvAvl(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        RSE(raiz);
                    }else{
                        RDE(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado\n");
            return 0;
        }
    }
    atual->alt = maior(alt_NO(atual->esq), alt_NO(atual->dir)) + 1;
    printf("Deu certo! \nValor da altura do nó inserido: %d", atual->alt);
    return res;
}

int main(){
    ArvAvl *raiz;

    int x = insere_ArvAvl(raiz, 10);
    x = insere_ArvAvl(raiz, 20);
    x = insere_ArvAvl(raiz, 8);
    x = insere_ArvAvl(raiz, 13);
    return 0;
}
