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
  insere_na_cabeca(dados, aux);
  printf("Livro cadastrado com sucesso!\n");
}

// solicita um livro para ser removido
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: no retirado da lista caso pertenca a ela
void remover_livro(FILE *dados) {
  int target;
  printf("Digite o codigo do livro: ");
  scanf("%d", &target);
  remove_item(dados, target);
}

// Retira um no da lista
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: no retirado da lista caso pertenca a ela
void remove_item(FILE *dados, int target) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!\n");
    return;
  }

  cabecalho *cab = le_cabecalho(dados);
  int pos_aux = cab->pos_cabeca;
  int pos_ant = cab->pos_cabeca;
  Livro aux = le_livro(dados, pos_aux);

  while ((pos_aux != -1) && (aux.codigo != target)) {
    pos_ant = pos_aux;
    pos_aux = aux.prox;
    aux = le_livro(dados, pos_aux);
  }

  if (pos_aux != -1) { // encontrou o elemento
    printf("\nLivro encontrado!\n");
    if (pos_ant == pos_aux) { // remocao na cabe ca
      cab->pos_cabeca = aux.prox;
    } else { // remocao no meio
      Livro ant = le_livro(dados, pos_ant);
      ant.prox = aux.prox;
      escreve_livro(dados, ant, pos_ant);
    }

    aux.prox = cab->pos_livre; // torna o no removido um no livre
    cab->pos_livre = pos_aux;
    escreve_livro(dados, aux, pos_aux);
    escreve_cabecalho(dados, cab);
    printf("Livro de codigo: %d removido!\n", target);

    free(cab);
    rewind(dados);
    return;
  }

  printf("\nLivro nao encontrado...\n");
  free(cab);
  rewind(dados);
}

// Funcao principal da insercao, insere um registro de livro no arquivo
// binario pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: livro passado é inserido no arquivo binario, na posicao livre
// ou no topo
void insere_na_cabeca(FILE *dados, Livro x) {
  cabecalho *cab = le_cabecalho(dados);
  x.prox = cab->pos_cabeca;
  if (cab->pos_livre == -1) { // nao ha nos livres, entao usar o topo
    escreve_livro(dados, x, cab->pos_topo);
    cab->pos_cabeca = cab->pos_topo;
    cab->pos_topo++;
  } else { // usar no da lista de livres
    Livro aux = le_livro(dados, cab->pos_livre);
    escreve_livro(dados, x, cab->pos_livre);
    cab->pos_cabeca = cab->pos_livre;
    cab->pos_livre = aux.prox;
  }
  escreve_cabecalho(dados, cab);
  free(cab);
}

// Imprime as posicoes livres do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivre(FILE *dados) {
  cabecalho *cab = le_cabecalho(dados);
  Livro vazio = le_livro(dados, cab->pos_livre);
  printf("Posicao livre = %d\n", cab->pos_livre);
  if (cab->pos_livre != -1)
    while (vazio.prox != -1) {
      printf("Posicao livre = %d\n", vazio.prox);
      vazio = le_livro(dados, vazio.prox);
    }
}

// Imprime a quantidade total de livros cadastrados
// pre-condicao: arquivo de dados aberto e livros cadastrados
// pos-codicao: quantidade de livros mostrada
void calcula_total(FILE *dados) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!\n");
    return;
  }

  Livro aux;
  int estoque_total = 0;
  int livros_unicos = 0;
  cabecalho *cab = le_cabecalho(dados);
  aux = le_livro(dados, cab->pos_cabeca);

  while (aux.prox != -1) {
    livros_unicos++;
    estoque_total += aux.estoque;
    aux = le_livro(dados, aux.prox);
  }

  printf("\nLivros da biblioteca:\n");
  printf("%d livros distintos.\n", livros_unicos);
  printf("%d em estoque.\n", estoque_total);

  free(cab);
  rewind(dados);
}

