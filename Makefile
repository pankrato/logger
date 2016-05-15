CC=g++
CFLAGS= -std=c++11 -Wall

TARGET=test

all: $(TARGET)

$(TARGET): logger.o test.o
	$(CC) $(CFLAGS) -o $(TARGET) -pthread test.o logger.o log.o

test.o: log.h test.cpp
	$(CC) $(CFLAGS) -c test.cpp

logger.o: log.h log.cpp logger.h logger.cpp
	$(CC) $(CFLAGS) -c log.cpp logger.cpp

clean:
	rm -rf *.o *.log $(TARGET)

run:
	./$(TARGET)

