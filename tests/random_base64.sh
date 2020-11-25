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
file_to_encode="file_to_encode.txt"
logs="./logs"

function printResult() {
	if [ "$1" == "$2" ]; then
		printf "\t$3:$GREEN Valid $DEFAULT \n"
		((ok+=1))
	else
		printf "\t$3:$RED Invalid $DEFAULT\n"
		printf "\t\tft_ssl  output: [%s]\n" "$1"
		printf "\t\topenssl output: [%s]\n" "$2"
		((ko+=1))
	fi
}

function printLogs() {
	printf "String to $5: [%s]\n\n" "$4" > $logs/logs_test"$3"_b64_$5.txt
	printf "ft_ssl output:  [%s]\n\n" "$2" >> $logs/logs_test"$3"_b64_$5.txt
	printf "openssl output: [%s]\n" "$1" >> $logs/logs_test"$3"_b64_$5.txt
}

	#SCRIPT
rm -f $logs/*
mkdir -p $logs
for (( i=1; i <= 50; i++))
do
	((chars+= $RANDOM % 255))
	string_to_encode=$(head -c $chars $file)
	printf "Test [$YELLOW$n$DEFAULT]:\n"

	#ENCODE
	output_openssl="$(echo "$string_to_encode" | openssl base64)"
	output_ft_ssl="$(echo "$string_to_encode" | ../ft_ssl base64)"
	printLogs "$output_openssl" "$output_ft_ssl" $n "$string_to_encode" "Encode"
	printResult "$output_ft_ssl" "$output_openssl" "Encode"

	#DECODE
	string_to_decode="$output_openssl"
	output_openssl="$(echo "$string_to_decode" | openssl base64 -d)"
	output_ft_ssl="$(echo "$string_to_decode" | ../ft_ssl base64 -d)"
	printLogs "$output_openssl" "$output_ft_ssl" $n "$string_to_decode" "Decode"
	printResult "$output_ft_ssl" "$output_openssl" "Decode"
	((n+=1))
done
total=$(($ok+$ko))
printf "\n$PURPLE Valid tests: %d / %d $DEFAULT \n\n" $ok $total
printf "Every tests logs available here: $logs/\n"
