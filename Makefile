cc = g++
CFLAGS = -std=c++17 -O3 -Wall

all: skeleton init pivots operations algorithms
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


skeleton:
	$(cc) $(CFLAGS) -c src/skeleton/config/configuration.cpp -o bin/configuration.o
	$(cc) $(CFLAGS) -c src/skeleton/instance/instance.cpp -o bin/instance.o
	$(cc) $(CFLAGS) -c src/skeleton/utilities/utilities.cpp -o bin/utilities.o
	$(cc) $(CFLAGS) -c src/skeleton/output/output.cpp -o bin/output.o
	$(cc) $(CFLAGS) -c src/main.cpp -o bin/main.o



test_first:
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --transpose --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --insert --random
#	./lop -i assets/instances/N-tiw56r72_250 --iter --first --exchange --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --first --transpose --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --first --insert --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --first --exchange --cw

test_best:
	./lop -i assets/instances/N-tiw56r72_250 --iter --best --transpose --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --best --insert --random
#	./lop -i assets/instances/N-tiw56r72_250 --iter --best --exchange --random
	#./lop -i assets/instances/N-tiw56r72_250 --iter --best --transpose --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --best --insert --cw
#	./lop -i assets/instances/N-tiw56r72_250 --iter --best --exchange --cw

test_vnd:
	./lop -i assets/instances/N-tiw56r72_250 --vnd TIE
	#./lop -i assets/instances/N-tiw56r72_250 --vnd --TEI

mourir:
	$(cc) $(CFLAGS) test/outest.cpp -o outest

clean:
	rm -f src/*~ bin/*.o lop mourir outest