CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

all: search crawler

search: search.cpp parse.cpp queryhandler.cpp webpage.cpp parse.h queryhandler.h webpage.h setutility.h
	$(CXX) $(CPPFLAGS) $^ -o $@

crawler: crawler.cpp crawl.cpp crawl.h webpage.cpp webpage.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f search crawler