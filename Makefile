
all:
	g++ -std=c++11 -g -O3 -c -o main.o main.cc
	g++ -std=c++11 -g -O3 -o app main.o 

clean:
	rm *.o
	rm app
