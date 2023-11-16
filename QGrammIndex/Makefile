CXX = /usr/bin/g++
LDFLAGS =
CPPFLAGS = 
INC =
CXXFLAGS = -std=c++17 -Wall -pedantic -O2 -D_GLIBCXX_ASSERTIONS -g -fsanitize=address -fopenmp
# -D_GLIBCXX_DEBUG // bad for openmp performance


%.o: %.cpp QGramIndex.h
	${CXX} ${CXXFLAGS} -I . -c $*.cpp
	

qgi_main: QGramIndex.o qgi_main.o a5_util.o
	${CXX} ${CXXFLAGS} -I . $^ -o qgi_main

