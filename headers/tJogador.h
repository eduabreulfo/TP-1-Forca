#ifndef _TJOGADOR_H_
#define _TJOGADOR_H_

#define PONTUACAO_INICIAL 6
#define TAM_NOME 14
#define MIN_NOME 3

typedef struct{
  char nome[TAM_NOME];
  int pontos;
  int qtdAcertos;
  int id;
} tJogador;

tJogador mudar_nome(tJogador jogador, char nome[TAM_NOME]);
void imprime_tela_escolher_nomes(int qtd);
int eh_letra(char c);
int eh_numero(char c);
int eh_nome_errado(char nome[TAM_NOME]);
tJogador alterar_id(tJogador jogador, int id);
tJogador reiniciar_pontuacao(tJogador jogador);
tJogador alterar_pontuacao(tJogador jogador, int qtd);
tJogador reiniciar_qtd_acertos(tJogador jogador);
tJogador alterar_qtd_acertos(tJogador jogador, int qtd);
int obtem_pontuacao_jogador(tJogador jogador);
int obtem_qtd_acertos_jogador(tJogador jogador);
void obtem_nome_jogador(char * copiaNome, tJogador jogador);

#endif