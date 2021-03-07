all: main.o media.o
	g++ -o WeightedAverage main.o media.o
main.o: main.cpp media.h
	g++ -c -o main.o main.cpp
media.o: media.cpp media.h
	g++ -c -o media.o media.cpp
clean:
	rm -f *.o
