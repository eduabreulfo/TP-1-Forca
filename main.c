#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/tJogo.h"

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

  jogo = InicializaJogo(jogo);
  printf("InicializaJogo(jogo) saiu ok\n");
  jogo = MenuPrincipal(jogo);
  jogo = EscolherNomes(jogo);
  Jogar(jogo);
  
  return 0;
}

//Eduardo Abreu Lanes Fidelis de Oliveira
//UFES | Goiabeiras - 04/2023