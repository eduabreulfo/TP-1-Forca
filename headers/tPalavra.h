#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_

#include <stdio.h>

#define TAM_PALAVRA 14

typedef struct{
  char palavra[2][TAM_PALAVRA];
  int tamanho;
} tPalavra;

int conta_palavras(FILE *arq);
void le_palavras(FILE *arq, tPalavra * palavras, int qtd);
void obtem_dica(char * copiaNome, tPalavra palavra);
void obtem_palavra(char * copiaNome, tPalavra palavra);

#endif