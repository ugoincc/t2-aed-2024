//
// Created by Hugo on 27/09/2024.
//

#include "arvorebinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao auxiliar teste
// Pre-condicao: arquivo deve estar aberto
// Pos-condicao: printa o cabecalho
void printa_cabecalho(FILE *dados) {
  cabecalho *cab = le_cabecalho(dados);
  printf("Cabeca: %d Topo: %d Livre: %d\n", cab->pos_cabeca, cab->pos_topo,
         cab->pos_livre);
}

// solicita um livro para ser cadastrado
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: livro inserido na lista
void cadastrar_livro(FILE *dados) {
  Livro aux;
  char precoStr[50];
  printf("Entre com o codigo: \n");
  printf("> ");
  scanf("%d%*c", &aux.codigo);
  printf("Entre com o titulo: \n");
  printf("> ");
  scanf("%[^\n]%*c", aux.titulo);
  printf("Entre com o autor: \n");
  printf("> ");
  scanf("%[^\n]%*c", aux.autor);
  printf("Entre com a editora: \n");
  printf("> ");
  scanf("%[^\n]%*c", aux.editora);
  printf("Entre com a edicao: \n");
  printf("> ");
  scanf("%d%*c", &aux.edicao);
  printf("Entre com o ano: \n");
  printf("> ");
  scanf("%d%*c", &aux.ano);
  printf("Entre com o preco: \n");
  printf("> ");
  scanf("%s%*c", precoStr);
  printf("Entre com o estoque: \n");
  printf("> ");
  scanf("%u%*c", &aux.estoque);
  for (char *p = precoStr; *p; ++p) {
    if (*p == ',') {
      *p = '.';
    }
  }
  aux.preco = atof(precoStr);
  insereLivro(dados, aux);
  printf("Livro cadastrado com sucesso!\n");
}

// solicita um livro para ser removido
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: no retirado da lista caso pertenca a ela
int remover_livro(FILE *dados, int pos_atual, int codigo, cabecalho *cab) {
    if (pos_atual == -1) {
        printf("Livro nao encontrado.\n");
        return -1;
    }

    Livro livro_atual = le_livro(dados, pos_atual);

    if (codigo < livro_atual.codigo) {
        livro_atual.esq = remover_livro(dados, livro_atual.esq, codigo, cab);
        escreve_livro(dados, livro_atual, pos_atual);
        return pos_atual;
    }

    if (codigo > livro_atual.codigo) {
        livro_atual.dir = remover_livro(dados, livro_atual.dir, codigo, cab);
        escreve_livro(dados, livro_atual, pos_atual);
        return pos_atual;
    }

    if (codigo == livro_atual.codigo) {
        if (livro_atual.esq == -1 && livro_atual.dir == -1) {
            printf("Livro removido.\n");

            livro_atual.esq = cab->pos_livre;
            cab->pos_livre = pos_atual;
            escreve_livro(dados, livro_atual, pos_atual);
            return -1;
        }

        if (livro_atual.esq == -1) {
            printf("Livro removido com filho a direita.\n");
            return livro_atual.dir;
        }

        if (livro_atual.dir == -1) {
            printf("Livro removido com filho a esquerda.\n");
            return livro_atual.esq;
        }

        int pos_sucessor = encontrar_sucessor(dados, livro_atual.dir);
        Livro sucessor = le_livro(dados, pos_sucessor);

        livro_atual.codigo = sucessor.codigo;
        strcpy(livro_atual.titulo, sucessor.titulo);
        strcpy(livro_atual.autor, sucessor.autor);
        strcpy(livro_atual.editora, sucessor.editora);
        livro_atual.edicao = sucessor.edicao;
        livro_atual.ano = sucessor.ano;
        livro_atual.preco = sucessor.preco;
        livro_atual.estoque = sucessor.estoque;

        livro_atual.dir = remover_livro(dados, livro_atual.dir, sucessor.codigo, cab);

        escreve_livro(dados, livro_atual, pos_atual);
        return pos_atual;
    }

    return pos_atual;
}

// Função auxiliar para encontrar o sucessor (o menor nó na subárvore direita)
int encontrar_sucessor(FILE *dados, int pos_atual) {
    Livro livro_atual = le_livro(dados, pos_atual);

    while (livro_atual.esq != -1) {
        pos_atual = livro_atual.esq;
        livro_atual = le_livro(dados, pos_atual);
    }

    return pos_atual;
}

