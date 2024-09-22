all:
	g++ main.cpp Drawer.cpp -c
	g++ main.o Drawer.o -lSDL2