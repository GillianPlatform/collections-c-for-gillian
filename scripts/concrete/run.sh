#!/bin/bash

# Set the directory where the library source files are located
LIB_DIR="../../libs/fixed"

# Set the directory where the library header files are located
INCLUDE_DIR="$LIB_DIR/include"

TEST_DIR="../../concrete_tests"

# Name of the output executable
OUTPUT_NAME="testProgram"

# Compile the library and the main program
gcc -I"$INCLUDE_DIR" "$LIB_DIR"/*.c $TEST_DIR/$1 -o $OUTPUT_NAME -fsanitize=address,undefined

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program:"
    ./$OUTPUT_NAME
else
    echo "Compilation failed."
fi