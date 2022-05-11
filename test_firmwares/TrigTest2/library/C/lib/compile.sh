#!/bin/bash
gcc -o ratecheck.exe src/ratecheck.c -L. ./gcc/libTrigTest2.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
