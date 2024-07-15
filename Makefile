# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Iinc

# Source and header files
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
TST_DIR = tst

# Sources and objects
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable
TARGET = $(BUILD_DIR)/binject

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "[*] Building $(@F) assembly..."
	@mkdir -p $(BUILD_DIR)
	@-$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to build the target executable
$(TARGET): $(OBJS)
	@echo "[*] Generating $(@F) executable..."
	@-$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[*] Verifying functionnality..."
	@$(TST_DIR)/tst.sh
	
# Default rule
all:
	$(TARGET)

# Test target
test:
	@$(TST_DIR)/tst.sh

# Phony targets
.PHONY: clean to_bin

# Copy built target with bin directory
to_bin:
	@cp $(BUILD_DIR)/binject ~/bin/binject
	@echo "[*] Copy built target within binary directory"

# Clean build directory
clean:
	@-rm -rf $(BUILD_DIR)
	@echo "[*] Removed build directory"

# Ensure build directory exists
$(BUILD_DIR):
	@-mkdir -p $(BUILD_DIR)