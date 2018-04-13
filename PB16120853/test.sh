#!/bin/sh
g++ core.cpp -g
./a.out > test.py
python3 test.py