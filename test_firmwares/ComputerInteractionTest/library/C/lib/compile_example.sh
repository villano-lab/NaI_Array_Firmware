#!/bin/bash
#gcc -o ex2 src/calibration_example.cpp -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
g++ -fPIC -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L./gcc -lComputerInteractionTest ../../../../r5560_sdk/linux/libr5560.so.1.0.0
