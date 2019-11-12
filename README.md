# Corewar

C implementation of the Core War Game

## 1: The Virtual Machine



This is the main part of the project:



The Virtual Machine will create a memory space dedicated to the players (called the arena).

It will host multiple ``champions`` and allow them to fight against each other in a fair way.

It has multiple functions:



- Receiving ``.cor`` files (champions);

- Loading each champion in the arena;

- Reading the byte codes of each champion, cycle after cycle, interpreting and running instructions if they are still valid (champions can overwrite each other and corrupt their code).


<h4 align = "center">This is how a game looks when the ncurse output ( -visu ) is set:</h4>
<p align="center">
<img align="center" src="https://media.giphy.com/media/MBwnDQYj8EMTMgzLdx/giphy.gif" >
</p>





- Terminating the game when all the processes are dead. The winner is the last player reported to be alive;



## 2: The Champions



Champions have 3 main objectives:
- To make sure its player is reported alive;
- To understand the meaning of life;
- To eradicate its opponents;


They consist in: a name, a comment and a set of instructions.

<h4 align="center">As an example, this is a very basic champion (usually a champion has arround 150 lines of assembly code) : </h4>

<p align="center">
<img src="https://i.imgur.com/D78rgTB.png">
</p


Please check the project ``man`` page to get the list of the different instructions available and their parameters:

``man ./corewar.man``


## 3: The Assembler

The assembler will compile a champion into a byte code that will be stored in a `.cor` file.

<h4 align="center">In the above champion example, it will be modified into:</h4>

<p align="center">
<img src="https://i.imgur.com/PH5KJ2B.png">
</p>



  ### Disassembler:

It works the other way around, creates a  ``champion.s`` file from a ``champion.cor``
It reconstitutes a champion into a readeable state, revealing his labels and instructions, namely his strategy.

```./disassembler <file_name.cor>```


## Installation



``` git clone --single-branch --branch Corewar https://github.com/hlombard/42.git hlombard_Corewar ```




## Compiling and running




Run `make` to create the executable for the Assembler, Virtual Machine and Disassembler.



Once all the executables are created :

- Assemble a champion:  `` ./asm <file_name.s> ``
- Start a game: `` ./corewar [-n N] [-dump N] [-v N] [-visu] [--stealth] [-a] <file_name.cor> ... ``
```
  -n N - Assign order N to next champion, default is : first champ is first to play;
  -dump N - Dumps memory after N cycles then exits;
  -v - Verbosity levels (Binary mask, use 31 to set everything on)
    - 0 : Show only essentials
    - 1 : Show lives
    - 2 : Show cycles
    - 4 : Show operations (Params are NOT litteral ...)
    - 8 : Show deaths
    - 16 : Show PC movements (Except for jumps);
  -visu - Ncurses output mode;
  -stealth - Competition mode, hide champions code with ncurse;
  -a - Prints output from "aff".
  ```
Check the ``man`` page for more info: **man ./corewar.man**

**This project was made with [ratin](https://github.com/ratin42), [syzhang](https://github.com/syzhang16) and [gly](https://github.com/gokily).**
