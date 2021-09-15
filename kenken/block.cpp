#include "block.hpp"

#include <stdexcept>

Block get_block(const BlockTable& blocktable, char key) {
    for(Block b : blocktable) {
        if(b.key == key)
            return b;
    }
    throw std::runtime_error("Block not found");
}