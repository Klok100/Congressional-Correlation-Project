CXX=clang++
INCLUDES=-Iincludes/ -Ilib/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++14 -g -fsanitize=address,null

exec: bin/exec
tests: bin/tests

bin/exec: ./main.cpp ./src/XMLParser.cpp ./src/graphs.cpp ./src/DFS.cpp ./src/Dijkstra.cpp ./src/Tarjan.cpp ./src/Utils.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: ./tests/tests.cpp ./src/graphs.cpp ./src/DFS.cpp ./src/Dijkstra.cpp ./src/Tarjan.cpp ./src/Utils.cpp obj/catch.o 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

obj/catch.o: catch/catchmain.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/* obj/*