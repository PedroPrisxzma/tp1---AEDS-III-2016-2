#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "ordenaext.h"
#include "pesquisa.h"

////////////////////////////////////////////////////////////////////////
/* Protótipo:void pesquisa(FILE **ESTANTES, char *title, int e, int k)//
// Função: Tem como função iniciar e fazer a pesquisa dos livros      //
// Entrada: Um array/ponteiro para arquivos, as estantes, uma string, //
//          o livro que será procurado e dois inteiros, o número de   //
//          estantes e o total de livros a serem procurados           //
// Saída: Não há, função do tipo void                                 */
////////////////////////////////////////////////////////////////////////

void pesquisa(FILE **ESTANTES, char *title, int e, int k){
  int i,j, fim;
  int estante;
  Livro *aux = AlocaBuffer(2);
  for(i = 0;i < k;i++){
    scanf("%s", title);
    estante = pesquisaIndice(aux, title, e);//Descobre a possivel estante do livro
    if(estante != -1){
      fseek(ESTANTES[estante], 0, SEEK_END);
      fim = (ftell(ESTANTES[estante])/54);
      pesquisaEstante(ESTANTES, aux, title, estante, 0, fim);//Procura na estante do livro
    }
    for(j = 0;j < 52;j++){
      title[j] = 0;
    }
  }
  free(aux);
}

////////////////////////////////////////////////////////////////////////
/* Protótipo:int pesquisaIndice(Livro *aux, char *title, int e)       //
// Função: Tem como função fazer a busca/pesquisa no indice           //
// Entrada: Um ponteiro para struct do tipo Livro, uma string, o      //
//          titulo sendo buscado no indice e um inteiro, o numero     //
//          total de estantes                                         //
// Saída: Um inteiro, o número da estante onde o livro pode estar, ou //
//        -1, caso não encontre uma estante que possa conter o livro  */
////////////////////////////////////////////////////////////////////////

int pesquisaIndice(Livro *aux, char *title, int e){
  int count = 0;
  FILE *I = fopen("indice", "r");
  while(count < e){
    fscanf(I, "%s %s", aux[0].title, aux[1].title);
    if(aux[0].title[0] == '#'){
      break;
    }
    else if(strcmp(title, aux[0].title) < 0){
      break;
    }
    else if(strcmp(title, aux[0].title) >= 0 && strcmp(title, aux[1].title) <= 0){
      fclose(I);
      return count;
    }
    count++;
  }
  fclose(I);
  printf("Livro nao encontrado\n");
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Protótipo:void pesquisaEstante(FILE **ESTANTES, Livro *aux, char *title, int estante, int inicio, int fim) //
// Função: Tem como função busca binária na estante que pode conter o livro                                   //
// Entrada: Um array/ponterio de arquivos, as estantes, um ponteiro para struct do tipo Livro, uma string, o  //
//          titulo sendo buscado e três inteiros, o numero da estante no qual deve-se procurar, um marcador de//
//          inicio(esquerda) e outro de fim(direita) para busca binaria                                       //
// Saída: Não há, função do tipo void                                                                         */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pesquisaEstante(FILE **ESTANTES, Livro *aux, char *title, int estante, int inicio, int fim){
  if((fim - inicio) < 0){
    printf("livro não encontrado\n");
    return;
  }
  int pivo = (fim+inicio)/2;//Marcador da busca binária
  int i;//Auxiliar
  fseek(ESTANTES[estante], pivo*54*sizeof(char), SEEK_SET);
  fread(aux[0].title, sizeof(char)*52, 1, ESTANTES[estante]);
  fread(&aux[0].disponivel, sizeof(char), 1, ESTANTES[estante]);
  i = strcmp(title, aux[0].title);

  if(i == 0){//achamos o livro
    if(aux[0].disponivel == '0'){
      printf("emprestado\n");
    }
    else{
      i = ftell(ESTANTES[estante])/54;
      printf("disponivel na posicao %d na estante %d\n", i, estante);
    }
  }
  else if(i < 0){//livro antes do pivo
    pesquisaEstante(ESTANTES, aux, title, estante, inicio, pivo-1);
  }
  else if(i > 0){//livro depois do pivo
    pesquisaEstante(ESTANTES, aux, title, estante, pivo+1, fim);
  }
}
