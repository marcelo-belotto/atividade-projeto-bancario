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

void cadastrar(struct Conta * contas,int posicaoAtual){
    contas[posicaoAtual].cliente.Id = posicaoAtual+1;
    printf("Nome do Cliente: ");
    scanf("%s", &contas[posicaoAtual].cliente.Nome);
    printf("Agência: ");
    scanf("%d", &contas[posicaoAtual].Agencia);
    printf("Conta: ");
    scanf("%s", &contas[posicaoAtual].ContaCorrente);
    contas[posicaoAtual].SaldoAtual = 0.00;
    printf("\nCliente Cadastrado com sucesso!\n");
}

bool depositar(struct Conta * conta,double valorDeposito){
    conta->SaldoAtual = conta->SaldoAtual + valorDeposito;
    return true;
}

bool sacar(struct Conta * conta,double valorSaque){
    if (valorSaque <= conta->SaldoAtual){
        conta->SaldoAtual = conta->SaldoAtual - valorSaque;
        return true;
    }else{
        printf("Saldo Insuficiente!\n");
        return false;
    }
}


bool transferir(struct Conta * origem, struct Conta * destino,double valorTransferencia){
    if (sacar(origem,valorTransferencia)){
        depositar(destino,valorTransferencia);
        return true;
    }
    return false;

}

int localizarContaCorrente(struct Conta * contas,int posicaoAtual){
    char numeroConta[10];
    int Id = -1;
    printf("Conta Corrente: ");
    scanf("%s",&numeroConta);
    for (int i = 0; i < posicaoAtual;i++){
        if (strcmp(numeroConta,contas[i].ContaCorrente)==0){
            Id = i;
            return Id;
        }
    }
    return Id;
}

void exibirTodosOsClientes(struct Conta * contas,int posicaoAtual){
    printf("\t\tTodos os Clientes\n");
    printf("|Nome\t\t|Agencia\t|Conta\t|Saldo\n");
    for (int i = 0; i < posicaoAtual;i++){
        printf("|%s\t",contas[i].cliente.Nome);
        printf("|%d\t\t",contas[i].Agencia);
        printf("|%s\t",contas[i].ContaCorrente);
        printf("|%.2f\n",contas[i].SaldoAtual);
    }
}

void exibirUmCliente(struct Conta * contas, int posicaoAtual){
    int idCliente = localizarContaCorrente(contas,posicaoAtual);
    if (idCliente >= 0){
        printf("|Nome\t\t|Agencia\t|Conta\t|Saldo\n");
        printf("|%s\t",contas[idCliente].cliente.Nome);
        printf("|%d\t\t",contas[idCliente].Agencia);
        printf("|%s\t",contas[idCliente].ContaCorrente);
        printf("|%.2f\n",contas[idCliente].SaldoAtual);
    }
}


/*sacar, depositar, efetuar pix, cadastrar novo cliente, transferir dinheiro
entre contas e consultar saldo. (A consulta deverá apresentar informação da conta de um
cliente específico ou de todas as contas cadastradas).*/
int main()
{
    //ToDo: Carregar clientes através de um arquivo a parte
    bool menuAtivado = true;
    int opcaoSelecionada,posicaoAtual = 0;
    double valorSaque,valorDeposito;
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
                    int IdCliente = localizarContaCorrente(contas,posicaoAtual);
                    if (IdCliente < 0){
                        printf("Conta Corrente não encontrada!\n");
                        break;
                    }
                    printf("Valor a ser Depositado: ");
                    scanf("%lf", &valorDeposito);
                    if (valorDeposito <= 0 ){
                        printf("Valor inválido!\n");
                        break;
                    }
                    if (depositar(&contas[IdCliente],valorDeposito)){
                        printf("Deposito Realizado com sucesso!\n");
                    }
                }
            break;
            case 3:
                if (posicaoAtual != 0){
                    int IdCliente = localizarContaCorrente(contas,posicaoAtual);
                    if (IdCliente < 0){
                        printf("Conta Corrente não encontrada!\n");
                        break;
                    }
                    printf("Valor a ser retirado: ");
                    scanf("%lf", &valorSaque);
                    if (valorSaque < 0 ){
                        printf("Valor inválido!\n");
                        break;
                    }
                    if (sacar(&contas[IdCliente],valorSaque)){
                        printf("Saque Realizado com sucesso!\n");
                    }

                }
            break;
            case 4:
                if (posicaoAtual != 0){
                    int idClienteOrigem,idClienteDestino;
                    double valorTransferencia;
                    printf("Origem:\n");
                    idClienteOrigem = localizarContaCorrente(contas,posicaoAtual);
                    if (idClienteOrigem < 0){
                        printf("Conta de Origem não encontrada\n");
                        break;
                    }
                    printf("Destino:\n");
                    idClienteDestino = localizarContaCorrente(contas,posicaoAtual);
                    if (idClienteDestino < 0){
                        printf("Conta de Destino não encontrada\n");
                        break;
                    }
                    printf("Valor da Transferência: ");
                    scanf("%lf",&valorTransferencia);
                    if (transferir(&contas[idClienteOrigem],&contas[idClienteDestino],valorTransferencia)){
                        printf("Transferência realizada com sucesso!\n");
                    }else{
                        printf("Ocorreu um erro durante a Transferência!\n");
                    }
                }
            break;
            case 5:
            //Area Pix
            break;
            case 6:
                int opcaoExibirSaldo;
                printf("1 - Pesquisar por conta\n2 - Exibir Todos\nOpção: ");
                scanf("%d", &opcaoExibirSaldo);
                switch (opcaoExibirSaldo){
                    case 1:
                        exibirUmCliente(contas,posicaoAtual);
                    break;
                    case 2:
                        exibirTodosOsClientes(contas,posicaoAtual);
                    break;
                    default:
                        printf("\nOpção Inválida!\n");
                    break;
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
