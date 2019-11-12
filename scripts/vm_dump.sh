#!/bin/bash

YELLOW='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
TOTAL=1
OK=0
ZERO=0


make -C .. -s
mkdir -p ./results
mkdir -p ./results/vm_dump
rm -rf ./results/vm_dump/*


echo "Which cycle to compare ? "
read CYCLE

for file in ./champions/*.cor;
do
	echo $YELLOW"[TEST $TOTAL]: Comparing `basename $file` at cycle $CYCLE"$NC
	./../corewar $file -dump $CYCLE 1>&- > ./results/vm_dump/our_output_$TOTAL
	./../ressources/vm_champs/corewar $file -d $CYCLE 2>&- > ./results/vm_dump/zaz_output_$TOTAL
	diff ./results/vm_dump/our_output_$TOTAL ./results/vm_dump/zaz_output_$TOTAL > ./results/vm_dump/diff_$TOTAL
	if [ "$?" = "$ZERO" ]; then
		echo $GREEN"[OK]\n"$NC
		OK=$((OK+1))
	else
		echo $RED"[KO]\n"$NC
		echo "Check details ? Y/n "
		read ANSWER
		if [ "$ANSWER" = "Y" ] ; then
			clear
			cat ./results/vm_dump/diff_$TOTAL
			echo "\n\nContinue tests ? Y/n"
			read ANSWER
			if [ "$ANSWER" != "Y" ] ; then
				TOTAL=$((TOTAL+1))
				break;
			fi
		fi
	fi
	TOTAL=$((TOTAL+1))
done;

TOTAL=$((TOTAL-1))

echo "\n\n-------------------------\n"
echo "Results : $OK / $TOTAL\n"

if  [ $OK != $TOTAL ]; then
	echo $RED"FAILED check details in ./results/vm_dump/\n" $NC
else
	echo $GREEN"PERFECT ✔" $NC
fi
