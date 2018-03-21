CXX = g++
CPPFLAGS = -g -Wall -Wextra -Wconversion -std=c++11
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

Thanksgiving.o: Thanksgiving.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f Thanksgiving.o