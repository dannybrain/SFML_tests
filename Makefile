CPPFLAGS=-std=c++11 -g
LDFLAGS=-L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -framework Foundation

game: main.o ResourcePath.o
	c++ $(CPPFLAGS) $(LDFLAGS) main.o ResourcePath.o -o game

main.o: main.cpp
	c++ $(CPPFLAGS) -c main.cpp
