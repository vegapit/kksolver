#include "block.hpp"
#include "kenken.hpp"

int main() {
    
    size_t grid_size = 6;
    
    char grid[] = {
        'a', 'b', 'b', 'c', 'd', 'd',
        'a', 'e', 'e', 'c', 'f', 'd',
        'g', 'g', 'h', 'h', 'f', 'd',
        'g', 'g', 'i', 'j', 'k', 'k',
        'l', 'l', 'i', 'j', 'j', 'm',
        'n', 'n', 'n', 'o', 'o', 'm'
    };

    BlockTable blocktable = {
        Block{'a', 11, ADD},
        Block{'b', 2, DIV},
        Block{'c', 20, MUL},
        Block{'d', 6, MUL},
        Block{'e', 3, SUB},
        Block{'f', 3, DIV},
        Block{'g', 240, MUL},
        Block{'h', 6, MUL},
        Block{'i', 6, MUL},
        Block{'j', 7, ADD},
        Block{'k', 30, MUL},
        Block{'l', 6, MUL},
        Block{'m', 9, ADD},
        Block{'n', 8, ADD},
        Block{'o', 2, DIV}
    };
 
    Kenken kenken(grid_size, grid, blocktable);
    kenken.solve();
    kenken.print_values();

    return 0;
}