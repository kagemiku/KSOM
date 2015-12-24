CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .h .o

program = ksom
objs = node.o ksom.o viewer.o main.o
libs = -lopencv_highgui -lopencv_core

$(program): CXXFLAGS += -L/usr/local/lib
$(program): $(objs)
	$(CXX) $(CXXFLAGS) $(libs) -o $@ $^

.h.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

viewer.o: CXXFLAGS += -I/usr/local/include
viewer.o: viewer.cpp viewer.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: CXXFLAGS += -I/usr/local/include
main.o: main.cpp node.h ksom.h viewer.o
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
