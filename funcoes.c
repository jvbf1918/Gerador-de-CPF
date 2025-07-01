#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

//função que calcula a validade do primeiro digito verificador
int calcular_primeiro_digito(int cpf[]) {
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += cpf[i] * (10 - i);
    }
    int resto = (soma * 10) % 11;
    return (resto == 10) ? 0 : resto;
}

//função que calcula a validade do segundo digito verificador
int calcular_segundo_digito(int cpf[]) {
    int soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += cpf[i] * (11 - i);
    }
    int resto = (soma * 10) % 11;
    return (resto == 10) ? 0 : resto;
}

//função que coloca como nono digito, o digito de sua UF correspondente
int digito_Estado_Por_UF(char uf[]) {
    if (strcmp(uf, "RS") == 0) return 0;
    if (strcmp(uf, "DF") == 0 || strcmp(uf, "GO") == 0 || strcmp(uf, "MS") == 0 || strcmp(uf, "MT") == 0 || strcmp(uf, "TO") == 0) return 1;
    if (strcmp(uf, "AM") == 0 || strcmp(uf, "PA") == 0 || strcmp(uf, "AC") == 0 || strcmp(uf, "AP") == 0 || strcmp(uf, "RO") == 0 || strcmp(uf, "RR") == 0) return 2;
    if (strcmp(uf, "CE") == 0 || strcmp(uf, "MA") == 0 || strcmp(uf, "PI") == 0) return 3;
    if (strcmp(uf, "PE") == 0 || strcmp(uf, "RN") == 0 || strcmp(uf, "PB") == 0 || strcmp(uf, "AL") == 0) return 4;
    if (strcmp(uf, "BA") == 0 || strcmp(uf, "SE") == 0) return 5;
    if (strcmp(uf, "MG") == 0) return 6;
    if (strcmp(uf, "RJ") == 0 || strcmp(uf, "ES") == 0) return 7;
    if (strcmp(uf, "SP") == 0) return 8;
    if (strcmp(uf, "PR") == 0 || strcmp(uf, "SC") == 0) return 9;
    return -1;
}

//função que gera o cpf
void gerar_cpf_valido(int cpf[], int digitoUF) {
    for (int i = 0; i < 8; i++) {
        cpf[i] = rand() % 10;
    }
    cpf[8] = digitoUF;
    cpf[9] = calcular_primeiro_digito(cpf);
    cpf[10] = calcular_segundo_digito(cpf);
}
