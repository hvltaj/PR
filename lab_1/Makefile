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
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy
moj_program: moj_program.o 
#pomiar_czasu.o 
	$(LOADER) $(INC) $(LIB) $(OPT) moj_program.o -lpomiar_czasu -o moj_program

# jak uzyskac plik moj_program.o ?
moj_program.o: moj_program.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) $(INC) -c $(OPT) moj_program.c


#pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
#	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o
