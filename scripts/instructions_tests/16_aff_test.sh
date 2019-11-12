#!/bin/bash

#This test makes the assumption that instructions LD, ST and ZJMP work correctly.

# Need to test
# - Print the right ascii character on the std output.
# - The character is modulo 256.

source $(dirname $0)/param.sh

echo "### TESTING AFF ###"
test='16_aff'
source $(dirname $0)/test.sh

source $(dirname $0)/result.sh