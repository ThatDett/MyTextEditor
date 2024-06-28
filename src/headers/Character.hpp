#ifndef CHARACTER_H
#define CHARACTER_H

#include "glm.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

struct Character 
{
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    FT_Vector_ Advance;    // Offset to advance to next glyph
};

#endif