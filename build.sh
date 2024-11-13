#!/bin/bash

# Compiler and flags
CC="gcc"
CFLAGS="-Wall -Werror -Wextra -pedantic"

# Target executable
TARGET="simple_shell"

# Source files
SRC="main.c shell_interactive.c shell_no_interactive.c read_line.c split_line.c execute_args.c new_process.c read_stream.c builtin_functions.c"

# Compile each source file to an object file
echo "Compiling source files..."
for file in $SRC; do
    $CC $CFLAGS -c "$file" -o "${file%.c}.o"
    if [ $? -ne 0 ]; then
        echo "Error compiling $file"
        exit 1
    fi
done

# Link all object files to create the executable
echo "Linking object files..."
$CC $CFLAGS -o $TARGET *.o
if [ $? -ne 0 ]; then
    echo "Error creating $TARGET"
    exit 1
fi

echo "Build successful. Executable $TARGET created."

# Clean up function to remove object files
function clean() {
    echo "Cleaning up object files..."
    rm -f *.o
}

# Check if "clean" argument is passed
    clean

# Run the executable if "run" argument is passed
    ./$TARGET