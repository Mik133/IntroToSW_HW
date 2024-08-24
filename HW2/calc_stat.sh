#!/bin/bash

#course_id=$(cat -)
course_id=$1
scourse_len=${#course_id}

if [ $# != 1 ]
then
       	echo "Wrong number of arguments" >&2
	exit 1
fi
course_find=$(find -type f -name $course_id)
if [ -n "$course_find" ]
then
	:
else 
	echo "Course not found"
	exit 1
fi

folder_name="${course_id}_stat"
if [ -e "$folder_name" ]
then 
	rm -r $folder_name
fi
mkdir $folder_name
cat $course_id|./hist.exe > $folder_name/histogram.txt
mean_id=$(./mean.exe < $course_id)
median_id=$(./median.exe < $course_id)
min_id=$(./min.exe < $course_id)
max_id=$(./max.exe < $course_id)
statistic="$mean_id\t$median_id\t$min_id\t$max_id"
echo -e "$statistic" > $folder_name/statistics.txt
