#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "loja.h"


int main (){
    Produto produtos[20];
    Venda vendas[20];
    Produto P;
    Venda V;
    int numeroProdutos = 0, numeroVendas = 0;
    char descricao[50], nomeComprador[50];
    int estoque, id, quantidade, produtosCarrinho;
    float valor;
    int resposta = -1;
    float valorTotal;

    inicializarProdutos(produtos, &numeroProdutos);

    // Loop principal do programa que exibe o menu e processa a escolha do usuário
    while (resposta != 0){

        resposta = menu();// Exibe o menu e registra a resposta do usuário
        
        switch (resposta) {
            case 1:
            // Registrar venda
                printf("\nDigite o nome do comprador: \n");
                while (getchar() != '\n');
                fgets(nomeComprador, sizeof(nomeComprador), stdin);
                nomeComprador[strcspn(nomeComprador, "\n")] = '\0';
                produtosCarrinho = 0;
                Carrinho carrinho[20];
                id = -1;
                valorTotal = 0;
                int numItens = 0;
                
                // Loop para adicionar produtos ao carrinho até que o usuário digite 0
                while(id != 0){

                    mostrarEstoque(produtos, numeroProdutos);

                    if(numeroProdutos == 0){
                        break; // Sai do loop se não houver produtos
                    }

                    if(numeroProdutos > 0){
                        printf("\nDigite o ID do produto desejado (0 para confirmar produtos): \n");
                        scanf("%d", &id);

                        if(id < 0 || id > numeroProdutos){
                            printf("\nProduto com ID %d nao encontrado!\n\n", id);
                        }
                        else if (id != 0){
                            Produto p = produtos[id - 1];
                            
                            if(p.estoque < 1){
                                printf("\nProduto indisponivel!\n\n");
                            }
                            else{
                                printf("\nDigite a quantidade desejada: \n");
                                scanf("%d", &quantidade);

                                if(quantidade > p.estoque){
                                    printf("\nQuantidade indisponivel.\n\n");
                                }
                                else {
                                    // Adiciona o produto ao carrinho
                                    carrinho[produtosCarrinho].produto = p;
                                    carrinho[produtosCarrinho].quantidade = quantidade;
                                    valorTotal += p.valor * quantidade; // Atualiza o valor total
                                    produtos[id - 1].estoque -= quantidade;// Atualiza o estoque 
                                    produtosCarrinho++;
                                    numItens++;
                                    printf("\nProduto adicionado no carrinho!\n\n");
                                }
                            }
                        }   
                    }
                }
                
                // Confirmação da compra
                if(numeroProdutos > 0){
                    printf("\nFinalizando compra\n");

                    int temp = -1;

                    while(temp < 0 || temp > 1){
                    printf("Valor total: %.2f\n", valorTotal);
                    printf("Deseja confirmar a compra? (1 - Sim; 0 - Nao)\n");
                    scanf("%d", &temp);
                    }

                    // Cancela a compra e repõe os produtos no estoque
                    if(!temp){
                        for(int i = 0; i < produtosCarrinho; i++){
                            produtos[carrinho[i].produto.id - 1].estoque += carrinho[i].quantidade;
                        }
                        printf("Compra cancelada com sucesso!\n\n");
                    }
                    // Confirma a compra e registra a venda
                    else{
                        setVenda(&V, &numeroVendas, nomeComprador, carrinho, numItens, valorTotal);
                        vendas[numeroVendas - 1] = V;
                        printf("Compra efetuada com sucesso!\n\n");
                    }
                }     
                break;

            case 2:
                // Repor estoque
                reporEstoque(produtos, numeroProdutos);
                break;

            case 3:
                // Mostrar estoque
                mostrarEstoque(produtos, numeroProdutos);
                break;

            case 4:
                // Mostrar compras
                mostrarCompras(vendas, numeroVendas);
                break;

            case 5:
                // Maior compra
                maiorCompra(vendas, numeroVendas);
                break;

            case 6:
            // Cadastrar produto
    
                printf("\nDigite a descricao do produto: \n");
                while (getchar() != '\n');
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0';

                printf("Digite a quantidade em estoque:\n");
                scanf("%d", &estoque);

                printf("Digite o valor do produto:\n");
                scanf("%f", &valor);

                // Adiciona o novo produto ao vetor de produtos
                setProduto(&P, &numeroProdutos, descricao, estoque, valor);
                produtos[numeroProdutos - 1] = P;
                break;

            case 0:
                break;
        }
    }


    return 0;
}

//Apresenta e retorna a opção selecionada pelo usuário
int menu() {
    int resposta = -1;
    while (resposta < 0 || resposta > 6) {

        printf("\n\nOla, segue a lista de opcoes:\n");
        printf("1 - Registrar venda.\n");
        printf("2 - Repor estoque de produto.\n");
        printf("3 - Mostrar estoque.\n");
        printf("4 - Mostrar vendas.\n");
        printf("5 - Mostrar maior venda.\n");
        printf("6 - Adicionar produto.\n");
        printf("0 - Sair\n");
        printf("\nO que deseja fazer?\n");
        scanf("%d", &resposta);
        
        //Caso seja digitado uma opção fora do menu
        if (resposta >= 7 || resposta < 0) 
        {
            printf("\nEscolha uma alternatativa valida! \n");
        }
    }

    return resposta;
}

