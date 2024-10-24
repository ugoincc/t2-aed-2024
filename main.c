#include "arvorebinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int opcao;
    char arquivoTexto[50];
    FILE *dados = fopen("ArquivoDados.bin", "rb+");

    if (dados == NULL) {
        dados = fopen("ArquivoDados.bin", "wb+");
        cria_lista_vazia(dados);
    }

    printMenu();
    printf("> ");
    scanf("%d%*c", &opcao);
    while (opcao != 0) {
        switch (opcao) {
            case 1:
                cadastrar_livro(dados);
            break;

            case 2:
                //remover_livro(dados);
                    break;

            case 3:
                //imprimir_dados_livro(dados);
                    break;

            case 4:{
                cabecalho *cab = le_cabecalho(dados);
                listar_todos(dados, cab->pos_cabeca);
                free(cab);
                break;
            }

            case 5:
                //busca_autor(dados);
                    break;

            case 6:
                //busca_titulo(dados);
                    break;

            case 7:
                //calcula_total(dados);
                    break;

            case 8:
                printf("Entre com o nome do arquivo txt (arq.txt):\n");
            printf("> ");
            scanf("%[^\n]%*c", arquivoTexto);
            lerArquivoEntrada(arquivoTexto, dados);
            break;

            case 9:
                // printPosLivre(dados);
                    break;

            case 11:
                printa_cabecalho(dados);
            break;

            default:
                printf("Opcao invalida!!\n");
        }
        printf("\n");
        printMenu();
        printf("> ");
        scanf("%d%*c", &opcao);
    }

    return 0;
}
