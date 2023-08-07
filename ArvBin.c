#include <stdio.h>
#include <stdlib.h>

typedef struct NO* ArvBin;

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return 1;
    }else if(*raiz == NULL){
        return 1;
    }else{
        return 0;
    }
}

int altura_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return (alt_esq + 1);
    }else{
        return (alt_dir + 1);
    }
}

int totalNO_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}

int insere_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL){
        return 0;
    }
    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    if(*raiz == NULL){
        *raiz = novo;
    }else{
        struct NO* atual =  *raiz;
        struct NO* ant =  NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;
            }else if(valor > atual->info){
                atual = atual->dir;
            }else{
                atual = atual->esq;
            }
        }
        if(valor > ant->info){
            ant->dir = novo;
        }else{
            ant->esq = novo;
        }
        return 1;
    }
}

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){ //sem filho a esquerda. Aponta para o flho da direita (trata nó folha e nó com 1 filho)
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){ //procura o filho mais a direita na sub-arvore da esquerda
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){ //copia o filho mais a direita na sub-arvore esquerda para o lugar do removido
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO* atual =  *raiz;
    struct NO* ant =  NULL;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz){
                *raiz = remove_atual(atual);
            }else{
                if(ant->dir == atual){
                    ant->dir = remove_atual(atual);
                }else{
                    ant->esq = remove_atual(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return 0;
}

int main(){
    ArvBin* raiz = cria_ArvBin();
    int x = estaVazia_ArvBin(raiz);
    int y = altura_ArvBin(raiz);
    int z = totalNO_ArvBin(raiz);
    preOrdem_ArvBin(raiz);
    emOrdem_ArvBin(raiz);
    posOrdem_ArvBin(raiz);
    int a = insere_ArvBin(raiz, 20);
    return 0;
}
