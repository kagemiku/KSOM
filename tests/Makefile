CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .h .cpp .o

program = gtest
objs = node.o ksom.o main.o node_test.o
libs = -lgtest

$(program): CXXFLAGS += -L./
$(program): $(objs)
	$(CXX) $(CXXFLAGS) $(libs) -o $@ $^

.h.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ksom.o: node.h

main.o: CXXFLAGS += -isystem googletest/googletest/include

node_test.o: CXXFLAGS += -isystem googletest/googletest/include
node_test.o: node.h


.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
