#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_

#define TAM_PALAVRA 15

typedef struct{
  char palavra[2][TAM_PALAVRA];
  int tamanho;
} tPalavra;

void LePalavras(tPalavra * palavras, int qtd);
int ContaPalavras();
void ObtemDica(char * copiaNome, tPalavra palavra);
void ObtemPalavra(char * copiaNome, tPalavra palavra);

#endif