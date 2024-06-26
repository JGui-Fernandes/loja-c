#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "loja.h"
#include "loja.c"

// Arthur Alves Pasini
// João Guilherme Borges Fernandes
// Vinícius da Rosa Fröhlich

int main (){
    Produto produtos[50];
    Venda vendas[50];
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