main.exe: main.o hash.o
	g++ -o main.exe main.o hash.o

main.o: main.cpp hash.h
	g++ -c main.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp


