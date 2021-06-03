# KKSolver

Lightweight KenKen puzzle solver written in C.

## Build and Run

Cmake handles the building process, so here are the commands on Linux:

```shell
mkdir build
cd build
cmake ..
make
./bin/kksolver
```

## Problem definition

A KenKen puzzle is defined by first setting the location of all the groups of numbers on the grid. This is done by defining a `char` array, where each character represents a group. In our example, this is done with the lines:

```c
uint8_t grid_size = 6;

char grid[] = {
        'a', 'b', 'b', 'c', 'c', 'd',
        'a', 'e', 'c', 'c', 'f', 'd',
        'g', 'e', 'e', 'e', 'f', 'h',
        'i', 'j', 'j', 'k', 'l', 'h',
        'i', 'm', 'n', 'k', 'o', 'o',
        'm', 'm', 'm', 'p', 'p', 'o'
    };
```

Then we need to create a `BlockTable` struct and use the `blocktable_insert` function to define the operation and total result characterising the specific groups. For example, `blocktable_insert( p_block_table, 'c', 720, MUL)` means the product of all elements in group C equals 720.

Finally, we can create the `KenKen` struct, use `kenken_solve` to derive a solution and `kenken_print` to print it into the terminal
