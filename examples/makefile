CC = clang++
OPT = -std=c++1y
TARGET = ksom

ksom: main.o ../Node.h ../KSOM.h
	$(CC) $(OPT) -o $(TARGET) main.o

main.o: main.cpp ../Node.h ../KSOM.h
	$(CC) $(OPT) -c -o main.o main.cpp

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o
