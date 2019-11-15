CXX = g++
CXXFLAGS = -g -Wall

JQueue: JQueue.o MyJQTest.cpp
	$(CXX) $(CXXFLAGS) JQueue.o MyJQTest.cpp -o JQueue

JQueue.o: JQueue.cpp JQueue.h
	$(CXX) $(CXXFLAGS) -c JQueue.cpp

runJQueue:
	./JQueue

valgrind:
	valgrind ./JQueue
