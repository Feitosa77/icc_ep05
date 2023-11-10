
all: labMonteCarlo.c
	gcc utils.c labMonteCarlo.c -Wall -lm
	./a.out 0 1 10000000 2
