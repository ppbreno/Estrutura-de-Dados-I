#include <stdio.h>
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
    printf("Entrou inicializa\n");
	int i;
    for (i=0;i < N; i++) {
        matriz->linha[i] = NULL;
    }
    for (i=0;i < M; i++){
        matriz->coluna[i] = NULL;
    }
    printf("saiu inicializa\n");
}

void insercao(MatrizEsparsa *matriz, int lin, int col, int info){
    printf("Entrou insercao\n");
    elemento *novo, *pontlin, *pontcol, *ant;
	novo= (elemento *)malloc(sizeof(elemento));
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
                printf("Já existente elemento na linha!!");
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
    }if (pontlin == NULL){ // não há elementos na linha
        matriz->linha[lin] = novo;
    }else{ // inserção ordenada na linha considerando o valor da coluna
        ant = NULL;
        while ((pontlin->coluna < col) && (pontlin!= NULL)){
            ant = pontlin;
            pontlin = pontlin->direita;
        }
        if (pontlin != NULL){
            if (pontlin->coluna == col){
                printf("Já existente elemento na coluna!!");
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
    printf("Inseriu\n");
}

void imprimirLinha(MatrizEsparsa *matriz, int lin){
    elemento *aux;
	aux = matriz->linha[lin]; // primeiro elemento da linha
   	while (aux != NULL){
        printf(" %d", aux->info);
        aux= aux->direita;
    }
}

void imprimirColuna(MatrizEsparsa *matriz, int col){
    elemento *aux;
	aux = matriz->coluna[col]; // primeiro elemento da coluna
   	while (aux != NULL){
        printf(" %d", aux->info);
        aux= aux->baixo;
    }
}

void imprimirLinha2(MatrizEsparsa *matriz, int lin){
	int col;
    elemento *aux;
	aux = matriz->linha[lin]; // primeiro elemento da linha
   	for (col = 0; col < M ; col++){ // m número de colunas
        if ((aux != NULL) && (aux->coluna == col)){
            printf(" %d", aux->info);
            aux= aux->direita;
        }
        else printf(" 0"); // imprimir zero não elementos nulos
   	}
}

void imprimirColuna2(MatrizEsparsa *matriz, int col){
	int lin;
    elemento *aux;
	aux = matriz->coluna[col]; // primeiro elemento da coluna
   	for (lin = 0; lin < N ; lin++){ // n número de linhas
        if ((aux != NULL) && (aux->linha == lin)){
            printf(" %d", aux->info);
            aux= aux->baixo;
        }
        else printf(" 0"); // imprimir zero não elementos nulos
   	}
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

void remover(MatrizEsparsa *matriz, int lin, int col){
    elemento *aux, *ant;
    *aux = matriz->linha[lin];
    for (col; col < M ; col++){
        if(aux->)
    }
}

int main(){
    MatrizEsparsa *matriz;

    inicializarMatriz(&matriz);

    insercao(&matriz, 0, 1, 10);
    insercao(&matriz, 1, 3, 30);
    insercao(&matriz, 3, 0, 80);
    insercao(&matriz, 4, 4, 20);
    imprimir(&matriz);
}
