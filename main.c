#include "arvorebinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int opcao, target;
    char arquivoTexto[50];
    Livro livro_encontrado;
    cabecalho* cab = NULL;
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
                cab = le_cabecalho(dados);
                printf("Digite o codigo do livro: ");
                scanf("%d", &target);
                cab->pos_cabeca = remover_livro(dados, cab->pos_cabeca, target, cab);
                escreve_cabecalho(dados, cab);
                free(cab);
            break;

            case 3:
                printf("Digite o codigo do livro: ");
                scanf("%d", &target);
                livro_encontrado = busca_livro(dados, target);
                    if(livro_encontrado.codigo != -1) {
                        imprimir_livro(livro_encontrado);
                    }
                break;


            case 4:{
                cab = le_cabecalho(dados);
                listar_todos(dados, cab->pos_cabeca);
                free(cab);
                break;
            }

            case 5:
                char autorStr[200];
                cab = le_cabecalho(dados);
                printf("Digite o autor a ser pesquisado: ");
                scanf("%[^\n]%*c", autorStr);
                busca_autor(dados, cab->pos_cabeca, autorStr);
                printf("\n");
                break;

            case 6:
                char tituloStr[200];
                cab = le_cabecalho(dados);
                printf("Digite o titulo a ser pesquisado: ");
                scanf("%[^\n]%*c", tituloStr);
                busca_titulo(dados, cab->pos_cabeca, tituloStr);
                printf("\n");
                break;

            case 7:
                //calcula_total(dados);
                //break;

            case 8:
                printf("Entre com o nome do arquivo txt (arq.txt):\n");
                printf("> ");
                scanf("%[^\n]%*c", arquivoTexto);
                lerArquivoEntrada(arquivoTexto, dados);
                break;

            case 9:
                // printPosLivre(dados);
                // break;

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
