#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 5

typedef struct no {
    int info, linha, coluna;
    struct no *direita;
    struct no *baixo;
} elemento;

typedef struct {
 	elemento *linha[N];
    elemento *coluna[M];
} MatrizEsparsa;

void inicializarMatriz(MatrizEsparsa *matriz){
	int i;
    for (i=0;i < N; i++) {
        matriz->linha[i] = NULL;
    }
    for (i=0;i < M; i++){
        matriz->coluna[i] = NULL;
    }
}

void insercao(MatrizEsparsa *matriz, int lin, int col, int info){
    elemento *novo, *pontlin, *pontcol, *ant;
	novo = (elemento *)malloc(sizeof(elemento));
	novo->info  = info; novo->linha = lin; novo->coluna = col;
    novo->direita = NULL; novo->baixo = NULL;
    pontcol = matriz->coluna[col];
    pontlin = matriz->linha[lin];
    if (pontcol == NULL){ // não há elementos na coluna
        matriz->coluna[col] = novo;
    }else{ // inserção ordenada na coluna considerando o valor da linha
        ant = NULL;
        while ((pontcol!= NULL) && (pontcol->linha < lin)){
            ant = pontcol;
            pontcol = pontcol->baixo;
        }
        if (pontcol != NULL){
            if (pontcol->linha == lin){
                printf("\nJa existe elemento na linha!!\n");
            }else if (ant == NULL){ // inserção no início
                novo->baixo = matriz->coluna[col];
                matriz->coluna[col] = novo;
            }else{
                novo->baixo = pontcol;
                ant->baixo = novo;
            }
        }else{
            ant->baixo = novo; // inserção no final
        }
    }
    if (pontlin == NULL){ // não há elementos na linha
        matriz->linha[lin] = novo;
    }else{ // inserção ordenada na linha considerando o valor da coluna
        ant = NULL;
        while ((pontlin!= NULL) && (pontlin->coluna < col)){
            ant = pontlin;
            pontlin = pontlin->direita;
        }
        if (pontlin != NULL){
            if (pontlin->coluna == col){
                printf("Ja existe elemento na coluna!!\n");
            }else if(ant == NULL){ // inserção no início
                novo->direita = matriz->linha[lin];
                matriz->linha[lin] = novo;
            }else{ // inserção no meio
                novo->direita = pontlin;
                ant->direita = novo;
            }
        }else{
            ant->direita = novo; // inserção no final
        }
    }
}

void remover(MatrizEsparsa *matriz, int lin, int col){
    elemento *removido, *pontlin, *pontcol, *ant;
    pontcol = matriz->coluna[col];
    pontlin = matriz->linha[lin];
    if (pontcol == NULL){ // não há elementos na coluna
        printf("Elemento nao existe");
    }else{ // inserção ordenada na coluna considerando o valor da linha
        ant = NULL;
        while ((pontcol!= NULL) && (pontcol->linha < lin)){
            ant = pontcol;
            pontcol = pontcol->baixo;
        }
        if (pontcol != NULL){ //há elemento
            if ((pontcol->linha == lin) && (ant != NULL)){
                printf("\n\nAchou elemento na coluna\n");
                ant->baixo = pontcol->baixo;
            }else if(ant == NULL){//primeiro elemento da linha, naquela coluna
                printf("\n\nAchou elemento na coluna(primeiro)\n");
                matriz->coluna[col] = matriz->coluna[col]->baixo;
            }else{
                printf("Elemento nao existe");
            }
        }else{
            printf("Elemento nao existe"); // inserção no final
        }
    }if (pontlin == NULL){ // não há elementos na linha
        printf("Elemento nao existe");
    }else{ // inserção ordenada na linha considerando o valor da coluna
        ant = NULL;
        while ((pontlin->coluna < col) && (pontlin!= NULL)){
            ant = pontlin;
            pontlin = pontlin->direita;
        }
        if (pontlin != NULL){
            if ((pontlin->coluna == col) && (ant != NULL)){
                    printf("Achou elemento na linha\n");
                ant->direita = pontlin->direita;
            }else if(ant == NULL){ //primeiro elemento da coluna, naquela linha
                printf("Achou elemento na linha(primeiro)\n");
                matriz->linha[lin] = matriz->linha[lin]->direita;
            }else{ // inserção no meio
                printf("Elemento nao existe");
            }
        }else{
            printf("Elemento nao existe");
        }
    }
    printf("\nRemoveu\n");
}

 void imprimir(MatrizEsparsa *matriz){
    elemento *aux; 	int lin, col;
    for (lin=0; lin < N; lin++){ // n número de linhas
  		aux = matriz->linha[lin]; // primeiro elemento da linha
        printf("\n");
   		for (col =0; col < M; col++){ // m número de colunas
            if ((aux != NULL) && (aux->coluna == col)){
                printf(" %d", aux->info);
                aux= aux->direita;
            }else{ // imprimir zero não não há elementos
                printf(" 0");
            }
   		}
    }
}

void somark(MatrizEsparsa *matriz, int lin, int valork){
    elemento *aux;
    aux = matriz->linha[lin];
    for (int col =0; col < M; col++){ // m número de colunas
        if ((aux != NULL) && (aux->coluna == col)){
            aux->info += valork;
            if(aux->info == 0){
                remover(matriz, lin, col);
            }
            aux = aux->direita;
        }else{ // inserindo onde não há elementos
            insercao(matriz, lin, col, valork);
        }
    }
}

int main(){
    MatrizEsparsa *matriz;

    inicializarMatriz(&matriz);

    insercao(&matriz, 0, 1, 10);
    insercao(&matriz, 1, 0, 30);
    insercao(&matriz, 1, 1, 60);
    insercao(&matriz, 2, 3, 40);
    insercao(&matriz, 3, 0, 80);
    insercao(&matriz, 4, 4, 20);
    imprimir(&matriz);
    printf("\n\n");
    somark(&matriz, 1, -30);
    imprimir(&matriz);
}
