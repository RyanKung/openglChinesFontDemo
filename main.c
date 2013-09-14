#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

int next_p2(int);
void initGLUT(int, char**);
void initView();
void drawFont();
void reshape(int, int);
void mainViewController();
FT_Face initFont();
void setPixel(FT_Face, int, int);
FT_GlyphSlot loadGlyph(FT_Face, wchar_t);

int main(int argc, char** argv) {
    initGLUT(argc, argv);
    glutDisplayFunc(mainViewController);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

//Doc: http://www.freetype.org/freetype2/docs/tutorial/step1.html

FT_GlyphSlot loadGlyph(FT_Face face, wchar_t code) {
    FT_GlyphSlot slot = face->glyph;
    int pen_x, pen_y, n;
    FT_UInt glyph_index = FT_Get_Char_Index(face, code);
    int error = FT_Load_Glyph(face,glyph_index ,0);
    if (error) perror("Load Glyph");
    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) perror("Render Glyph");
    return slot;
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

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0, h, -1.0, 1.0);
    //gluOrtho2D(0,1,0,1);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}


void setPixel(FT_Face face, int width, int height) {
    int horizReso = 300,
        vertiReso = 300;
    if (FT_Set_Char_Size(face, width, height, horizReso, vertiReso))
        perror("Set piex failed");
}

void initGLUT(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 550);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("runes");
    initView();
}

void initView() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0,0,0,0);
    //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

void mainViewController() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glRasterPos2f(20,250);
    drawFont();
    glFlush(); 
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
    GLubyte data[width*height*2];
    memset(data, 0, height*width*sizeof(GLubyte));
    
    for(int j=0; j <height;j++) {
        for(int i=0; i < width; i++){ 
            data[2*(i+j*width)]= data[2*(i+j*width)+1] =
                (i>=bitmap.width || j>=bitmap.rows) ?
                0 : bitmap.buffer[i + bitmap.width*j];
        }
    }
    return *data;
}

void drawFont() {
    wchar_t strText[] = L"中华人民共和国";
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

