#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//tPalavra
#define NOME_ARQUIVO_PALAVRAS "palavras.csv"
#define ID_DICA 0
#define ID_PALAVRA 1
#define QTD_MAX_PALAVRAS 100
#define TAM_PALAVRA 15
typedef struct{
  char palavra[2][TAM_PALAVRA];
  int tamanho;
} tPalavra;
void LePalavras(tPalavra * palavras, int qtd);
int ContaPalavras();
void ObtemDica(char * copiaNome, tPalavra palavra);
void ObtemPalavra(char * copiaNome, tPalavra palavra);

//tJogador
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

//tPlacar
/*
typedef struct{
  tJogador vencedores[100]; //top 100
} tPlacar;
tPlacar OrganizaPlacar(tPlacar placar);
*/

//tJogo
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
int Jogar(tJogo jogo);
tJogo MenuPrincipal(tJogo jogo);
void ImprimeTelaMenuPrincipal();
void ImprimeMargemCima();
void ImprimeMargemBaixo();
tJogo MenuOpcoes(tJogo jogo);
tJogo EscolherNomes(tJogo jogo);
tJogo InicializaJogo(tJogo jogo);
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

int main(void){
  tJogo jogo;
  srand(time(NULL));

  jogo = InicializaJogo(jogo); //inicializacao dos temas
  jogo = MenuPrincipal(jogo); //tela inicial
  jogo = EscolherNomes(jogo); //escolha dos nomes
  Jogar(jogo); //partida
  
  return 0;
}

/*
      _____       _      _       _ _                          
     |_   _|     (_)    (_)     | (_)                         
       | |  _ __  _  ___ _  __ _| |_ ______ _  ___ __ _  ___  
       | | | '_ \| |/ __| |/ _' | | |_  / _' |/ __/ _' |/ _ \ 
      _| |_| | | | | (__| | (_| | | |/ / (_| | (_| (_| | (_) |
     |_____|_| |_|_|\___|_|\__,_|_|_/___\__,_|\___\__,_|\___/ 
                                                              
*/

tJogo InicializaJogo(tJogo jogo){
  int i=0;

  jogo.qtdPalavras = ContaPalavras();
  LePalavras(jogo.palavras, jogo.qtdPalavras);
  jogo.jogadorVencedor[0] = 0;
  jogo.jogadorVencedor[1] = -1;
  jogo.qtdVencedores = -1;

  for(i=0;i<27;i++){
    jogo.letrasUsadas[i] = '\0';
  }

  return jogo;
}

int ContaPalavras(){
  FILE * arq = fopen(NOME_ARQUIVO_PALAVRAS, "r");
  int qtd=1;
  char letra;

  while(fscanf(arq, "%c", &letra)==1){
    if(letra=='\n'){
      qtd++;
    }
  }
  fclose(arq);
  return qtd;
}

void LePalavras(tPalavra * palavras, int qtd){
  FILE * arq = fopen(NOME_ARQUIVO_PALAVRAS, "r");
  char letra;
  int i=0, q=0;

  for(i=0;i<qtd;i++){

    while(fscanf(arq, "%c", &letra) == 1){
      if(letra == ','){
        break;
      }
      palavras[i].palavra[ID_DICA][q] = letra;
      q++;
    }
    palavras[i].palavra[ID_DICA][q] = '\0';
    q=0;

    while(fscanf(arq, "%c", &letra) == 1){
      if(letra == '\n'){
        break;
      }
      palavras[i].palavra[ID_PALAVRA][q] = letra;
      q++;
    }
    palavras[i].tamanho = q;
    palavras[i].palavra[ID_PALAVRA][q] = '\0';
    q=0;
  }

  fclose(arq);
}

/*
      __  __                    _____      _            _             _ 
     |  \/  |                  |  __ \    (_)          (_)           | |
     | \  / | ___ _ __  _   _  | |__) | __ _ _ __   ___ _ _ __   __ _| |
     | |\/| |/ _ \ '_ \| | | | |  ___/ '__| | '_ \ / __| | '_ \ / _` | |
     | |  | |  __/ | | | |_| | | |   | |  | | | | | (__| | |_) | (_| | |
     |_|  |_|\___|_| |_|\__,_| |_|   |_|  |_|_| |_|\___|_| .__/ \__,_|_|
                                                         | |            
                                                         |_|            
*/

