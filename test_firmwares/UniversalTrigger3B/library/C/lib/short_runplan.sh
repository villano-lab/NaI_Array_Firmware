#!/bin/bash

#a header
echo "detectors, rate"
#each of these will take 10 seconds
#1-4
echo "Running dets 1-4."
echo "================="
./singlerate.exe -t4337 -T142000 -D30 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D30 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D30 -g20-200 -d75 -s
echo ""
#2-8
echo "Running dets 2-8."
echo "================="
./singlerate.exe -t4337 -T142000 -D480 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D480 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D480 -g20-200 -d75 -s
echo ""
#9-12
echo "Running dets 9-12."
echo "=================="
./singlerate.exe -t4337 -T142000 -D7680 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D7680 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D7680 -g20-200 -d75 -s
echo ""
#13-16
echo "Running dets 13-16."
echo "==================="
./singlerate.exe -t4337 -T142000 -D122880 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D122880 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D122880 -g20-200 -d75 -s
echo ""
#17-20
echo "Running dets 17-20."
echo "==================="
./singlerate.exe -t4337 -T142000 -D1966080 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D1966080 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D1966080 -g20-200 -d75 -s
echo ""
#21-23
echo "Running dets 21-23."
echo "==================="
./singlerate.exe -t4337 -T142000 -D14680065 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D14680065 -g20-200 -d75 -s
echo ""
./singlerate.exe -t4337 -T142000 -D14680065 -g20-200 -d75 -s
echo ""
