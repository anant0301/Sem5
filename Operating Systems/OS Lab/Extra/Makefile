all: file

file: main.o rat_add.o rat_sub.o rat_mul.o rat_div.o gcd.o
	g++ -o file main.o rat_add.o rat_sub.o rat_mul.o rat_div.o gcd.o

main.o: main.cpp
	g++ -c main.cpp

rat_add.o: rat_add.cpp
	g++ -c rat_add.cpp

rat_sub.o: rat_sub.cpp
	g++ -c rat_sub.cpp

rat_mul.o: rat_mul.cpp
	g++ -c rat_mul.cpp

rat_div.o: rat_div.cpp
	g++ -c rat_div.cpp

gcd.o: gcd.cpp
	g++ -c gcd.cpp

