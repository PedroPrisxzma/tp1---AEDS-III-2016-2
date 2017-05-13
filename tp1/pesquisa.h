///////////////////////////

//inicia a pesquisa
void pesquisa(FILE **ESTANTES, char *title, int e, int k);

//pesquisa no indice
int pesquisaIndice(Livro *aux, char *title, int e);

//pesquisa na estante
void pesquisaEstante(FILE **ESTANTES, Livro *aux, char *title, int estante, int inicio, int fim);
