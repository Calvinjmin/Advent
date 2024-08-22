# Variables
COMPILER = g++
CFLAGS = -g -Wall -std=c++17
TARGET = main

# List of directories
DIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d)

# Default target to build the main project
all: $(TARGET)

# Custom target to compile and run main.cpp in a specific folder
run%: %/main.o
	$(COMPILER) $(CFLAGS) -o $*/main $*/main.o
	./$*/main

%/main.o: %/main.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

# Rule to clean up compiled files in all directories
clean:
	rm -f $(TARGET) *.o
	@for dir in $(DIRS); do rm -f $$dir/*.o $$dir/main; done

# Rule to run the main project
run: $(TARGET)
	./$(TARGET)