#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <ft2build.h>
#include FT_FREETYPE_H


void initGL(int, char**);
void initView();
void mainViewController();
FT_Face initFont();
void setPixel(FT_Face, int, int);
void loadGlyph(FT_Face);

int main(int argc, char** argv) {
    FT_Face font = initFont();
    setPixel(font, 0, 16*64);
    initGL(argc, argv);
    loadGlyph(font);
    glutDisplayFunc(mainViewController);
    glutMainLoop();
    return 0;
}

//Doc: http://www.freetype.org/freetype2/docs/tutorial/step1.html

void loadGlyph(FT_Face face) {
    int error = FT_Load_Glyph(face,1 ,0);

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

void initGL(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 550);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("runes");
}

void initView() {
    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

void mainViewController() {
    initView();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, .8, 1.0);
    //draw ply
    glBegin(GL_POLYGON);
    glVertex3f(0.25, .25, .0);
    glVertex3f(0.75, .75, .0);
    glVertex3f(.75, .85, .0);
    glEnd();
    glFlush();
    
}

