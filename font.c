#include "font.h"

FT_Bitmap loadBitmap(FT_Face face, wchar_t code) {
    int error = FT_Load_Glyph(face, FT_Get_Char_Index(face, code) , FT_LOAD_DEFAULT);
    if (error) perror("Load Glyph failed!");

   if(face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        if (error) perror("Get Glyph failed!");
    }
    FT_Bitmap bitmap = face->glyph->bitmap;
    return bitmap;
}

FT_Face initFont(int size) {
    FT_Library library;
    FT_Face face;

    int error = FT_Init_FreeType( &library );
    if ( error ) {
        perror("Can't init the library");
    };

    error = FT_New_Face( library, "./fonts/Hei.ttf", 0, &face );
    if ( error ) {
        perror("Can't find or open the file");
    };

    FT_Set_Pixel_Sizes(face, 0, size*16);

    if ( error == FT_Err_Unknown_File_Format ) {
    } else if ( error ) {
        perror("Can't read the file or the file is broken");
    }

    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

    return face;
}

void drawBitmap(FT_Bitmap *bitmap) {
    int width = bitmap->width;
    int rows = bitmap->rows;

    if (width%8 != 0) { 
        width += (8 - width%8);
    }
    if (rows%8 != 0) { 
        rows += (8 - rows%8);
    }

    int len = rows*width/8;
    GLubyte res[len];
    memset(res, 0, len*sizeof(GLubyte));

    printf("w: %d,h: %d\n", width, rows);

    char data;
    for(int j=0, t=0; j < rows; j++) {
        for(int i=0; i < width; i++) {
            if (i>= bitmap->width||j>=bitmap->rows) {
                data <<= 1;
            } else if (!(i%8)) {
                if ((char) bitmap->buffer[i+bitmap->width*(rows-j-1)] == '\0') {
                    data = 0;
                } else {
                    data = 1;
                }
            } else {
                if (bitmap->buffer[i+bitmap->width*(rows-j-1)] == '\0') {
                    data <<= 1;
                } else {
                    data <<= 1;
                    data |= 1;
                }
            }
            if ( i>6 && (i%8 == 7) ) {
                res[(j*rows + i)/8] = data;
            }
        }
    }
    glBitmap(width, rows, 0, 0, 0, -rows, res);
}

void drawFont(wchar_t* strText, long len) {
    FT_Face font = initFont(2);
    FT_Bitmap bitmap;
    for (int i=0; i<len; ++i) {
        bitmap = loadBitmap(font, strText[i]);
        drawBitmap(&bitmap);
    }
}

int next_p2 (int a ) {
    int rval=1;
    while(rval<a) rval<<=1;
    return rval;
}

void printBmp (FT_Bitmap bitmap) {
    int width = bitmap.width;
    int height = bitmap.rows;

    if ((width & 0x3) != 0) { 
        width += 4 - (width & 0x3); 
    } 
    
    int t = 0;
    char data;
    printf("%d\t%d \n", width,height);
    for(int j=0; j < height ; j++) {
        for(int i=0; i < width; i++) {
            data = (char) ((i>= bitmap.width||j>=bitmap.rows)?0:bitmap.buffer[i+bitmap.width*j]);
            // row j, col i
            if (t!=j) {
                printf("\n");
                t = j;
            }
            if (data == '\0') {
                printf("0");
            } else {
                //printf("%#x", data);
                printf("1");
            }
        }
    }
} 
