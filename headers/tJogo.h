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
tJogo InicializaJogo(FILE *arq, tJogo jogo);
tJogo MenuPrincipal(tJogo jogo);
int Jogar(tJogo jogo);
void ImprimeTelaMenuPrincipal();
void ImprimeMargemCima();
void ImprimeMargemBaixo();
tJogo MenuOpcoes(tJogo jogo);
tJogo EscolherNomes(tJogo jogo);
void ImprimeTelaJogo(tJogo jogo, int codigo);
void CentralizaString(char * nome, int strSize);
void DeixaPrimeiraLetraMaiuscula(char * str);
void DeixaTodasLetrasMaiusculas(char * str);
char DeixaLetraMaiscula(char letra);
int PalavraTemLetra(char * palavra, char letra);
void AdicionarLetra(char * str, char letra);
tJogo CalculaFimDeJogo(tJogo jogo);
int PalavraFoiDescoberta(tJogo jogo);
int EhFimDeJogo(tJogo jogo);
tJogo ReinicializaJogo(tJogo jogo, int jogadorInicial); //1 a 4, ou 0 para aleatorio
int JogarNovamente();

#endif