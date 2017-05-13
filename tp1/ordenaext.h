/////////////////////////////////////////////////////////////
//Quicksort Externo


//Organiza a primeira chamada do quicksort externo
void quicksortExtMain(FILE *A, int m, int esq, int dir);

//tem função de ordenar externamente o arquivo binário
void quicksortExt(FILE *A, Livro *buffer, Livro *compare, int m, int esq, int dir);

//Aloca o bufffer
Livro *AlocaBuffer(int size);

//Desaloca o buffer
void DesalocaBuffer(Livro **buffer, int size);

//Função usada pelo qsort para comparar os elementos no buffer
int compara(const void *a, const void *b);
