#!/bin/bash

if [[ $result -eq 0 ]]
then
	echo -e "Result: [${GREEN}OK${NC}]"
else
	echo -e "Result: [${RED}ERROR${NC}]"
fi
echo -e -n '\n'