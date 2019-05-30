CC=g++
CFLAGS= -std=c++11

OBJ = main.o option.o manager.o tile.o FastNoise.o toolTip.o map.o resource.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -lncurses -o $@ $^ $(CFLAGS)

clean:
	rm *.o
