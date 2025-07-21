# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Isrc

# Output binaries
DEBUG_TARGET = bin/smasher-debug
RELEASE_TARGET = bin/sfmlgame.x86_64

# SFML libraries
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SRC = $(wildcard src/*.cpp)

# Default: debug build
all: smasher-debug

smasher-debug: CXXFLAGS += -g -O0 -DDEBUG_ASSET_PATH
smasher-debug: $(DEBUG_TARGET)

release: CXXFLAGS += -O2 -DNDEBUG
release: $(RELEASE_TARGET)

$(DEBUG_TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(RELEASE_TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Clean build files
clean:
	rm -rf bin/*

# Phony targets
.PHONY: all smasher-debug release clean

