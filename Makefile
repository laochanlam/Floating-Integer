
all:
	g++ -std=c++11 -g -O3 -c -mavx2 -o main.o main.cc
	g++ -std=c++11 -g -O3 -mavx2 -o app main.o 

clean:
	rm *.o
	rm app
