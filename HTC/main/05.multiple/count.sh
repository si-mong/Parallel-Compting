#!/bin/bash

NUM_START=$1
NUM_END=$2
LOOP_COUNT=$NUM_START
SUM=0

echo "Sum from $NUM_START to $NUM_END"
while [ $LOOP_COUNT -le $NUM_END ]
do
	SUM=`expr $SUM + $LOOP_COUNT`
	LOOP_COUNT=`expr $LOOP_COUNT + 1`
done

echo "Total Sum = $SUM"
