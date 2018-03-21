CXX = g++
CPPFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

Thanksgiving.o: Thanksgiving.cpp qsort.h
	$(CXX) $(CPPFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f Thanksgiving.o