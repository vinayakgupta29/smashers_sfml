#!/bin/bash
mkdir -p build

for file in src/*.cpp; do
    filename=$(basename "$file" .cpp)
    g++ -std=c++20 -O2 -Iinclude -c "$file" -o "build/$filename.o"
done

