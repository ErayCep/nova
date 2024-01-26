CC = clang++
CFLAGS = -O3
LIBS = -lglfw3 -lGL -lassimp
SRC = ./src/*.cpp
OUTPUT = ./build/nova
INCLUDE = ./lib/glad.o 

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) $(INCLUDE) -o $(OUTPUT)
	$(OUTPUT)

clean:
	rm -f $(OUTPUT)

