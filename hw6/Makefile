CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wconversion -std=c++11

all: search crawler

search: search.cpp parse.cpp queryhandler.cpp webpage.cpp configvarextractor.cpp parse.h queryhandler.h webpage.h setutility.h configvarextractor.h
	$(CXX) $(CPPFLAGS) $^ -o $@

crawler: crawler.cpp crawl.cpp configvarextractor.cpp crawl.h configvarextractor.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f search crawler