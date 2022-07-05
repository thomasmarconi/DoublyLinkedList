HEADER		= list.h List.hpp

testlist: test_list.o
	g++ -g test_list.o -o proj2.x

test_list.o:
	g++ -g -c -Wall test_list.cpp -std=c++11

clean:
	rm *.o *.x; clear
