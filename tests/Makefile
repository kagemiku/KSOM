CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .hpp .cpp .o

program = gtest
objs = node.o ksom.o evaluator.o main.o node_test.o ksom_test.o evaluator_test.o
libs = -lgtest

$(program): $(objs)
	$(CXX) $(CXXFLAGS) -L./ $(libs) -o $@ $^

.hpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ksom.o: node.hpp

evaluator.o: node.hpp ksom.hpp

main.o: CXXFLAGS += -isystem googletest/googletest/include

node_test.o: CXXFLAGS += -isystem googletest/googletest/include
node_test.o: node.o

ksom_test.o: CXXFLAGS += -isystem googletest/googletest/include
ksom_test.o: ksom.o node.o

evaluator_test.o: CXXFLAGS += -isystem googletest/googletest/include
evaluator_test.o: ksom.o node.o


.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
