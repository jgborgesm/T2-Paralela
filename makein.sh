#!/bin/bash

M=$1 
for ((i=0; i<M; i++))
do
    num=$(echo "$RANDOM%100" | bc)
    #num=$(echo "scale=2; $RANDOM/32767" | bc)
    #printf "%0.2f " $num
    echo -n "$num "
done
echo