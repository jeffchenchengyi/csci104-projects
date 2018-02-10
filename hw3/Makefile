CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: stringparser

stringparser: lliststr.o stackstr.o stringparser.cpp 
	$(CXX) $(CPPFLAGS) $^ -o $@

stackstr.o: stackstr.cpp stackstr.h lliststr.o 
	$(CXX) $(CPPFLAGS) -c $< -o $@

lliststr.o: lliststr.cpp lliststr.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm stringparser stackstr.o lliststr.o