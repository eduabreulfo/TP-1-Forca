
FLAGS = -Wall -Wno-unused-result

DEPS = tJogador.h tJogo.h tPalavra.h
OBJ = tJogador.o tJogo.o tPalavra.o main.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(FLAGS)

all: $(OBJ)
	gcc -o main $(OBJ) $(FLAGS)

clean:
	rm -f main *.o

run: 
	./main 
