CXX = g++
CPPFLAGS = -g -Wall -std=c++11

Thanksgiving: LengthMismatch.o Thanksgiving.cpp 
	$(CXX) $(CPPFLAGS) $^ -o $@

LengthMismatch.o: LengthMismatch.cpp LengthMismatch.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

qsort_test: qsort.h qsort_test.cpp 
	$(CXX) $(CPPFLAGS) $^ -o $@

functor_test: functor.o functor_test.cpp 
	$(CXX) $(CPPFLAGS) $^ -o $@

functor.o: functor.cpp functor.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f functor.o functor_test qsort_test LengthMismatch.o Thanksgiving