tJogo MenuPrincipal(tJogo jogo){
  int i=0;
  char opcao='a';

  system("cls");
  ImprimeTelaMenuPrincipal(0); //padrao
  while(1){
    opcao='a';
    scanf("%c", &opcao);
    if(opcao == '0'){
      system("cls");
      ImprimeTelaMenuPrincipal(-1); //sair do jogo
      scanf("%c", &opcao);
      if(opcao == '0'){
        exit(0);
      }
    }
    if(opcao>='1' && opcao<='4'){
      jogo.qtdJogadores = opcao-'0';
      for(i=0;i<jogo.qtdJogadores;i++){
        jogo.jogadores[i] = AlterarID(jogo.jogadores[i], i+1);
        jogo.jogadores[i] = ReiniciarPontuacao(jogo.jogadores[i]);
        jogo.jogadores[i] = ReiniciarQtdAcertos(jogo.jogadores[i]);
      }
      break;
    }
    system("cls");
    ImprimeTelaMenuPrincipal(1); //entrada invalida
  }
  
  return jogo;
}

void ImprimeTelaMenuPrincipal(int erro){
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
  ImprimeMargemCima();
  printf("\n"
  "           _________________      |        |\n"
  "          |                 |   ._|()(|() (|(|\n"
  "          |     ____________|        _|\n"
  "          |    |     (>>>>)    ___ ____    _______   __________\n"
  "          |    |__   (>>>>)   |   |    |  /       | /   ____   \\\n"
  "          |       |  (>>>>)   |     ,__| /     ___| |__|    |  |\n"
  "          |     __| / /^^\\/\\  |    /     |    |      _______|  |\n"
  "          |    |   ( (    )/) |    |     |    |     /   ____   |\n"
  "          |    |   | |    |/| |    |     |    |___  |  |    |  |\n"
  "          |    |   \\ \\____/// |    |     \\        | |  \\____/  |\n"
  "          |____|    \\_____,/  |____|      \\_______| \\_______,__|\n"
  "                                 __               _\n"
  "                                |_  |       |    /_||    _\n"
  "                         |)()|' |__(|(/(||'(|() /  ||)|'(-(/\n"
  "                         |\n"
  "\n"
  "                           %s\n"
  "                       +-------------------------+\n"
  "                       |  1- Solo (Treinamento)  |\n"
  "                       |  2- 2 jogadores         |\n"
  "                       |  3- 3 jogadores         |\n"
  "                       |  4- 4 jogadores         |\n"
  "                       |  0- Sair do Jogo        |                v1.0\n"
  "                       +-------------------------+                2022\n"
  "\n", msg);
  ImprimeMargemBaixo();
}

void ImprimeMargemCima(){
  printf("========================================================================\n");
}

void ImprimeMargemBaixo(){
  printf("========================================================================\n");
}

/*
      ______               _ _                 _        _   _                           
     |  ____|             | | |               | |      | \ | |                          
     | |__   ___  ___ ___ | | |__   __ _    __| | ___  |  \| | ___  _ __ ___   ___  ___ 
     |  __| / __|/ __/ _ \| | '_ \ / _' |  / _` |/ _ \ | . ' |/ _ \| '_ ' _ \ / _ \/ __|
     | |____\__ \ (_| (_) | | | | | (_| | | (_| |  __/ | |\  | (_) | | | | | |  __/\__ \
     |______|___/\___\___/|_|_| |_|\__,_|  \__,_|\___| |_| \_|\___/|_| |_| |_|\___||___/

*/

