DyV: DyV.h
	g++ -o DyV DyV.h
test_DyV: DyV test_DyV.cpp
	g++ -o test_DyV test_DyV.cpp DyV.h
monedas: monedas.cpp
	g++ -o monedas monedas.cpp
testCambio: monedas
	./monedas
mochila: mochila.cpp
	g++ -o mochila mochila.cpp
testMochila: mochila
	./mochila
clean:
	rm monedas mochila test_DyV DyV
