#!/bin/bash
N1=1600
N2=300000
delta=$(( (N2 - N1) / 10 ))
for ((i=0; i<=10; i++))
do
    printf "lab1-seq N:%d " $N1
    ./lab1-seq $N1
    printf " lab1-par-1 N:%d " $N1
    ./lab1-par-1 $N1
    printf " lab1-par-4 N:%d " $N1
    ./lab1-par-4 $N1
    printf " lab1-par-8 N:%d " $N1
    ./lab1-par-8 $N1
    printf " lab1-par-12 N:%d " $N1
    ./lab1-par-12 $N1
    N1=$((N1 + delta))
done
