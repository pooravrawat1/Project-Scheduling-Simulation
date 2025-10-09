# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = scheduler
SRCDIR = src
SOURCE = $(SRCDIR)/ProcessScheduler.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean compiled files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Force rebuild
rebuild: clean all

# Mark these as phony targets (not files)
.PHONY: all clean run rebuild