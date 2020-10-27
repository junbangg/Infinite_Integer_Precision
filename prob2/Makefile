
output: main.o inf_int.o
	g++ main.o inf_int.o -o run.exe 
calc.o: main.cpp
	g++ -c main.cpp
inf_int.o: ../prob1/inf_int.cpp ../prob1/inf_int.h
	g++ -c ../prob1/inf_int.cpp

clean:
	rm *.o run.exe 
