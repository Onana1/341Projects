CXX = g++
CXXFLAGS = -g -Wall

CTree: CTree.o Driver.cpp
	$(CXX) $(CXXFLAGS) CTree.o Driver.cpp -o CTree

CTree.o: CTree.cpp CTree.h
	$(CXX) $(CXXFLAGS) -c CTree.cpp

runCTree:
	./CTree

valgrind:
	valgrind ./CTree

