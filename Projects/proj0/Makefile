CXX = g++
CXXFLAGS = -Wall

driver: driver.o joke.o
	$(CXX) $(CXXFLAGS) -o driver driver.o joke.o

driver.o: driver.cpp joke.h
	$(CXX) $(CXXFLAGS) -ansi -c driver.cpp

joke.o: joke.cpp joke.h
	$(CXX) $(CXXFLAGS) -ansi -c  joke.cpp

clean:
	rm *.o*
	rm *driver

run:
	./driver
