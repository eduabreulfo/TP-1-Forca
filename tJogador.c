#ifndef _TJOGADOR_C_
#define _TJOGADOR_C_

#include "tJogador.h"

tJogador MudarNome(tJogador jogador, char nome[TAM_NOME]){
  sprintf(jogador.nome, nome);
  return jogador;
}

tJogador AlterarID(tJogador jogador, int id){
  jogador.id = id;
  return jogador;
}

tJogador AlterarPontuacao(tJogador jogador, int qtd){
  jogador.pontos += qtd;
  return jogador;
}

tJogador ReiniciarPontuacao(tJogador jogador){
  jogador.pontos = PONTUACAO_INICIAL;
  return jogador;
}

tJogador AlterarQtdAcertos(tJogador jogador, int qtd){
  jogador.qtdAcertos += qtd;
  return jogador;
}

tJogador ReiniciarQtdAcertos(tJogador jogador){
  jogador.qtdAcertos = 0;
  return jogador;
}

int ObtemPontuacaoJogador(tJogador jogador){
  int pts;
  pts = jogador.pontos;
  return pts;
}

int ObtemQtdAcertosJogador(tJogador jogador){
  int qtd;
  qtd = jogador.qtdAcertos;
  return qtd;
}

#endif