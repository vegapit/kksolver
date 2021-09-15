#include "block.hpp"
#include "kenken.hpp"

#include <iostream>
#include <vector>

Kenken::Kenken(size_t _grid_size, char * _grid, BlockTable _blocktable) {
    grid_size = _grid_size;
    grid = _grid;
    blocktable = _blocktable;
    for (size_t i = 0; i < _grid_size * _grid_size; i++)
        values.push_back(0);
}

char Kenken::get_grid(size_t i, size_t j) {
    return grid[j*grid_size + i];
}

unsigned int Kenken::get_value(size_t i, size_t j) {
    return values[j*grid_size + i];
}

void Kenken::set_value(size_t i, size_t j, unsigned int val) {
    values[j*grid_size + i] = val;
}

bool Kenken::is_complete() {
    bool res = true;
    for (unsigned int val: values)
        if (val == 0) {
            res = false;
            break;
        }
    return res;
}

bool Kenken::check_block(char key) {
    std::vector<unsigned int> block_values;
    size_t matches = 0;
    for(size_t i = 0; i < grid_size; i++) {
        for(size_t j = 0; j < grid_size; j++) {
            if( get_grid(i, j) == key ) {
                matches++;
                unsigned int val = get_value(i, j);
                if( val > 0 )
                    block_values.push_back( val );
            }
        }
    }
    if( matches != block_values.size() ) { // If block is not full, assume it is valid
        return true;
    }
    Block block = get_block(blocktable, key);
    if (block.op == ADD) {
        int sum = 0;
        for (unsigned int val : block_values)
            sum += val;
        return (sum == block.res);
    }
    else if (block.op == MUL) {
        int prod = 1;
        for (unsigned int val : block_values)
            prod *= val;
        return (prod == block.res);
    }
    else if (block.op == SUB) {
        if (block_values[0] > block_values[1])
            return (block.res == block_values[0] - block_values[1]);
        else
            return (block.res == block_values[1] - block_values[0]);
    }
    else { // Must be a DIV operation
        if ((block_values[0] > block_values[1]) && (block_values[1] > 0))
            return ((block.res == block_values[0] / block_values[1]) && (block_values[0] % block_values[1] == 0));
        else if ((block_values[1] > block_values[0]) && (block_values[0] > 0))
            return ((block.res == block_values[1] / block_values[0]) && (block_values[1] % block_values[0] == 0));
        else
            return true;
    }
}

bool Kenken::check_col(size_t col) {
    for(size_t i = 0; i < grid_size; i++) {
        int val = get_value(i, col);
        if(val == 0) {
            continue; // Ignore all zero values
        } else {
            for(size_t k = i + 1; k < grid_size; k++)
                if( get_value(k, col) == val )
                    return false;
        }
    }
    return true;
}

bool Kenken::check_row(size_t row) {
    for(size_t j = 0; j < grid_size; j++) {
        size_t val = get_value(row, j);
        if(val == 0) {
            continue; // Ignore all zero values
        } else {
            for(size_t k = j + 1; k < grid_size; k++)
                if( get_value(row, k) == val )
                    return false;
        }
    }
    return true;
}

bool Kenken::check_values() {
    // Check Blocks
    for(Block block : blocktable)
        if(!check_block(block.key))
            return false;
    // Check Rows and Columns
    for(size_t k = 0; k < grid_size; k++) {
        if(!check_row(k)) { return false; }
        if(!check_col(k)) { return false; }
    }
    return true;
}

void Kenken::print_values() {
    for(size_t j = 0; j < grid_size; j++) {
        std::cout << "[";
        for(size_t i = 0; i < grid_size; i++) {
            std::cout << get_value(i, j);
            if( i < grid_size - 1 )
                std::cout << ", ";
            else
                std::cout << "]";
        }
        std::cout << std::endl;
    }
}

void Kenken::print_grid() {
    for(size_t j = 0; j < grid_size; j++) {
        std::cout << "[";
        for(size_t i = 0; i < grid_size; i++) {
            std::cout << get_grid(i, j);
            if( i < grid_size - 1 )
                std::cout << ", ";
            else
                std::cout << "]";
        }
        std::cout << std::endl;
    }
}

bool Kenken::solve() {
    for(size_t j = 0; j < grid_size; j++) {
        for(size_t i = 0; i < grid_size; i++) {
            if( get_value(i, j) == 0) {
                for(unsigned int val = 1; val <= grid_size; val++) {
                    set_value(i, j, val);
                    if( check_values() ) {
                        if( is_complete() ) {
                            return true;
                        } else {
                            if( solve() )
                                return true;
                            else
                                set_value(i, j, 0);
                        }
                    } else
                        set_value(i, j, 0);
                }
                return false;
            }
        }
    }
    return true;
}