#include <stdio.h>
#include <string.h>

typedef enum{false, true} bool;

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

void inserirMeio(tpstring **str1, tpstring *str2, tpstring **str3, int start){
    tpstring *aux1 = *str1;
    tpstring *aux2 = str2;
    int i = 0;
    if(start == tamanho_str(*str1)){
        concatenar(*str1, str2, *str3);
    }else if(start < tamanho_str(*str1)){
        while(i < start){
            aux1 = aux1->prox;
            i++;
        }
        tpstring *backup = aux1->prox;
        aux1->prox = aux2;
        while(aux2->prox != NULL){
            aux2 = aux2->prox;
        }
        aux2->prox = backup;
    }else{
        printf("Posicao invalida, maior que a String");
    }
}

bool menor(tpstring *str1, tpstring *str2){
    tpstring *aux1 = str1;
    tpstring *aux2 = str2;
    while(aux1 != NULL && aux2 != NULL){
        if(aux1->elem < aux2->elem){
                printf("String 1 é MENOR\n");
            return true;
        }else if(aux1->elem == aux2->elem){
            aux1 = aux1->prox;
            aux2 = aux2->prox;
        }else{
            printf("String 1 é MAIOR\n");
            return false;
        }

    }
    if(aux1 == NULL && aux2 == NULL){
        printf("String 1 é MAIOR\n");
        return false;
    }else if(aux2 == NULL){
        printf("String 1 é MAIOR\n");
        return false;
    }else if(aux1 == NULL){
        printf("String 1 é MENOR\n");
        return true;
    }
}

bool comparacao(tpstring *str1, tpstring *str2){
    tpstring *aux1, *aux2;
    aux1 = str1;
    aux2 = str2;
    while((aux1 != NULL) && (aux2 != NULL)){
        if(aux1->elem == aux2->elem){
            aux2 = aux2->prox;
            aux1 = aux1->prox;
        }else{
            printf("As strings NAO sao iguais\n");
            return false;
        }
    }
    if((aux1 == NULL) && (aux2 == NULL)){
        printf("As strings SAO iguais\n");
        return true;
    }else if((aux1 == NULL) || (aux2 == NULL)){
        printf("As strings NAO sao iguais\n");
        return false;
    }else{
        printf("As strings SAO iguais\n");
        return true;
    }
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
        printf("7 - Inserir substring na String\n");
        printf("8 - Verificar String maior\n");
        printf("9 - Verificar igualdade\n");
        printf("10 - Sair\n");
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
            break;
        case 7:
            printf("Inserir a partir de qual posicao? (0 - %d)\n", tamanho_str(*str1)-1);
            scanf("%d", &start);
            inserirMeio(str1, *str2, str3, start);
            if(*str3 != NULL){
                imprimir_str(*str3);
            }else{
                imprimir_str(*str1);
            }
            break;
        case 8:
            menor(*str1, *str2);
            break;
        case 9:
            comparacao(*str1, *str2);
            break;
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
    insercao(&str2,'b');
    insercao(&str2,'a');
    insercao(&str2,'c');
    insercao(&str2,'a');
    insercao(&str2,'t');
    insercao(&str2,'e');

    menu(&str1, &str2, &str3);
    //imprimir_str(str1);

}
