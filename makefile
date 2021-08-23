all:
	g++ -Wall -O3 -o PSO main.cpp

clean:
	rm -f main *.o