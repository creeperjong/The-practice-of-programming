all: chef.o customer.o kitchen.o item.o
	g++ main.cpp chef.o customer.o kitchen.o item.o -o main
chef:
	g++ -c chef.cpp -o chef.o
customer:
	g++ -c customer.cpp -o customer.o
kitchen:
	g++ -c kitchen.cpp -o kitchen.o
item:
	g++ -c item.cpp -o item.o
clear:
	rm -rf *.o main