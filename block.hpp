#ifndef BLOCK_HPP
#define BLOCK_HPP

#define BlockType            char
#define BLOCK_UNDEFINED     (0<<0)
#define BLOCK_TERMINATOR    (1<<0)
#define BLOCK_PROCESS       (1<<1)
#define BLOCK_CONDITION     (1<<2)
#define BLOCK_IO            (1<<3)

struct Block
{
    std::string label;

    BlockType type = BLOCK_UNDEFINED;
};

#endif