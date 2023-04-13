#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_

#define TAM_PALAVRA 15

typedef struct{
  char palavra[2][TAM_PALAVRA];
  int tamanho;
} tPalavra;

int ContaPalavras(FILE *arq);
void LePalavras(FILE *arq, tPalavra * palavras, int qtd);
void ObtemDica(char * copiaNome, tPalavra palavra);
void ObtemPalavra(char * copiaNome, tPalavra palavra);

#endif