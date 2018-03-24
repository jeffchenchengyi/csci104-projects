CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

all: search

search: search.cpp webpage.o
	$(CXX) $(CPPFLAGS) $^ -o $@

webpage.o: webpage.cpp webpage.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f search webpage.o