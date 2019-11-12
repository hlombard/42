#!/bin/bash

make -C .. -s
mkdir -p ./results
mkdir -p ./results/instructions
rm -rf ./results/instructions/*
./instructions_tests/02_ld_test.sh
./instructions_tests/03_st_test.sh
./instructions_tests/04_add_test.sh
./instructions_tests/05_sub_test.sh
./instructions_tests/06_and_test.sh
./instructions_tests/07_or_test.sh
./instructions_tests/08_xor_test.sh
./instructions_tests/10_ldi_test.sh
./instructions_tests/11_sti_test.sh
./instructions_tests/12_fork_test.sh
./instructions_tests/13_lld_test.sh
./instructions_tests/14_lldi_test.sh
./instructions_tests/15_lfork_test.sh
./instructions_tests/16_aff_test.sh
