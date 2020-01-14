merge.exe: merge.o
	g++ -o merge.exe merge.o

merge.o: merge.cpp merge.h
	g++ -c merge.cpp

clean: 
	rm -f *.exe *.o *.stackdump *~
