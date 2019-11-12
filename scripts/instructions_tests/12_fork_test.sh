#!/bin/bash

#This test makes the assumption that instructions LD and ZJMP work correctly.

# Need to test
# - Create a new process
# - Does not modify the carry
# - Has restricted address

source $(dirname $0)/param.sh

echo "### TESTING FORK ###"
test='12_fork'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh
