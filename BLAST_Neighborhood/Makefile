CXX = /usr/bin/g++
LDFLAGS =
CPPFLAGS = 
INC =
CXXFLAGS = -std=c++17 -Wall -pedantic -O2 -D_GLIBCXX_ASSERTIONS -g -fsanitize=address -fopenmp

%.o: %.cpp a4_util.h BLAST_Neighborhood.hpp
	$(CXX) $(CXXFLAGS) -I . -c $*.cpp
	
blastMain: BLAST_Neighborhood.o blastNH_main.o a4_util.o
	$(CXX) $(CXXFLAGS) -I . $^ -o blastMain
