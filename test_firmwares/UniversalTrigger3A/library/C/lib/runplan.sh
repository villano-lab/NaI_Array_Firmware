#!/bin/bash


#each of these will take 10 seconds
#1-4
echo "Running dets 1-4."
echo "================="
./singlerate.exe -t4337 -T142000 -D30 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D30 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D30 -g200-20
echo ""
#2-8
echo "Running dets 2-8."
echo "================="
./singlerate.exe -t4337 -T142000 -D480 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D480 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D480 -g200-20
echo ""
#9-12
echo "Running dets 9-12."
echo "=================="
./singlerate.exe -t4337 -T142000 -D7680 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D7680 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D7680 -g200-20
echo ""
#13-16
echo "Running dets 13-16."
echo "==================="
./singlerate.exe -t4337 -T142000 -D122880 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D122880 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D122880 -g200-20
echo ""
#17-20
echo "Running dets 17-20."
echo "==================="
./singlerate.exe -t4337 -T142000 -D1966080 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D1966080 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D1966080 -g200-20
echo ""
#21-23
echo "Running dets 21-23."
echo "==================="
./singlerate.exe -t4337 -T142000 -D14680065 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D14680065 -g200-20
echo ""
./singlerate.exe -t4337 -T142000 -D14680065 -g200-20
echo ""

#this will take 15 minutes
echo "Running window scan."
echo "===================="
./scanwindow.exe -t4337 -r0-12000-120 -D"All" -g200-20