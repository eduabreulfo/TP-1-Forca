#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tJogo.h"

//tPlacar
/*
typedef struct{
  tJogador vencedores[100]; //top 100
} tPlacar;
tPlacar OrganizaPlacar(tPlacar placar);
*/

int main(void){
  tJogo jogo;
  srand(time(NULL));

  jogo = InicializaJogo(jogo); //inicializacao dos temas
  jogo = MenuPrincipal(jogo); //tela inicial
  jogo = EscolherNomes(jogo); //escolha dos nomes
  Jogar(jogo); //partida
  
  return 0;
}

//Eduardo Abreu Lanes Fidelis de Oliveira
//UFES - Goiabeiras, Brazil