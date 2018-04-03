# Instructions on how to execute hw6 programs:

## [Step 1 (Change your **`intersect`** and **`union`** functions to templated, 5%):](setutility.h)

> Templated intersection, union, and other query functions in **`setutility.h`**.


## Step 2 (Use configuration files, 5%): [search.cpp](search.cpp) [crawler.cpp](crawler.cpp)

> Changed expected input to be config file in **`search.cpp`** and **`crawler.cpp`**.


## [Step 3 (Write a "Web Crawler", 30%): ](crawl.cpp)
### [Header file for Crawl class](crawl.h)

> DFS Algorithm inside 
**`void Crawl::DFScrawl(
	vector<string>& webpages_explored, 
	string curr_weblink)`**
> Use [Makefile](Makefile) to compile crawler to executable by running **`make crawler`**
> Run by **`./crawler config.txt`**


## [Step 4 (Expand the Set of candidate search results, 10%): ](queryhandler.cpp)
### [Header file for QueryHandler class](queryhandler.h)

> Expand candidate search results inside 
**`vector<string> QueryHandler::addToCandidateSet(
		const vector<string>& results_vec, 
		const map<string, WebPage*>& webpage_map)`** function


## [Step 5 (Implement and use PageRank, 50%): ](queryhandler.cpp)

> Use [Makefile](Makefile) to compile search to executable by running **`make search`**
> Run by **`./search config.txt`**