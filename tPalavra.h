#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_

#define NOME_ARQUIVO_PALAVRAS "palavras.csv"
#define ID_DICA 0
#define ID_PALAVRA 1
#define QTD_MAX_PALAVRAS 100
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