
CXX = g++
CXXFLAG = -std=c++11
CPPFLAG = -fopenmp -O3


main : main.o EM.o LoadMnist.o
	$(CXX) $(CXXFLAG) $(CPPFLAG) $^ -o $@

main.o : main.cpp LoadMnist.hpp EM.hpp
	$(CXX) $(CXXFLAG) $(CPPFLAG) $< -c -o $@
LoadMnist.o : LoadMnist.cpp LoadMnist.hpp
	$(CXX) $(CXXFLAG) $(CPPFLAG) $< -c -o $@
EM.o : EM.cpp EM.hpp
	$(CXX) $(CXXFLAG) $(CPPFLAG) $< -c -o $@


.phony :clean
clean:
	rm -f *.o *.exe

