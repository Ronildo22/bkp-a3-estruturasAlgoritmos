#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Voo
{
    char numero[10];
    char companhiaAerea[50];
    char destino[50];
    char horario[6];
    char status[20];
    struct Voo *ant;
    struct Voo *prox;
} Voo;

Voo *inicio = NULL;
Voo *fim = NULL;

Voo *criarVoo(char numero[], char companhiaAerea[], char destino[], char horario[], char status[])
{
    Voo *novo = (Voo *)malloc(sizeof(Voo));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(novo->numero, numero);
    strcpy(novo->companhiaAerea, companhiaAerea);
    strcpy(novo->destino, destino);
    strcpy(novo->horario, horario);
    strcpy(novo->status, status);
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

void adicionarVoo(char numero[], char companhiaAerea[], char destino[], char horario[], char status[])
{
    Voo *novo = criarVoo(numero, companhiaAerea, destino, horario, status);
    if (inicio == NULL)
    {
        inicio = fim = novo;
    }
    else
    {
        fim->prox = novo;
        novo->ant = fim;
        fim = novo;
    }
}

void removerVoo(char numero[])
{
    Voo *atual = inicio;
    while (atual != NULL && strcmp(atual->numero, numero) != 0)
    {
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        printf("Voo não encontrado.\n");
        return;
    }
    if (atual->ant != NULL)
        atual->ant->prox = atual->prox;
    else
        inicio = atual->prox;
    if (atual->prox != NULL)
        atual->prox->ant = atual->ant;
    else
        fim = atual->ant;
    free(atual);
    printf("Voo removido com sucesso.\n");
}

void atualizarStatus(char numero[], char novoStatus[])
{
    Voo *atual = inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->numero, numero) == 0)
        {
            strcpy(atual->status, novoStatus);
            printf("Status atualizado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Voo não encontrado.\n");
}

void exibirVoos()
{
    Voo *atual = inicio;
    if (atual == NULL)
    {
        printf("Nenhum voo registrado.\n");
        return;
    }
    printf("\n--- Painel de Voos (Ordem de Inserção) ---\n");
    while (atual != NULL)
    {
        printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
               atual->numero, atual->companhiaAerea, atual->destino, atual->horario, atual->status);
        atual = atual->prox;
    }
}

void exibirVoosInverso()
{
    Voo *atual = fim;
    if (atual == NULL)
    {
        printf("Nenhum voo registrado.\n");
        return;
    }
    printf("\n--- Painel de Voos (Ordem Reversa) ---\n");
    while (atual != NULL)
    {
        printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
               atual->numero, atual->companhiaAerea, atual->destino, atual->horario, atual->status);
        atual = atual->ant;
    }
}

void exibirPorStatus(char statusBusca[])
{
    Voo *atual = inicio;
    int encontrados = 0;
    printf("\n--- Voos com Status: '%s' ---\n", statusBusca);
    while (atual != NULL)
    {
        if (strcmp(atual->status, statusBusca) == 0)
        {
            printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
                   atual->numero, atual->companhiaAerea, atual->destino, atual->horario, atual->status);
            encontrados = 1;
        }
        atual = atual->prox;
    }
    if (encontrados == 0)
    {
        printf("Nenhum voo encontrado com este status.\n");
    }
}

// --- Funções de Comparação ---
int compararNumero(const void *a, const void *b) { return strcmp((*(Voo **)a)->numero, (*(Voo **)b)->numero); }
int compararCompanhia(const void *a, const void *b) { return strcmp((*(Voo **)a)->companhiaAerea, (*(Voo **)b)->companhiaAerea); }
int compararDestino(const void *a, const void *b) { return strcmp((*(Voo **)a)->destino, (*(Voo **)b)->destino); }
int compararHorario(const void *a, const void *b)
{
    Voo *v1 = *(Voo **)a;
    Voo *v2 = *(Voo **)b;
    int h1 = 0, m1 = 0, h2 = 0, m2 = 0;
    sscanf(v1->horario, "%d:%d", &h1, &m1);
    sscanf(v2->horario, "%d:%d", &h2, &m2);
    return (h1 * 60 + m1) - (h2 * 60 + m2);
}
// NOVO: Função para comparar por status (para ordenação)
int compararStatus(const void *a, const void *b)
{
    return strcmp((*(Voo **)a)->status, (*(Voo **)b)->status);
}

