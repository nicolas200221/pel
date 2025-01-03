# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Iinclude -MMD -MP

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Check operating system
ifeq ($(OS),Windows_NT)
    FIND_SRCS = $(shell powershell -ExecutionPolicy Bypass -File get_sources.ps1 $(SRC_DIR))
    RM = cmd /C del /Q /F
    RMDIR = cmd /C rd /S /Q
    MKDIR = mkdir
    PATH_SEP = /
else
    FIND_SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
    RM = rm -rf
    MKDIR = mkdir -p
    PATH_SEP = /
endif

# Source files
SRCS = $(FIND_SRCS)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
# Dependency files
DEPS = $(OBJS:.o=.d)

# Target executable
TARGET = pel

# Default target
all: $(TARGET)

# Link object files into the target executable
$(TARGET): $(OBJS)
	@echo "[LINK]: Linking $@"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "[COMPILE]: Compiling $< -> $@"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	@echo "[CLEAN]: Cleaning up generated files"
	$(RM) $(TARGET).exe
	$(RMDIR) $(OBJ_DIR)
else
	@echo "[CLEAN]: Cleaning up generated files"
	$(RM) $(OBJS) $(DEPS) $(TARGET)
	$(RMDIR) $(OBJ_DIR)
endif

# Debug target to print SRCS and OBJS for troubleshooting
debug:
	@echo "FIND_SRCS: $(FIND_SRCS)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"

.PHONY: all clean debug
