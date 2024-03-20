cc = g++
CFLAGS = -std=c++17 -O3 -Wall

all: init pivots operations configuration skeleton
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
		bin/optimization.o \
		bin/timer.o \
		bin/utilities.o \
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

configuration:
	$(cc) $(CFLAGS) -c src/algorithms/config/configuration.cpp -o bin/configuration.o

skeleton:
	$(cc) $(CFLAGS) -c src/skeleton/instance/instance.cpp -o bin/instance.o
	$(cc) $(CFLAGS) -c src/skeleton/optimization/optimization.cpp -o bin/optimization.o
	$(cc) $(CFLAGS) -c src/skeleton/timer/timer.cpp -o bin/timer.o
	$(cc) $(CFLAGS) -c src/skeleton/utilities/utilities.cpp -o bin/utilities.o
	$(cc) $(CFLAGS) -c src/main.cpp -o bin/main.o

clean:
	rm bin/*.o lop