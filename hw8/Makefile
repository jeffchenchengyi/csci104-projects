CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

all: hypercube

hypercube: hypercube.cpp hypercubegraph.cpp hypercubegraph.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f hypercube