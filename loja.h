#ifndef LOJA_H
#define LOJA_H

//Representa um produto na loja
typedef struct {
    int id; 
    char descricao[50];
    int estoque;
    float valor;
} Produto;

//Representa um item no carrinho de compras
typedef struct{
    Produto produto;
    int quantidade;
} Carrinho;

//Representa uma venda realizada
typedef struct {
    int id;
    char nomeComprador[50];
    Carrinho carrinho[20];
    int numItens;
    float valorTotal;
} Venda;

int menu();
void setProduto(Produto *P, int *id, char descricao[], int estoque, float valor);
void mostrarEstoque(Produto produtos[], int qtdeProdutos);
void setVenda(Venda *V, int *id, char nomeComprador[], Carrinho carrinho[], int numItens, float valorTotal);
void inicializarProdutos(Produto produtos[], int *numeroProdutos);
void reporEstoque(Produto produtos[], int numeroProdutos);
void mostrarCompras(Venda vendas[], int numeroVendas);
void maiorCompra(Venda vendas[], int numeroVendas);

#endif