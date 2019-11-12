#!/bin/bash

#This test makes the assumption that instructions LD, ST and ZJMP work correctly.

# Need to test
# - All the combination of parameters
# - Modify the carry
# - Has restricted address

source $(dirname $0)/param.sh

echo "### TESTING AND ###"
test='06_and'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh

