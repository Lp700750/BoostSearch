.PHONY:all
all:Parse Debug 

Parse:Parse.cpp
	g++ -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem
Debug:Debug.cpp 
	g++ -o $@ $^ -std=c++11 -ljsoncpp

.PHONY:clean
clean:
	rm -rf Parse Debug

