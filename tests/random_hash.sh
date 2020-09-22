#!/bin/bash


DEFAULT='\033[0m'
RED='\033[00;31m'
GREEN='\033[00;32m'
YELLOW='\033[00;33m'
BLUE='\033[00;34m'
PURPLE='\033[00;35m'
CYAN='\033[00;36m'
LIGHTGRAY='\033[00;37m'

n=1
ok=0
ko=0
chars=0
file="loremipsum.txt"
file_to_hash="file_to_hash.txt"
logs="./logs"
algos=(md5 sha256 sha224 sha512 sha384)

	#FUNCS
function printResult() {
	if [ "$2" == "$3" ]; then
		printf "\t $CYAN $1 $DEFAULT: $GREEN Valid $DEFAULT \n"
		((ok+=1))
	else
		printf "\t $CYAN $1 $DEFAULT: $RED Invalid $DEFAULT\n"
		printf "\t\tft_ssl  output: %s\n" "$2"
		printf "\t\topenssl output: %s\n" "$3"
		((ko+=1))
	fi
}

function printLogs() {
	printf "STRING TO HASH: [%s]\n\n" "$5" > $logs/logs_test$4_$1.txt
	printf "ft_ssl output:  [%s]\n" "$3" >> $logs/logs_test$4_$1.txt
	printf "openssl output: [%s]\n" "$2" >> $logs/logs_test$4_$1.txt
}

	#SCRIPT
rm -f $logs/*
mkdir -p $logs
for (( i=1; i <= 50; i++))
do
	((chars+= $RANDOM % 255))
	string_to_hash=$(head -c $chars $file)
	echo -n $string_to_hash > $file_to_hash
	printf "Test [$YELLOW$n$DEFAULT]:\n"
	for algo in "${algos[@]}";
	do
		output_openssl=$(openssl $algo $file_to_hash | cut -d ' ' -f2)
		output_ft_ssl=$(../ft_ssl $algo $file_to_hash | cut -d ' ' -f4)
		#echo $string_to_hash
		printLogs $algo $output_openssl $output_ft_ssl $n "$string_to_hash"
		printResult $algo $output_ft_ssl $output_openssl
	done
	((n+=1))
	rm $file_to_hash
done
total=$(($ok+$ko))
printf "\n$PURPLE Valid tests: %d / %d $DEFAULT \n\n" $ok $total
printf "Every tests logs available here: $logs/\n"
