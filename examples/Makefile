CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .h .o

program = ksom
objs = node.o ksom.o evaluator.o main.o

$(program): $(objs)
	$(CXX) $(CXXFLAGS) -o $@ $^

.h.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp node.h ksom.h evaluator.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
