#!/bin/bash

#This test makes the assumption that instructions ST and ZJMP work correctly.

# Need to test
# - Write in register
# - Modify the carry
# - Has restricted address for indirect parameters.

source $(dirname $0)/param.sh

echo "### TESTING LD ###"
test='02_ld'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh