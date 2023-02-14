#!/bin/bash
mkdir -p data
for ((i = 10000; i <= 320000; i*=2)) # tamanho da entrada
do
    for ((j = 10; j <= 1000; j*=10)) # tamanho da janela
    do
        for ((k = 32; k >= 1; k/=2)) # numero de threads
        do
            FILE="thread${k}_window${j}_array${i}-raw.txt"
            echo "Preenchendo data/${FILE}..."
            > data/${FILE} # apaga o conteudo dos arquivos
            for ((NUMTIMES = 1; NUMTIMES <= 20; NUMTIMES++)) # num de execucoes do programa
            do
                /usr/bin/time -f %e mpirun -q -np $k ./teste $i $j < input/$i.in 2>> data/${FILE}
            done
        done
    done

    
    
done