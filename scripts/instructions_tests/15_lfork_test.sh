#!/bin/bash

#This test makes the assumption that instructions LD, ST and ZJMP work correctly.

# Need to test
# - Write on memory (positive and negative value)
# - All combination of arg2(RG/ID/D2) and arg3(ID/D2)
# - Modify the carry
# - Has unrestricted address for indirect parameters.

source $(dirname $0)/param.sh

echo "### TESTING LFORK ###"
test='15_lfork'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh