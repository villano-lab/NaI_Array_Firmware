#!/bin/bash
gcc -o scanrate.exe src/scanrate.c -L. ./gcc/libUniversalTrigger2.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o scanwindow.exe src/scanwindow.c -L. ./gcc/libUniversalTrigger2.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o setthresh.exe src/setthresh.c -L. ./gcc/libUniversalTrigger2.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0