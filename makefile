all:
	g++ -Wall -O3 -o pso main.cpp search_algorithm.cpp pso.cpp test_function.cpp

clean:
	rm -f main *.o