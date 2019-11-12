#!/bin/bash

#This test makes the assumption that instructions LD, ST and ZJMP work correctly.

# Need to test
# - Write in register
# - Modify the carry
# - Has unrestricted address for indirect parameters.

source $(dirname $0)/param.sh

echo "### TESTING LLD ###"
test='13_lld'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh