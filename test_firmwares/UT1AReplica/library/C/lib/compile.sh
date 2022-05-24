#!/bin/bash
gcc -o scanwindow.exe src/scanwindow.c src/UT1AReplica_lib.c src/circular_buffer.c -L. ../../../../SCIDK-SDKLinux/libSCIDK/Debug/libSCIDK.so
gcc -o test.exe src/UT1AReplica_example.c src/UT1AReplica_lib.c src/circular_buffer.c -L. ../../../../SCIDK-SDKLinux/libSCIDK/Debug/libSCIDK.so
