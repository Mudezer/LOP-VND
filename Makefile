cc = g++
CFLAGS = -std=c++17 -O3 -Wall

all: skeleton init pivots operations algorithms
	$(cc) $(CFLAGS) \
		bin/CW_heuristic.o \
		bin/random_permutation.o \
		bin/best_improvement.o \
		bin/first_improvement.o \
		bin/exchange.o \
		bin/insert.o \
		bin/transpose.o \
		bin/configuration.o \
		bin/instance.o \
		bin/iterative.o \
		bin/main.o \
		-o lop

init:
	$(cc) $(CFLAGS) -c src/algorithms/initialisation/CW_heuristic.cpp -o bin/CW_heuristic.o
	$(cc) $(CFLAGS) -c src/algorithms/initialisation/random_permutation.cpp -o bin/random_permutation.o

pivots:
	$(cc) $(CFLAGS) -c src/algorithms/pivots/best_improvement.cpp -o bin/best_improvement.o
	$(cc) $(CFLAGS) -c src/algorithms/pivots/first_improvement.cpp -o bin/first_improvement.o

operations:
	$(cc) $(CFLAGS) -c src/algorithms/operations/exchange.cpp -o bin/exchange.o
	$(cc) $(CFLAGS) -c src/algorithms/operations/insert.cpp -o bin/insert.o
	$(cc) $(CFLAGS) -c src/algorithms/operations/transpose.cpp -o bin/transpose.o

algorithms:
	$(cc) $(CFLAGS) -c src/algorithmType/iterative/iterative.cpp -o bin/iterative.o
	#$(cc) $(CFLAGS) -c src/algorithmType/vnd/vnd.cpp -o bin/vnd.o


skeleton:
	$(cc) $(CFLAGS) -c src/skeleton/config/configuration.cpp -o bin/configuration.o
	$(cc) $(CFLAGS) -c src/skeleton/instance/instance.cpp -o bin/instance.o
	$(cc) $(CFLAGS) -c src/main.cpp -o bin/main.o

clean:
	rm -f src/*~ bin/*.o lop