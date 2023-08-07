#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 13

typedef struct aluno {
     int matricula;
     char nome[80];
     float nota;
};

typedef struct hash{
    int qtd, TABLE_SIZE;
    struct aluno **itens;
}Hash;

Hash* criaHash(int TABLE_SIZE){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (struct aluno**) malloc (TABLE_SIZE * sizeof(struct aluno*));
        if(ha->itens == NULL){ //se falhou a alocação dos endereços que salvaram os endereços dos itens
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i = 0; i < ha->TABLE_SIZE; i++){
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

void liberaHash(Hash* ha){
    if(ha != NULL){
        int i;
        for(i = 0; i < ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL){
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE; //0x7FFFFFFF elimita o bit de sinal, evitando overflow
}

int chaveMultiplicacao(int chave, int TABLE_SIZE){
    float A = 0.6180339887;
    float val = chave * A;
    val = val - (int) val;
    return (int) (TABLE_SIZE * val);
}

int chaveDobra(int chave, int TABLE_SIZE){
    int num_bits = 10; //quantos bits serão deslocados
    int parte1 = chave >> num_bits; //deslocamento para direita
    int parte2 = chave & (TABLE_SIZE - 1);
    return (parte1 ^ parte2); //OU exclusivo
}

int valorString(char *str){ //converte a String para inteiro, para ser aplicado numa função hashing
    int i, valor = 7;
    int tam = strlen(str);
    for(i = 0; i < tam; i++){
        valor = 31 * valor + (int) str[i]; //o 31 é um bom valor a ser multiplicado
    }
    return valor;
}

int insereHash_SemColisao(Hash* ha, struct aluno al){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE){
        return 0;
    }
    int chave = al.matricula;
    //int chave = valorString(al.nome);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE); //pode ser usado qualquer uma das funções hash implementadas
    struct aluno* novo;
    novo = (struct aluno*) malloc(sizeof(struct aluno));
    if(novo == NULL){
        return 0;
    }
    *novo = al;
    ha->itens[pos] = novo;
    ha->qtd++;
    printf("Aluno inserido\n");
    return 1;
}

int buscaHash_SemColisao(Hash* ha, int mat, struct aluno* al){
    if(ha == NULL){
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    if(ha->itens[pos] == NULL){
        return 0;
    }
    *al = *(ha->itens[pos]);
    return 1;
}

int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int sondagemQuadratica(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int duploHash(int H1, int chave, int i, int TABLE_SIZE){
    int H2 = chaveDivisao(chave, TABLE_SIZE-1) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereHash_EnderAberto(Hash* ha, struct aluno al){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE){
        return 0;
    }
    int chave = al.matricula;
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    for(i = 0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL){
            struct aluno* novo;
            novo = (struct aluno*) malloc(sizeof(struct aluno));
            if(novo == NULL){
                return 0;
            }
            *novo = al;
            ha->itens[newPos] = novo;
            ha->qtd++;
            printf("Aluno inserido\n");
            return 1;
        }
    }
    return 0;
}

int buscaHash_EnderAberto(Hash* ha, int mat, struct aluno* al){
    if(ha == NULL){
        return 0;
    }
    int i, pos, newPos;
    pos = chaveDivisao(mat, ha->TABLE_SIZE);
    for(i = 0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if(ha->itens[newPos] == NULL){
            return 0;
        }
        if(ha->itens[newPos]->matricula == mat){
            *al = *(ha->itens[newPos]);
            printf("Aluno encontrado no endereco: %d", newPos);
            return 1;
        }
    }
    return 0;
}

int main(){
    Hash* ha = criaHash(1427);
    struct aluno al;
    int mat = 12345;
    al.matricula = 12345;
    strcpy(al.nome, "Breno");
    al.nota = 8.5;
    //int x = insereHash_SemColisao(ha, al);
    int x = insereHash_EnderAberto(ha, al);
    //int y = buscaHash_SemColisao(ha, mat, &al);
    int y = buscaHash_EnderAberto(ha, mat, &al);
    //liberaHash(ha);
}

/*void inicializarTabela(tpAluno **tabela[]){
    printf("Entrou inicializar\n");
    for(int i = 0; i < MAX; i++){
        tabela[i] = NULL;
    }
 }

void inicializarTabelaHash(tpAluno *tbHash){
	int i = 0;
	for (i=0; i < MAX; i++)
		tbHash[i].matricula = -1;
}

void imprimir(tpAluno *tabela[MAX]){
    for(int i = 0; i < MAX; i++){
        if(tabela[i] != NULL){
            printf("Matricula: %d\n", tabela[i]->matricula);
            printf("Nome: %s\n", tabela[i]->nome);
            printf("Email: %s\n", tabela[i]->email);
        }
    }
 }

void imprimir2(tpAluno tabela[MAX]){
    for(int i = 0; i < MAX; i++){
        if(tabela[i].matricula != 0){
            printf("Matricula: %d\n", tabela[i].matricula);
            printf("Nome: %s\n", tabela[i].nome);
            printf("Email: %s\n", tabela[i].email);
        }
    }
}

int hash_alfa(char chave[]){
    int soma = 0;
    int i;
    int comp = strlen(chave);
    for (i = 0; i < comp; i++){
        soma = soma + (i * chave[i]);
    }
    // sugestão: soma = soma + ((i+1) * chave[i]);
    return (soma % MAX);
}

int hashUniversal(int chave){
    printf("Entrou hash\n");
    int soma = 0;
    int i;
    itoa(chave, chave, 10);
    int comp = strlen(chave);
    char aux[comp];
    for (i = 0; i < comp; i++){
        soma = soma + ((i+1) * aux[i]);
    }
    return (soma % MAX);
}

void inserir(tpAluno **tbHash[], tpAluno *reg){
    printf("Entrou inserir\n");
    // x é endereço do vetor
	int x = hashUniversal(reg->matricula);
	printf("%d\n", x);
	// não trata a colisão
	tpAluno *aux;
	aux = malloc(sizeof(tpAluno));
	aux->matricula = reg->matricula;
	strcpy(aux->nome,reg->nome);
	strcpy(aux->email,reg->email);
	tbHash[x] = aux;
	printf("Inseriu\n");
}

void inserir2(tpAluno *tbHash, tpAluno reg){
	// x é endereço do vetor
	int x = hashUniversal(reg.matricula);
   //  x será igual a 0 ou menor que MAX
	// não trata a colisão
	tbHash[x].matricula = reg.matricula;
	strcpy(tbHash[x].nome, reg.nome);
	strcpy(tbHash[x].email, reg.email);
}

void remocao(tpAluno **tbHash[], int matricula){
    int x = hashUniversal(matricula);
    tpAluno *aux = tbHash[x];
	if (aux->matricula == matricula){
		free (aux);
		tbHash[x] = NULL;
	}else{
        printf("Matrícula não existente na tabela");
 	}
}

void remocao2(tpAluno *tbHash, int matricula){
    int x = hashUniversal(matricula);
	 // verifica se a chave matricula está na tabela
    if (tbHash[x].matricula == matricula)
		tbHash[x].matricula = -1; // valor nulo
 	 else
		printf("Matrícula não existente na tabela");
}

void busca(tpAluno *tbHash[], int matricula){
	int x = hashUniversal(matricula);
	tpAluno *aux = tbHash[x];
   	if (aux != NULL){
		if (aux->matricula == matricula){
			printf("Nome: %s ", aux->nome);
			printf("Email: %s ", aux->email);
		}
   	}else{
        printf("Chave não existente na tabela");
   	}
}

void busca2(tpAluno *tbHash, int matricula){
   	int x = hashUniversal(matricula); // x é endereço do vetor
	// verifica se a chave matrícula está na tabela
    if (tbHash[x].matricula == matricula){
		printf("Nome: %s ", tbHash[x].nome);
		printf("Email: %s ", tbHash[x].email);
	}
 	else
		printf("Chave não existente na tabela");
}

int main(){
    //****Vetor de ponteiros*****
    tpAluno *tabHash[MAX];
    tpAluno *aux;
    aux = malloc (sizeof(tpAluno));
    aux->matricula = 321;
    strcpy(aux->nome, "Breno");
    strcpy(aux->email, "brenonalin@hotmail.com");
    inicializarTabela(&tabHash);
    printf("Vai entrar no inserir\n");
    inserir(&tabHash, aux);
    imprimir(&tabHash);

    //****Vetor*****
    /*tpAluno tabelaHash[MAX];

    for(int i = 0; i < MAX; i++){
        tabelaHash[i].matricula = 0;
    }
    tabelaHash[0].matricula = 321;
    strcat(tabelaHash[0].nome, "Breno");
    strcat(tabelaHash[0].email, "brenonalin@hotmial.com");;
    imprimir2(&tabelaHash);
}*/
