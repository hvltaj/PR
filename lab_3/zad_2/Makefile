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
	$(CCOMP) $(INC) $(LIB) $(OPT) pthreads_detach_kill.c -lpthread -o pthreads_detach_kill
# jak uzyskac plik moj_program.o ?

clean:
	rm -f *.o
