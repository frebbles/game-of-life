CC=g++
DEL=rm

gol:
	$(CC) -Wall gameoflife.cpp -o gol

clean:
	$(DEL) gol
