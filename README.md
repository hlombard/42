# Push_Swap

**This is a sorting algorithm project.**

We have 2 stacks called Stack A and Stack B, when the program starts, all the numbers given in parameters are stored in Stack A.

The goal is to sort Stack A from biggest to smallest using the Stack B and a limited set of instructions.

## Instructions

**sa : swap a** - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).

**sb : swap b** - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).

**ss : sa and sb at the same time**.

**pa : push a** - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.

**pb : push b** - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.

**ra : rotate a** - shift up all elements of stack a by 1. The first element becomes the last one.

**rb : rotate b** - shift up all elements of stack b by 1. The first element becomes the last one.

**rr : ra and rb at the same time.**

**rra : reverse rotate a** - shift down all elements of stack a by 1. The last element becomes the first one.

**rrb : reverse rotate b** - shift down all elements of stack b by 1. The last element becomes the first one.

**rrr : rra and rrb at the same time.**

## Installation

``` git clone --single-branch --branch push_swap https://github.com/hlombard/42.git hlombard_ps ```

## Compiling and running

Run `make`

Once executables are created : `ARG="<list of numbers (no duplicates)>"; ./push_swap $ARG | ./checker $ARG`

## Compatibility

Developed on macOS X.
