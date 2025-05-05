CC = gcc
CFLAGS = -Wall -std=c99 -I/opt/homebrew/Cellar/gsl/2.8/include
LDFLAGS = -L/opt/homebrew/Cellar/gsl/2.8/lib
LIBS = -lgsl -lgslcblas -lm

all: matrix_multiplication

matrix_multiplication: matrix_multiplication.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

optimized: matrix_multiplication.c
	$(CC) $(CFLAGS) $(LDFLAGS) -O3 -o matrix_multiplication_optimized $^ $(LIBS)

clean:
	rm -f matrix_multiplication matrix_multiplication_optimized

.PHONY: all clean optimized
