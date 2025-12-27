CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET = memory_latency_profiler
SOURCE = memory_latency_profiler.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean