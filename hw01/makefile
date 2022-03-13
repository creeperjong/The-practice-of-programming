all: robot.o maze.o
	g++ main.cpp robot.o maze.o -o main
robot:
	g++ -c robot.cpp -o robot.o
maze:
	g++ -c maze.cpp -o maze.o
clear:
	rm -rf *.o main
