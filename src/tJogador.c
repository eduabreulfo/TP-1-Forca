
#include <stdio.h>
#include "../headers/tJogador.h"

tJogador mudar_nome(tJogador jogador, char nome[TAM_NOME]){
  sprintf(jogador.nome, "%s", nome);
  return jogador;
}

tJogador alterar_id(tJogador jogador, int id){
  jogador.id = id;
  return jogador;
}

tJogador alterar_pontuacao(tJogador jogador, int qtd){
  jogador.pontos += qtd;
  return jogador;
}

tJogador reiniciar_pontuacao(tJogador jogador){
  jogador.pontos = PONTUACAO_INICIAL;
  return jogador;
}

tJogador alterar_qtd_acertos(tJogador jogador, int qtd){
  jogador.qtdAcertos += qtd;
  return jogador;
}

tJogador reiniciar_qtd_acertos(tJogador jogador){
  jogador.qtdAcertos = 0;
  return jogador;
}

int obtem_pontuacao_jogador(tJogador jogador){
  int pts;
  pts = jogador.pontos;
  return pts;
}

int obtem_qtd_acertos_jogador(tJogador jogador){
  int qtd;
  qtd = jogador.qtdAcertos;
  return qtd;
}