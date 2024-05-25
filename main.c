#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void menu(){
    for (int i = 0; i < 50; i++){
        printf("=");
    }
    printf("\n");
    printf("1 - CADASTRO\n");
    printf("2 - DEPOSITAR\n");
    printf("3 - SACAR\n");
    printf("4 - TRANFERIR\n");
    printf("5 - PIX\n");
    printf("6 - CONSULTAR SALDO\n");
    printf("7 - SAIR\n");
    for (int i = 0; i < 50; i++){
        printf("=");
    }
    printf("\n");
}
/*sacar, depositar, efetuar pix, cadastrar novo cliente, transferir dinheiro
entre contas e consultar saldo. (A consulta deverá apresentar informação da conta de um
cliente específico ou de todas as contas cadastradas).*/

int main()
{
    bool menuAtivado = true;
    int opcaoSelecionada;

    while (menuAtivado){
        menu();
        printf("OPERAÇÃO: ");
        scanf("%d",&opcaoSelecionada);
        switch(opcaoSelecionada){
            case 1:
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
                menuAtivado = false;
            break;
            default:
            break;

        }
    }
}
