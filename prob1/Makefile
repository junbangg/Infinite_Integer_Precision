
output: main.o inf_int.o
	g++ main.o inf_int.o -o run.exe
main.o: main.cpp 
	g++ -c main.cpp
inf_int.o: inf_int.cpp inf_int.h
	g++ -c inf_int.cpp
clean:
	rm *.o run.exe
