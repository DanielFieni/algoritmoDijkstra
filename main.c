#include "lista.h"

int main(int argc, char *argv[])
{

    FILE *arq;
    int opcao;

    // Matriz apenas ilustrativa
    int matriz[TAM][TAM];

    // Vetor do tipo Lista para guarda a posicao de cada cidade
    TLista vetor[TAM];

    // inicializar matriz e vetor do tipo TLista
    inicializarMatriz(matriz);
    inicializaVetor(vetor);

    // Ler o nome das cidades do arquivo
    lerCidadesArquivo(vetor);
    // Ler as relacoes da cidade do arquivo
    lerRelacoesArquivo(vetor, matriz);

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 0:
            // Sair do programa
            printf("\nPROGRAMA ENCERRADO!\n\n");
            break;

        case 1:
            // Imprimir relacoes das cidades
            exibir_vetor(vetor);
            break;

        case 2:
            // Imprimir cidades Inseridas
            imprimirVertices(vetor);
            break;

        case 3:
            // Imprimir menor caminho (algoritmo dijkstra)
            printf("\n");

            imprimirVertices(vetor);
            algoritmoMenorCaminho(matriz, vetor);

            printf("\n");
            break;

        default:
            printf("\nOPCAO INVALIDA! TENTE NOVAMENTE\n\n");

        } 

        system("pause");

    } while (opcao != 0);

    return 0;
}

