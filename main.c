#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    int Id;
    char Nome[50];
}Cliente;

typedef struct{
    int Agencia;
    char ContaCorrente[10];
    double SaldoAtual;
    Cliente cliente;
}Conta;

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

bool cadastrar(Conta * contas,int posicaoAtual){
    int idTemp = posicaoAtual+1;
    char nomeTemp[50];
    int agenciaTemp;
    char contaCorrente[50];

    printf("Nome do Cliente: ");
    scanf("%s", &nomeTemp);
    printf("Agência: ");
    scanf("%d", &agenciaTemp);
    printf("Conta: ");
    scanf("%s", &contaCorrente);

    for (int i = 0; i < posicaoAtual;i++){
        if (strcmp(contaCorrente,contas[i].ContaCorrente)==0){
            return false;
        }
    }
    contas[posicaoAtual].cliente.Id = idTemp;
    strcpy(contas[posicaoAtual].cliente.Nome,nomeTemp);
    contas[posicaoAtual].Agencia = agenciaTemp;
    strcpy(contas[posicaoAtual].ContaCorrente,contaCorrente);
    contas[posicaoAtual].SaldoAtual = 0.00;
    return true;
}

bool depositar(Conta * conta,double valorDeposito){
    conta->SaldoAtual = conta->SaldoAtual + valorDeposito;
    return true;
}

bool sacar(Conta * conta,double valorSaque){
    if (valorSaque < 0){
        printf("Valor Inválido!\n");
        return false;
    }
    if (valorSaque <= conta->SaldoAtual){
        conta->SaldoAtual = conta->SaldoAtual - valorSaque;
        return true;
    }else{
        printf("Saldo Insuficiente!\n");
        return false;
    }
}

bool transferir(Conta * origem,Conta * destino,double valorTransferencia){
    if (sacar(origem,valorTransferencia)){
        depositar(destino,valorTransferencia);
        return true;
    }
    return false;

}

int localizarContaCorrente(Conta * contas,int posicaoAtual){
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

void exibirTodosOsClientes(Conta * contas,int posicaoAtual){
    printf("\t\t\tTodos os Clientes\n");
    printf("Nome\t\t|Agencia\t|Conta\t|Saldo\n\n");
    for (int i = 0; i < posicaoAtual;i++){
        printf("%-15s\t",contas[i].cliente.Nome);
        printf("|%d\t\t",contas[i].Agencia);
        printf("|%s\t",contas[i].ContaCorrente);
        printf("|%.2f\n",contas[i].SaldoAtual);
    }
}

void exibirUmCliente(Conta * contas, int posicaoAtual){
    int idCliente = localizarContaCorrente(contas,posicaoAtual);
    if (idCliente >= 0){
        printf("|Nome\t\t|Agencia\t|Conta\t|Saldo\n");
        printf("|%s\t",contas[idCliente].cliente.Nome);
        printf("|%d\t\t",contas[idCliente].Agencia);
        printf("|%s\t",contas[idCliente].ContaCorrente);
        printf("|%.2f\n",contas[idCliente].SaldoAtual);
    }
}

int contarLinhas(const char *filename) {
    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) {
        return -1;
    }

    int contador = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        contador++;
    }

    fclose(arquivo);
    return contador;
}

void pegarDadosDoBanco(Conta * contas,const char *filename){
    FILE *arquivo = fopen(filename, "r");
    char linha[256];
    int posicaoLinha = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");
        int coluna = 0;
        while (registro && coluna < 5) {
            switch (coluna) {
                case 0:
                //ID
                    contas[posicaoLinha].cliente.Id = atoi(registro);
                    break;
                case 1:
                //CLIENTE
                    strncpy(contas[posicaoLinha].cliente.Nome, registro, 50);
                    contas[posicaoLinha].cliente.Nome[49] = '\0';
                    break;
                case 2:
                //AGENCIA
                    contas[posicaoLinha].Agencia = atoi(registro);
                    break;
                case 3:
                //CONTA CORRENTE
                    strncpy(contas[posicaoLinha].ContaCorrente, registro, 10);
                    contas[posicaoLinha].ContaCorrente[9] = '\0';
                    break;
                case 4:
                //SALDO ATUAL
                    contas[posicaoLinha].SaldoAtual = atof(registro);
                    break;
            }
            registro = strtok(NULL, ",");
            coluna++;
        }
        posicaoLinha++;
    }
    fclose(arquivo);
}

