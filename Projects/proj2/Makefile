CXX = g++
CXXFLAGS = -g -Wall

Grader: BaselineGraph.o GraphTest1.o Grader.o driver.cpp
	$(CXX) $(CXXFLAGS) BaselineGraph.o GraphTest1.o Grader.o driver.cpp -o Grader

Grader.o: Grader.cpp Grader.h
	$(CXX) $(CXXFLAGS) -c Grader.cpp

Baseline: BaselineGraph.o test1bg.cpp
	$(CXX) $(CXXFLAGS) BaselineGraph.o test1bg.cpp -o Baseline

BaselineGraph.o: BaselineGraph.cpp BaselineGraph.h
	$(CXX) $(CXXFLAGS) -c BaselineGraph.cpp

GraphTest1.o: GraphTest1.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c GraphTest1.cpp

runBase:
	./Baseline

clean:
	rm *.o*
	rm *driver

runGrader:
	./Grader

valgrind:
	valgrind ./Grader
