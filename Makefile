cc = g++
CFLAGS = -std=c++17 -O3 -Wall #-v

all: skeleton init pivots operations algorithms memetic
	$(cc) $(CFLAGS)   \
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
		bin/vnd.o \
		bin/utilities.o \
		bin/output.o \
		bin/memetic.o \
		bin/random_initialisation.o \
		bin/selection.o \
		bin/recombination.o \
		bin/two_point_crossover.o \
		bin/mutation.o \
		bin/iterative_local_search.o \
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
	$(cc) $(CFLAGS) -c src/algorithmType/vnd/vnd.cpp -o bin/vnd.o
	$(cc) $(CFLAGS) -c src/algorithmType/genetic/memetic.cpp -o bin/memetic.o
	$(cc) $(CFLAGS) -c src/algorithmType/iterative_local_search/iterative_local_search.cpp -o bin/iterative_local_search.o

memetic:
	$(cc) $(CFLAGS) -c src/algorithms/genetic/initialisation/random_initialisation.cpp -o bin/random_initialisation.o
	$(cc) $(CFLAGS) -c src/algorithms/genetic/selection/selection.cpp -o bin/selection.o
	$(cc) $(CFLAGS) -c src/algorithms/genetic/recombination/recombination.cpp -o bin/recombination.o
	$(cc) $(CFLAGS) -c src/algorithms/genetic/recombination/crossover/two_point_crossover.cpp -o bin/two_point_crossover.o
	$(cc) $(CFLAGS) -c src/algorithms/genetic/mutation/mutation.cpp -o bin/mutation.o

skeleton:
	$(cc) $(CFLAGS) -c src/skeleton/config/configuration.cpp -o bin/configuration.o
	$(cc) $(CFLAGS) -c src/skeleton/instance/instance.cpp -o bin/instance.o
	$(cc) $(CFLAGS) -c src/skeleton/utilities/utilities.cpp -o bin/utilities.o
	$(cc) $(CFLAGS) -c src/skeleton/output/output.cpp -o bin/output.o
	$(cc) $(CFLAGS) -c src/main.cpp -o bin/main.o

test_first:
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --transpose --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --insert --random
#    ./lop -i assets/instances/N-tiw56r72_250 --iter --first --exchange --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --transpose --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --first --insert --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --first --exchange --cw

test_best:
	./lop -i assets/instances/N-tiw56r72_250 --iter --pivot best --neighbour transpose --init random

test_vnd:
	./lop -i assets/instances/N-tiw56r72_250 --vnd TIE
	#./lop -i assets/instances/N-tiw56r72_250 --vnd --TEI

test_genetic:
	./lop -i assets/size_150/N-tiw56r72_150 --memetic --neighbour exchange --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --time 22.41135
	#./lop -i assets/instances/N-tiw56r72_150 --memetic --neighbour transpose --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --gen 10
	#./lop -i assets/instances/N-tiw56r72_150 --memetic --neighbour insert --rank-comb --rank-select --rank-mut --pop 10 --rate 0.1 --gen 10

test_ils:
	./lop -i assets/size_150/N-tiw56r72_150 --ils  --neighbour insert --perturb exchange --time 22.41135 --moves 3 --init cw
	#./lop -i assets/instances/N-tiw56r72_150 --ils --neighbour transpose --rate 0.1 --gen 10
	#./lop -i assets/instances/N-tiw56r72_150 --ils --neighbour insert --rate 0.1 --gen 10

kek:
	$(cc) $(CFLAGS) -o test/test test/test.cpp
	#$(cc) $(CFLAGS) -o test/test2 test/test2.cpp

kek1:
	./test/test
	#./test/test2


clean:
	rm -f src/*~ bin/*.o lop mourir outest