#ifndef FREE_TYPE_LIB_HPP
# define FREE_TYPE_LIB_HPP

#include <string>
#include <functional>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Vect.hpp"
#include <iostream>

class Display;

class FreeTypeLib
{
private:
  FT_Library library;
  FT_Face face;
  char badPadding[8];
public:
  FreeTypeLib(std::string fontFile);
  FreeTypeLib(FreeTypeLib const &) = delete;
  ~FreeTypeLib();

  template<class A>
  void renderText(std::string text, A renderBuffer, unsigned int size, Vect<2u, float> step)
  {
    FT_Set_Pixel_Sizes(face, 0, size);
    Vect<2u, float> pen(0.0f, 0.0f);

    for (auto it(text.begin()); it != text.end(); ++it)
      {
	FT_GlyphSlot &slot(face->glyph);
	FT_Load_Char(face, static_cast<FT_ULong>(*it), FT_LOAD_RENDER);
    	renderBuffer((pen + Vect<2u, float>{static_cast<float>(slot->bitmap_left), static_cast<float>(slot->bitmap_top)}) * step / static_cast<float>(size),
		     Vect<2u, float>{static_cast<float>(slot->bitmap.pitch), static_cast<float>(slot->bitmap.rows)} * step / static_cast<float>(size),
		     slot->bitmap.buffer, {static_cast<int>(slot->bitmap.pitch), static_cast<int>(slot->bitmap.rows)});
	pen[0] += static_cast<float>(face->glyph->advance.x >> 6u);
      }
  }
};

#endif
