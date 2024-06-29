#ifndef FONT_H
#define FONT_H
    
#include <unordered_map>

#include "Character.hpp"

class Font
{
public:
    Font(const char *filepath, unsigned int width, unsigned int height);
    Font(const Font &other);

    unsigned int Height();
public:
    std::unordered_map<char, Character> characters;
    std::string filepath;

private:
    unsigned int m_height;
};
#endif