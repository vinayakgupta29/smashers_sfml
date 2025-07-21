# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Isrc

# Output
TARGET = bin/sfmlgame

# SFML libraries
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SRC = $(wildcard src/*.cpp)

# Default rule
all: $(TARGET)

# Link object files
$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean build files
clean:
	rm -rf bin/*

# Phony targets
.PHONY: all clean

