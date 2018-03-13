CXX = g++
CPPFLAGS = -g -Wall -std=c++11

functor_test: functor.o functor_test.cpp 
	$(CXX) $(CPPFLAGS) $^ -o $@

functor.o: functor.cpp functor.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f functor.o functor_test