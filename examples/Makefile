CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .h .cpp .o

program = ksom
objs = node.o ksom.o evaluator.o main.o

$(program): $(objs)
	$(CXX) $(CXXFLAGS) -o $@ $^

.h.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ksom.o: node.h

main.o: node.h ksom.h evaluator.h

.PHONY: run
run:
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
