#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum { false, true } bool;

typedef struct tipoelem{
    int tempoChegada;
    int cliente;
}tipoelem;

typedef struct noFila{
    tipoelem elem;
    struct noFila *prox;
}noFila;

typedef struct Fila{
	struct noFila *inicio;
	struct noFila *fim;
} Fila;

void inicializarFila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

bool vazia(Fila *fila){
    if (fila->inicio == fila->fim && fila->inicio == NULL){
        return true;
    }else{
        return false;
    }
}

bool inserirFila(Fila *f, int tempo){
    noFila *novo = (noFila *) malloc(sizeof(noFila));
    novo->elem.cliente = rand()%2; //criando o tipoelem
    if(novo->elem.cliente == 0){
        printf("Nao cliente\n");
    }else{
        printf("Cliente\n");
    }
    novo->elem.tempoChegada = tempo; //criando o tipoelem
    printf("Tempo de chegada: %d\n", novo->elem.tempoChegada);
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

bool removerFila(Fila *f, tipoelem *atend){
    if(f->inicio == NULL){
        return false;
    }
    *atend = f->inicio->elem;
    noFila *apagar = f->inicio;
    noFila *aux = f->inicio;
    f->inicio = aux->prox;
    free(apagar);
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    return true;
}

void exibirFila(Fila *f){
    noFila *end = f->inicio;
    printf("Fila: \" ");
    while(end != NULL){
        printf("%d ", end->elem.cliente);
        end = end->prox;
    }
    printf("\"\n");
}

void clientesAtendidos(tipoelem *f, int *total){
    if(f->cliente == 1){
        *total = *total + 1;
    }
}

void naoClientesAtendidos(tipoelem *f, int *total){
    if(f->cliente == 0){
        *total = *total + 1;
    }
}

int main(){
    int tempoSimulacao=500, tempoAtual=0,  i, totalNaoAtendidos=0, totalClientes=0, totalNaoClientes=0, totalAtendimentos=0, totalMediaEspera;
    int atendimentoCaixa[4], tempoEspera[4], numAtendimentos[4], mediaEspera[4];
    Fila caixas[4];
    noFila *aux;

    srand(time(NULL));

    for(int x = 0; x < 4; x++){
        inicializarFila(&caixas[x]);
    }

    for(int x = 0; x < 4; x++){
        atendimentoCaixa[x] = 0;

    }

    for(int x = 0; x < 4; x++){
        tempoEspera[x] = 0;
    }

    for(int x = 0; x < 4; x++){
        numAtendimentos[x] = 0;
    }

    for(int x = 0; x < 4; x++){
        mediaEspera[x] = 0;
    }

    while(tempoAtual <= tempoSimulacao){
        if((tempoAtual % 5) == 0){ //clientes a cada 5 unidades de tempo
            i = rand()%4;
            printf("Caixa[%d]\n", i);
            inserirFila(&caixas[i], tempoAtual);
            exibirFila(&caixas[i]);
            for(int ncaixa = 0; ncaixa < 4; ncaixa++){ //processo comum aos 4 caixas, em cada unidade de tempo
                if(atendimentoCaixa[ncaixa] == 0){ //se caixa n vazio
                   if(!vazia(&caixas[ncaixa])){ //se fila do caixa n está vazia
                        tipoelem atendido;
                        removerFila(&caixas[ncaixa], &atendido);
                        printf("Atendido - Cliente: %d   Tempo de chegada: %d\n",atendido.cliente, atendido.tempoChegada);
                        exibirFila(&caixas[ncaixa]);
                        numAtendimentos[ncaixa]+=1; //numero de atendimentos por caixa
                        clientesAtendidos(&atendido, &totalClientes);
                        naoClientesAtendidos(&atendido, &totalNaoClientes);
                        tempoEspera[ncaixa] = tempoEspera[ncaixa] + (tempoAtual - atendido.tempoChegada);
                        atendimentoCaixa[ncaixa] = rand() % 10; //tempo de atendimento
                        printf("O atendimento durara %d unidades de tempo\n", atendimentoCaixa[ncaixa]);
                    }else{
                        continue;
                    }
                }else{
                    atendimentoCaixa[ncaixa] -= 1;
                    printf("Atendimento no caixa %d: %d\n", ncaixa, atendimentoCaixa[ncaixa]);
                }
            }
        }
        tempoAtual+=1;
        printf("\n");
    }

    for(int j = 0; j < 4; j++){
        mediaEspera[j] = tempoEspera[j] / numAtendimentos[j];
    }

    totalAtendimentos = numAtendimentos[0]+numAtendimentos[1]+numAtendimentos[2]+numAtendimentos[3];
    totalMediaEspera = mediaEspera[0] + mediaEspera[1] + mediaEspera[2] + mediaEspera[3];

    printf("\n***Estatisticas***\n");

    printf("Total de atendimentos: %d\n", totalAtendimentos);
    for(int j = 0; j < 4; j++){
        printf("Quantidade de atendimentos do caixa %d: %d\n", j, numAtendimentos[j]);
    }
    for(int j = 0; j < 4; j++){
        printf("Tempo medio de espera do caixa %d: %d\n", j, mediaEspera[j]);
    }
    printf("Tempo medio de espera no banco: %d\n", totalMediaEspera / 4);
    for (int i = 0; i< 4; i++){
        aux = &caixas[i].inicio;
        while (aux != NULL){
            totalNaoAtendidos = totalNaoAtendidos + 1;
            aux = aux->prox;
        }
    }
    printf("Total de pessoas nao atendidas: %d\n", totalNaoAtendidos);
    printf("Quantidade de clientes atendidos: %d\n", totalClientes);
    printf("Quantidade de nao clientes atendidos: %d\n", totalNaoClientes);

}