// ALTERADO: Adicionado critério 5 para ordenação por Status
void exibirOrdenado(int criterio, int ordem)
{
    int count = 0;
    Voo *atual = inicio;
    while (atual != NULL)
    {
        count++;
        atual = atual->prox;
    }
    if (count == 0)
    {
        printf("Nenhum voo registrado.\n");
        return;
    }
    Voo **vetor = (Voo **)malloc(count * sizeof(Voo *));
    if (vetor == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return;
    }
    atual = inicio;
    for (int i = 0; i < count; i++)
    {
        vetor[i] = atual;
        atual = atual->prox;
    }

    switch (criterio)
    {
    case 1:
        qsort(vetor, count, sizeof(Voo *), compararNumero);
        printf("\n--- Voos Ordenados por Número ---\n");
        break;
    case 2:
        qsort(vetor, count, sizeof(Voo *), compararCompanhia);
        printf("\n--- Voos Ordenados por Companhia Aérea ---\n");
        break;
    case 3:
        qsort(vetor, count, sizeof(Voo *), compararDestino);
        printf("\n--- Voos Ordenados por Destino ---\n");
        break;
    case 4:
        qsort(vetor, count, sizeof(Voo *), compararHorario);
        printf("\n--- Voos Ordenados por Horário ---\n");
        break;
    // NOVO: Case para a ordenação por status
    case 5:
        qsort(vetor, count, sizeof(Voo *), compararStatus);
        printf("\n--- Voos Ordenados por Status ---\n");
        break;
    default:
        printf("Critério de ordenação inválido.\n");
        free(vetor);
        return;
    }

    if (ordem == 2)
    {
        for (int i = count - 1; i >= 0; i--)
        {
            printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
                   vetor[i]->numero, vetor[i]->companhiaAerea, vetor[i]->destino, vetor[i]->horario, vetor[i]->status);
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
                   vetor[i]->numero, vetor[i]->companhiaAerea, vetor[i]->destino, vetor[i]->horario, vetor[i]->status);
        }
    }
    free(vetor);
}

void liberarMemoria()
{
    Voo *atual = inicio;
    Voo *proximo;
    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    inicio = fim = NULL;
}

int main()
{
    int opcao, ordem;
    char numero[10], companhiaAerea[50], destino[50], horario[6], status[20];

    do
    {
        // ALTERADO: Menu com a nova opção de ordenação e filtro
        printf("\n========== Painel de Aeroporto ==========\n");
        printf("1. Adicionar Voo\n");
        printf("2. Remover Voo\n");
        printf("3. Atualizar Status do Voo\n");
        printf("4. Exibir Todos os Voos (Ordem de Inserção)\n");
        printf("5. Exibir Todos os Voos (Ordem Reversa)\n");
        printf("-----------------------------------------\n");
        printf("6. Exibir Voos Ordenados por Número\n");
        printf("7. Exibir Voos Ordenados por Companhia Aérea\n");
        printf("8. Exibir Voos Ordenados por Destino\n");
        printf("9. Exibir Voos Ordenados por Horário\n");
        printf("10. Exibir Voos Ordenados por Status\n"); // NOVO (Ordenação)
        printf("-----------------------------------------\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            printf("Número do Voo: ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = '\0';
            printf("Companhia Aérea: ");
            fgets(companhiaAerea, sizeof(companhiaAerea), stdin);
            companhiaAerea[strcspn(companhiaAerea, "\n")] = '\0';
            printf("Destino: ");
            fgets(destino, sizeof(destino), stdin);
            destino[strcspn(destino, "\n")] = '\0';
            printf("Horário (HH:MM): ");
            fgets(horario, sizeof(horario), stdin);
            horario[strcspn(horario, "\n")] = '\0';
            printf("Status: ");
            fgets(status, sizeof(status), stdin);
            status[strcspn(status, "\n")] = '\0';
            adicionarVoo(numero, companhiaAerea, destino, horario, status);
            break;
        case 2:
            printf("Número do Voo a remover: ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = '\0';
            removerVoo(numero);
            break;
        case 3:
            printf("Número do Voo: ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = '\0';
            printf("Novo Status: ");
            fgets(status, sizeof(status), stdin);
            status[strcspn(status, "\n")] = '\0';
            atualizarStatus(numero, status);
            break;
        case 4:
            exibirVoos();
            break;
        case 5:
            exibirVoosInverso();
            break;
        // ALTERADO: Lógica de ordenação agora inclui o case 10
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            printf("Deseja ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
            scanf("%d", &ordem);
            getchar();
            // A fórmula 'opcao - 5' continua funcionando para todos os casos
            exibirOrdenado(opcao - 5, ordem);
            break;
        case 0:
            liberarMemoria();
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}