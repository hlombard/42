#!/bin/bash

#This test makes the assumption that instructions LD, AND and ZJMP work correctly.

# Need to test
# - Write in register
# - Write on memory (positive and negative value)
# - Modify the carry
# - Has restricted address

source $(dirname $0)/param.sh

echo "### TESTING ST ###"
test='03_st'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh