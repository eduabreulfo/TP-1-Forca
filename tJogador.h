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
tJogador MudarNome(tJogador jogador, char nome[TAM_NOME]);
void ImprimeTelaEscolherNomes(int qtd);
int EhLetra(char c);
int EhNumero(char c);
int EhNomeErrado(char nome[TAM_NOME]);
tJogador AlterarID(tJogador jogador, int id);
tJogador ReiniciarPontuacao(tJogador jogador);
tJogador AlterarPontuacao(tJogador jogador, int qtd);
tJogador ReiniciarQtdAcertos(tJogador jogador);
tJogador AlterarQtdAcertos(tJogador jogador, int qtd);
int ObtemPontuacaoJogador(tJogador jogador);
int ObtemQtdAcertosJogador(tJogador jogador);
void ObtemNomeJogador(char * copiaNome, tJogador jogador);

#endif