#!/bin/bash

YELLOW='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
TOTAL=1
OK=0
ZERO=0

#Making sure that binaries are ready, and clearing results folder

make .. -s
mkdir -p ./results
mkdir -p ./results/asm_valid/
rm -rf ./results/asm_valid/*


#Generating our .cor files

for file in ./asm_valid/*.s
do
	./../asm $file 2>&- 1>&-
done;

#Stocking hexdump results

for file in ./asm_valid/*.cor
do
	hexdump -C $file > ./results/asm_valid/our_hexdump_`basename $file`
done;

#Deleting our .cor files

for file in ./asm_valid/*.cor
do
	rm -rf $file
done;

#Generating zaz .cor files

for file in ./asm_valid/*.s
do
	./../ressources/vm_champs/asm $file 1>&- 2>&-
done;

#Stocking zaz hexdump

for file in ./asm_valid/*.cor
do
	hexdump -C $file > ./results/asm_valid/zaz_hexdump_`basename $file`
done


#This script, verify that we and zaz, both create a .cor file from the .s
#If its the case, then compare the hexdump of .cor generated and if there is no diff
#Then it considers the test as OK and not failed.

for file in ./asm_valid/*.s;
do
	echo $YELLOW"[TEST $TOTAL]: `basename $file`"$NC
	./../asm $file > ./results/asm_valid/our_output_`basename ${file/.s/.cor}` 
	./../ressources/vm_champs/asm $file 2>&1 > ./results/asm_valid/zaz_output_`basename ${file/.s/.cor}` 
	diff ./results/asm_valid/our_output_`basename ${file/.s/.cor}` ./results/asm_valid/zaz_output_`basename ${file/.s/.cor}` > ./results/asm_valid/diff_`basename ${file/.s/.cor}` 
	if [ "$?" = "$ZERO" ]; then
		echo "\nGenerating .cor file       $GREEN[OK]"$NC
		diff ./results/asm_valid/our_hexdump_`basename ${file/.s/.cor}` \
		./results/asm_valid/zaz_hexdump_`basename ${file/.s/.cor}` 2>&1 \
		> ./results/asm_valid/diff_hexdump_`basename ${file/.s/.cor}`
		if [ "$?" = "$ZERO" ]; then
			echo "Hexdump similar with zaz   $GREEN[OK]\n"$NC
			OK=$((OK+1))
		else
			echo "Hexdump similar with zaz   $RED[KO]\n"$NC
		fi
	else
		echo "\nGenerating .cor file $RED[KO]\n"$NC
		fi
	TOTAL=$((TOTAL+1))
done;

TOTAL=$((TOTAL-1))

echo "\n\n-------------------------\n"
echo $YELLOW"Results : $OK / $TOTAL\n"$NC

if  [ $OK != $TOTAL ]; then
	echo $RED"FAILED check details in ./results/asm_valid/\n" $NC
else
	echo $GREEN"PERFECT ✔" $NC
fi

#Clearing ./asm_valid to be ready for next use of the script

for file in ./asm_valid/*.cor
do
	rm -rf $file
done;