// Funcao principal da insercao, insere um registro de livro no arquivo
// binario pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: livro passado é inserido no arquivo binario, na posicao livre
// ou no topo
void insereLivro(FILE *dados, Livro x) {
    cabecalho *cab = le_cabecalho(dados);

    x.esq = -1;
    x.dir = -1;

    int nova_posicao;
    if (cab->pos_livre != -1) {
        nova_posicao = cab->pos_livre;
        Livro livro_livre = le_livro(dados, nova_posicao);
        cab->pos_livre = livro_livre.esq;  // Atualiza a lista de posições livres
    } else {
        nova_posicao = cab->pos_topo;
        cab->pos_topo++;
    }

    if (cab->pos_cabeca == -1) {
        escreve_livro(dados, x, nova_posicao);
        cab->pos_cabeca = nova_posicao;
        escreve_cabecalho(dados, cab);
        printf("Livro inserido como raiz da arvore.\n");
    } else {
        int pos_atual = cab->pos_cabeca;
        while (1) {
            Livro livro_atual = le_livro(dados, pos_atual);

            if (x.codigo < livro_atual.codigo) {
                if (livro_atual.esq == -1) {
                    livro_atual.esq = nova_posicao;
                    escreve_livro(dados, livro_atual, pos_atual);
                    escreve_livro(dados, x, nova_posicao);
                    escreve_cabecalho(dados, cab);
                    printf("Livro inserido a esquerda.\n");
                    break;
                } else {
                    pos_atual = livro_atual.esq;
                }
            } else if (x.codigo > livro_atual.codigo) {
                if (livro_atual.dir == -1) {
                    livro_atual.dir = nova_posicao;
                    escreve_livro(dados, livro_atual, pos_atual);
                    escreve_livro(dados, x, nova_posicao);
                    escreve_cabecalho(dados, cab);
                    printf("Livro inserido a direita.\n");
                    break;
                } else {
                    pos_atual = livro_atual.dir;
                }
            } else {
                printf("Erro: Código de livro duplicado.\n");
                break;
            }
        }
    }

    free(cab);
}

// Imprime as posicoes livres do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivre(FILE *dados) {
    cabecalho *cab = le_cabecalho(dados);

    int pos_livre = cab->pos_livre;
    if (pos_livre == -1) {
        printf("Posicao livre: -1\n");
        free(cab);
        return;
    }

    printf("Posicoes livres:\n");

    // Percorre a lista encadeada de posições livres
    while (pos_livre != -1) {
        printf("Posicao livre: %d\n", pos_livre);
        Livro livro_livre = le_livro(dados, pos_livre);
        pos_livre = livro_livre.esq;  // A próxima posição livre está no campo esq
    }

    free(cab);
}

// Imprime a quantidade total de livros cadastrados
// pre-condicao: arquivo de dados aberto e livros cadastrados
// pos-codicao: quantidade de livros mostrada
void calcula_total(FILE *dados, int pos_atual, int *total_livros, int *total_estoque) {

    if (pos_atual == -1) {
        return;  }

    Livro livro_atual = le_livro(dados, pos_atual);
    (*total_livros)++;  // Incrementa o número total de livros
    *total_estoque += livro_atual.estoque;
    calcula_total(dados, livro_atual.esq, total_livros, total_estoque);

    calcula_total(dados, livro_atual.dir, total_livros, total_estoque);

}

// Função para imprimir as informações de um livro
// Entrada: Ponteiro para o registro de livro
// Saída: Dados do Livro
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são exibidas na tela
void imprimir_livro(Livro info) {
    printf("\nInformacoes do Livro:\n");
    printf("Codigo: %d\n", info.codigo);
    printf("Titulo: %s\n", info.titulo);
    printf("Autor: %s\n", info.autor);
    printf("Editora: %s\n", info.editora);
    printf("Edicao: %d\n", info.edicao);
    printf("Ano: %d\n", info.ano);
    printf("Preco: R$%.2f\n", info.preco);
    printf("Estoque: %d\n", info.estoque);
    printf("Proxima esquerda: %d\n" , info.esq);
    printf ("Proxima direita: %d\n", info.dir);
}

// Busca e imprime apenas livro de codigo informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
Livro busca_livro(FILE *dados, int codigo) {
  cabecalho *cab = le_cabecalho(dados);
  int pos_atual = cab->pos_cabeca;
  free(cab);

  while (pos_atual != -1) {
    Livro livro_atual = le_livro(dados, pos_atual);

    if (codigo == livro_atual.codigo) {
      // Livro encontrado
      return livro_atual;
    } else if (codigo < livro_atual.codigo) {
      // Se o código for menor, vá para o filho à esquerda
      pos_atual = livro_atual.esq;
    } else {
      // Se o código for maior, vá para o filho à direita
      pos_atual = livro_atual.dir;
    }
  }

  printf("Erro: Livro com código %d não encontrado.\n", codigo);

  Livro livro_vazio;
  livro_vazio.codigo = -1; // Código inválido para indicar que não foi encontrado
  return livro_vazio;
}

