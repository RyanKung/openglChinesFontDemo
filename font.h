#ifndef FONT_H
#define FONT_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <GLUT/glut.h>

void printBmp(FT_Bitmap);
FT_Face initFont(int);
void setPixel(FT_Face, int, int);
FT_Bitmap loadBitmap(FT_Face, wchar_t);
void drawBitmap(FT_Bitmap*);
int next_p2(int);
void drawFont(wchar_t*, long);
#endif
