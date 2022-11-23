#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 20
#define INFINITY 9999

typedef struct tipoVertice
{
    char nome[30];
    int distancia;
    struct tipoVertice *prox;
}TVertice;


typedef struct tipoLista
{
    int distancia;
    TVertice *inicio;
    TVertice *fim;
}TLista;

// Funcoes para ler dados do arquivo
void lerCidadesArquivo(TLista *vetor);
void lerRelacoesArquivo(TLista *vetor, int matriz[TAM][TAM]);

int menu();

// Funcoes para inicializar vetores, matrizes e listas
void inicializarMatriz(int matriz[TAM][TAM]);
void inicializaVetor(TLista *vetor);
void inicializaLista(TLista *lista);

// Funcoes para exibir
void imprimirVertices(TLista *vetor);
void exibir_lista(TLista *lista);
void exibir_vetor(TLista *vetor);

// Funcoes para inserir as cidades
void inserirNomeCidades(TLista *lista, char *nomeCidade, int distancia);
void inserirRelacoesMatriz(int matriz[TAM][TAM], TLista *vetor, char *nomeCidade1, char *nomeCidade2, int distancia);
void inserirCidadesLista(TLista *vetor, int matriz[TAM][TAM]);
int encontrarPosicaoCidade(TLista *vetorCidades, char *nomeCidade);

// Funcoes utilizadas para no algoritmo dijkstra
void dijkstra(int mat[TAM][TAM], int codOrigem, int codDestino, TLista *vetorCidades);
void inicializarVetoresDijkstra(int matCusto[TAM][TAM], int *vetDistancia, int *vetAnterior, int *visitados, int codOrigem, int mat[TAM][TAM]);
void algoritmoMenorCaminho(int matriz[TAM][TAM], TLista *vetorCidades);

