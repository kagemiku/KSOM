CXX = clang++
OPT = -std=c++1y
TARGET = ksom

ksom: main.o ../sources/node.h ../sources/ksom.h
	$(CXX) $(OPT) -o $(TARGET) main.o

main.o: main.cpp ../sources/node.h ../sources/ksom.h
	$(CXX) $(OPT) -c -o main.o main.cpp

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o
