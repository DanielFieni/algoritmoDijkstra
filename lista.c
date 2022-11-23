#include "lista.h"

void lerCidadesArquivo(TLista *vetor)
{
    FILE *arq;
    char nomeCidade[30];

    arq = fopen("nomeCidadesFile.txt", "r");

    int i = 0;
    while (fgets(nomeCidade, 256, arq))
    {
        char *linha = strtok(nomeCidade, "\n");
        printf("CIDADE: %s\n", linha);
        // Inserir as cidades nas suas posicoes, toda cidade no inicio tera distancia 0
        inserirNomeCidades(&vetor[i], linha, 0);
        i++;
    }

    fclose(arq);
}

void lerRelacoesArquivo(TLista *vetor, int matriz[TAM][TAM])
{
    FILE *arq;
    char nomeCidade[30], nomeCidade2[30];
    int distanciaCidades;

    arq = fopen("relacoesCidades.txt", "r");

    while (fgets(nomeCidade, 256, arq))
    {
        char *cidadeOrigem = strtok(nomeCidade, "\n");
        fgets(nomeCidade2, 256, arq);
        char *cidadeDestino = strtok(nomeCidade2, "\n");
        fscanf(arq, "%d\n", &distanciaCidades);

        inserirRelacoesMatriz(matriz, vetor, cidadeOrigem, cidadeDestino, distanciaCidades);
    }

    fclose(arq);
}

// Criacao do MENU
int menu()
{

    int opcao;

    system("CLS");

    printf("\n\n\n\t| MENU |\n\n");
    printf("1 - Imprimir Relacoes.\n");
    printf("2 - Imprimir Cidades.\n");
    printf("3 - Dijkstra.\n");
    printf("Informe uma opcao: ");
    scanf("%d", &opcao);

    return opcao;

}

/* ================================================================= */

void inicializarMatriz(int matriz[TAM][TAM])
{

    // Inicializar todas as posicoes da matriz com 0
    int i, j;
    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

            matriz[i][j] = 0;

        }
    }

}

void inicializaLista(TLista *lista)
{

    // Inicializa a lista definido NULL para o inicio e o fim e distancia 0
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->distancia = 0;

}

void inicializaVetor(TLista *vetor)
{

    // Inicializa todas a posicoes do vetor que são do tipo TLista
    int i;
    for(i = 0; i < TAM; i++){
        inicializaLista(&vetor[i]);
    }

}

/* ================================================================= */

void imprimirVertices(TLista *vetor)
{

    int i;
    printf("\n");
    
    // Percorre o vetor sempre printando o elemento da primeira posicao da lista
    for(i = 0; i < TAM; i++){
        printf("(%d) - %s\n", i, vetor[i].inicio->nome);
    }
    printf("\n");

}

// Funcao para exibir cada elemento da lista de uma determinada posicao do vetor
void exibir_lista(TLista *lista)
{
	TVertice *atual = lista->inicio;

	while(atual != NULL){
		printf("\t(%d) \t%s\n", atual->distancia, atual->nome);
		atual = atual->prox;
	}

    printf("\n");

}

// Percorre o vetor e chama uma funcao para mostrar a lista de cada posicao do vetor
void exibir_vetor(TLista *vetor)
{
	int i;

	for(i = 0; i < TAM; i++){
		printf("%d - " ,i);
		// E passado como parametro cada posição do vetor para ser listado no exibir_lista()
		exibir_lista(&vetor[i]);

	}
}

/* ================================================================= */
void inserirNomeCidades(TLista *lista, char *nomeCidade, int distancia)
{

    // Alocar espaco para a insercao de um novo elemento
    TVertice *novo = (TVertice *) malloc (sizeof(TVertice));

    // Atribui os valores do novo elemento que sera inserido
    strcpy(novo->nome, nomeCidade);
    novo->distancia = distancia;
    novo->prox = NULL;

    // Se a lista for vazia insere o elemento no comeco da lista
    if (lista->inicio == NULL){
        lista->inicio = novo;

    } else {

        // Se nao inserir no comeco, o novo elemento sera inserido no final da lista
        TVertice *aux = lista->inicio;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;

    }

}

int encontrarPosicaoCidade(TLista *vetorCidades, char *nomeCidade)
{

    int i;

    // Percorrer todas as posicoes do vetor de lista
    for(i = 0; i < TAM; i++)
    {
        if(strcmp(vetorCidades[i].inicio->nome, nomeCidade) == 0){
            // Se encontrar o nome da cidade, retorna a posicao no vetor que a cidade esta localizada
            return i;

        }

    }

    return -1;

}

