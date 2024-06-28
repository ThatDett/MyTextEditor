#ifndef FONT_H
#define FONT_H
    
#include <unordered_map>

#include "Character.hpp"

class Font
{
public:
    Font(const char *filepath, unsigned int width, unsigned int height);

    std::unordered_map<char, Character> Characters;
};
#endif