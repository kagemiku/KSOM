CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .hpp .cpp .o

program = ksom
objs = node.o ksom.o evaluator.o main.o

$(program): $(objs)
	$(CXX) $(CXXFLAGS) -o $@ $^

.hpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ksom.o: node.hpp

main.o: node.hpp ksom.hpp evaluator.hpp

.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
