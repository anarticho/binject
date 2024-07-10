# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Source files
SRCS = main.cpp Binject.cpp Builder.cpp Output.cpp

# Object files (located in the build directory)
OBJS = $(SRCS:%.cpp=build/%.o)

# Executable name (located in the build directory)
EXEC = build/binject

# Default rule
all: $(EXEC)

# Rule to link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to create the build directory if it doesn't exist
build/%.o: %.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the build directory
build:
	mkdir -p build

# Clean rule to remove all generated files
clean:
	rm -rf build