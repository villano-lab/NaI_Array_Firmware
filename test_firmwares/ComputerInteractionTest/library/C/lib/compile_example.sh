#!/bin/bash
#gcc -o ex2 src/calibration_example.cpp -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
#g++ -shared -fPIC -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L./gcc -lComputerInteractionTest ../../../../r5560_sdk/linux/libr5560.so.1.0.0
g++ -fPIC -I./src/ -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L. ./gcc/libComputerInteractionTest.so ../../../../r5560_sdk/linux/libr5560.so.1.0.0
#g++ -fPIC -I./src/ -o example src/ComputerInteractionTest_example.cpp -L/home/villaa/new-roots/ROOT-6-24-02/root/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -pthread -m64 -I/home/villaa/new-roots/ROOT-6-24-02/root/include -L./gcc/ -lComputerInteractionTest ../../../../r5560_sdk/linux/libr5560.so.1.0.0
#g++ -fPIC -I./src/ -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L./gcc/ -lComputerInteractionTest
#g++ -shared -fPIC -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` -L./gcc -lComputerInteractionTest
#g++ -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags` 
#g++ -shared -fPIC -o example src/ComputerInteractionTest_example.cpp `root-config --glibs --cflags`  ../../../../r5560_sdk/linux/libr5560.so.1.0.0
