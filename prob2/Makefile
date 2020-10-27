
output: calc.o inf_int.o
	g++ calc.o inf_int.o -o run.exe 
calc.o: calc.cpp
	g++ -c calc.cpp
inf_int.o: ../prob1/inf_int.cpp ../prob1/inf_int.h
	g++ -c ../prob1/inf_int.cpp

clean:
	rm *.o run.exe 
