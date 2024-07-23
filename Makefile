# Compiler stuff
CXX ?= c++
CXXFLAGS = -std=c++14 

# Dependencies
LIBS = -lGL -lGLEW -lglfw

# Source files
SOURCE_FILES = $(wildcard ./*.cpp)
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# Executable
TARGET = crystal

# Build
all: $(TARGET)

# Link
$(TARGET): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(TARGET) $(OBJECT_FILES)

# Run
run: $(TARGET)
	./$(TARGET)

# Debug
debug: $(TARGET)
	gdb ./$(TARGET)

# Phony
.PHONY: all clean run debug