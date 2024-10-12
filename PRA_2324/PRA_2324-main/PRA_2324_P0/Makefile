all: main
clean:
	rm -f *.o main
test: all
	main	

brazoRobotico.o: brazoRobotico.cpp brazoRobotico.h
	g++ -c brazoRobotico.cpp
main.o: main.cpp brazoRobotico.h
	g++ -c main.cpp
main: main.o brazoRobotico.o
	g++ -o main main.o brazoRobotico.o	
