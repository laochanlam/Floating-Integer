
all:
	g++ -std=c++11 -g -O3 -c -mavx2 -mno-avx256-split-unaligned-load -mno-avx256-split-unaligned-store -o main.o main.cc
	g++ -std=c++11 -g -O3 -mavx2 -mno-avx256-split-unaligned-load -mno-avx256-split-unaligned-store -o app main.o 

clean:
	rm *.o
	rm app
