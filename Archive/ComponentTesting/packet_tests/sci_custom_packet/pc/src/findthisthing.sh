#!/bin/bash
ldd test | \
while read i
do
	j=$(echo $i | awk '{print $(NF-1)}')
	echo "${j}:"
	nm $j | grep -i FRAME
	echo "========="
done