// Busca e imprime apenas livro informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
void busca_titulo(FILE *dados, int pos_atual, char* tituloStr) {
  if (pos_atual == -1) {
    return;  }

  Livro livro_atual = le_livro(dados, pos_atual);

  busca_titulo(dados, livro_atual.esq, tituloStr);
  if (strstr(livro_atual.titulo, tituloStr) != NULL) {
    imprimir_livro(livro_atual);
  }
  busca_titulo(dados, livro_atual.dir, tituloStr);
}

// Busca e imprime apenas livros do autor informado
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados
void busca_autor(FILE *dados, int pos_atual, char* autorStr) {
  if (pos_atual == -1) {
    return;  }

  Livro livro_atual = le_livro(dados, pos_atual);

  busca_autor(dados, livro_atual.esq, autorStr);
    if (strstr(livro_atual.autor, autorStr) != NULL) {
      imprimir_livro(livro_atual);
    }
  busca_autor(dados, livro_atual.dir, autorStr);
}


// Imprime apenas o codigo, o titulo, autor, e quantidade em estoque de todos
// os livros do cadastro
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados "in-ordem"
void listar_todos(FILE *dados, int pos_atual) {
    if (pos_atual == -1) {
        return;
    }
    Livro livro_atual = le_livro(dados, pos_atual);
    listar_todos(dados, livro_atual.esq);
    imprimir_livro(livro_atual);
    listar_todos(dados, livro_atual.dir);
}

// Escrita do livro
// pre-condicao: arquivo de dados deve existir e estar aberto, livro e posicao
// devem ser validos pos-condicao: armazena a informacao do livro passado na
// sua posicao correspondente no arquivo de dados
void escreve_livro(FILE *dados, Livro x, int pos) {
  fseek(dados, sizeof(cabecalho) + pos * sizeof(Livro), SEEK_SET);
  fwrite(&x, sizeof(Livro), 1, dados);
}

// Leitura de um Livro
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve
// ser valida pos-condicao: retorna um ponteiro para livro com as informacoes
// salvas no arquivo de dados
Livro *le_no(FILE *dados, int pos) {
  Livro *x = malloc(sizeof(Livro));
  fseek(dados, sizeof(cabecalho) + pos * sizeof(Livro), SEEK_SET);
  fread(&x, sizeof(Livro), 1, dados);
  return x;
}

// Leitura de um Livro
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve
// ser valida pos-condicao: retorna um livro com as informacoes salvas no
// arquivo de dados
Livro le_livro(FILE *dados, int pos) {
  Livro x;
  fseek(dados, sizeof(cabecalho) + pos * sizeof(Livro), SEEK_SET);
  fread(&x, sizeof(Livro), 1, dados);
  return x;
}

// Le o cabecalho do arquivo contendo as informacoes da lista
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho *le_cabecalho(FILE *arq) {
  cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
  fseek(arq, 0, SEEK_SET); // posiciona no inicio do arquivo
  fread(cab, sizeof(cabecalho), 1, arq);
  return cab;
}

// Escreve no arquivo o cabecalho contendo as informacoes da lista
// Pre-condiao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condiao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE *arq, cabecalho *cab) {
  fseek(arq, 0, SEEK_SET); // posiciona no inicio do arquivo
  fwrite(cab, sizeof(cabecalho), 1, arq);
}

// Cria uma lista nova em arquivo
// Pre-condicao: arquivo aberto para leitura/escrita
// Pos-condicao: arquivo e inicializado com uma lista vazia
void cria_lista_vazia(FILE *arq) {
  cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
  cab->pos_cabeca = -1;
  cab->pos_topo = 0;
  cab->pos_livre = -1;
  escreve_cabecalho(arq, cab);
  free(cab);
}

