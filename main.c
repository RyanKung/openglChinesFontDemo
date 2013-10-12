#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "font.h"

void initGLUT(int, char**);
void initView();
void reshape(int, int);
void mainViewController();
long wcharLen(wchar_t*);


int main(int argc, char** argv) {
    initGLUT(argc, argv);
    glutDisplayFunc(mainViewController);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void initGLUT(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 550);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("runes");
    initView();
}

void initView() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(1,1,1,0);
}

void mainViewController() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glRasterPos2f(300,400);
    wchar_t *text = L"永和九年，岁在葵丑。";
    long len = wcharLen(text);
    drawFont(text, len);
    glFlush(); 
}

long wcharLen(wchar_t* str) {
    int i= 0;
    while(str[i]!='\0') {
        i++;
    }
    return i;
}
