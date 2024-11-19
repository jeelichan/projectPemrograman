# Variables
CXX = g++
CXXFLAGS = -Wall
TARGET = perencanaanDanaPensiun
SRC = perencanaanDanaPensiun.cpp

# Default target: compile the program
all: $(TARGET)

# Compile the SumOfNaturalNumber.cpp
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up the compiled files
clean:
	rm -f $(TARGET)
	rm -f $(TARGETTEST)

# Phony targets to avoid conflicts
.PHONY: all clean test