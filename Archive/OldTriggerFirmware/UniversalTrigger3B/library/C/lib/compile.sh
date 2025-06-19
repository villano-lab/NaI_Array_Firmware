#!/bin/bash
gcc -o scanrate.exe src/scanrate.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o scanwindow.exe src/scanwindow.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o setthresh.exe src/setthresh.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o fifotest.exe src/fifotest.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o singlerate.exe src/singlerate.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
gcc -o currentrate.exe src/currentrate.c src/UniversalTriggerShared.c -L. ./gcc/libUniversalTrigger3B.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
