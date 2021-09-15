# KKSolver

Lightweight KenKen puzzle solver written in C++.

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
size_t grid_size = 6;

char grid[] = {
    'a', 'b', 'b', 'c', 'd', 'd',
    'a', 'e', 'e', 'c', 'f', 'd',
    'g', 'g', 'h', 'h', 'f', 'd',
    'g', 'g', 'i', 'j', 'k', 'k',
    'l', 'l', 'i', 'j', 'j', 'm',
    'n', 'n', 'n', 'o', 'o', 'm'
};
```

Then we need to create a `BlockTable` variable to define the operation and total result characterising the specific groups. For example, `Block{'c', 20, MUL}` means the product of all elements in group C equals 20.

Finally, we can create a `KenKen` instance, use the `solve` method to derive a solution and the `print_values` method to output the answer to the terminal.