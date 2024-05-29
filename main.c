#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct Cliente{
    int Id;
    char Nome[50];
};

struct Conta{
    int Agencia;
    char ContaCorrente[10];
    double SaldoAtual;
    struct Cliente cliente;
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

void cadastrar(struct Conta * contas,int posicaoAtual){
    contas[posicaoAtual].cliente.Id = posicaoAtual+1;
    printf("Nome do Cliente: ");
    scanf("%s", &contas[posicaoAtual].cliente.Nome);
    printf("Agência da Conta: ");
    scanf("%d", &contas[posicaoAtual].Agencia);
    printf("Numero da Conta: ");
    scanf("%s", &contas[posicaoAtual].ContaCorrente);
    contas[posicaoAtual].SaldoAtual = 0.00;
    printf("\nCliente Cadastrado com sucesso!\n");
}

void depositar(struct Conta * contas,int posicaoAtual){

    double valorDeposito;
    int IdCliente = localizaContaCorrente(contas,posicaoAtual);

    if (IdCliente >= 0){
        printf("Valor a ser depositado: ");
        scanf("%lf", &valorDeposito);
        if (valorDeposito > 0){
            contas[IdCliente].SaldoAtual = contas[IdCliente].SaldoAtual + valorDeposito;
            printf("Deposito Realizado com sucesso!\n");

        }else{
            printf("Valor inválido!\n");
        }
    }else{
        printf("Conta Corrente não encontrada!\n");
    }
    sleep(1);
}

void sacar(struct Conta * contas,int posicaoAtual){
    double valorSaque;
    int IdCliente = localizaContaCorrente(contas,posicaoAtual);

    if (IdCliente >= 0){
        printf("Valor a ser retirado: ");
        scanf("%lf", &valorSaque);
        if (valorSaque > 0 ){
            if (valorSaque <= contas[IdCliente].SaldoAtual){
                contas[IdCliente].SaldoAtual = contas[IdCliente].SaldoAtual - valorSaque;
                printf("Saque Realizado com sucesso!\n");

            }else{
                printf("Saldo Insuficiente!\n");
            }
        }else{
            printf("Valor inválido!\n");
        }
    }else{
        printf("Conta Corrente não encontrada!\n");
    }
    sleep(1);
}


void transferir(){

}

int localizaContaCorrente(struct Conta * contas,int posicaoAtual){
    char numeroConta[10];
    double valorSaque;
    int Id = -1;
    printf("Numero da conta: ");
    scanf("%s",&numeroConta);
    for (int i = 0; i < posicaoAtual;i++){
        if (strcmp(numeroConta,contas[i].ContaCorrente)==0){
            Id = i;
            return Id;
        }
    }
    return Id;
}

void mostrarTodosOsDados(struct Conta * contas,int posicaoAtual){
    printf("\t\tTodos os Clientes\n");
    printf("|Id\t|Nome\t\t|Agencia\t|Conta\t|Saldo\n");
    for (int i = 0; i < posicaoAtual;i++){
        printf("|%d\t",contas[i].cliente.Id);
        printf("|%s\t",contas[i].cliente.Nome);
        printf("|%d\t\t",contas[i].Agencia);
        printf("|%s\t",contas[i].ContaCorrente);
        printf("|%.2f\n",contas[i].SaldoAtual);
    }
}

int main()
{
    //ToDo: Carregar clientes através de um arquivo a parte
    bool menuAtivado = true;
    int opcaoSelecionada,posicaoAtual = 0;
    struct Conta contas[5];

    while (menuAtivado){
        menu();
        printf("OPERAÇÃO: ");
        scanf("%d",&opcaoSelecionada);
        switch(opcaoSelecionada){
            case 1:
                if(posicaoAtual < 5){
                    cadastrar(contas,posicaoAtual);
                    posicaoAtual++;
                }else{
                    printf("Numero de Clientes totais atingido!");
                }
            break;
            case 2:
                if (posicaoAtual != 0){
                    depositar(contas,posicaoAtual);
                }
            break;
            case 3:
            if (posicaoAtual != 0){
                    sacar(contas,posicaoAtual);
                }
            break;
            case 4:
            //Transferir
            break;
            case 5:
            //Area Pix
            break;
            case 6:
            //Consultar saldo
            //ToDo: pesquisa binária
                mostrarTodosOsDados(contas,posicaoAtual);
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