//Inicializa um objeto Produto com os dados fornecidos
void setProduto(Produto *P, int *id, char descricao[], int estoque, float valor){
    strcpy(P->descricao, descricao);
    (*id)++;
    P->id = *id;
    P->estoque = estoque;
    P->valor = valor;
}

//Lista todos os produtos em estoque
void mostrarEstoque(Produto produtos[], int qtdeProdutos){
    if(qtdeProdutos < 1){
        printf("\nNenhum produto em estoque\n");
    }
    else{
        printf("\nProdutos em estoque: \n\n");
        printf("%-8s %-20s %-10s %-8s\n", "ID", "Descricao", "Valor", "Estoque");
        for (int i = 0; i < qtdeProdutos; i++) {
            if (produtos[i].estoque > 0) {
                Produto p = produtos[i];
                char descricao[21];
                strncpy(descricao, p.descricao, 17);
                descricao[17] = '.';
                descricao[18] = '.';
                descricao[19] = '.';
                descricao[20] = '\0';
                printf("%-8d %-20s %-10.2f %-8d\n", p.id, descricao, p.valor, p.estoque);

            }
        }
    }
}

//Inicializa uma venda com os dados fornecidos
void setVenda(Venda *V, int *id, char nomeComprador[], Carrinho carrinho[], int numItens, float valorTotal){
    strcpy(V->nomeComprador, nomeComprador);
    (*id)++;
    V->id = *id;
    V->valorTotal = valorTotal;
    V->numItens = numItens;
    for (int i = 0; i < numItens; i++) {
        V->carrinho[i] = carrinho[i];
    }
}

//Inicializa um vetor de produtos com valores predefinidos.
void inicializarProdutos(Produto produtos[], int *numeroProdutos) {
    Produto P;

    setProduto(&P, numeroProdutos, "Calca", 20, 112.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Camisa", 18, 95.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Bermuda", 23, 49.90);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Saia", 12, 169.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Blusa", 9, 120.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Moletom", 4, 135.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Meia", 17, 12.99);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Tenis", 8, 183.00);
    produtos[*numeroProdutos - 1] = P;

    setProduto(&P, numeroProdutos, "Bota", 3, 219.90);
    produtos[*numeroProdutos - 1] = P;
}

// Função para repor o estoque de um produto
void reporEstoque(Produto produtos[], int numeroProdutos) {
    
    int id, quantidade;

    mostrarEstoque(produtos, numeroProdutos);
    printf("\nDigite o ID do produto para repor o estoque: \n");
    scanf("%d", &id);

    if (id <= 0 || id > numeroProdutos) {
        printf("Produto com ID %d nao encontrado!\n\n", id);
    } else {
        printf("Digite a quantidade a ser adicionada ao estoque: \n");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            printf("Quantidade invalida!\n\n");
        } else {
            produtos[id - 1].estoque += quantidade; // Atualiza o estoque do produto
            printf("Estoque do produto %s atualizado para %d unidades.\n\n",
                   produtos[id - 1].descricao, produtos[id - 1].estoque);
        }
    }
}

// Função para exibir todas as compras realizadas
void mostrarCompras(Venda vendas[], int numeroVendas) {
    if (numeroVendas == 0) {
        printf("\nNenhuma venda registrada.\n");
    } else {
        printf("\nHistorico de vendas:\n\n");
        // Exibe cada venda registrada
        for (int i = 0; i < numeroVendas; i++) {
            printf("Venda ID: %d\n", vendas[i].id);
            printf("Nome do Comprador: %s\n", vendas[i].nomeComprador);
            printf("Valor Total: %.2f\n", vendas[i].valorTotal);
            printf("Itens Comprados:\n");
            // Exibe os itens comprados na venda
            for (int j = 0; j < vendas[i].numItens; j++) {
                printf("- %s (Quantidade: %d, Preco unitario: %.2f)\n",
                       vendas[i].carrinho[j].produto.descricao,
                       vendas[i].carrinho[j].quantidade,
                       vendas[i].carrinho[j].produto.valor);
            }
            printf("\n");
        }
    }
}

// Função para encontrar e exibir a maior compra registrada
void maiorCompra(Venda vendas[], int numeroVendas) {
    if (numeroVendas == 0) {
        printf("\nNenhuma venda registrada.\n");
    } else {
        float maiorValor = vendas[0].valorTotal;
        int indiceMaiorVenda = 0;

        // Encontra a venda com o maior valor total
        for (int i = 1; i < numeroVendas; i++) {
            if (vendas[i].valorTotal > maiorValor) {
                maiorValor = vendas[i].valorTotal;
                indiceMaiorVenda = i;
            }
        }

        // Exibe a maior venda
        printf("\nMaior venda registrada:\n\n");
        printf("Venda ID: %d\n", vendas[indiceMaiorVenda].id);
        printf("Nome do Comprador: %s\n", vendas[indiceMaiorVenda].nomeComprador);
        printf("Valor Total: %.2f\n", vendas[indiceMaiorVenda].valorTotal);
        printf("Itens Comprados:\n");
        // Exibe os itens comprados na maior venda
        for (int j = 0; j < vendas[indiceMaiorVenda].numItens; j++) {
            printf("- %s (Quantidade: %d, Preco unitario: %.2f)\n",
                   vendas[indiceMaiorVenda].carrinho[j].produto.descricao,
                   vendas[indiceMaiorVenda].carrinho[j].quantidade,
                   vendas[indiceMaiorVenda].carrinho[j].produto.valor);
        }
        printf("\n");
    }
}

