#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Voo
{
    char numero[10];
    char companhiaAerea[50]; // NOVO: Campo para a companhia aérea
    char destino[50];
    char horario[6]; // formato HH:MM
    char status[20];
    struct Voo *ant;
    struct Voo *prox;
} Voo;

Voo *inicio = NULL;
Voo *fim = NULL;

// ALTERADO: Adicionado o parâmetro 'companhiaAerea'
Voo *criarVoo(char numero[], char companhiaAerea[], char destino[], char horario[], char status[])
{
    Voo *novo = (Voo *)malloc(sizeof(Voo));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(novo->numero, numero);
    strcpy(novo->companhiaAerea, companhiaAerea); // NOVO: Copia a companhia
    strcpy(novo->destino, destino);
    strcpy(novo->horario, horario);
    strcpy(novo->status, status);
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

// ALTERADO: Adicionado o parâmetro 'companhiaAerea'
void adicionarVoo(char numero[], char companhiaAerea[], char destino[], char horario[], char status[])
{
    // ALTERADO: Passa o novo parâmetro para criarVoo
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
    printf("Voo adicionado com sucesso!\n");
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
        // ALTERADO: Adicionado 'companhiaAerea' na exibição
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
        // ALTERADO: Adicionado 'companhiaAerea' na exibição
        printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
               atual->numero, atual->companhiaAerea, atual->destino, atual->horario, atual->status);
        atual = atual->ant;
    }
}

// --- Funções de Comparação ---

int compararNumero(const void *a, const void *b)
{
    Voo *v1 = *(Voo **)a;
    Voo *v2 = *(Voo **)b;
    return strcmp(v1->numero, v2->numero);
}

// NOVO: Função para comparar por companhia aérea
int compararCompanhia(const void *a, const void *b)
{
    Voo *v1 = *(Voo **)a;
    Voo *v2 = *(Voo **)b;
    return strcmp(v1->companhiaAerea, v2->companhiaAerea);
}

int compararDestino(const void *a, const void *b)
{
    Voo *v1 = *(Voo **)a;
    Voo *v2 = *(Voo **)b;
    return strcmp(v1->destino, v2->destino);
}

int compararHorario(const void *a, const void *b)
{
    Voo *v1 = *(Voo **)a;
    Voo *v2 = *(Voo **)b;
    int h1 = 0, m1 = 0, h2 = 0, m2 = 0;
    sscanf(v1->horario, "%d:%d", &h1, &m1);
    sscanf(v2->horario, "%d:%d", &h2, &m2);
    int total_minutos1 = h1 * 60 + m1;
    int total_minutos2 = h2 * 60 + m2;
    return total_minutos1 - total_minutos2;
}

// ALTERADO: Adicionado critério 4 para companhia aérea
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
        qsort(vetor, count, sizeof(Voo *), compararCompanhia); // NOVO: Chamada para o comparador
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
    default:
        printf("Critério de ordenação inválido.\n");
        free(vetor);
        return;
    }

    if (ordem == 2)
    { // Ordem decrescente
        for (int i = count - 1; i >= 0; i--)
        {
            // ALTERADO: Adicionado 'companhiaAerea' na exibição
            printf("Voo: %s | Companhia: %s | Destino: %s | Horário: %s | Status: %s\n",
                   vetor[i]->numero, vetor[i]->companhiaAerea, vetor[i]->destino, vetor[i]->horario, vetor[i]->status);
        }
    }
    else
    { // Ordem crescente
        for (int i = 0; i < count; i++)
        {
            // ALTERADO: Adicionado 'companhiaAerea' na exibição
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

// Menu principal
int main()
{
    int opcao, ordem;
    // NOVO: Adicionada variável para companhiaAerea
    char numero[10], companhiaAerea[50], destino[50], horario[6], status[20];

    do
    {
        // ALTERADO: Menu com nova opção de ordenação
        printf("\n========== Painel de Aeroporto ==========\n");
        printf("1. Adicionar Voo\n");
        printf("2. Remover Voo\n");
        printf("3. Atualizar Status do Voo\n");
        printf("4. Exibir Todos os Voos (Ordem de Inserção)\n");
        printf("5. Exibir Todos os Voos (Ordem Reversa)\n");
        printf("-----------------------------------------\n");
        printf("6. Exibir Voos Ordenados por Número\n");
        printf("7. Exibir Voos Ordenados por Companhia Aérea\n"); // NOVO
        printf("8. Exibir Voos Ordenados por Destino\n");
        printf("9. Exibir Voos Ordenados por Horário\n");
        printf("-----------------------------------------\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer

        switch (opcao)
        {
        case 1:
            printf("Número do Voo: ");
            fgets(numero, sizeof(numero), stdin);
            numero[strcspn(numero, "\n")] = '\0';

            // NOVO: Pede a companhia aérea ao usuário
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

            // ALTERADO: Passa a companhia para a função
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

        // ALTERADO: Reorganização das opções de ordenação
        case 6: // Ordenar por Número (critério 1)
            printf("Deseja ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
            scanf("%d", &ordem);
            getchar();
            exibirOrdenado(1, ordem);
            break;

        case 7: // Ordenar por Companhia (critério 2)
            printf("Deseja ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
            scanf("%d", &ordem);
            getchar();
            exibirOrdenado(2, ordem);
            break;

        case 8: // Ordenar por Destino (critério 3)
            printf("Deseja ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
            scanf("%d", &ordem);
            getchar();
            exibirOrdenado(3, ordem);
            break;

        case 9: // Ordenar por Horário (critério 4)
            printf("Deseja ordem:\n1. Crescente\n2. Decrescente\nEscolha: ");
            scanf("%d", &ordem);
            getchar();
            exibirOrdenado(4, ordem);
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