tJogo EscolherNomes(tJogo jogo){
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

    system("cls");
    ImprimeMargemCima();
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
    ImprimeMargemBaixo();
    
    seta[i][0][0] = '\0';
    seta[i][1][0] = '\0';
    seta[i][2][0] = '\0';

    msgErro[0] = '\0';
    scanf("%49s", &entrada);
    deuErro = EhNomeErrado(entrada);
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
      sprintf(jog[i], entrada);
      jogo.jogadores[i] = MudarNome(jogo.jogadores[i], entrada);
      CentralizaString(jog[i], sizeof(jog[i]));
      break;
    }
  }

  return jogo;
}

int EhNomeErrado(char nome[TAM_NOME]){
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

  if( !EhLetra(nome[0]) ){
    return 1;
  }

  for(i=1;i<TAM_NOME-1;i++){
    if( nome[i] == '\0'){
      break;
    }
    if( !EhLetra(nome[i]) && !EhNumero(nome[i]) ){
      return 2;
    }
  }

  return 0;
}

int EhLetra(char c){
  if( (c>='a' && c<='z') || (c>='A' && c<='Z') ){
    return 1;
  }
  return 0;
}

int EhNumero(char c){
  if(c>='0' && c<='9'){
    return 1;
  }
  return 0;
}

tJogador MudarNome(tJogador jogador, char nome[TAM_NOME]){
  sprintf(jogador.nome, nome);
  return jogador;
}

tJogador AlterarID(tJogador jogador, int id){
  jogador.id = id;
  return jogador;
}

/*
           _                        
          | |
          | | ___   __ _  __ _ _ __
      _   | |/ _ \ / _` |/ _` | '__|
     | |__| | (_) | (_| | (_| | |
      \____/ \___/ \__, |\__,_|_|
                    __/ |
                   |___/
*/

int Jogar(tJogo jogo){
  int i=0, codigo=0, continuar=0;
  char entrada;
  char pal[TAM_PALAVRA];

  jogo.jogadorAtual = (rand()%jogo.qtdJogadores);
  do{
    jogo.idTema = (rand()%jogo.qtdPalavras);
    ObtemPalavra(pal, jogo.palavras[jogo.idTema]);
    DeixaTodasLetrasMaiusculas(pal);
    while(1){
      while(1){
        system("cls");
        ImprimeTelaJogo(jogo, codigo);
        scanf("\n");
        scanf("%c", &entrada);
        if( !EhLetra(entrada) ){
          codigo=1;
          continue;
        }
        DeixaTodasLetrasMaiusculas(&entrada);
        if( PalavraTemLetra(jogo.letrasUsadas, entrada)){
          codigo=2;
          continue;
        }
        codigo=0;
        break;
      }
      AdicionarLetra(jogo.letrasUsadas, entrada);

      if( PalavraTemLetra(pal, entrada) ){
        AlterarQtdAcertos(jogo.jogadores[jogo.jogadorAtual], 1);
      }
      else jogo.jogadores[jogo.jogadorAtual] = AlterarPontuacao(jogo.jogadores[jogo.jogadorAtual], -1);
      
      jogo = CalculaFimDeJogo(jogo);
      if( EhFimDeJogo(jogo) ){//fim de jogo
        system("cls");
        ImprimeTelaJogo(jogo, 3);
        break;
      }

      do{
        jogo.jogadorAtual = (jogo.jogadorAtual+1)%jogo.qtdJogadores;
      } while(!ObtemPontuacaoJogador(jogo.jogadores[jogo.jogadorAtual]));
    }
    if(JogarNovamente()){
      continuar=1;
      jogo = ReinicializaJogo(jogo, jogo.jogadorVencedor[0]);
    }
    else continuar=0;
    
  } while(continuar);

  return 0;
}

