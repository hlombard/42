#!/bin/bash

YELLOW='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
TOTAL=1
OK=0
ISOK="Writing output program to"

#Making sure binaries are ready, and clearing results folder

make -C .. -s
mkdir -p ./results
mkdir -p ./results/asm_invalid/
rm -rf ./results/asm_invalid/*

#This script, check if we and zaz, both reject .s files
#Every files in ./asm_invalid should be rejected

for file in ./asm_invalid/*.s;
do
	echo $YELLOW"[TEST $TOTAL]: `basename $file`"$NC
	./../asm $file > ./results/asm_invalid/our_output_$TOTAL 2>&1
	./../ressources/vm_champs/asm $file > ./results/asm_invalid/zaz_output_$TOTAL
	DATA1=$(cat ./results/asm_invalid/our_output_$TOTAL)
	DATA2=$(cat ./results/asm_invalid/zaz_output_$TOTAL)
	echo "\nOur Output: $DATA1"
	echo "Zaz Output: $DATA2\n"
	if [ "$DATA1" != "$ISOK ${file/.s/.cor}" ] && [ "$DATA2" != "$ISOK ${file/.s/.cor}" ]; then
		echo $GREEN"[OK]\n"$NC
		OK=$((OK+1))
	else
		echo $RED"[KO]\n"$NC
	fi
	TOTAL=$((TOTAL+1))
done;

TOTAL=$((TOTAL-1))

echo "\n\n-------------------------\n"
echo "Results : $OK / $TOTAL\n"

if  [ $OK != $TOTAL ]; then
	echo $RED"FAILED Check details in ./results/asm_invalid/\n" $NC
else
	echo $GREEN"PERFECT ✔" $NC
fi

for file in ./asm_invalid/*.cor
do
	rm -rf $file
done;
