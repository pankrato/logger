
CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=test

all:
	$(CC) $(CFLAGS) -pthread logger.cpp test.cpp -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)

run:
	./$(TARGET)

