#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum { false, true } bool;

typedef struct{
    int tempoChegada;
    int cliente;
}tipoelem;

typedef struct{
    tipoelem elem;
    struct noFila *prox;
}noFila;

typedef struct{
	struct noFila *inicio;
	struct noFila *fim;
} Fila;

void inicializarFila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

bool vazia(Fila *fila){
    if (fila->inicio == fila->fim){
        return true;
    }else{
        return false;
    }
}

bool inserirFila(Fila *f, int tempo){
    noFila *novo = (noFila *) malloc(sizeof(noFila));
    novo->elem.cliente = rand()%1; //criando o tipoelem
    novo->elem.tempoChegada = tempo; //criando o tipoelem
    novo->prox = NULL;
    if(f->inicio == NULL){
        f->inicio = novo;
    }else{
        noFila *aux = f->fim;
        aux->prox = novo;
    }
    f->fim = novo;
    return true;
}

bool removerFila(Fila *f, noFila *atend){
    if(f->inicio == NULL){
        return false;
    }
    atend = f->inicio;
    noFila *apagar = f->inicio;
    noFila *aux = f->inicio;
    f->inicio = aux->prox;
    free(apagar);
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    return true;
}

int main(){
    int tempoSimulacao=500, tempoAtual=0, atendimentoCaixa[4], tempoEspera[4], i, numAtendimentos[4], mediaEspera = 0;
    Fila caixas[4];
    tempoEspera = calloc(sizeof(tempoEspera));
    numAtendimentos = (int *) calloc(sizeof(numAtendimentos));

    srand(time(NULL));

    while(tempoSimulacao >= tempoAtual){
        if((tempoAtual % 5) == 0){
            i = rand()%4;
            inserirFila(&caixas[i], tempoAtual);
            for(int ncaixa = 0; i < 4; i++){
                if(atendimentoCaixa[i] == 0){
                    if(!vazia(&caixa[i])){
                        noFila atendido;
                        removerFila(&caixas[i], &atendido);
                        numAtendimentos[i]++;
                        tempoEspera[i] = tempoEspera[i] + (tempoAtual - atendido.elem.tempoChegada);
                        atendimentoCaixa[i] = rand() % 20; //tempo de atendimento
                    }
                }else{
                    atendimentoCaixa[i] = atendimentoCaixa[i] - 1;
                }
            }
        }
        tempoAtual++;
    }

    for(int j = 0; j < 4; j++){
        mediaEspera = mediaEspera + tempoEspera[j];
    }
    mediaEspera = mediaEspera / 4;

    printf("Estatísticas:\n");
    printf("Total de atendimentos: %d\n", numAtendimentos[0]+numAtendimentos[1]+numAtendimentos[2]+numAtendimentos[3]);
    for(int j = 0; i < 4; j++){
        printf("Quantidade de atendimentos do caixa %d: %d\n", numAtendimentos[i]);
    }
    printf("Tempo medio de espera: %d", mediaEspera);

}
