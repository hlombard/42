#!/bin/bash

#This test makes the assumption that instructions LD and ZJMP work correctly.

# Need to test
# - Write on memory (positive and negative value)
# - All combination of arg2(RG/ID/D2) and arg3(ID/D2)
# - Does not modify the carry
# - Has restricted address

source $(dirname $0)/param.sh

echo "### TESTING LDI ###"
test='10_ldi'
source $(dirname $0)/test.sh
source $(dirname $0)/result.sh
