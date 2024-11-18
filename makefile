machine: main.o machine.o
	g++ -o machine main.o machine.o
main.o: main.cpp machine.h
	g++ -c main.cpp
machine.o: machine.cpp machine.h
	g++ -c machine.cpp
clean:
	rm *.o machine