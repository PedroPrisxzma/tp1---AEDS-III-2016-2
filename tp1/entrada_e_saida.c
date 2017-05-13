#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada_e_saida.h"
#include "read.h"
#include "ordenaext.h"

/////////////////////////////////////////////////////////////
/* Protótipo:void LeEntradaTxt(char *t, char *indicador)   //
// Função: Tem como função Ler o titulo e o indicador de   //
//         disponibilidade do livro e preencher o arquivo  //
//         para ordenar                                    //
// Entrada: Dois pointeiros para char, um contendo a       //
//          string do título e outro a indicadora          //
// Saída: Não há, função do tipo void                      */
/////////////////////////////////////////////////////////////

void LeEntradaTxt(FILE *A, char *t, char *indicador){
  int i;
  if(!scanf("%s %s", t, indicador)){
    printf("Erro ao ler título e/ou indicador do livro\n");
  }
  fwrite(t, 51*sizeof(char), 1, A);
  for(i = 0;i < 52;i++){
    t[i] = 0;
  }
  fwrite(" ", sizeof(char), 1, A);
  fwrite(indicador, sizeof(char), 1, A);
  fwrite("\n", sizeof(char), 1, A);
}

/////////////////////////////////////////////////////////////////////
/* Protótipo:void LeEntrada(int *n, int *m, int *e, int *l, int *k)//
// Função: Tem como função Ler os cinco inteiros iniciais da       //
//         entrada do programa                                     //
// Entrada: Cinco ponteiros para inteiro, um para cada             //
//          argumento da primeira entrada                          //
// Saída: Não há, função do tipo void                              */
/////////////////////////////////////////////////////////////////////

int LeEntrada(int *n, int *m, int *e, int *l, int *k){
  if(scanf("%d %d %d %d %d", n, m, e, l, k)){
    return 1;
  }
  else
    printf("Erro na primeira entrada do programa\n");
    return 0;
}

/////////////////////////////////////////////////////////////
/* Protótipo:void converteBinParaTxt(FILE *B, int n)       //
// Função: Tem como função convertar o arquivo binario     //
//        para texto.                                      //
// Entrada: Um arquivo, o arquivo binário e um inteiro, o  //
//          número de liivros contidos no arquivo          //
// Saída: Não há, função do tipo void                      */
/////////////////////////////////////////////////////////////


void converteBinParaTxt(FILE *B, int n){
  FILE *T;
  if((T = fopen("livro_ordenados", "w")) == NULL){
    printf("Erro ao abrir arquivo txt");
    return;
  }
  Livro *aux = AlocaBuffer(1);
  int i;
  for(i = 0;i < n;i++){
    fseek(B, i*54*sizeof(char), SEEK_SET);
    fread(aux[0].title, sizeof(char)*52, 1, B);
    fread(&aux[0].disponivel, sizeof(char), 1, B);
    fprintf(T, "%s %c\n", aux[0].title, aux[0].disponivel);
  }
  free(aux);
  fclose(T);
}

///////////////////////////////////////////////////////////////////////////////////////////
/* Protótipo:void fazEstantes_E_indice(FILE **ESTANTES, FILE *Bin, int n, int e, int l ) //
// Função: Tem como função preencher as estantes e montar o indice                       //
// Entrada: Um array/ponteiro para arquivos, as estantes, o arquivo binário e três       //
//          inteiros, o número total de livros, o de estantes e o de livros por estante  //                                   //
// Saída: Não há, função do tipo void                                                    */
///////////////////////////////////////////////////////////////////////////////////////////

void fazEstantes_E_indice(FILE **ESTANTES, FILE *Bin, int n, int e, int l){
  int i, j, h, h2;//Auxiliares
  j = 0;//Auxiliar para checar limite de livros na estante
  h = 0;//Auxiliar para checar em qual estante estamos
  h2 = -1;//Marca a estante anterior
  FILE *I = fopen("indice", "w");
  Livro *aux = AlocaBuffer(1);

  for(i = 0;i < n;i++){//Preenche todos os livros em estantes
    fseek(Bin, i*54*sizeof(char), SEEK_SET);
    fread(aux[0].title, sizeof(char)*52, 1, Bin);
    fread(&aux[0].disponivel, sizeof(char), 1, Bin);
    fwrite(aux[0].title, 51*sizeof(char), 1, ESTANTES[h]);
    fwrite(" ", sizeof(char), 1, ESTANTES[h]);
    fwrite(&aux[0].disponivel, sizeof(char), 1, ESTANTES[h]);
    fwrite("\n", sizeof(char), 1, ESTANTES[h]);

    if(h != h2){//Indica começo de uma nova estante
      fprintf(I, "%s ", aux[0].title); // Marca primeira palavra de uma estante no indice
      h2++;
    }
    if(j == (l-1) || i == (n-1)){// Marca última palavra de uma estante no indice
      fprintf(I, "%s\n", aux[0].title);
      j = -1;//Faz ser -1 devido ao j++ no final do while, correção, caso contrário pularia um titulo
      h++;
    }
    j++;
  }

  for(i = h;i < e;i++){//Marca estantes vazias no indice
    fprintf(I, "#\n");
  }

  fclose(I);
  free(aux);
}
