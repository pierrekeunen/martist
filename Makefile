# Makefile
CC = g++
CFLAGS = -std=c++11 -Wextra -Wall


martist: martist.o parser.o
	ar rcu libmartist.a $^

martist.o: martist.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)

parser.o: parser.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf *.o
