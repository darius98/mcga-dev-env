#!/usr/bin/env bash

git clone https://github.com/darius98/mcga-cli cli
git clone https://github.com/darius98/mcga-matchers matchers
git clone https://github.com/darius98/mcga-meta meta
git clone https://github.com/darius98/mcga-proc proc
git clone https://github.com/darius98/mcga-test test
git clone https://github.com/darius98/mcga-threading threading

git submodule update --init
cd threading
git submodule update --init
cd ..
