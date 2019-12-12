#CC=clang
CC=g++
CFLAGS=-std=c++17 -Os
INCLUDES=-I/projects/guidom `pkg-config --cflags freetype2 fontconfig`
LFLAGS=`pkg-config --libs freetype2 xcb-image fontconfig`

debug: CFLAGS += -g
debug: guidom.out

release: LFLAGS += -s
release: guidom.out


guidom.out: main.o viewManager.o
	$(CC) -o guidom.out main.o viewManager.o -lstdc++ -lm -lxcb -lxcb-keysyms $(LFLAGS) 
main.o: main.cpp viewManager.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

viewManager.o: viewManager.cpp viewManager.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c viewManager.cpp -o viewManager.o

clean:
	rm *.o *.out

