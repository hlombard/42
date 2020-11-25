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
file_to_encrypt="file_to_encrypt.txt"
logs="./logs"
algos=(ecb cbc cfb)

function printResult() {
	if [ "$1" == "$2" ]; then
		printf "\t$3 des-$4 :$GREEN Valid $DEFAULT \n"
		((ok+=1))
	else
		printf "\t$3 des-$4 :$RED Invalid $DEFAULT\n"
		printf "\t\tft_ssl  output: [%s]\n" "$1"
		printf "\t\topenssl output: [%s]\n" "$2"
		((ko+=1))
	fi
}

function printLogs() {
	printf "String to $5: [%s]\n\n" "$4" > $logs/logs_test"$3"_des-$6_$5.txt
	printf "ft_ssl output:  [%s]\n\n" "$2" >> $logs/logs_test"$3"_des-$6_$5.txt
	printf "openssl output: [%s]\n" "$1" >> $logs/logs_test"$3"_des-$6_$5.txt
}

	#SCRIPT
rm -f $logs/*
mkdir -p $logs
echo "Enter salt value (IN HEX): "
read salt
echo "Enter IV"
read IV
echo "Enter a password: "
read password
echo ""

#LOOP NB TESTS
for (( i=1; i <= 25; i++))
do
	((chars+= $RANDOM % 255))
	string_to_encrypt=$(head -c $chars $file)
	echo -n $string_to_encrypt > $file_to_encrypt
	printf "Test [$YELLOW$n$DEFAULT]:\n"

	#LOOP EVERY ALGOS
	for algo in "${algos[@]}";
	do
		#ENCRYPT
		openssl des-$algo -md md5 -S "$salt" -pass "pass:$password" -iv $IV -in "$file_to_encrypt" -out "openssl.enc" 2>/dev/null
		../ft_ssl des-$algo -s "$salt" -p "$password" -v $IV -i "$file_to_encrypt" -o "ft_ssl.enc" 2>/dev/null
		output_openssl=$(tr -d '\0' < openssl.enc)
		output_ft_ssl=$(tr -d '\0' < ft_ssl.enc)
		printLogs "$output_openssl" "$output_ft_ssl" $n "$string_to_encrypt" "Encrypt" $algo
		printResult "$output_ft_ssl" "$output_openssl" "Encrypt" $algo

		#DECRYPT
		openssl des-$algo -md md5 -S $salt -pass "pass:$password" -iv $IV -d -in "openssl.enc" -out "openssl.dec" 2>/dev/null
		../ft_ssl des-$algo -s $salt -p $password -v "$IV" -d -i "ft_ssl.enc" -o "ft_ssl.dec"

		string_to_decrypt=$(tr -d '\0' < openssl.enc)
		output_openssl=$(tr -d '\0' < openssl.dec)
		output_ft_ssl=$(tr -d '\0' < ft_ssl.dec)
		printLogs "$output_openssl" "$output_ft_ssl" $n "$string_to_decrypt" "Decrypt" $algo
		printResult "$output_ft_ssl" "$output_openssl" "Decrypt" $algo

		echo ""
		#CLEAN
		rm *.enc
		rm *.dec
	done
	((n+=1))
	rm $file_to_encrypt
done
total=$(($ok+$ko))
printf "\n$PURPLE Valid tests: %d / %d $DEFAULT \n\n" $ok $total
printf "Every tests logs available here: $logs/\n"
