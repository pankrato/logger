CXXFLAGS += -std=c++11 -Wall

TARGET=test

all: $(TARGET)

$(TARGET): logger.o log.o test.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) -pthread test.o logger.o log.o

test.o: log.h test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

logger.o: log.h logger.h log.cpp logger.cpp
	$(CXX) $(CXXFLAGS) -c log.cpp logger.cpp

clean:
	rm -rf *.o *.log $(TARGET)

run:
	./$(TARGET)

