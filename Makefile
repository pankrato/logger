
CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=test

all:
	$(CC) $(CFLAGS) -pthread log.cpp logger.cpp test.cpp -o $(TARGET)

clean:
	rm -rf *.o *.log $(TARGET)

run:
	./$(TARGET)

