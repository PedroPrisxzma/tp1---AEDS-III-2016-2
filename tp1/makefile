CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c99 -pedantic
DEPS = ordenaext.h read.h entrada_e_saida.h pesquisa.h
OBJ = ordenaext.o main.o read.o entrada_e_saida.o pesquisa.o
%.o: %.c $(DEPS)
				$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