// Essa funcao serve para formar a lista de adjacencia, sempre que um elemento tem relacao outro, ele eh adicionado na lista
void inserirRelacoesMatriz(int matriz[TAM][TAM], TLista *vetor, char *nomeCidade1, char *nomeCidade2, int distancia)
{
    // Os parametros passados nas funcoes sao: a posicao no vetor que o elemento sera inserido, o nome da cidade que sera inserida e a distancia entre as cidades
    int posicaoCidade1, posicaoCidade2;

    posicaoCidade1 = encontrarPosicaoCidade(vetor, nomeCidade1);
    posicaoCidade2 = encontrarPosicaoCidade(vetor, nomeCidade2);
    matriz[posicaoCidade1][posicaoCidade2] = distancia;

    // Inseri o nome da cidade 2 na lista de adjacencia da cidade 1
    inserirNomeCidades(&vetor[posicaoCidade1], vetor[posicaoCidade2].inicio->nome, distancia);

}

/* ================================================================= */

// Funcao chamada na main onde sao pedidos o codigo da cidade origem e cidade destino
void algoritmoMenorCaminho(int matriz[TAM][TAM], TLista *vetorCidades)
{
    int codOrigem, codDestino;

    printf("Codigo de ORIGEM: ");
    scanf("%d", &codOrigem);

    printf("Codigo de DESTINO: ");
    scanf("%d", &codDestino);

    // Chamada da funcao Dijkstra
    dijkstra(matriz, codOrigem, codDestino, vetorCidades);
}

// Funcao para inicializar todos os vetores e matrizes utilizados na funcao dijkstra()
void inicializarVetoresDijkstra(int matCusto[TAM][TAM], int *vetDistancia, int *vetAnterior, int *visitados, int codOrigem, int mat[TAM][TAM])
{

    int i, j;
    
    // Inicializa a matCusto[][], matriz que ira conter os custos das cidades
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            if (mat[i][j] == 0)
                matCusto[i][j] = INFINITY;
            else
                matCusto[i][j] = mat[i][j];

    // Inicializar o vetAnterior[], vetDistancia e visitados[]
    for (i = 0; i < TAM; i++)
    {
        vetDistancia[i] = matCusto[codOrigem][i];
        vetAnterior[i] = codOrigem;
        visitados[i] = 0;
    }

    vetDistancia[codOrigem] = 0;
    visitados[codOrigem] = 1;
}

// Funcao que ira mostrar o menor caminho de uma cidade origem para uma cidade destino
void dijkstra(int mat[TAM][TAM], int codOrigem, int codDestino, TLista *vetorCidades)
{

    int matCusto[TAM][TAM], vetDistancia[TAM], vetAnterior[TAM];
    int visitados[TAM], contador, menorDistancia, proximaVertice, i, j;

    // Chamada da funcao inicializarVetoresDijkstra()
    inicializarVetoresDijkstra(matCusto, vetDistancia, vetAnterior, visitados, codOrigem, mat);

    contador = 1;

    while (contador < TAM - 1)
    {
        menorDistancia = INFINITY;
        // proximaVertice recebe a vertice de menor distancia

        for (i = 0; i < TAM; i++)
        {
            if (vetDistancia[i] < menorDistancia && !visitados[i])
            {
                menorDistancia = vetDistancia[i];
                proximaVertice = i;
            }
        }

        // Verifica se existe um caminho melhor através da próximaVertice
        visitados[proximaVertice] = 1;
        for (i = 0; i < TAM; i++)
        {
            if (!visitados[i])
            {
                if (menorDistancia + matCusto[proximaVertice][i] < vetDistancia[i])
                {
                    vetDistancia[i] = menorDistancia + matCusto[proximaVertice][i];
                    vetAnterior[i] = proximaVertice;
                }
            }
        }
        contador++;
    }

    printf("\nDistancia para cidade %s = %d", vetorCidades[codDestino].inicio->nome, vetDistancia[codDestino]);
    printf("\nCaminho Percorrido: \n\t%s", vetorCidades[codDestino].inicio->nome);
    j = codDestino;

    while (j != codOrigem)
    {
        j = vetAnterior[j];
        printf(" <= %s ", vetorCidades[j].inicio->nome);
    }

    printf("\n");
    system("PAUSE");
}

