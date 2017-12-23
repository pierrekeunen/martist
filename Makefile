#Makefile

OBJECTS = parser.cpp martist.cpp

martist :  $(OBJECTS:.cpp=.o)

	ar rcu libmartist.a $(OBJECTS:.cpp=.o)

parser.o : parser.cpp

	g++ -std=c++11 -Wall -Wextra -g -c parser.cpp

martist.o :     martist.cpp
	g++ -std=c++11 -Wall -Wextra -g -c martist.cpp

clean:
	rm -f *~ *.o *.bak

mrproper :clean
	rm -f $(OBJECTS:.cpp=)

depend:
	makedepend $(OBJECTS)
