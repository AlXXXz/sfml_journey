CC=g++
PROJECT=game
SRC=main.cpp Game.cpp AssetManager.cpp Animator.cpp
OBJ=$(SRC:.cpp=.o)
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all

all: $(SRC) $(PROJECT)
	rm *.o

$(PROJECT): $(OBJ)
	$(CC) $(OBJ) -o $(PROJECT) $(SFML_FLAGS)

.cpp.o:
	$(CC) -c -Wall $< -o $@

clean:
	rm template
