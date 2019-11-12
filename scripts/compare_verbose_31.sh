#!/bin/bash

make -C .. -s
mkdir -p ./results
mkdir -p ./results/verbose
rm -rf ./results/verbose/*

first='./champions/Kappa.cor'
second='./champions/MarineKing.cor'
i=0
n=25000
incre=1000
while [[ $i -eq 0 ]]
do	
	echo $n
	((n +=  $incre))
	../corewar -v 31 -dump $n $first $second > ./results/verbose/our.txt
	../ressources/vm_champs/corewar -v 31 -d $n $first $second > ./results/verbose/zaz.txt
	diff ./results/verbose/our.txt ./results/verbose/zaz.txt > ./results/verbose/diff.txt
	i=$?
done
