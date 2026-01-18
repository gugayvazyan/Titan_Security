# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# Source files
SOURCES = $(SRC_DIR)/Alarm.cpp \
          $(SRC_DIR)/Sound.cpp \
          $(SRC_DIR)/Notify.cpp \
          $(SRC_DIR)/Log.cpp \
          $(SRC_DIR)/TitanSecurity.cpp \
          main.cpp

# Object files
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/titan_security

# Default target
all: $(TARGET)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)

# Link object files to create executable
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	rm -f info.txt
	@echo "Clean complete"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

# Phony targets
.PHONY: all clean run rebuild