// Busca e imprime apenas livro de codigo informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
void imprimir_dados_livro(FILE *dados) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!\n");
    return;
  }

  Livro aux;
  int target;
  cabecalho *cab = le_cabecalho(dados);
  aux = le_livro(dados, cab->pos_cabeca);

  printf("Digite o codigo do livro: ");
  scanf("%d", &target);

  while (aux.prox != -1) {
    if (aux.codigo == target) {
      printf("\nCodigo: %d, Titulo: %s, Autor: %s, Editora: %s, Edicao: %d, "
             "Ano: "
             "%d, Preco: %.2lf, Estoque: %u\n",
             aux.codigo, aux.titulo, aux.autor, aux.editora, aux.edicao,
             aux.ano, aux.preco, aux.estoque);
      rewind(dados);
      return;
    }
    aux = le_livro(dados, aux.prox);
  }

  printf("Livro de codigo %d nao encontrado!\n", target);
  free(cab);
  rewind(dados);
}

// Busca e imprime apenas livro informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
void busca_titulo(FILE *dados) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!");
    return;
  }

  Livro aux;
  char titleStr[150];
  cabecalho *cab = le_cabecalho(dados);
  aux = le_livro(dados, cab->pos_cabeca);

  printf("\nDigite o titulo a ser pesquisado: ");
  scanf("%[^\n]%*c", titleStr);

  while (aux.prox != -1) {
    if (strstr(aux.titulo, titleStr) != 0) {
      printf("\nCodigo: %d, Titulo: %s, Autor: %s, Editora: %s, Edicao: %d, "
             "Ano: "
             "%d, Preco: %.2lf, Estoque: %u\n",
             aux.codigo, aux.titulo, aux.autor, aux.editora, aux.edicao,
             aux.ano, aux.preco, aux.estoque);
      rewind(dados);
      free(cab);
      return;
    }
    aux = le_livro(dados, aux.prox);
  }

  printf("\nTitulo nao encontrado...\n");
  free(cab);
  rewind(dados);
}

// Busca e imprime apenas livros do autor informado
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados
void busca_autor(FILE *dados) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!");
    return;
  }

  Livro aux;
  char autorStr[200];
  cabecalho *cab = le_cabecalho(dados);
  aux = le_livro(dados, cab->pos_cabeca);

  printf("Digite o autor a ser pesquisado: ");
  scanf("%[^\n]%*c", autorStr);

  while (aux.prox != -1) {
    if (strstr(aux.autor, autorStr) != 0) {
      printf("Titulo: %s\n", aux.titulo);
    }
    aux = le_livro(dados, aux.prox);
  }

  printf("\nBusca Finalizada...\n");
  free(cab);
  rewind(dados);
}

// Imprime apenas o codigo, o titulo, autor, e quantidade em estoque de todos
// os livros do cadastro
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados
void listar_todos(FILE *dados) {
  if (dados == NULL) {
    printf("Arquivo de dados inválido!");
    return;
  }

  Livro aux;
  cabecalho *cab = le_cabecalho(dados);
  if(cab->pos_cabeca == -1){
    printf("Lista Vazia...\n");
    free(cab);
    rewind(dados);
    return;
  }
  aux = le_livro(dados, cab->pos_cabeca);
  printf("\nCodigo: %d, Titulo: %s, Autor: %s, Estoque: %u\n", aux.codigo,
     aux.titulo, aux.autor, aux.estoque);

  while (aux.prox != -1) {
    aux = le_livro(dados, aux.prox);
    printf("\nCodigo: %d, Titulo: %s, Autor: %s, Estoque: %u\n", aux.codigo,
           aux.titulo, aux.autor, aux.estoque);
  }

  rewind(dados);
  free(cab);
}

// Escrita do livro
// pre-condicao: arquivo de dados deve existir e estar aberto, livro e posicao
// devem ser validos pos-condicao: armazena a informacao do livro passado na
// sua posicao correspondente no arquivo de dados
void escreve_livro(FILE *dados, Livro x, int pos) {
  fseek(dados, sizeof(cabecalho), SEEK_SET);
  fseek(dados, pos * sizeof(Livro), SEEK_CUR);
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
  char teste, branco[200], precoStr[20];
  Livro aux;
  FILE *f;
  f = fopen(fileName, "r");
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
      insere_na_cabeca(dados, aux);
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
  printf(" 0 - Fechar Programa\n");
  printf("\n\n");
}