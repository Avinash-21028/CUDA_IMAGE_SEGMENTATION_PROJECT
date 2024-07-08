#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate to build directory
cd build

# Run CMake
cmake ..

# Build the project
make

# Run the segmentation program
./segmentation
