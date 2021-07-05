#!/bin/bash
cd build/
cmake .. && cmake --build . -- -j 4 && ./PCE