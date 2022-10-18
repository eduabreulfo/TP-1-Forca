#ifndef _TPALAVRA_C_
#define _TPALAVRA_C_

#include "tPalavra.h"

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

#endif