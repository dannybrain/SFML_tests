CC=c++
CPPFLAGS=-std=c++11 -g
LDFLAGS=-L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -framework Foundation
SOURCES=main.cpp ResourcePath.mm Game.cpp Snake.cpp Window.cpp
OBJECTS=main.o ResourcePath.o Game.o Snake.o Window.o
EXECUTABLE=game

all: $(EXECUTABLE) $(OBJECTS)

game:$(OBJECTS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

main.o:main.cpp
	$(CC) $(CPPFLAGS) -c $<

ResourcePath.o: ResourcePath.mm
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm game $(OBJECTS)


.PHONY: all clean
