#include <stdio.h>
#include <string.h>

typedef struct tpstring{
    char elem;
    struct tpstring *prox;
}tpstring;

void cria_str(tpstring **str){
    *str = NULL;
}

void imprimir_str(tpstring *str){
    printf("\n\n");
    if(str == NULL){
        printf("String vazia.");
    }else{
        printf("String: ");
        while (str != NULL){
        printf("%c",str->elem);
        str = str->prox;
    }
    }
    printf("\n\n");
}

int tamanho_str(tpstring *str){
    int count = 0;
    if(str->elem == NULL){
        return count;
    }else{
        while (str != NULL){
            count++;
            str = str->prox;
        }
        return count;
    }
}

void insercao(tpstring **str, char elemento){
    tpstring *aux = *str;
    tpstring *novo;
    novo = malloc(sizeof(tpstring)); // novo caractere a ser inserido
    novo->elem = elemento;
    novo->prox = NULL;

    if(aux == NULL){ // string vazia
        *str = novo;
    }
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    printf("Inserido\n\n");
}

void copia(tpstring *str1, tpstring **str2){
    tpstring *aux = str1;
    //count = 0;
    while (aux != NULL){
        insercao(str2, aux->elem);
        aux = aux->prox;
    }
}

void concatenar(tpstring *str1, tpstring *str2, tpstring **str3){
    copia(str1, str3);
    copia(str2, str3);
    printf("Strings concatenadas");
}

void deletar(tpstring **str1, int nro, int start){
    printf("Entrou deletar\n");
    tpstring *aux = *str1;
    int i = 0, j = 0;
    if(start <= tamanho_str(*str1)){//verifica se a posição é válida
        while(i < start){ //vai parar na posição anterior a desejada
            aux = aux->prox;
            i++;
        }
        tpstring *leitor = aux; //leitor vai percorrer o numero de elementos que se deseja deletar a partir do start
        while(j <= nro || leitor->prox != NULL){
            leitor = leitor->prox;
            j++;
        }
        aux->prox = leitor; //liga o aux com o proximo elemento depois das exclusões
    }else{
        printf("Posicao invalida, maior que a String");
    }
    printf("Removido com sucesso.");
}

void menu (tpstring **str1, tpstring **str2, tpstring **str3){
    int op = 0, nro, start;
    char letra;
    while(op != 9){
        printf("***Menu***\n");
        printf("1 - Inserir\n");
        printf("2 - Listar\n");
        printf("3 - Tamanho da String\n");
        printf("4 - Copiar String para outra\n");
        printf("5 - Concatenar Strings\n");
        printf("6 - Remover caracteres da String\n");
        printf("9 - Sair\n");
        printf("Sua opcao: ");
        scanf("%d", &op);
        fflush(stdin);
        switch(op){
        case 1:
            printf("\n\nLetra que deseja adicionar: ");
            scanf("%c", &letra);
            fflush(stdin);
            insercao(str1,letra);
            break;
        case 2:
            imprimir_str(*str1);
            break;
        case 3:
            printf("\n\nA string possui: %d caracteres\n\n",tamanho_str(*str1));
            break;
        case 4:
            copia(*str1, str2);
            imprimir_str(*str2);
            break;
        case 5:
            concatenar(*str1, *str2, str3);
            imprimir_str(*str3);
            break;
        case 6:
            printf("Quantos caracteres quer excluir?\n");
            scanf("%d", &nro);
            printf("A partir de qual posicao? (0 - %d)\n", tamanho_str(*str1)-1);
            scanf("%d", &start);
            deletar(str1, nro, start);
            imprimir_str(*str1);
        }
    }

}


int main (){
    tpstring *str1, *str2, *str3;
    char letra;

    cria_str(&str1);
    cria_str(&str2);
    cria_str(&str3);


    insercao(&str1,'a');
    insercao(&str1,'b');
    insercao(&str1,'a');
    insercao(&str1,'c');
    insercao(&str1,'a');
    insercao(&str1,'t');
    insercao(&str1,'e');

    insercao(&str2,'a');
    insercao(&str2,'z');
    insercao(&str2,'u');
    insercao(&str2,'l');

    menu(&str1, &str2, &str3);
    //imprimir_str(str1);

}
