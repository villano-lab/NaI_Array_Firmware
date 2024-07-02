#!/bin/bash
gcc -o integrate.exe src/integrate.c -L. ./gcc/libIntegration2.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
