CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

all: search

search: search.cpp parser.cpp queryhandler.cpp webpage.cpp parser.h queryhandler.h webpage.h setutility.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f search