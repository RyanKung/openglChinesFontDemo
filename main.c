#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void initGL(int, char**);
void initView();
void mainViewController();

int main(int argc, char** argv) {
    initGL(argc, argv);
    glutDisplayFunc(mainViewController);
    glutMainLoop();
    return 0;
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

