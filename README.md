# Sistema de Gerenciamento de Livros com Árvore Binária
**Autores:** 
[@Hugo Gustavo Cordeiro](https://github.com/ugoincc) 
[@Diogo Ferreira Ribeiro](https://github.com/dfr20)  <br/>
**Outubro de 2024** <br/>
Segundo Trabalho da disciplina "Algoritmos e Estruturas de Dados". <br/>
Este projeto implementa um sistema de gerenciamento de livros em C, onde os dados dos livros são armazenados e manipulados usando uma **árvore binária de busca** (ABB). O programa permite a inserção, remoção, busca e listagem dos livros, além de outras operações úteis como a contagem do total de livros e estoque.

## Funcionalidades

- **Inserir Livro**: Adiciona um novo livro à árvore binária, mantendo a ordenação pelo código do livro.
- **Remover Livro**: Remove um livro da árvore, ajustando a estrutura para manter as propriedades da árvore binária de busca.
- **Imprimir Dados do Livro**: Imprime dados de um único livro, dado seu código.
- **Listar Todos os Livros**: Imprime todos os dados de livros cadastrados.
- **Buscar Livro por Título ou Autor**: Realiza a busca por um livro com base no título ou autor, retornando as informações correspondentes.
- **Imprimir Árvore**:
  - Em notação estruturada no formato `[chave, [subEsquerda, subDireita]]`.
  - Em ordem de níveis (percurso em largura), onde cada nível da árvore é impresso em uma linha.
- **Calcular Total de Livros e Estoque**: Calcula o número total de livros e o estoque disponível na árvore.
- **Listar Posições Livres**: Exibe as posições livres no arquivo de dados que podem ser reutilizadas para novos livros.
- **Carregar arquivo**: Permite a inserção de dados a partir de um arquivo de texto, para informações sobre o formato veja: [Modelo de Input](./entrada_modelo.txt).
## Estrutura dos Dados

Dentro do arquivo header arvorebinaria.h estrutura principal de cada livro é:
```c
typedef struct {
  int codigo;
  char titulo[150];
  char autor[200];
  char editora[50];
  int edicao;
  int ano;
  double preco;
  unsigned int estoque;
  int esq;  // Posição da subárvore esquerda
  int dir;  // Posição da subárvore direita
} Livro;
```

## Como Compilar
Para compilar o programa, utilize o comando abaixo no terminal:
```c
gcc -o gerenciamento_livros main.c livro.c -Wall
```
Isso gerará um executável chamado gerenciamento_livros.

## Como Executar
Após a compilação, você pode executar o programa com o comando:
```c
./gerenciamento_livros
```
