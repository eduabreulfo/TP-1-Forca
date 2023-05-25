#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/common.h"


#if defined _WIN32
    //#define OS 'w'
    #define CLEAR "cls"

#else
    //#define OS 'l'
    #define CLEAR "clear"
#endif


void limpa_tela(){
  system(CLEAR);
}

void imprime_prefixo(){
  printf("> ");
}
