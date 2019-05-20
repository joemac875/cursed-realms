CC=g++
CFLAGS=-lncurses

OBJ = main.o manager.o terrain.o FastNoise.o toolTip.o map.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o
