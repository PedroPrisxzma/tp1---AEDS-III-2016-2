#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "ordenaext.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Protótipo:void ReadLeft(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir)//
// Função: Tem como função ler da "esquerda" do arquivo, realizar as devidadas comparações com o pivo e então escrever no local        //
//          o valor lido, é uma função auxiliar a do quicksort externo                                                                 //
// Entrada: Um arquivo, o arquivo binário a se ordenar, dois ponteiros para struct, contendo o buffer e um auxiliar  e um inteiro,     //
//          o limite de memória que pode ser usado e seis ponteiros para inteiro, contendo os limites de esquerda e direita do arquivo,//
//          início e fim da atual chamada, os indices de escrita e leitura da direita e esquerda                                       //
// Saída: Não há, função do tipo void                                                                                                  */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadLeft(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir){
  fseek(A, resq[0]*sizeof(char)*54, SEEK_SET);
  fread(compare[0].title, sizeof(char)*52, 1, A);
  fread(&compare[0].disponivel, sizeof(char), 1, A);

  if(strcmp(compare[0].title, buffer[0].title) <= 0){//antes do pivo
    fseek(A, wesq[0]*sizeof(char)*54, SEEK_SET);
    fwrite(compare[0].title, sizeof(char)*51, 1, A);
    fwrite(" ", sizeof(char), 1, A);
    fwrite(&compare[0].disponivel, sizeof(char), 1, A);
    fwrite("\n", sizeof(char), 1, A);

    resq[0]++;
    wesq[0]++;
  }
  else if((strcmp(compare[0].title, buffer[0].title) > 0) && (strcmp(compare[0].title, buffer[m-2].title) < 0)){//Colaca valor no buffer pivo e reordena ele
    if((resq[0] - esq) <= (dir - rdir[0])){
      fseek(A, wdir[0]*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[m-2].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[m-2].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
      buffer[m-2] = compare[0];

      qsort(buffer, m-1, sizeof(Livro), compara);

      resq[0]++;
      wdir[0]--;
    }
    else if((resq[0] - esq) > (dir - rdir[0])){
      fseek(A, wesq[0]*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[0].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[0].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
      buffer[0] = compare[0];

      qsort(buffer, m-1, sizeof(Livro), compara);

      resq[0]++;
      wesq[0]++;
    }
  }

  else if(strcmp(compare[0].title, buffer[m-2].title) >= 0){//dps do pivo
    fseek(A, wdir[0]*sizeof(char)*54, SEEK_SET);
    fwrite(compare[0].title, sizeof(char)*51, 1, A);
    fwrite(" ", sizeof(char), 1, A);
    fwrite(&compare[0].disponivel, sizeof(char), 1, A);
    fwrite("\n", sizeof(char), 1, A);
    resq[0]++;
    wdir[0]--;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Protótipo:void ReadRight(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir)//
// Função: Tem como função ler da "direita" do arquivo, realizar as devidadas comparações com o pivo e então escrever no local          //
//          o valor lido, é uma função auxiliar a do quicksort externo                                                                  //
// Entrada: Um arquivo, o arquivo binário a se ordenar, dois ponteiros para struct, contendo o buffer e um auxiliar  e um inteiro,      //
//          o limite de memória que pode ser usado e seis ponteiros para inteiro, contendo os limites de esquerda e direita do arquivo, //
//          início e fim da atual chamada, os indices de escrita e leitura da direita e esquerda                                        //
// Saída: Não há, função do tipo void                                                                                                   */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReadRight(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir){
  fseek(A, rdir[0]*sizeof(char)*54, SEEK_SET);
  fread(compare[0].title, sizeof(char)*52, 1, A);
  fread(&compare[0].disponivel, sizeof(char), 1, A);

  if(strcmp(compare[0].title, buffer[0].title) <= 0){//antes do pivo
    fseek(A, wesq[0]*sizeof(char)*54, SEEK_SET);
    fwrite(compare[0].title, sizeof(char)*51, 1, A);
    fwrite(" ", sizeof(char), 1, A);
    fwrite(&compare[0].disponivel, sizeof(char), 1, A);
    fwrite("\n", sizeof(char), 1, A);

    rdir[0]--;
    wesq[0]++;
  }
  else if((strcmp(compare[0].title, buffer[0].title) > 0) && (strcmp(compare[0].title, buffer[m-2].title) < 0)){//Colaca valor no buffer pivo e reordena ele
    if((resq[0] - esq) <= (dir - rdir[0])){
      fseek(A, wdir[0]*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[m-2].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[m-2].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
      buffer[m-2] = compare[0];

      qsort(buffer, m-1, sizeof(Livro), compara);

      rdir[0]--;
      wdir[0]--;
    }
    else if((resq[0] - esq) > (dir - rdir[0])){
      fseek(A, wesq[0]*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[0].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[0].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
      buffer[0] = compare[0];

      qsort(buffer, m-1, sizeof(Livro), compara);

      rdir[0]--;
      wesq[0]++;
    }
  }

  else if(strcmp(compare[0].title, buffer[m-2].title) >= 0){//dps do pivo
    fseek(A, wdir[0]*sizeof(char)*54, SEEK_SET);
    fwrite(compare[0].title, sizeof(char)*51, 1, A);
    fwrite(" ", sizeof(char), 1, A);
    fwrite(&compare[0].disponivel, sizeof(char), 1, A);
    fwrite("\n", sizeof(char), 1, A);

    rdir[0]--;
    wdir[0]--;
  }
}
