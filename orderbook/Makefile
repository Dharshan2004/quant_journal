CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = OrderBook

$(TARGET): OrderBook.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) OrderBook.cpp

.PHONY: clean
clean:
	rm -f $(TARGET)
