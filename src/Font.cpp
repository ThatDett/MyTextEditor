#include <iostream>
#include <unordered_map>

#include "GLAD/glad.h"
#include "glm.hpp"

#include "Font.hpp"

#define FontCheck(x) if (x){std::cout << "ERROR::FREETYTPE: Failed to load Glyph. Line: " << __LINE__ << " File: " << __FILE__ << std::endl;exit(EXIT_FAILURE);}

Font::Font(const char *filepath, unsigned int width, unsigned int height)
{
    FT_Library ft;
    FontCheck(FT_Init_FreeType(&ft));

    FT_Face face;
    FontCheck(FT_New_Face(ft, filepath, 0, &face));

    FontCheck(FT_Set_Pixel_Sizes(face, width, height));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    for (unsigned char c = 0; c < 255; ++c)
    {
        // load character glyph 
        FontCheck(FT_Load_Char(face, c, FT_LOAD_RENDER))

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Font::Font(const Font &other) :
    characters(other.characters)
{}