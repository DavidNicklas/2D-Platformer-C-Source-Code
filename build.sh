#!/bin/bash

libs=-luser32
warnings=-Wno-writable-strings

clang src/main.cpp -o2DPlatformer.exe $libs $warnings