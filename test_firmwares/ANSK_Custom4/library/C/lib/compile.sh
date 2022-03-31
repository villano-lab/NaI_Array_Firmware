#!/bin/bash
gcc -o integrate.exe src/integrate.c -L. ./gcc/libANSK_Custom4.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o spectrum.exe src/spectrum.c -L. ./gcc/libANSK_Custom4.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
