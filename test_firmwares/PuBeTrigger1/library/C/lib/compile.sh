#!/bin/bash
gcc -o getrate.exe src/getrate.c -L. ./gcc/libPuBeTrigger1.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
