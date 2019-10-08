#CC=clang-9
CC=g++
CFLAGS=-std=c++17
INCLUDES=-I/projects/guidom

guidom.out: main.o viewManager.o
	$(CC) $(INCLUDES) -o guidom.out main.o viewManager.o

main.o: main.cpp viewManager.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -g  main.cpp -o main.o

viewManager.o: viewManager.cpp viewManager.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -g viewManager.cpp -o viewManager.o
