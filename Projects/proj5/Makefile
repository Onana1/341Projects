CXX = g++
CXXFLAGS = -g -Wall

Anahash: Anahash.o Driver.cpp
	$(CXX) $(CXXFLAGS) Anahash.o Driver.cpp -o Anahash

Anahash.o: Anahash.cpp Anahash.h
	$(CXX) $(CXXFLAGS) -c Anahash.cpp

runHash:
	./Anahash

valgrind:
	valgrind ./Anahash
