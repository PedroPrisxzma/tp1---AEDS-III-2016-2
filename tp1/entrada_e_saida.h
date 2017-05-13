//////////////////////////////////////////////////////////////////////////
// Leitura de Entradas

//Le uma entrada contendo o titulo do livro e o indicador de disponibilidade do mesmo
void LeEntradaTxt(/*char *nome_arquivo*/FILE *A, char *t, char *indicador);

//Le a Entrada principal
int LeEntrada(int *n, int *m, int *e, int *l, int *k);

//converte Binario ParaTxt
void converteBinParaTxt(FILE *B, int n);

//Preenche as estantes
void fazEstantes_E_indice(FILE **ESTANTES, FILE *Bin, int n, int e, int l);
