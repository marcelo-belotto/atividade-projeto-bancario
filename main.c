#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Conta{
    int Agencia;
    char ContaCorrente[10];
    double SaldoAtual;
};

struct Cliente{
    int Id;
    char Nome[50];
    struct Conta conta;
};

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

void cadastrar(struct Cliente * cliente,int posicaoAtual){
    cliente[posicaoAtual].Id = posicaoAtual+1;
    printf("Nome do Cliente: ");
    scanf("%s", &cliente[posicaoAtual].Nome);
    printf("Agência da Conta: ");
    scanf("%d", &cliente[posicaoAtual].conta.Agencia);
    printf("Numero da Conta: ");
    scanf("%s", &cliente[posicaoAtual].conta.ContaCorrente);
    cliente[posicaoAtual].conta.SaldoAtual = 0.00;
    printf("\nCliente Cadastrado com sucesso!\n");
}

void depositar(struct Cliente * cliente,int posicaoAtual){
    char numeroConta[10];
    double valorDeposito;
    printf("Digite o numero da Conta para deposito: ");
    scanf("%s",&numeroConta);
    for (int i = 0; i < posicaoAtual;i++){
        if (strcmp(numeroConta,cliente[i].conta.ContaCorrente)==0){
            printf("Digite o valor a ser depositado: ");
            scanf("%lf", &valorDeposito);
            if (valorDeposito > 0){
                cliente[i].conta.SaldoAtual = cliente[i].conta.SaldoAtual + valorDeposito;
            }else{
                printf("Valor inválido!\n");
            }
        }else{
            printf("Conta Corrente não encontrada!\n");
        }
    }
}

void sacar(struct Cliente * cliente,int posicaoAtual){
    char numeroConta[10];
    double valorSaque;
    printf("Digite o numero da conta para saque: ");
    scanf("%s",&numeroConta);
    for (int i = 0; i < posicaoAtual;i++){
        if (strcmp(numeroConta,cliente[i].conta.ContaCorrente)==0){
            printf("Digite o valor a ser sacado: ");
            scanf("%lf", &valorSaque);
            if (valorSaque > 0 ){
                if (valorSaque < cliente[i].conta.SaldoAtual){
                    cliente[i].conta.SaldoAtual = cliente[i].conta.SaldoAtual - valorSaque;
                }else{
                    printf("Saldo Insuficiente!\n");
                }
            }else{
                printf("Valor inválido!\n");
            }
        }else{
            printf("Conta Corrente não encontrada!\n");
        }
    }
}


void transferir(){

}

int main()
{
    bool menuAtivado = true;
    int opcaoSelecionada,posicaoAtual = 0;
    struct Cliente clientes[5];

    while (menuAtivado){
        menu();
        printf("OPERAÇÃO: ");
        scanf("%d",&opcaoSelecionada);
        switch(opcaoSelecionada){
            case 1:
                if(posicaoAtual < 5){
                    cadastrar(clientes,posicaoAtual);
                    posicaoAtual++;
                }else{
                    printf("Numero de Clientes totais atingido!");
                }
            break;
            case 2:
                if (posicaoAtual != 0){
                    depositar(clientes,posicaoAtual);
                }
            break;
            case 3:
            if (posicaoAtual != 0){
                    sacar(clientes,posicaoAtual);
                }
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
                for (int i = 0; i < posicaoAtual;i++){
                    printf("%d |",clientes[i].Id);
                    printf("%s |",clientes[i].Nome);
                    printf("%d |",clientes[i].conta.Agencia);
                    printf("%s |",clientes[i].conta.ContaCorrente);
                    printf("%.2f\n",clientes[i].conta.SaldoAtual);
                }
            break;
            case 7:
                menuAtivado = false;
            break;
            default:
                printf("Opção Inválida!\n");
            break;

        }
    }
}
/*
for (int i = 0; i < posicaoAtual;i++){
printf("%d |",clientes[i].Id);
printf("%s |",clientes[i].Nome);
printf("%d |",clientes[i].conta.Agencia);
printf("%d |",clientes[i].conta.ContaCorrente);
printf("%.2f\n",clientes[i].conta.SaldoAtual);
}*/