// Leitura do arquivo de texto, suas informacoes sao gravadas nos arquivos de
// dados pre-condicao: arquivo de dados deve existir e estar aberto, o nome do
// arquivo deve ser valido pos-condicao: as informacoes lidas do arquivo de
// texto sao gravadas no arquivo binario
void lerArquivoEntrada(char *fileName, FILE *dados) {
  char branco[200], precoStr[20];
  Livro aux;
  FILE *f = fopen(fileName, "r");

  if (f != NULL) {
    while (fscanf(f, " %d ;", &aux.codigo) == 1) {
      fscanf(f, " %[^;];", branco);
      eliminaBranco(aux.titulo, branco);
      fscanf(f, " %[^;];", branco);
      eliminaBranco(aux.autor, branco);
      fscanf(f, " %[^;];", branco);
      eliminaBranco(aux.editora, branco);
      fscanf(f, " %d ;", &aux.edicao);
      fscanf(f, " %d ;", &aux.ano);
      fscanf(f, " %19[^;];", precoStr);
      fscanf(f, " %u \n", &aux.estoque);

      for (char *p = precoStr; *p; ++p) {
        if (*p == ',') {
          *p = '.';
        }
      }

      aux.preco = atof(precoStr);
      insereLivro(dados, aux);
    }
    printf("\nLeitura de arquivo concluida!!\n");
    rewind(dados);
    fclose(f);
  } else
    printf("\nArquivo invalido!!\n");
}

// Funcao auxiliar para filtrar os brancos de uma string
// pre-condicao: as strings passadas devem ser validas
// pos-condicao: a string de destino recebe a string filtrada, sem os brancos
// extras
void eliminaBranco(char *destino, char *branco) {
  while (*branco) {
    if (*branco == ' ')
      if (*(branco + 1) == ' ')
        break;
    *destino++ = *branco++;
  }
  *destino = '\0';
}

// Imprime o menu de operacoes na tela
// pre-condicao: nenhuma
// pos-condicao: as operacoes do menu sao impressas na tela
void printMenu() {
  printf(" Menu Principal\n");
  printf(" 1 - Cadastrar Livro\n");
  printf(" 2 - Remover Livro\n");
  printf(" 3 - Imprimir Dados do Livro\n");
  printf(" 4 - Listar Todos os Livros\n");
  printf(" 5 - Busca por Autor\n");
  printf(" 6 - Busca por Titulo\n");
  printf(" 7 - Calcular Total\n");
  printf(" 8 - Carregar Arquivo\n");
  printf(" 9 - Imprimir Posicoes Livres\n");
  printf(" 10 - Imprimir Arvore em Lista\n");
  printf(" 11 - Imprimir Arvore por Niveis\n");
  printf(" 0 - Fechar Programa\n");
  printf("\n\n");
}

// Imprime a árvore binária no formato [chave, [subEsquerda, subDireita]]
// pre-condicao: arquivo de dados aberto e posição inicial válida (pos_raiz)
// pos-condicao: imprime a árvore no formato especificado recursivamente
void imprime_arvore_lista(FILE *dados, int pos_atual) {
    if (pos_atual == -1) {
        printf("[ ]");  // Imprime subárvore vazia
        return;
    }

    Livro livro_atual = le_livro(dados, pos_atual);

    printf("[%d, ", livro_atual.codigo);  // Imprime a chave do livro

    // Imprime a subárvore esquerda
    imprime_arvore_lista(dados, livro_atual.esq);

    printf(", ");  // Separador entre subárvores

    // Imprime a subárvore direita
    imprime_arvore_lista(dados, livro_atual.dir);

    printf("]");  // Fecha o nó atual
}

// Enfileira um nó na fila com sua posição e nível
// pre-condicao: a fila deve estar inicializada e com espaço disponível
// pos-condicao: o nó é adicionado à fila
void enfileirar(NoFila fila[], int *fim, int pos, int nivel) {
    fila[*fim].pos = pos;
    fila[*fim].nivel = nivel;
    (*fim)++;
}

// Imprime a árvore binária em níveis (um nível por linha)
// pre-condicao: arquivo de dados aberto e posição inicial válida (pos_raiz)
// pos-condicao: imprime a árvore nível a nível em ordem de BFS (largura)
void imprime_por_niveis(FILE *dados, int pos_raiz) {
    if (pos_raiz == -1) {
        printf("A árvore está vazia.\n");
        return;
    }

    NoFila fila[1000];
    int inicio = 0, fim = 0;

    enfileirar(fila, &fim, pos_raiz, 0);

    int nivel_atual = 0;

    while (inicio < fim) {
        NoFila no_atual = fila[inicio];
        inicio++;

        Livro livro_atual = le_livro(dados, no_atual.pos);

        if (no_atual.nivel != nivel_atual) {
            printf("\n");
            nivel_atual = no_atual.nivel;
        }

        printf("%d ", livro_atual.codigo);

        if (livro_atual.esq != -1) {
            enfileirar(fila, &fim, livro_atual.esq, no_atual.nivel + 1);
        }
        if (livro_atual.dir != -1) {
            enfileirar(fila, &fim, livro_atual.dir, no_atual.nivel + 1);
        }
    }

    printf("\n");
}