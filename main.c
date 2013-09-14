#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void initGLUT(int, char**);
void initView();
void reshape(int, int);
void mainViewController();


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
    //gluOrtho2D(0,1,0,1);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
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
    glFlush(); 
}


