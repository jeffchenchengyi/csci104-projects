CXX = g++
CPPFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

Thanksgiving.o: Thanksgiving.cpp LengthMismatch.o qsort.h
$(CXX) $(CPPFLAGS) -c $^ -o $@

LengthMismatch.o: LengthMismatch.cpp LengthMismatch.h
$(CXX) $(CPPFLAGS) -c $^ -o $@

Functor.o: Functor.cpp Functor.h
$(CXX) $(CPPFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f Thanksgiving.o LengthMismatch.o Functor.o