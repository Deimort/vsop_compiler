#!/bin/bash

cd vsopcompiler/

# Run the make command to build the vsopc executable
make

# Navigate to the directory with the test files
cd ../examples/tests

# Loop over all the files in the directory with .txt extension
for file in *.txt; do
    # Run the vsopc program with the -l flag and the current file
    echo "--- Running test: $file ---"
    ../../vsopcompiler/vsopc -l "$file"
    echo "--- Test $file complete ---"
    echo ""
done

cd ../../vsopcompiler
make clean