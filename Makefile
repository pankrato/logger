CC=g++
CFLAGS= -std=c++11 -Wall

TARGET=test

all: $(TARGET)

$(TARGET): logger.o log.o test.o
	$(CC) $(CFLAGS) -o $(TARGET) -pthread test.o logger.o log.o

test.o: log.h test.cpp
	$(CC) $(CFLAGS) -c test.cpp

logger.o: log.h logger.h log.cpp logger.cpp
	$(CC) $(CFLAGS) -c log.cpp logger.cpp

clean:
	rm -rf *.o *.log $(TARGET)

run:
	./$(TARGET)

