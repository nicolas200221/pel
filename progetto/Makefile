# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Iinclude -MMD -MP

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
# Dependency files
DEPS = $(OBJS:.o=.d)

# Target executable
TARGET = pel

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Include dependency files
-include $(DEPS)

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(OBJ_DIR)\*) $(TARGET).exe
else
	rm -rf $(OBJ_DIR) $(TARGET)
endif

.PHONY: all clean