# Compiler
CC = gcc

# Compiler Flags (Adjust as needed)
CFLAGS = -Wall -g -std=c11

# Object Files (Note the "bin" prefix)
OBJ = bin/main.o

# Target (Executable)
TARGET = CodeComplexityAnalyzer

# Compilation Rule (Note how "src" and "bin" are used)
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Linking Rule
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Clean Rule
clean:
	rm -f $(TARGET) $(OBJ)
