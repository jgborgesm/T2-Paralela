#!/bin/bash
#mkdir -p data
mkdir -p input
for ((i = 10000; i <= 320000; i*=2)) # tamanho das entradas
do
    ./generateinput $i > input/$i.in
    
done
