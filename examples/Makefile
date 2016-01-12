CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .hpp .cpp .o

program = ksom
objs = node.o ksom.o viewer.o main.o
libs = -lopencv_highgui -lopencv_core

$(program): CXXFLAGS += -L/usr/local/lib
$(program): $(objs)
	$(CXX) $(CXXFLAGS) $(libs) -o $@ $^

.hpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ksom.o: node.hpp

viewer.o: CXXFLAGS += -I/usr/local/include
viewer.o: viewer.h

main.o: CXXFLAGS += -I/usr/local/include
main.o: node.hpp ksom.hpp viewer.o

.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
