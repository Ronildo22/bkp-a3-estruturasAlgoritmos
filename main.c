
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Voo {
    char numero[10];
    char destino[50];
    char horario[6]; // formato HH:MM
    char status[20];
    struct Voo* ant;
    struct Voo* prox;
} Voo;

Voo* inicio = NULL;
Voo* fim = NULL;

// Cria novo nó (voo)
Voo* criarVoo(char numero[], char destino[], char horario[], char status[]) {
    Voo* novo = (Voo*) malloc(sizeof(Voo));
    strcpy(novo->numero, numero);
    strcpy(novo->destino, destino);
    strcpy(novo->horario, horario);
    strcpy(novo->status, status);
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

// Adiciona voo no final da lista
void adicionarVoo(char numero[], char destino[], char horario[], char status[]) {
    Voo* novo = criarVoo(numero, destino, horario, status);
    if (inicio == NULL) {
        inicio = fim = novo;
    } else {
        fim->prox = novo;
        novo->ant = fim;
        fim = novo;
    }
    printf("Voo adicionado com sucesso!\n");
}

// Remove voo pelo número
void removerVoo(char numero[]) {
    Voo* atual = inicio;

    while (atual != NULL && strcmp(atual->numero, numero) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
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

// Atualiza status do voo
void atualizarStatus(char numero[], char novoStatus[]) {
    Voo* atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->numero, numero) == 0) {
            strcpy(atual->status, novoStatus);
            printf("Status atualizado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Voo não encontrado.\n");
}

// Exibe voos do início ao fim
void exibirVoos() {
    Voo* atual = inicio;
    if (atual == NULL) {
        printf("Nenhum voo registrado.\n");
        return;
    }

    printf("\n--- Painel de Voos (Ordem normal) ---\n");
    while (atual != NULL) {
        printf("Voo: %s | Destino: %s | Horário: %s | Status: %s\n",
               atual->numero, atual->destino, atual->horario, atual->status);
        atual = atual->prox;
    }
}

// Exibe voos do fim ao início
void exibirVoosInverso() {
    Voo* atual = fim;
    if (atual == NULL) {
        printf("Nenhum voo registrado.\n");
        return;
    }

    printf("\n--- Painel de Voos (Ordem reversa) ---\n");
    while (atual != NULL) {
        printf("Voo: %s | Destino: %s | Horário: %s | Status: %s\n",
               atual->numero, atual->destino, atual->horario, atual->status);
        atual = atual->ant;
    }
}

// Menu principal
int main() {
    int opcao;
    char numero[10], destino[50], horario[6], status[20];

    do {
        printf("\n====== Painel de Aeroporto ======\n");
        printf("1. Adicionar Voo\n");
        printf("2. Remover Voo\n");
        printf("3. Atualizar Status do Voo\n");
        printf("4. Exibir Todos os Voos (Ordem Normal)\n");
        printf("5. Exibir Todos os Voos (Ordem Reversa)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                printf("Número do Voo: ");
                fgets(numero, sizeof(numero), stdin);
                numero[strcspn(numero, "\n")] = '\0';

                printf("Destino: ");
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';

                printf("Horário (HH:MM): ");
                fgets(horario, sizeof(horario), stdin);
                horario[strcspn(horario, "\n")] = '\0';

                printf("Status: ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = '\0';

                adicionarVoo(numero, destino, horario, status);
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

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
