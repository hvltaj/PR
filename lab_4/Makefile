# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC = -I/usr/include

# biblioteki
LIB = -L/usr/lib -lm

# zaleznosci i komendy
all: 
#	$(CCOMP) $(INC) $(LIB) $(OPT) pub_sym_1.c -lpthread -o pub_sym_1
	$(CCOMP) $(INC) $(LIB) $(OPT) pub_sym_11.c -lpthread -o pub_sym_11
# jak uzyskac plik moj_program.o ?

clean:
	rm -f *.o
