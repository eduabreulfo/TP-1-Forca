#include <stdio.h>
#include <stdlib.h>
#include "../headers/common.h"
#include "../headers/tJogo.h"
#include "../headers/tJogador.h"
#include "../headers/tPalavra.h"

tJogo inicializa_jogo(FILE *arq, tJogo jogo){
  int i=0;

  jogo.qtdPalavras = conta_palavras(arq); printf("contou palavras!\n");
  le_palavras(arq, jogo.palavras, jogo.qtdPalavras); printf("leu palavras!!\n");

  jogo.jogadorVencedor[0] = 0;
  jogo.jogadorVencedor[1] = -1;
  jogo.qtdVencedores = -1;

  for(i=0;i<27;i++){
    jogo.letrasUsadas[i] = '\0';
  }

  return jogo;
}

tJogo menu_principal(tJogo jogo){//
  int i=0;
  char opcao='a';

  limpa_tela();
  imprime_tela_menu_principal(0); //padrao
  while(1){
    opcao='a';
    imprime_prefixo();
    scanf("%c", &opcao);
    if(opcao == '0'){
      exit(0);
    }
    if(opcao>='1' && opcao<='4'){
      jogo.qtdJogadores = opcao-'0';
      for(i=0;i<jogo.qtdJogadores;i++){
        jogo.jogadores[i] = alterar_id(jogo.jogadores[i], i+1);
        jogo.jogadores[i] = reiniciar_pontuacao(jogo.jogadores[i]);
        jogo.jogadores[i] = reiniciar_qtd_acertos(jogo.jogadores[i]);
      }
      break;
    }
    limpa_tela();
    imprime_tela_menu_principal(1); //entrada invalida
  }
  
  return jogo;
}

void imprime_tela_menu_principal(int erro){//
  char msg[24];
  switch(erro){
    case 0:
      sprintf(msg, " ");
    break;
    
    case -1:
      sprintf(msg, "Digite 0 para confirmar");
    break;

    case 1:
      sprintf(msg, "   Opcao invalida!!!");
    break;
  }
  imprime_margem_cima();
  printf(
  "s       _________________     |        |                       s\n"
  "s      |                 |  <_|()(|() (|(|                     s\n"
  "s      |     ____________|       _|                            s\n"
  "s      |    |     (>>>>)    ___ ___    ______   ________       s\n"
  "s      |    |__   (>>>>)   |   |   |  /      | /   __   \\      s\n"
  "s      |       |  (>>>>)   |    ___| /    ___| |__|  |  |      s\n"
  "s      |     __| / /^^\\/\\  |   /     |   |      _____|  |      s\n"
  "s      |    |   ( (    )/) |   |     |   |     /   __   |      s\n"
  "s      |    |   | |    |/| |   |     |   |___  |  /  |  |      s\n"
  "s      |    |   \\ \\____/// |   |     \\       | |  \\__|  |      s\n"
  "s      |____|    \\______/  |___|      \\______| \\_____,__|      s\n"
  "s                      __               _                      s\n"
  "s                     |_  |       |    /_||    _               s\n"
  "s              |)()|' |__(|(/(||'(|() /  ||)|'(-(/             s\n"
  "s              |                                               s\n"
  "s%40s                      s\n"
  "s                  +-------------------------+                 s\n"
  "s                  |  1- Solo (Treinamento)  |                 s\n"
  "s                  |  2- 2 jogadores         |                 s\n"
  "s                  |  3- 3 jogadores         |                 s\n"
  "s                  |  4- 4 jogadores         |                 s\n"
  "s                  |  0- Sair do Jogo        |                 s\n"
  "s  UFES 2023       +-------------------------+           v1.0  s\n"
  , msg);
  imprime_margem_baixo();
}

void imprime_margem_cima(){//
  printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
}

