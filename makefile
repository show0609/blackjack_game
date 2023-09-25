all: card.o game.o player.o a.out

card.o: card.h card.cpp
	g++ -c card.cpp
game.o: game.h game.cpp
	g++ -c game.cpp
player.o: player.h player.cpp
	g++ -c player.cpp
	
a.out: card.o game.o player.o main.cpp
	g++ card.o game.o player.o main.cpp
	
cleano:
	rm *.o
clean: cleano
	rm ./a.out
