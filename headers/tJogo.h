#ifndef _TJOGO_H_
#define _TJOGO_H_

#include "../headers/tPalavra.h"
#include "../headers/tJogador.h"

#define QTD_MAX_PALAVRAS 100

typedef struct{
  int qtdPalavras;
  tPalavra palavras[QTD_MAX_PALAVRAS];
  int qtdJogadores;
  tJogador jogadores[4];
  char letrasUsadas[27];
  int jogadorAtual;
  int idTema;
  int qtdVencedores;
  int jogadorVencedor[2];
  //tPlacar placar;
} tJogo;
tJogo inicializa_jogo(FILE *arq, tJogo jogo);
tJogo menu_principal(tJogo jogo);
int jogar(tJogo jogo);
void imprime_tela_menu_principal();
void imprime_margem_cima();
void imprime_margem_baixo();
tJogo menu_opcoes(tJogo jogo);
tJogo escolher_nomes(tJogo jogo);
void imprime_tela_jogo(tJogo jogo, int codigo);
void centraliza_string(char * nome, int strSize);
void deixa_primeira_letra_maiuscula(char * str);
void deixa_todas_letras_maiusculas(char * str);
char deixa_letra_maiscula(char letra);
int palavra_tem_letra(char * palavra, char letra);
void adicionar_letra(char * str, char letra);
tJogo calcula_fim_de_jogo(tJogo jogo);
int palavra_foi_descoberta(tJogo jogo);
int eh_fim_de_jogo(tJogo jogo);
tJogo reinicializa_jogo(tJogo jogo, int jogadorInicial); //1 a 4, ou 0 para aleatorio
int jogar_novamente();

#endif