void imprime_margem_baixo(){//
  printf("+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
}

tJogo escolher_nomes(tJogo jogo){//
  int i=0, j=0;
  char entrada[50];
  char jog[4][TAM_NOME];
  char seta[4][3][4];
  char numeroJogadorAscii[4][7];
  char msgErro[48];
  int deuErro=0;

  for(i=0;i<4;i++){
    for(j=0;j<3;j++){
      seta[i][j][0] = '\0';
    }
  }
  
  for(i=0;i<4;i++){
    jog[i][0] = '\0';
  }

  msgErro[0] = '\0';

  switch(jogo.qtdJogadores){
    case 4:
      sprintf(jog[3], "_____________");
    
    case 3:
      sprintf(jog[2], "_____________");

    case 2:
      sprintf(jog[1], "_____________");

    case 1:
      sprintf(jog[0], "_____________");
    break;
  }

  for(i=0;i<jogo.qtdJogadores;i++){
    sprintf(seta[i][0], " _ ");
    sprintf(seta[i][1], "\\ \\");
    sprintf(seta[i][2], "/_/");

    switch(i){
      case 0:
        sprintf(numeroJogadorAscii[0], " ___|_");
        sprintf(numeroJogadorAscii[1], "|_  | ");
        sprintf(numeroJogadorAscii[2], " _| |_");
        sprintf(numeroJogadorAscii[3], "|_____");
      break;

      case 1:
        sprintf(numeroJogadorAscii[0], " ___|_");
        sprintf(numeroJogadorAscii[1], "|_  | ");
        sprintf(numeroJogadorAscii[2], "|  _| ");
        sprintf(numeroJogadorAscii[3], "|___| ");
      break;

      case 2:
        sprintf(numeroJogadorAscii[0], " ___|_");
        sprintf(numeroJogadorAscii[1], "|_  | ");
        sprintf(numeroJogadorAscii[2], "|_  | ");
        sprintf(numeroJogadorAscii[3], "|___| ");
      break;

      case 3:
        sprintf(numeroJogadorAscii[0], " ___|_");
        sprintf(numeroJogadorAscii[1], "| | | ");
        sprintf(numeroJogadorAscii[2], "|_  | ");
        sprintf(numeroJogadorAscii[3], "  |_| ");
      break;
    }

    limpa_tela();
    imprime_margem_cima();
    printf("\n"
    "        _____                                 _                   \n"
    "       |     |___ _____ ___    ___ ___    ___| |_ ___ _____ ___\n"
    "       |   --| . |     | . |  |_ -| -_|  |  _|   | .'|     | .'|_\n"
    "       |_____|___|_|_|_|___|  |___|___|  |___|_|_|__,|_|_|_|__,| |\n"
    "                                                  _____        |_|\n"
    "                __               _           %6s__  |\n"
    "             __|  |___ ___ ___ _| |___ ___   %6s|  _|\n"
    "            |  |  | . | . | .'| . | . |  _|  %6s|_|\n"
    "            |_____|___|_  |__,|___|___|_|    %6s|_|\n"
    "                      |___|\n"
    "\n"
    "\n"
    "\n"
    "         %47s\n"
    "\n"
    "          %3s                          %3s\n"
    "          %3s                          %3s\n"
    "          %3s  %13s           %3s  %13s\n"
    "\n"
    "          %3s                          %3s\n"
    "          %3s                          %3s\n"
    "          %3s  %13s           %3s  %13s\n"
    "\n"
    "\n"
    "\n",
    numeroJogadorAscii[0],
    numeroJogadorAscii[1],
    numeroJogadorAscii[2],
    numeroJogadorAscii[3], msgErro,
    seta[0][0], seta[1][0],
    seta[0][1], seta[1][1],
    seta[0][2], jog[0], seta[1][2], jog[1],
    seta[2][0], seta[3][0],
    seta[2][1], seta[3][1],
    seta[2][2], jog[2], seta[3][2], jog[3]);
    imprime_margem_baixo();
    
    seta[i][0][0] = '\0';
    seta[i][1][0] = '\0';
    seta[i][2][0] = '\0';

    msgErro[0] = '\0';

    imprime_prefixo();
    scanf("%49s", entrada);

    deuErro = eh_nome_errado(entrada);
    switch(deuErro){
      case 1:
      sprintf(msgErro, "          O nome deve comecar com uma letra!!! ");
      i--;
      break;

      case 2:
      sprintf(msgErro, "            Use somente letras ou numeros!!!   ");
      i--;
      break;

      case 3:
      sprintf(msgErro, "           Nao use mais que %d caracteres!!!   ", TAM_NOME-1);
      i--;
      break;

      case 4:
      sprintf(msgErro, "             Use pelo menos %d caracteres!!!   ", MIN_NOME);
      i--;
      break;
      
      case 0:
      sprintf(jog[i], "%s", entrada);
      jogo.jogadores[i] = mudar_nome(jogo.jogadores[i], entrada);
      centraliza_string(jog[i], sizeof(jog[i]));
      break;
    }
  }

  return jogo;
}

int eh_nome_errado(char nome[TAM_NOME]){
  int i=0, cont=0;

  for(i=0;i<TAM_NOME;i++){
    if(!nome[i]){
      cont=i;
      break;
    }
  }

  if(cont>=TAM_NOME){
    return 3;
  }
  if(cont<MIN_NOME){
    return 4;
  }

  if( !eh_letra(nome[0]) ){
    return 1;
  }

  for(i=1;i<TAM_NOME-1;i++){
    if( nome[i] == '\0'){
      break;
    }
    if( !eh_letra(nome[i]) && !eh_numero(nome[i]) ){
      return 2;
    }
  }

  return 0;
}

int eh_letra(char c){
  if( (c>='a' && c<='z') || (c>='A' && c<='Z') ){
    return 1;
  }
  return 0;
}

int eh_numero(char c){
  if(c>='0' && c<='9'){
    return 1;
  }
  return 0;
}

int jogar(tJogo jogo){
  int codigo=0, continuar=0;
  char entrada;
  char pal[TAM_PALAVRA];

  jogo.jogadorAtual = (rand()%jogo.qtdJogadores);
  do{
    jogo.idTema = (rand()%jogo.qtdPalavras);
    obtem_palavra(pal, jogo.palavras[jogo.idTema]);
    deixa_todas_letras_maiusculas(pal);
    while(1){
      while(1){
        limpa_tela();
        imprime_tela_jogo(jogo, codigo);
        scanf("\n");
        imprime_prefixo();
        scanf("%c", &entrada);
        if( !eh_letra(entrada) ){
          codigo=1;
          continue;
        }
        deixa_todas_letras_maiusculas(&entrada);
        if( palavra_tem_letra(jogo.letrasUsadas, entrada)){
          codigo=2;
          continue;
        }
        codigo=0;
        break;
      }
      adicionar_letra(jogo.letrasUsadas, entrada);

      if( palavra_tem_letra(pal, entrada) ){
        alterar_qtd_acertos(jogo.jogadores[jogo.jogadorAtual], 1);
      }
      else jogo.jogadores[jogo.jogadorAtual] = alterar_pontuacao(jogo.jogadores[jogo.jogadorAtual], -1);
      
      jogo = calcula_fim_de_jogo(jogo);
      if( eh_fim_de_jogo(jogo) ){//fim de jogo
        limpa_tela();
        imprime_tela_jogo(jogo, 3);
        break;
      }

      do{
        jogo.jogadorAtual = (jogo.jogadorAtual+1)%jogo.qtdJogadores;
      } while(!obtem_pontuacao_jogador(jogo.jogadores[jogo.jogadorAtual]));
    }
    if(jogar_novamente()){
      continuar=1;
      jogo = reinicializa_jogo(jogo, jogo.jogadorVencedor[0]);
    }
    else continuar=0;
    
  } while(continuar);

  return 0;
}

void imprime_tela_jogo(tJogo jogo, int codigo){
  int i=0, j=0, verif=0;
  char msg[64];
  char msgVencedor[50];
  char nomeVencedor[2][TAM_NOME];
  char nome[4][TAM_NOME];
  char molduraNomeCima[4][TAM_NOME];
  char molduraNomeBaixo[4][TAM_NOME];
  char pontuacao[4];
  char pts[4][4];
  char palavraEspacada[TAM_PALAVRA*2];
  char dica[TAM_PALAVRA+6];
  char letrasUsadas[54];
  char hangman[6] = "      ";
  char nomeJogadorAtual[14];
  char trofeu[8][16];

  obtem_dica(dica, jogo.palavras[jogo.idTema]);
  obtem_palavra(palavraEspacada, jogo.palavras[jogo.idTema]);
  obtem_nome_jogador(nomeJogadorAtual, jogo.jogadores[jogo.jogadorAtual]);

  deixa_primeira_letra_maiuscula(dica);
  for(i=TAM_PALAVRA-1;i>=0;i--){
    dica[i+6] = dica[i];
  }
  dica[0] = 'D';
  dica[1] = 'i';
  dica[2] = 'c';
  dica[3] = 'a';
  dica[4] = ':';
  dica[5] = ' ';
  centraliza_string(dica, TAM_PALAVRA+6);

  deixa_todas_letras_maiusculas(palavraEspacada);
  for(i=TAM_PALAVRA-1;i>=0;i--){
    palavraEspacada[(i*2)+1] = palavraEspacada[i];
    palavraEspacada[(i*2)] = ' ';
  }
  centraliza_string(palavraEspacada, TAM_PALAVRA*2);
  
  sprintf(letrasUsadas, "%s", jogo.letrasUsadas);
  for(i=26;i>=0;i--){
    letrasUsadas[(i*2)+1] = letrasUsadas[i];
    letrasUsadas[(i*2)] = ' ';
  }
  letrasUsadas[sizeof(letrasUsadas)-1] = '\0';

  for(i=0;i<jogo.qtdJogadores;i++){
    sprintf(molduraNomeCima[i], "----- %1d -----", i+1);
    sprintf(molduraNomeBaixo[i], "-------------");
  }
  sprintf(molduraNomeBaixo[jogo.jogadorAtual], "----- ^ -----");

  for(i=jogo.qtdJogadores;i<4;i++){
    molduraNomeCima[i][0] = '\0';
    molduraNomeBaixo[i][0] = '\0';
  }

  for(i=0;i<jogo.qtdJogadores;i++){
    obtem_nome_jogador(nome[i], jogo.jogadores[i]);
  }
  for(i=jogo.qtdJogadores;i<4;i++){
    nome[i][0] = '\0';
  }
  for(i=0;i<jogo.qtdJogadores;i++){
    centraliza_string(nome[i], sizeof(nome[i]));
  }

  for(i=jogo.qtdJogadores;i<4;i++){
    pontuacao[i] = ' ';
  }
  for(i=0;i<jogo.qtdJogadores;i++){
    pontuacao[i] = '0' + obtem_pontuacao_jogador(jogo.jogadores[i]);
  }
  for(i=jogo.qtdJogadores;i<4;i++){
    sprintf(pts[i], "   ");
  }
  for(i=0;i<jogo.qtdJogadores;i++){
    sprintf(pts[i], "pts");
  }

  //esconde a palavra
  for(i=0;i<sizeof(palavraEspacada);i++){
    verif=0;
    for(j=0;j<sizeof(letrasUsadas);j++){
      if(palavraEspacada[i] == letrasUsadas[j]){
        verif=1;
        break;
      }
    }
    if(!verif){
      palavraEspacada[i] = '_';
    }
  }

  switch(obtem_pontuacao_jogador(jogo.jogadores[jogo.jogadorAtual])){
    case 0:
      hangman[5] = '\\';

    case 1:
      hangman[4] = '/';

    case 2:
      hangman[3] = '\\';

    case 3:
      hangman[2] = '/';

    case 4:
      hangman[1] = '|';
      
    case 5:
      hangman[0] = 'O';
    break;
  }

  switch(jogo.qtdVencedores){
    case 0:
      sprintf(msgVencedor, "Voce perdeu!!!");
    break;

    case 1:
    if(jogo.qtdJogadores==1){
      sprintf(msgVencedor, "Voce venceu!!!");
    }
    else{
      obtem_nome_jogador(nomeVencedor[0], jogo.jogadores[jogo.jogadorVencedor[0]]);
      sprintf(msgVencedor, "Vencedor: %s!!!", nomeVencedor[0]);
    }
      
    break;

    case 2:
      obtem_nome_jogador(nomeVencedor[0], jogo.jogadores[jogo.jogadorVencedor[0]]);
      obtem_nome_jogador(nomeVencedor[1], jogo.jogadores[jogo.jogadorVencedor[1]]);
      sprintf(msgVencedor, "%s e %s empataram!!!", nomeVencedor[0], nomeVencedor[1]);
    break;

    default:
      msgVencedor[0] = '\0';
    break;
  }
  centraliza_string(msgVencedor, sizeof(msgVencedor));

  switch(jogo.qtdVencedores){//formatacao trofeu
    case 0:
      sprintf(trofeu[0], "               ");
      sprintf(trofeu[1], "               ");
      sprintf(trofeu[2], "               ");
      sprintf(trofeu[3], "    _______    ");
      sprintf(trofeu[4], "   (  (X)  )   ");
      sprintf(trofeu[5], "    \\_   _/    ");
      sprintf(trofeu[6], "     _| |_     ");
      sprintf(trofeu[7], "    /_____\\    ");
    break;

    case 1:
      sprintf(trofeu[0], "    _______    ");
      sprintf(trofeu[1], "   (  (1)  )   ");
      sprintf(trofeu[2], "    \\_   _/    ");
      sprintf(trofeu[3], "     _| |_     ");
      sprintf(trofeu[4], "    /_____\\    ");
      sprintf(trofeu[5], "      \\O/      ");
      sprintf(trofeu[6], "       |       ");
      sprintf(trofeu[7], "      / \\      ");
    break;

    case 2:
      sprintf(trofeu[0], "               ");
      sprintf(trofeu[1], "               ");
      sprintf(trofeu[2], "               ");
      sprintf(trofeu[3], "    _______    ");
      sprintf(trofeu[4], "   (  (1)  )   ");
      sprintf(trofeu[5], "\\O/ \\_   _/ \\O/");
      sprintf(trofeu[6], " |   _| |_   | ");
      sprintf(trofeu[7], "/ \\ /_____\\ / \\");
    break;

    default:
      sprintf(trofeu[0], "               ");
      sprintf(trofeu[1], "               ");
      sprintf(trofeu[2], "               ");
      sprintf(trofeu[3], "               ");
      sprintf(trofeu[4], "               ");
      sprintf(trofeu[5], "               ");
      sprintf(trofeu[6], "               ");
      sprintf(trofeu[7], "               ");
    break;
  }

  switch(codigo){
    case 0:
      sprintf(msg, "%s digite uma letra: ", nomeJogadorAtual);
    break;

    case 1:
      sprintf(msg, "Isso nao eh uma letra! %s digite uma letra: ", nomeJogadorAtual);
    break;

    case 2:
      sprintf(msg, "Essa letra ja foi usada! %s digite uma letra: ", nomeJogadorAtual);
    break;

    case 3:
      sprintf(msg, "JOGAR NOVAMENTE? (S/N): ");
    break;
  }

  imprime_margem_cima();
  printf(
  "\n"
  "    %13s    %13s    %13s    %13s\n"
  "    %13s    %13s    %13s    %13s\n"
  "    %13s    %13s    %13s    %13s\n"
  "        %c %3s            %c %3s            %c %3s            %c %3s    \n"
  "\n"
  "                          %20s\n"
  "\n"
  "            %49s\n"
  "       ________\n"
  "      | _______\n"
  "      ||/    |                                       %15s\n"
  "      ||     %c                                       %15s\n"
  "      ||    %c%c%c                                      %15s\n"
  "      ||    %c %c                                      %15s\n"
  "      ||                                             %15s\n"
  "     _||________                                     %15s\n"
  "    |           |_                                   %15s\n"
  "    |             |   %29s  %15s\n"
  "\n"
  "\n"
  "\n"
  "   Letras ja escolhidas:%s\n"
  "\n"
  "   %s\n"
  "\n",
  molduraNomeCima[0], molduraNomeCima[1], molduraNomeCima[2], molduraNomeCima[3],
  nome[0], nome[1], nome[2], nome[3],
  molduraNomeBaixo[0], molduraNomeBaixo[1], molduraNomeBaixo[2], molduraNomeBaixo[3],
  pontuacao[0], pts[0], pontuacao[1], pts[1], pontuacao[2], pts[2], pontuacao[3], pts[3], dica, msgVencedor,
  trofeu[0], hangman[0], trofeu[1], hangman[2], hangman[1], hangman[3],
  trofeu[2], hangman[4], hangman[5], trofeu[3], trofeu[4], trofeu[5], trofeu[6],
  palavraEspacada, trofeu[7], letrasUsadas, msg);
  imprime_margem_baixo();
}

void obtem_nome_jogador(char * copiaNome, tJogador jogador){
  sprintf(copiaNome, "%s", jogador.nome);
}

void centraliza_string(char * nome, int strSize){
  int i=0, tam=0;

  while(i<strSize){
    if(nome[i]=='\0'){
      tam = i;
      break;
    }
    i++;
  }
  int dif = strSize - tam;

  if(!dif){
    return;
  }
  
  for(i=tam;i>=0;i--){//desloca o nome para o meio da string
    nome[i+dif/2] = nome[i];
  }
  for(i=0;i<dif/2;i++){//preenche o inicio com espacos vazios
    nome[i] = ' ';
  }
  for(i=tam+dif/2;i<strSize;i++){//preenche o final com espacos vazios
    nome[i] = ' ';
  }
  nome[strSize-1] = '\0';
}

void deixa_primeira_letra_maiuscula(char * str){
  int i=0;
  for(i=0;i<999;i++){
    if(!str[i]){
      break;
    }
    if(eh_letra(str[i])){
      str[i] = deixa_letra_maiscula(str[i]);
      break;
    }
  }
}

void deixa_todas_letras_maiusculas(char * str){
  int i=0;
  for(i=0;i<999;i++){
    if(!str[i]){
      break;
    }
    str[i] = deixa_letra_maiscula(str[i]);
  }
}

char deixa_letra_maiscula(char letra){
  if( letra>='a' && letra<='z'){
    letra -= ' ';
  }
  return letra;
}

int palavra_tem_letra(char * palavra, char letra){
  int i=0, cont=0;
  for(i=0;i<999;i++){
    if(!palavra[i]){
      break;
    }
    if(palavra[i] == letra){
      cont++;
    }
  }
  return cont;
}

void adicionar_letra(char * str, char letra){
  int i=0;
  for(i=0;i<999;i++){
    if( !eh_letra(str[i]) ){
      str[i] = letra;
      str[i+1] = '\0';
      break;
    }
  }
}

tJogo calcula_fim_de_jogo(tJogo jogo){//-1 nao acabou 0- singleplayer perdeu 1- vitoria de um jogador ou todos os outros perderam 2- empate de dois jogadores
  int i=0, cont=0, idVencedor=0;
  
  if( jogo.qtdJogadores==1 ){//singleplayer
    if( !obtem_pontuacao_jogador(jogo.jogadores[0]) ){//singleplayer perdeu
      jogo.qtdVencedores=0;
    }
  }
  if( jogo.qtdJogadores>1 ){//multijogador
    for(i=0;i<jogo.qtdJogadores;i++){
      if( obtem_pontuacao_jogador(jogo.jogadores[i]) ){
        idVencedor = i;
        cont++;
      }
    }
    if(cont == 1){//todos menos um jogador perderam
      jogo.qtdVencedores=1;
      jogo.jogadorVencedor[0]=idVencedor;
    }
  }
  if( palavra_foi_descoberta(jogo) ){//palavra foi descoberta
    idVencedor=0;
    jogo.qtdVencedores=1;
    for(i=0;i<jogo.qtdJogadores;i++){//descobrir a maior pontuacao
      if(jogo.qtdJogadores==1){
        break;
      }
      if( obtem_pontuacao_jogador(jogo.jogadores[i]) > obtem_pontuacao_jogador(jogo.jogadores[idVencedor]) ){
        idVencedor = i;
      }
      else if( obtem_pontuacao_jogador(jogo.jogadores[i]) == obtem_pontuacao_jogador(jogo.jogadores[idVencedor]) ){
        if( obtem_qtd_acertos_jogador(jogo.jogadores[i]) > obtem_qtd_acertos_jogador(jogo.jogadores[idVencedor]) ){
          idVencedor = i;
        }
        else if( obtem_qtd_acertos_jogador(jogo.jogadores[i]) == obtem_qtd_acertos_jogador(jogo.jogadores[idVencedor]) ){
          if((!(jogo.jogadorVencedor>=0)) && (idVencedor!=i)){
            jogo.jogadorVencedor[1] = i;
            jogo.qtdVencedores = 2;
          }
        }
      }
    }
    jogo.jogadorVencedor[0] = idVencedor;
  }
  
  return jogo;
}

int palavra_foi_descoberta(tJogo jogo){
  int i=0, j=0, tam=0, qtd=0, cont=0;
  char pal[TAM_PALAVRA];
  obtem_palavra(pal, jogo.palavras[jogo.idTema]);
  deixa_todas_letras_maiusculas(pal);

  for(i=0;i<999;i++){
    if(!pal[i]){
      tam = i;
      break;
    }
  }
  for(i=0;i<999;i++){
    if(!jogo.letrasUsadas[i]){
      qtd = i;
      break;
    }
  }

  for(i=0;i<qtd;i++){
    for(j=0;j<tam;j++){
      if(pal[j] == jogo.letrasUsadas[i]){
        cont++;
      }
    }
  }

  if(cont == tam){
    return 1;
  }
  return 0;
}

int eh_fim_de_jogo(tJogo jogo){
  switch(jogo.qtdVencedores){
    case 0:
    return 1;
    break;

    case 1:
    return 1;
    break;

    case 2:
    return 1;
    break;

    default:
    return 0;
    break;
  }
}

tJogo reinicializa_jogo(tJogo jogo, int jogadorInicial){
  int i=0;

  jogo.jogadorVencedor[0] = 0;
  jogo.jogadorVencedor[1] = -1;
  jogo.qtdVencedores = -1;
  if(!jogadorInicial){
    jogo.jogadorAtual = rand()%jogo.qtdJogadores;
  }
  else jogo.jogadorAtual = jogadorInicial;
  
  for(i=0;i<jogo.qtdJogadores;i++){
    jogo.jogadores[i] = reiniciar_pontuacao(jogo.jogadores[i]);
    jogo.jogadores[i] = reiniciar_qtd_acertos(jogo.jogadores[i]);
  }
  for(i=0;i<27;i++){
    jogo.letrasUsadas[i] = '\0';
  }
  return jogo;
}

int jogar_novamente(){
  char opcao;
  int erro=0;
  
  do{
    scanf("%*[\n]");
    scanf("%c", &opcao);
    if(opcao=='S'||opcao=='s'||opcao=='N'||opcao=='n'){
      erro=0;
    }
    else erro=1;
  } while(erro);

  if(opcao=='S'||opcao=='s'){
    return 1;
  }
  return 0;
}