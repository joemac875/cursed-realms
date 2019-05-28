CC=g++
CFLAGS=-lncurses

OBJ = main.o manager.o tile.o FastNoise.o toolTip.o map.o resource.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o
