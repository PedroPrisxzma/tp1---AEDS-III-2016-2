#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "ordenaext.h"
#include "entrada_e_saida.h"
#include "pesquisa.h"

int main(){
  int aux, n, m, e, l, k;//Primeiras Entradas do problema, n = num livros, m = num suportado,
                    // e = num estantes, l = num livros por estante, k = num consultas
  if(LeEntrada(&n,&m,&e,&l,&k)){
    int i;// i auxiliar padrão
    char *x = malloc(sizeof(char)*11); ;//indica o número da estante
    char z[] = "estante";// auxiliar para criar o nome da estante
    char arqBin[] = "livro_ordenadosBin";//Arquivo temporario auxiliar, usado para ordenar e criar o txt ordenado
    char *nome_estante = malloc(sizeof(char)*18);//nome da estante
    char *t = calloc(52, sizeof(char)); //Leitor auxiliar dos titulos de livro da entrada
    char indicador;// inidicador = indicador de disponibilidade do livro
    FILE **ESTANTES = malloc(sizeof(FILE*)*e); //Cria os arquivos estante
    FILE *Bin = fopen(arqBin, "w+b");

    for(i = 0;i < e;i++){//Monta as estantes
      snprintf(x, 10, "%d", i);
      sprintf(nome_estante, "%s%s", z,x);
      ESTANTES[i] = fopen(nome_estante, "w+b");
    }

    aux = n;
    for(i = 0;i < n;i++){//Preenche o arquivo para se ordenar
      LeEntradaTxt(Bin, t, &indicador);/*fazer escrever no arquivo para orderbar tbm*/
      n = aux;
    }

    fclose(Bin);
    Bin = fopen(arqBin, "r+b");
    quicksortExtMain(Bin, m, 0, n);
    converteBinParaTxt(Bin, n);
    fazEstantes_E_indice(ESTANTES, Bin, n, e, l);
    fclose(Bin);
    for(i = 0;i < e;i++){
      fclose(ESTANTES[i]);
      snprintf(x, 5, "%d", i);
      sprintf(nome_estante, "%s%s", z,x);
      ESTANTES[i] = fopen(nome_estante, "r+b");
    }

    pesquisa(ESTANTES, t, e, k);//Parte das consultas

    for(i = 0;i < e;i++){
      fclose(ESTANTES[i]);
    }
    remove(arqBin);
    free(ESTANTES);
    free(x);
    free(nome_estante);
    free(t);
  }
  return 0;
}