void ImprimeTelaJogo(tJogo jogo, int codigo){
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

  ObtemDica(dica, jogo.palavras[jogo.idTema]);
  ObtemPalavra(palavraEspacada, jogo.palavras[jogo.idTema]);
  ObtemNomeJogador(nomeJogadorAtual, jogo.jogadores[jogo.jogadorAtual]);

  DeixaPrimeiraLetraMaiuscula(dica);
  for(i=TAM_PALAVRA-1;i>=0;i--){
    dica[i+6] = dica[i];
  }
  dica[0] = 'D';
  dica[1] = 'i';
  dica[2] = 'c';
  dica[3] = 'a';
  dica[4] = ':';
  dica[5] = ' ';
  CentralizaString(dica, TAM_PALAVRA+6);

  DeixaTodasLetrasMaiusculas(palavraEspacada);
  for(i=TAM_PALAVRA-1;i>=0;i--){
    palavraEspacada[(i*2)+1] = palavraEspacada[i];
    palavraEspacada[(i*2)] = ' ';
  }
  CentralizaString(palavraEspacada, TAM_PALAVRA*2);
  
  sprintf(letrasUsadas, jogo.letrasUsadas);
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
    ObtemNomeJogador(nome[i], jogo.jogadores[i]);
  }
  for(i=jogo.qtdJogadores;i<4;i++){
    nome[i][0] = '\0';
  }
  for(i=0;i<jogo.qtdJogadores;i++){
    CentralizaString(nome[i], sizeof(nome[i]));
  }

  for(i=jogo.qtdJogadores;i<4;i++){
    pontuacao[i] = ' ';
  }
  for(i=0;i<jogo.qtdJogadores;i++){
    pontuacao[i] = '0' + ObtemPontuacaoJogador(jogo.jogadores[i]);
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

  switch(ObtemPontuacaoJogador(jogo.jogadores[jogo.jogadorAtual])){
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
      ObtemNomeJogador(nomeVencedor[0], jogo.jogadores[jogo.jogadorVencedor[0]]);
      sprintf(msgVencedor, "Vencedor: %s!!!", nomeVencedor[0]);
    }
      
    break;

    case 2:
      ObtemNomeJogador(nomeVencedor[0], jogo.jogadores[jogo.jogadorVencedor[0]]);
      ObtemNomeJogador(nomeVencedor[1], jogo.jogadores[jogo.jogadorVencedor[1]]);
      sprintf(msgVencedor, "%s e %s empataram!!!", nomeVencedor[0], nomeVencedor[1]);
    break;

    default:
      msgVencedor[0] = '\0';
    break;
  }
  CentralizaString(msgVencedor, sizeof(msgVencedor));

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

  ImprimeMargemCima();
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
  ImprimeMargemBaixo();
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

void ObtemNomeJogador(char * copiaNome, tJogador jogador){
  sprintf(copiaNome, jogador.nome);
}

