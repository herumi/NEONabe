SRC=BN.c Domain.c Funciones.c NEON.c arithFp.c arithFpk.c bench.c benchPairing.c cpucycles.c main.c pairing.c

OBJ=$(SRC:.c=.o) arithFp_asm.o

CFLAGS=-Ofast -c -mfpu=neon -I./
all: main

%.o: %.c
	gcc $(CFLAGS) $<
arithFp_asm.o: arithFp_asm.s
	gcc $(CFLAGS) $<
main: $(OBJ)
	gcc $(OBJ) -o main

