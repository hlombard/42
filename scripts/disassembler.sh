#!/bin/bash

YELLOW='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
TOTAL=1
OK=0
ZERO=0
NB=0

#Making sure that binaries are ready, and clearing results folder

make .. -s
mkdir -p ./results
mkdir -p ./results/disassembler
rm -rf ./results/disassembler/*


#Make a copy of originals .s files and assemble them with zaz asm

for file in ./asm_valid/*.s
do
	cp $file $file.original
	./../ressources/vm_champs/asm $file 2>&1 1>&-
done;

#Stock hexdump of zaz .cor

for file in ./asm_valid/*.cor;
do
	hexdump -C $file > ./results/disassembler/original_hexdump_`basename $file`
done;

#Delete all .s files (not the .s.original)

for file in ./asm_valid/*.s
do
	rm -rf $file
done

#Disassemble zaz .cor into a .s file and delete the .cor 1 by 1

for file in ./asm_valid/*.cor
do
	./../disassembler $file 2>&- 1>&-
	rm -rf $file
done;

#Reassemble with zaz asm and create .cor files

for file in ./asm_valid/*.s
do
	./../ressources/vm_champs/asm $file 2>&- 1>&-
	rm -rf $file
done;

#Stocking output from new .cor file made from a disassemble .cor file

for file in ./asm_valid/*.cor
do
	hexdump -C $file > ./results/disassembler/our_hexdump_`basename $file`
	rm -rf $file
done;

#Restoring asm_valid folder back to original

for file in ./asm_valid/*.s.original
do
	mv "$file" "${file/.s.original/.s}"
done;

#This script compare originals .cor hexdump with new ones
#If no diff then the test is considered OK and not failed

for file in ./asm_valid/*
do
	echo $YELLOW"[TEST $TOTAL]: `basename ${file/.s/\/}`"$NC
	diff ./results/disassembler/our_hexdump_`basename ${file/.s/.cor}` ./results/disassembler/original_hexdump_`basename ${file/.s/.cor}` > ./results/disassembler/diff_`basename $file`
	if [ "$?" = "$ZERO" ];then
		echo "\nHexdump of original similar to disassembled one  $GREEN[OK]\n\n"$NC
		OK=$((OK+1))
	else
		echo "\nHexdump of original similar to disassembled one  $RED[KO]\n\n"$NC
	fi
		NB=$((NB + 1))
done;

echo "\n\n-------------------------\n"
echo "Results : $OK / $NB\n"

if  [ $OK != $NB ]; then
	echo $RED"FAILED check details in ./results/disassembler/\n" $NC
else
	echo $GREEN"PERFECT ✔" $NC
fi
