#include <stdio.h>

typedef struct{
    int tempoChegada;
    char cliente;
}tipoelem;

struct noFila{
    tipoelem elem;
    struct noFila *prox;
};

int main{
    int tempoSimulacao=500, tempoAtual=0;
    int atendimentoCaixa[4];

    while(tempoSimulacao <= tempoAtual){
        if(chegada){
            xfila = random(4);
            inserir_fila(Caixas[xfila], tempoAtual);
        }
        if(atendimentoCaixa[0] == 0){
            removerFila(Caixas[0], elemento);
            atendimentoCaixa[0] = random(20);
        }else{
            atendimentoCaixa[0] = atendimentoCaixa[0] - 1;
        }
    }

    for(int i = 0; i < 4; i++){
        if(atendimentoCaixa[i] == 0){
            if (!filaVazia(Caixas[i])){
                removerFila(Caixas[i], tempoChegou); // retira elemento fila
                tempoEspera[i] = tempoEspera[i] + (tempoAtual - tempoChegou);
                atendimentoCaixa[i] = random(20); // sorteia o tempo de atendimento do cliente
                numeroAtendimentos[i]++; // numero de clientes atendidos por caixa

            }
    }
}
