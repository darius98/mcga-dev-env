#!/usr/bin/env bash

set -e

mkdir -p .build/$1
cmake -G Ninja -DMCGA_test_tests=ON -H. -B.build/$1
cmake --build .build/$1 --target all
cd .build/$1
ctest --output-on-failure
