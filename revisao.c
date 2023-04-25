#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastra_usuario(char login[][13], char senha[][7], int privilegio[][3],
int linha) {
int i;
char *p;
char cont;
for (i=0; i<linha; i++) {
printf("\nUsuario %d:", i);
printf("\n\tlogin: ");
flushall();
fgets(login[i], 13, stdin); //limita entrada a 12 letras, pois
//última posição (coluna) tem de ser reservado para \0
flushall(); //limpa resquícios deixados no buffer
printf("\tsenha: ");
fgets(senha[i], 7, stdin);
flushall();
/*É preciso remover o caractere newline do string digitado.
strchr busca o char '\n' (newline) no string digitado. O ponteiro p
é igualado ao retorno desta função dentro do if.
Se o ponteiro não for NULL (isto é, o newline foi encontrado), então
o conteúdo da memória apontado por p é substituído por \0.
Ou seja, o newline é substituído por \o no string nome[i].*/
if ((p=strchr(login[i], '\n')) != NULL)
*p = '\0';
if ((p=strchr(senha[i], '\n')) != NULL)
*p = '\0';
printf("\tPrivilegio Armamentos: ");
scanf("%d", &privilegio[i][0]);
printf("\tPrivilegio Navegacao: ");
scanf("%d", &privilegio[i][1]);
printf("\tPrivilegio Comunicacoes: ");
scanf("%d", &privilegio[i][2]);
printf("\nDigite 'x' para sair, qualquer outra para continuar a entrada: ");
flushall();
scanf("%c", &cont);
if (cont == 'x')
return;
}
}


void lista_usuarios(char login[][13], char senha[][7], int privilegio[][3], int
linha) {
int i, j;
printf("\n\nTabela de Controle de Acessos\n\n");
printf("\t\t\t\tPrivilegios\n");
printf("Login\t\tSenha\tSubSist 1 SubSist 2 SubSist 3\n");
for (i=0; i<linha; i++) {
printf("\n%12s\t%6s\t", login[i], senha[i]);
for (j=0; j<3; j++) {
printf("\t%d", privilegio[i][j]);
}
}
}

int pedido_acesso(char login[][13], char senha[][7], int privilegio[][3], int
linha, int subsis) {
char loginl[13], senhal[7];
char *p;
int i=0;
printf("\nLogin: ");
flushall();
fgets(loginl, 13, stdin);
flushall();
printf("\nSenha: ");
fgets(senhal, 7, stdin);
flushall();
//remove newline \n se houver
if ((p=strchr(loginl, '\n')) != NULL)
*p = '\0';
if ((p=strchr(senhal, '\n')) != NULL)
*p = '\0';
//faz busca na lista de usuarios e compara senha
while (i<linha) {
if (strcmp(loginl, login[i])==0) { //login encontrado
if (strcmp(senhal, senha[i])==0)
return privilegio[i][subsis]; //senha confere; retorne privilégio
else
return -1; //login encontrado, mas senha não confere; retorne imediatamente com -1
}
i++; //login ainda não encontrado; continue a busca
}
return -1; //login não encontrado na lista; retorne com -1
}

void mensagem(int privSubsis, int priv) {
if (privSubsis < priv)
printf("\nAcesso liberado.");
else if (priv == -1)
printf("\nSenha invalida ou usuario inexistente.");
else printf("\nAcesso negado.");
}

int main() {
    char login[3][13]={0}, senha[3][7]={0};
    int privilegio[3][3]={0};
    int escolha, priv;

    while (1) {
        printf("\n\nSistema de Controle de Acesso - Submarino Nuclear\n\n");
        printf("1 - Cadastrar usuarios, senhas, privilegios");
        printf("\n2 - Listar usuarios, senhas, privilegios");
        printf("\n3 - Acessar Sub-sistema Armamentos");
        printf("\n4 - Acessar Sub-sistema Navegacao");
        printf("\n5 - Acessar Sub-sistema Comunicacoes");
        printf("\n0 - Sair do programa");
        printf("\nopcao: ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                cadastra_usuario(login, senha, privilegio, 3);
                break;
            case 2:
                lista_usuarios(login, senha, privilegio, 3);
                break;
            case 3:
                mensagem(8, priv);
                break;
            case 4:
                priv=pedido_acesso(login, senha, privilegio, 3, 1);
                mensagem(3, priv);
                break;
            case 5:
                priv=pedido_acesso(login, senha, privilegio, 3, 2);
                mensagem(4, priv);
                break;
            case 0:
                return 0;
                break;
            default:
                printf("\nOpcao invalida.");
                break;
        }
    }
}
