# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source and build info
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OUT = chatbot

# Required library
LIBS = -lcurl

# Default target
all: $(OUT)

$(OUT): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(OUT) $(LIBS)

# Clean build files
clean:
	rm -f $(OUT)
