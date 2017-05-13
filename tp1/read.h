/////////////////////////////////////////////
//Auxiliares do quicksort Externo
typedef struct {
  char title[52];
  char disponivel;
}Livro;

//Le da esquerda no arquivo
void ReadLeft(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir);

//Le da direita no arquivo
void ReadRight(FILE *A, int m, Livro *buffer, Livro *compare, int esq, int dir, int *resq, int *wesq, int *rdir, int *wdir);
