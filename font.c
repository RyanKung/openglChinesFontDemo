#include <ft2build.h>
#include FT_FREETYPE_H
#include <GLUT/glut.h>

FT_Face initFont(wchar_t*);
void setPixel(FT_Face, int, int);
FT_GlyphSlot loadGlyph(FT_Face, wchar_t);
int next_p2(int);


//Doc: http://www.freetype.org/freetype2/docs/tutorial/step1.html

FT_GlyphSlot loadGlyph(FT_Face face, wchar_t code) {
    int pen_x, pen_y, n;
    FT_UInt glyph_index = FT_Get_Char_Index(face, code);
    int error = FT_Load_Glyph(face,glyph_index ,0);
    if (error) perror("Load Glyph");
    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) perror("Render Glyph");
    return face->glyph;
}

FT_Face initFont() {
    FT_Library library;
    FT_Face face;
    int error = FT_Init_FreeType( &library );
    if ( error ) {
        perror("Can't find or open the file");
    };
    error = FT_New_Face( library, "./fonts/Hei.ttf", 0, &face );
    if ( error == FT_Err_Unknown_File_Format ) {
    } else if ( error ) {
        perror("Can't read the file or the file is broken");
    }
    return face;
}


void setPixel(FT_Face face, int width, int height) {
    int horizReso = 300,
        vertiReso = 300;
    if (FT_Set_Char_Size(face, width, height, horizReso, vertiReso))
        perror("Set piex failed");
}

int next_p2 (int a )
{
    int rval=1;
    while(rval<a) rval<<=1;
    return rval;
}

GLubyte FT_Bitmap2GLubyte(FT_Bitmap bitmap) {
    int height, width;
    width = next_p2( bitmap.width );
    height = next_p2( bitmap.rows );
    GLubyte data[width*height];
    memset(data, 0, height*width*sizeof(GLubyte));
    for(int j=0; j<height; ++j) {
        for(int i=0; i<width; ++i ){ 
            data[ j*width + i ] = 
                (j >= bitmap.rows || i >= bitmap.width ? 
                 0 : bitmap.buffer[ j*bitmap.width + i ]);
        }
    }
    return *data;
}

void drawFont(wchar_t* strText) {
    strText[] = L"中华人民共和国";
    FT_Face font = initFont();
    FT_GlyphSlot slot;
    FT_Bitmap* bitmap;
    
    setPixel(font, 0, 16*64);
    for (int i=0; i<sizeof(strText)/sizeof(wchar_t); ++i) {
        slot = loadGlyph(font, strText[i]);
        bitmap = &(slot->bitmap);
        GLubyte data = FT_Bitmap2GLubyte(*bitmap);
        glBitmap(64, 64 ,0,0,64,0, &data);
    }
}
