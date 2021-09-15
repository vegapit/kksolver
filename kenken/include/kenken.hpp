#ifndef KENKEN_HPP
#define KENKEN_HPP

#include "block.hpp"

class Kenken {
    private:
        size_t grid_size;
        char* grid;
        BlockTable blocktable;
        std::vector<unsigned int> values;

        char get_grid(size_t i, size_t j);
        unsigned int get_value(size_t i, size_t j);
        void set_value(size_t i, size_t j, unsigned int val);
        bool is_complete();
        bool check_block(char key);
        bool check_row(size_t row);
        bool check_col(size_t col);
        bool check_values();

    public:
        Kenken(size_t grid_size, char* grid, BlockTable blocktable);
        void print_values();
        void print_grid();
        bool solve();
};

#endif