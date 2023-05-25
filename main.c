
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/tJogo.h"

#define NOME_ARQUIVO_PALAVRAS "data/palavras.csv"

//tPlacar
/*
typedef struct{
  tJogador vencedores[100]; //top 100
} tPlacar;
tPlacar organiza_placar(tPlacar placar);
*/

int main(){
  tJogo jogo;
  // srand(time(NULL));
  FILE *arq = fopen(NOME_ARQUIVO_PALAVRAS, "r");

  jogo = inicializa_jogo(arq, jogo);
  fclose(arq);
  jogo = menu_principal(jogo);
  jogo = escolher_nomes(jogo);
  jogar(jogo);
  
  return 0;
}

//Eduardo Abreu Lanes Fidelis de Oliveira
//UFES | Goiabeiras - 04/2023