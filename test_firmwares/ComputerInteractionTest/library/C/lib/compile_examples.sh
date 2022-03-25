#!/bin/bash
gcc -o example src/ComputerInteractionTest_example.c -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
g++ -fPIC -o root_example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
