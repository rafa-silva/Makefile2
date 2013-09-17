CC = gcc -std=c99
CFLAGS = -W -Wall
EXEC = jogo
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIBS = -lallegro -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_font -lallegro_main -lallegro_ttf -lallegro_primitives -lm

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

clean:
	rm -rf *.o