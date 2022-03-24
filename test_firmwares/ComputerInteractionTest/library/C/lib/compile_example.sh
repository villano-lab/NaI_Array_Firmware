#!/bin/bash
#gcc -o ex2 src/calibration_example.cpp -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o example src/ComputerInteractionTest_example.c -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
