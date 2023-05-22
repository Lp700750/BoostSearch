.PHONY:all
all:Parse Debug Http 

Parse:Parse.cpp
	g++ -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem
Debug:Debug.cpp 
	g++ -o $@ $^ -std=c++11 -ljsoncpp
Http:http.cpp 
	g++ -o $@ $^ -std=c++11 -ljsoncpp -lpthread

.PHONY:clean
clean:
	rm -rf Parse Debug

