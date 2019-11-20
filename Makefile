Execute: card.o
	g++ -std=c++11 -g card.o -o Execute

card.o: card.cpp
	g++ -std=c++11 -g -c card.cpp

clean:
	rm *.o Execute
