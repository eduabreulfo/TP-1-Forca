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
tPlacar OrganizaPlacar(tPlacar placar);
*/

int main(void){
  tJogo jogo;
  //srand(time(NULL));
  FILE *arq = fopen(NOME_ARQUIVO_PALAVRAS, "r");

  jogo = InicializaJogo(arq, jogo);
  printf("InicializaJogo() saiu ok\n");
    fclose(arq);
  jogo = MenuPrincipal(jogo);
  jogo = EscolherNomes(jogo);
  Jogar(jogo);
  
  return 0;
}

//Eduardo Abreu Lanes Fidelis de Oliveira
//UFES | Goiabeiras - 04/2023