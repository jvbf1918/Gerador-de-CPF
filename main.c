//declaração de funções
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

// Inclui cabeçalhos com funções externas
#include "funcoes.h"
#include "funcoes.c"

// Define a struct que representa um CPF gerado
typedef struct {
    int cpf[11];
    char uf[3];
    int digitoUF;
} CPFInfo;

// Função para salvar o CPF no arquivo formatado
void salvar_cpf_formatado(FILE *arquivo, int cpf[]) {
    for (int j = 0; j < 11; j++) {
        fprintf(arquivo, "%d", cpf[j]);
        if (j == 2 || j == 5) fprintf(arquivo, ".");
        if (j == 8) fprintf(arquivo, "-");
    }
    fprintf(arquivo, "\n");
}

int main() {
    setlocale(LC_ALL, "pt_BR.utf8");
    srand(time(NULL));

    char uf[3];
    int quantidade;

    //pedir a uf para gerar cpf
    printf("Digite a sigla do estado com as letras em maiúsculo (ex: SP, RJ, MG):\n");
    scanf("%2s", uf);  // até 2 caracteres + \0

    // Corrige para maiúsculo se necessário
    for (int i = 0; uf[i] != '\0'; i++) {
        uf[i] = islower(uf[i]) ? toupper(uf[i]) : uf[i];
    }

    //retorna uf invalida caso não seja uma uf que está na função
    int digitoUF = digito_Estado_Por_UF(uf);
    if (digitoUF == -1) {
        printf("UF inválida.\n");
        return 1;
    }

    //pede a quantidade de cpfs
    printf("Quantos CPFs válidos deseja gerar? ");
    scanf("%d", &quantidade);

    // Alocar memória para os CPFs
    // Cria um ponteiro lista que ira armazenar os dados da struct
    CPFInfo *lista = malloc(sizeof(CPFInfo) * quantidade); //o malloc ira armazenar dinamicamente a memoria para a quantidade de cpfs
    if (lista == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // abrir o arquivo, se não funcionar, finaliza
    FILE *arquivo = fopen("cpfs_gerados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        free(lista);
        return 1;
    }

    //escreve no arquivo o lugar que os cpfs gerados pertencem
    fprintf(arquivo, "CPFs gerados para o estado %s:\n", uf);

    //laço para salvar os cpfs no arquivo com as funções
    for (int i = 0; i < quantidade; i++) {
        strcpy(lista[i].uf, uf);
        lista[i].digitoUF = digitoUF;

        gerar_cpf_valido(lista[i].cpf, digitoUF);
        salvar_cpf_formatado(arquivo, lista[i].cpf);
    }

    //fechar arquivo
    fclose(arquivo);
    //confirmar que funcionou
    printf("CPFs salvos em 'cpfs_gerados.txt'.");

    // Ler o arquivo gerado
    FILE *arquivo_leitura = fopen("cpfs_gerados.txt", "r");
    if (arquivo_leitura == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        free(lista);
        return 1;
    }

    printf("\nConteúdo do arquivo 'cpfs_gerados.txt':\n");

    //le linha por linha e imprime na tela
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo_leitura)) {
        printf("%s", linha);
    }

    //fecha o arquivo e finaliza o programa :)
    fclose(arquivo_leitura);
    free(lista);
    return 0;
}