void CentralizaString(char * nome, int strSize){
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

void ObtemDica(char * copiaNome, tPalavra palavra){
  sprintf(copiaNome, palavra.palavra[ID_DICA]);
}
void ObtemPalavra(char * copiaNome, tPalavra palavra){
  sprintf(copiaNome, palavra.palavra[ID_PALAVRA]);
}

void DeixaPrimeiraLetraMaiuscula(char * str){
  int i=0;
  for(i=0;i<999;i++){
    if(!str[i]){
      break;
    }
    if(EhLetra(str[i])){
      str[i] = DeixaLetraMaiscula(str[i]);
      break;
    }
  }
}
void DeixaTodasLetrasMaiusculas(char * str){
  int i=0;
  for(i=0;i<999;i++){
    if(!str[i]){
      break;
    }
    str[i] = DeixaLetraMaiscula(str[i]);
  }
}

char DeixaLetraMaiscula(char letra){
  if( letra>='a' && letra<='z'){
    letra -= ' ';
  }
  return letra;
}

int PalavraTemLetra(char * palavra, char letra){
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

void AdicionarLetra(char * str, char letra){
  int i=0;
  for(i=0;i<999;i++){
    if( !EhLetra(str[i]) ){
      str[i] = letra;
      str[i+1] = '\0';
      break;
    }
  }
}

tJogo CalculaFimDeJogo(tJogo jogo){//-1 nao acabou 0- singleplayer perdeu 1- vitoria de um jogador ou todos os outros perderam 2- empate de dois jogadores
  int i=0, cont=0, idVencedor=0;
  
  if( jogo.qtdJogadores==1 ){//singleplayer
    if( !ObtemPontuacaoJogador(jogo.jogadores[0]) ){//singleplayer perdeu
      jogo.qtdVencedores=0;
    }
  }
  if( jogo.qtdJogadores>1 ){//multijogador
    for(i=0;i<jogo.qtdJogadores;i++){
      if( ObtemPontuacaoJogador(jogo.jogadores[i]) ){
        idVencedor = i;
        cont++;
      }
    }
    if(cont == 1){//todos menos um jogador perderam
      jogo.qtdVencedores=1;
      jogo.jogadorVencedor[0]=idVencedor;
    }
  }
  if( PalavraFoiDescoberta(jogo) ){//palavra foi descoberta
    idVencedor=0;
    jogo.qtdVencedores=1;
    for(i=0;i<jogo.qtdJogadores;i++){//descobrir a maior pontuacao
      if(jogo.qtdJogadores==1){
        break;
      }
      if( ObtemPontuacaoJogador(jogo.jogadores[i]) > ObtemPontuacaoJogador(jogo.jogadores[idVencedor]) ){
        idVencedor = i;
      }
      else if( ObtemPontuacaoJogador(jogo.jogadores[i]) == ObtemPontuacaoJogador(jogo.jogadores[idVencedor]) ){
        if( ObtemQtdAcertosJogador(jogo.jogadores[i]) > ObtemQtdAcertosJogador(jogo.jogadores[idVencedor]) ){
          idVencedor = i;
        }
        else if( ObtemQtdAcertosJogador(jogo.jogadores[i]) == ObtemQtdAcertosJogador(jogo.jogadores[idVencedor]) ){
          if(!jogo.jogadorVencedor>=0 && idVencedor!=i){
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

int PalavraFoiDescoberta(tJogo jogo){
  int i=0, j=0, tam=0, qtd=0, cont=0;
  char pal[TAM_PALAVRA];
  ObtemPalavra(pal, jogo.palavras[jogo.idTema]);
  DeixaTodasLetrasMaiusculas(pal);

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

int EhFimDeJogo(tJogo jogo){
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

tJogo ReinicializaJogo(tJogo jogo, int jogadorInicial){
  int i=0;

  jogo.jogadorVencedor[0] = 0;
  jogo.jogadorVencedor[1] = -1;
  jogo.qtdVencedores = -1;
  if(!jogadorInicial){
    jogo.jogadorAtual = rand()%jogo.qtdJogadores;
  }
  else jogo.jogadorAtual = jogadorInicial;
  
  for(i=0;i<jogo.qtdJogadores;i++){
    jogo.jogadores[i] = ReiniciarPontuacao(jogo.jogadores[i]);
    jogo.jogadores[i] = ReiniciarQtdAcertos(jogo.jogadores[i]);
  }
  for(i=0;i<27;i++){
    jogo.letrasUsadas[i] = '\0';
  }
  return jogo;
}

int JogarNovamente(){
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

//Eduardo Abreu (2020102136)
//27-12-2021
//UFES - Goiabeiras
//Docete Omnes Gentes

/*
########################################################################################
########################################################################################
########################################################################################
                      #######  #######     #     #######  #######
                    ##########   ######   ###   ######   ##########
                  ###  ##   ###     ####  ###  ####     ###   ##  ###
                ####  ##     ##       ###  #  ###       ##     ##  ####
     #         ####  ##      ##        ###   ###        ##      ##  ####          #
    #         ####  ##    #  ##      ## ##   ## ##      ##  #    ##  ####          #
    #       ##### ###    ######     ######   ######     ######    ### #####        #
    ##    ###### ##### # #####      #####  #  #####      ##### # ##### ######     ##
     ##########  ######   ###        ###  ###  ###        ###   ######  ###########
      ##### ##     # ##                  ## ##                  ## #     ## #####
       ###  ##                         #### ####                         ##  ###
                                      #### # ####
                                       ## ### ##
                                          ###
                                           #
*/