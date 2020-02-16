OPTIONS=-g -O0 -Wall
# OPTIONS=-O2 -Wall

all : hashcode

hashcode : src/main.cpp bin/hashcode.o
	g++ ${OPTIONS} -o hashcode src/main.cpp bin/hashcode.o

bin/hashcode.o : src/hashcode.cpp src/hashcode.h
	g++ ${OPTIONS} -c -o bin/hashcode.o src/hashcode.cpp

clean:
	rm -rf hashcode *~ bin/* *.tmp
