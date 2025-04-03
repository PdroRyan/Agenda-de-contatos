#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define N 50
#define ARQUIVO "contatos.csv"

typedef struct {
    char nome[128];
    char telefone[15];
} contato;

void salvarContatoArquivo(contato c) {
    FILE *file = fopen(ARQUIVO, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(file, "%s,%s\n", c.nome, c.telefone);
    fclose(file);
}

void carregarContatos(contato agenda[], int *contador) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Nenhum arquivo encontrado. Criando novo...\n");
        return;
    }

    while (fscanf(file, "%127[^,],%14[^\n]\n", agenda[*contador].nome, agenda[*contador].telefone) == 2) {
        (*contador)++;
        if (*contador >= N) break;
    }
    
    fclose(file);
}

void salvarTodosContatos(contato agenda[], int contador) {
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para sobrescrever!\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        if (strcmp(agenda[i].nome, "Deletado") != 0) {
            fprintf(file, "%s,%s\n", agenda[i].nome, agenda[i].telefone);
        }
    }
    
    fclose(file);
}

void addContato(contato agenda[], int *contador) {
    if (*contador >= N) {
        printf("Agenda cheia!\n");
        return;
    }
    
    printf("Insira o nome do contato: ");
    scanf("%s", agenda[*contador].nome);
    printf("Insira o telefone do contato: ");
    scanf("%s", agenda[*contador].telefone);
    
    salvarContatoArquivo(agenda[*contador]); // Salvar no arquivo imediatamente
    (*contador)++;
}

void print(contato agenda[], int contador) {
    for (int j = 0; j < contador; j++) {
        if (strcmp(agenda[j].nome, "Deletado") != 0) {
            printf("NOME: %s\nTELEFONE: %s\n", agenda[j].nome, agenda[j].telefone);
        }
    }
}

void deletarContato(contato agenda[], int *contador) {
    char del[128];
    printf("Digite o nome que deseja deletar: ");
    scanf("%s", del);

    for (int i = 0; i < *contador; i++) {
        if (strcmp(del, agenda[i].nome) == 0) {
            strcpy(agenda[i].nome, "Deletado");
            strcpy(agenda[i].telefone, "----");
            printf("Contato deletado!\n");
        }
    }

    salvarTodosContatos(agenda, *contador); // Atualiza o arquivo após deletar
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    contato agenda[N] = {0};
    int contador = 0;

    carregarContatos(agenda, &contador);

    int z;
    printf("--> Aperte 1 para iniciar\n--> Aperte 2 para encerrar!\n: ");
    scanf("%d", &z);

    if (z == 1) {
        int h;
        do {
            int p;
            printf("\nEscolha uma das opções:\n");
            printf("1: Adicionar contato\n2: Imprimir contatos\n3: Deletar contato\n: ");
            scanf("%d", &p);

            switch (p) {
                case 1:
                    addContato(agenda, &contador);
                    break;
                case 2:
                    print(agenda, contador);
                    break;
                case 3:
                    deletarContato(agenda, &contador);
                    break;
                default:
                    printf("Opção inválida!\n");
            }

            printf("\nPara continuar aperte 1\nPara sair aperte 2\n: ");
            scanf("%d", &h);
        } while (h == 1);
    } else {
        printf("--- ENCERRADO! ---\n");
    }

    return 0;
}
