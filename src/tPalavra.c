#ifndef _TPALAVRA_C_
#define _TPALAVRA_C_

#include <stdio.h>
#include <stdlib.h>
#include "../headers/tPalavra.h"

#define ID_DICA 0
#define ID_PALAVRA 1

int ContaPalavras(FILE *arq){
  int qtd=0;
  char letra;

  while(1){
    if(feof(arq)){
      qtd++;
      break;
    }
  }

  return qtd;
}

void LePalavras(FILE *arq, tPalavra * palavras, int qtd){
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

}

void ObtemDica(char * copiaNome, tPalavra palavra){
  sprintf(copiaNome, "%s", palavra.palavra[ID_DICA]);
}

void ObtemPalavra(char * copiaNome, tPalavra palavra){
  sprintf(copiaNome, "%s", palavra.palavra[ID_PALAVRA]);
}

#endif