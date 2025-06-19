#!/bin/bash
gcc -o test.exe src/compile_sw_example.c src/compile_sw_lib.c src/circular_buffer.c -L. ../../../../SCIDK-SDKLinux/libSCIDK/Debug/libSCIDK.so
