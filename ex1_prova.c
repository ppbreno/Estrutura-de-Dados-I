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
}

int main (){
    tpstring *str1, *str2;
    char letra;

    cria_str(&str1);
    cria_str(&str2);

    insercao(&str1,'a');
    insercao(&str1,'b');
    insercao(&str1,'a');
    insercao(&str1,'c');
    insercao(&str1,'a');
    insercao(&str1,'t');
    insercao(&str1,'e');
    imprimir_str(str1);

    insercao(&str2,'a');
    insercao(&str2,'b');
    insercao(&str2,'a');
    insercao(&str2,'c');
    insercao(&str2,'a');
    insercao(&str2,'x');
    insercao(&str2,'i');
    imprimir_str(str2);

    comparacao(str1, str2);
    //imprimir_str(str1);

}
