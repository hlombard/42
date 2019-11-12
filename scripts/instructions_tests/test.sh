#!/bin/bash

./../../asm champions_instructions/${test}_champ.s
./../corewar -dump ${n_dump} champions_instructions/${test}_champ.cor > results/instructions/${test}_result.txt
./../ressources/vm_champs/corewar -d ${n_dump} champions_instructions/${test}_champ.cor > results/instructions/${test}_zaz.txt
diff ./results/instructions/${test}_result.txt ./results/instructions/${test}_zaz.txt
result=$?
