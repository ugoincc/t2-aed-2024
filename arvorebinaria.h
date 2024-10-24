//
// Created by Hugo on 27/09/2024.
//

#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include "stdio.h"

// cabeçalho do arquivo
typedef struct {
  int pos_cabeca; // posicao do inicio da lista
  int pos_topo;   // 1a posicao nao usada no fim do arquivo
  int pos_livre;  // posicao no inicio da lista de nós livres
} cabecalho;

typedef struct {
  int codigo;
  char titulo[150];
  char autor[200];
  char editora[50];
  int edicao;
  int ano;
  double preco;
  unsigned int estoque;
  int esq;
  int dir;
} Livro;

// Função auxiliar para encontrar o sucessor (o menor nó na subárvore direita)
int encontrar_sucessor(FILE *dados, int pos_atual);

// Função para imprimir as informações de um livro
// Entrada: Ponteiro para o registro de livro
// Saída: Dados do Livro
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são exibidas na tela
void imprimir_livro(Livro info);

// funcao auxiliar teste
// Pre-condicao: arquivo deve estar aberto
// Pos-condicao: printa o cabecalho
void printa_cabecalho(FILE *dados);

// solicita um livro para ser cadastrado
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: livro inserido na lista
void cadastrar_livro(FILE *dados);

// solicita um livro para ser removido
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: no retirado da lista caso pertenca a ela
int remover_livro(FILE *dados, int pos_atual, int codigo, cabecalho *cab);

// Retira um no da lista
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: no retirado da lista caso pertenca a ela
void remove_item(FILE *arq, int codigo);

// Funcao principal da insercao, insere um registro de livro no arquivo
// binario pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: livro passado é inserido no arquivo binario, na posicao livre
// ou no topo
void insereLivro(FILE *dados, Livro x);

// Imprime as posicoes livres do arquivo de dados
// pre-condicao: arquivo de dados deve existir e estar aberto
// pos-condicao: imprime na tela todas as posicoes livres do arquivo de index
void printPosLivre(FILE *dados);

// Imprime a quantidade total de livros cadastrados
// pre-condicao: arquivo de dados aberto e livros cadastrados
// pos-codicao:imprime na tela quantidade de livros unicos e em estoque
void calcula_total(FILE *dados);

// Busca e imprime apenas livro de codigo informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
Livro busca_livro(FILE *dados, int codigo);

// Busca e imprime apenas livro de titulo informado caso exista
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: as informacoes do livro serao mostradas
void busca_titulo(FILE *dados, int pos_atual, char* tituloStr);

// Busca e imprime apenas livros do autor informado
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados
void busca_autor(FILE *dados, int pos_atual, char *autorStr);

// Imprime apenas o codigo, o titulo, autor, e quantidade em estoque de todos
// os livros do cadastro
//  pre-condicao: arquivo de dados aberto
//  pos-condicao: os livros sao listados "in-ordem"
void listar_todos(FILE *dados, int pos_atual);

// Escrita do livro
// pre-condicao: arquivo de dados deve existir e estar aberto, livro e posicao
// devem ser validos pos-condicao: armazena a informacao do livro passado na sua
// posicao correspondente no arquivo de dados
void escreve_livro(FILE *dados, Livro x, int pos);

// Leitura de um Livro
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve
// ser valida pos-condicao: retorna um ponteiro para livro com as informacoes
// salvas no arquivo de dados
Livro *le_no(FILE *dados, int pos);

// Leitura de um Livro
// pre-condicao: arquivo de dados deve existir e estar aberto, a posicao deve
// ser valida pos-condicao: retorna um livro com as informacoes salvas no
// arquivo de dados
Livro le_livro(FILE *dados, int pos);

// Le o cabecalho do arquivo contendo as informacoes da lista
// Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho *le_cabecalho(FILE *arq);

// Escreve no arquivo o cabecalho contendo as informacoes da lista
// Pre-condiao: arquivo deve estar aberto e ser um arquivo de lista
// Pos-condiao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE *arq, cabecalho *cab);

// Cria uma lista nova em arquivo
// Pre-condicao: arquivo aberto para leitura/escrita
// Pos-condicao: arquivo e inicializado com uma lista vazia
void cria_lista_vazia(FILE *arq);

// Leitura do arquivo de texto, suas informacoes sao gravadas no arquivo binario
// pre-condicao: aquivo de entrada deve estar aberto
// pos-condicao: as informacoes lidas
// do arquivo de texto sao gravadas no arquivo binario
void lerArquivoEntrada(char *fileName, FILE *dados);

// Funcao auxiliar para filtrar os brancos de uma string
// pre-condicao: as strings passadas devem ser validas
// pos-condicao: a string de destino recebe a string filtrada, sem os brancos
// extras
void eliminaBranco(char *destino, char *branco);

// Imprime o menu de operacoes na tela
// pre-condicao: nenhuma
// pos-condicao: as operacoes do menu sao impressas na tela
void printMenu();

#endif //ARVOREBINARIA_H
