#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "ordenaext.h"

//////////////////////////////////////////////////////////////////////
/* Protótipo:void quicksortExtMain(FILE *A, int m, int esq, int dir)//
// Função: Tem como função organizar a primeira chamada do quicksort//
//          externo                                                 //
// Entrada: Um arquivo, o arquivo binário a se ordenar e            //
//          três inteiros, o limite de memória que pode ser usado   //
//          e os limites de esquerda e direita do arquivo, início e //
//          fim                                                     //
// Saída: Não há, função do tipo void                               */
//////////////////////////////////////////////////////////////////////

void quicksortExtMain(FILE *A, int m, int esq, int dir){
  Livro *buffer = AlocaBuffer(m-1);//buffer do quicksort externo
  Livro *compare = AlocaBuffer(1);
  quicksortExt(A, buffer, compare, m, esq, dir);
  free(compare);
  free(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/* Protótipo:void quicksortExt(FILE *A, Livro *buffer, Livro *compare, int m, int esq, int dir)//
// Função: Tem como função realizar a ordenação externa                                        //
// Entrada: Um arquivo, o arquivo binário a se ordenar, dois ponteiros para struct, contendo   //
//          o buffer e um auxiliar  e três inteiros, o limite de memória que pode ser usado    //
//          e os limites de esquerda e direita do arquivo, início e fim da atual chamada       //
// Saída: Não há, função do tipo void                                                          */
/////////////////////////////////////////////////////////////////////////////////////////////////

void quicksortExt(FILE *A, Livro *buffer, Livro *compare, int m, int esq, int dir){
  int i; //auxiliar
  int j = 0;//auxiliar pra ver se o buffer foi enchido
  int marcador;//Marcador pare escrever o buffer no arquivo
  int resq = esq;//leitura esquerda
  int rdir = dir-1;//leitura direita
  int wesq = esq;//escrita esquerda
  int wdir = dir-1;//escrita direita



//////////Casos buffer > m//////////////////////

  if((dir - esq) <= 1){
    return;
  }

  else if(m > (dir-esq)){//cabe tudo no bufer
    for(i = 0;i < (dir-esq);i++){
      resq = i+esq;
      fseek(A, resq*sizeof(char)*54, SEEK_SET);
      fread(buffer[i].title, sizeof(char)*52, 1, A);
      fread(&buffer[i].disponivel, sizeof(char), 1, A);
    }

    qsort(buffer, (dir-esq), sizeof(Livro), compara);

    for(i = 0;i < (dir-esq);i++){
      wesq = i+esq;
      fseek(A, wesq*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[i].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[i].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
    }
  }

////////Casos de buffer < m///////////////
  else if(m <= (dir-esq)){
    while(j < (m-1)){//não cabe tudo no buffer
        fseek(A, resq*sizeof(char)*54, SEEK_SET);
        fread(buffer[j].title, sizeof(char)*52, 1, A);
        fread(&buffer[j].disponivel, sizeof(char), 1, A);
        resq++;
        j++;
      if(j < (m-1)){
        fseek(A, rdir*sizeof(char)*54, SEEK_SET);
        fread(buffer[j].title, sizeof(char)*52, 1, A);
        fread(&buffer[j].disponivel, sizeof(char), 1, A);
        rdir--;
        j++;
      }
    }
    qsort(buffer, m-1, sizeof(Livro), compara);

    while(resq <= rdir){//comparação do resto dos titulos no arquivo maiores pra direita, menores pra esquerda
      if(wesq == resq){//esquerda cheio
        ReadLeft(A, m, buffer, compare, esq, dir, &resq, &wesq, &rdir, &wdir);
      }
      else if(wdir == rdir){//direita cheio
        ReadRight(A, m, buffer, compare, esq, dir, &resq, &wesq, &rdir, &wdir);
      }

      while(wesq != resq && wdir != rdir && resq <= rdir){//Nenhum dos lados está cheio
        ReadLeft(A, m, buffer, compare, esq, dir, &resq, &wesq, &rdir, &wdir);
        if(wesq == resq || wdir == rdir || resq > rdir){
          break;
        }
        ReadRight(A, m, buffer, compare, esq, dir, &resq, &wesq, &rdir, &wdir);
      }
    }

    for(i = 0;i < (m-1);i++){//Escrevendo o buffer no arquivo
      marcador = i+wesq;
      fseek(A, marcador*sizeof(char)*54, SEEK_SET);
      fwrite(buffer[i].title, sizeof(char)*51, 1, A);
      fwrite(" ", sizeof(char), 1, A);
      fwrite(&buffer[i].disponivel, sizeof(char), 1, A);
      fwrite("\n", sizeof(char), 1, A);
    }

    if((dir - wdir) <= (wesq - 0)){
      quicksortExt(A, buffer, compare, m, wdir+1, dir);
      quicksortExt(A, buffer, compare, m, esq, wesq);
    }
    else{
      quicksortExt(A, buffer, compare, m, esq, wesq);
      quicksortExt(A, buffer, compare, m, wdir+1, dir);
    }
  }
}

////////////////////////////////////////////
/* Protótipo:Livro  *AlocaBuffer(int size)//
// Função: Tem como função alocar structs //
//         do tipo Livro, em especial, o  //
//         buffer                         //
// Entrada: Um tamanho, o do número de    //
//          registro do array de structs  //
// Saída: Um ponteiro para struct         */
////////////////////////////////////////////

Livro  *AlocaBuffer(int size){
  Livro *new;
  new = (Livro*) calloc(size, sizeof(Livro));
  return new;
}

////////////////////////////////////////////////////////
/* Protótipo:int compara(const void *a, const void *b)//
// Função: Tem como função auxiliar no criterio de    //
//          comparação da função qsort presente no C  //
// Entrada: Dois ponteiros para constante do tipo void//
// Saída: Um inteiro, o valor retornado pela strcmp,  //
//        é o fator que determina a ordenação interna */
////////////////////////////////////////////////////////

int compara(const void *a, const void *b){
  Livro *i;
  Livro *j;
  i = (Livro *)a;
  j = (Livro *)b;
  return (strcmp(i->title, j->title));
}
