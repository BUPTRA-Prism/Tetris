#!/usr/bin/env bash

set -e

if [ ! -d "build" ]; then
    echo "First build: configuring project..."
    cmake -S . -B build -G Ninja
fi

echo "Building Tetris..."
cmake --build build

echo "Build completed. Running Tetris..."
./build/Tetris.exe
