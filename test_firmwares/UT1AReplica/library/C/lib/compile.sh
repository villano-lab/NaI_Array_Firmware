#!/bin/bash
gcc -o scanwindow.exe src/scanwindow.c src/Ut1AReplica_lib.c src/circular_buffer.c -L ../../../../SCIDK-SDKLinux/libSCIDK/Debug/libSCIDK.so
