CXX = g++
CXXFLAGS = -std=c++11 -O3 -pthread

TARGET1 = cpu_benchmark

SRC1 = benchmark.cpp

$(TARGET1): $(SRC1)
	$(CXX) $(SRC1) $(CXXFLAGS) -o $(TARGET1)


clean:
	rm -f $(TARGET1)