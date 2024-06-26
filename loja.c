#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "loja.h"

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