bool adicionarAoBanco(Conta* conta,const char *filename){
    FILE *arquivo = fopen(filename,"a");
    if (!arquivo) {
        return false;
    }
    fprintf(arquivo, "%d,%s,%d,%s,%.2f\n", conta->cliente.Id, conta->cliente.Nome,
    conta->Agencia,conta->ContaCorrente,conta->SaldoAtual);
    fclose(arquivo);
    return true;
}

void atualizaBancoDeDados(Conta* contas,int posicaoAtual, const char *filename){
    remove(filename);
    FILE * arquivo = fopen(filename,"wt");
    if (!arquivo) {
        return;
    }
    for (int i = 0; i < posicaoAtual;i++){
        fprintf(arquivo, "%d,%s,%d,%s,%.2f\n", contas[i].cliente.Id, contas[i].cliente.Nome,contas[i].Agencia,
        contas[i].ContaCorrente,contas[i].SaldoAtual);
    }
    fclose(arquivo);
}

/*DESCRIÇÂO DO PROBLEMA
sacar, depositar, efetuar pix, cadastrar novo cliente, transferir dinheiro
entre contas e consultar saldo. (A consulta deverá apresentar informação da conta de um
cliente específico ou de todas as contas cadastradas).*/

int main()
{
    const char *database = "database.csv";
    bool menuAtivado = true;
    int opcaoSelecionada,posicaoAtual = 0;
    double valorSaque,valorDeposito;
    int capacidade = contarLinhas(database);
    Conta *contas;

    if (capacidade < 0){
        capacidade = 5;
        contas = (Conta *)malloc(capacidade * sizeof(Conta));
    }else{
        posicaoAtual = capacidade;
        contas = (Conta *)malloc(capacidade * sizeof(Conta));
        pegarDadosDoBanco(contas,database);
    }

    while (menuAtivado){
        menu();
        if(posicaoAtual >= capacidade){
            capacidade *= 2;
            contas = realloc(contas,capacidade * sizeof(Conta));
        }
        printf("OPERAÇÃO: ");
        scanf("%d",&opcaoSelecionada);
        switch(opcaoSelecionada){
            case 1:
                if (cadastrar(contas,posicaoAtual)){
                    if (adicionarAoBanco(&contas[posicaoAtual],database)){
                        printf("\nCliente Cadastrado com sucesso!\n");
                        posicaoAtual++;
                    }else{
                        printf("\nFalha ao Cadastrar novo cliente!\n");
                    }
                }else{
                    printf("\nConta Corrente já existente!\n");
                }
            break;
            case 2:
                if (posicaoAtual != 0){
                    int IdCliente = localizarContaCorrente(contas,posicaoAtual);
                    if (IdCliente < 0){
                        printf("Conta Corrente não encontrada!\n");
                        break;
                    }
                    char valorTemp[200];
                    printf("Valor a ser Depositado: ");
                    scanf("%s", &valorTemp);
                    for (int i = 0; i < strlen(valorTemp);i++){
                        if (valorTemp[i] == ','){
                            valorTemp[i] = '.';
                        }
                    }
                    valorDeposito = atof(valorTemp);
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
                    char valorTemp[200];
                    printf("Valor a ser retirado: ");
                    scanf("%s", &valorTemp);
                    for (int i = 0; i < strlen(valorTemp);i++){
                        if (valorTemp[i] == ','){
                            valorTemp[i] = '.';
                        }
                    }
                    valorSaque = atof(valorTemp);
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
                    int posicaoClienteOrigem,posicaoClienteDestino;
                    double valorTransferencia;
                    printf("Origem:\n");
                    posicaoClienteOrigem = localizarContaCorrente(contas,posicaoAtual);
                    if (posicaoClienteOrigem < 0){
                        printf("Conta de Origem não encontrada\n");
                        break;
                    }
                    printf("Destino:\n");
                    posicaoClienteDestino = localizarContaCorrente(contas,posicaoAtual);
                    if (posicaoClienteDestino < 0){
                        printf("Conta de Destino não encontrada\n");
                        break;
                    }
                    char valorTemp[200];
                    printf("Valor da Transferência: ");
                    scanf("%s",&valorTemp);
                    for (int i = 0; i < strlen(valorTemp);i++){
                        if (valorTemp[i] == ','){
                            valorTemp[i] = '.';
                        }
                    }
                    valorTransferencia = atof(valorTemp);
                    if (transferir(&contas[posicaoClienteOrigem],&contas[posicaoClienteDestino],valorTransferencia)){
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
        atualizaBancoDeDados(contas,posicaoAtual,database);
    }
    free(contas);
}
