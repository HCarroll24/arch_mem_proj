CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET1 = memory_latency_profiler
SOURCE1 = memory_latency_profiler.cpp
TARGET2 = matrix_mult_no_prefetch
SOURCE2 = matrix_mult_no_prefetch.cpp
TARGET3 = matrix_mult_no_prefetch
SOURCE3 = matrix_mult_prefetch.cpp

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(SOURCE1)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(SOURCE1)

$(TARGET2): $(SOURCE2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SOURCE2)

$(TARGET3); $(SOURCE3)
	$(CXX) $(CSSFLAGS) -o $(TARGET3) $(SOURCE3)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)

.PHONY: clean