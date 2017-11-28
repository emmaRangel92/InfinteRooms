

/*
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdio>
#else
#include "glew.h"
#include "freeglut.h"
#include <stdio.h>
#include <math.h>
#endif


// COPY FROM THIS

#define CREATE 1
#define DELETE 2
#define MODIFY 3



// menu status
int menuFlag = 0;

float rotationY;

// -----------------------------------
//             MENUS
// -----------------------------------

void processMenuStatus(int status, int x, int y) {
    
    if (status == GLUT_MENU_IN_USE)
        menuFlag = 1;
    else
        menuFlag = 0;
}

void processMenu(int option) {
    
    switch (option) {
        case CREATE : break;
        case DELETE : break;
        case MODIFY :break;
    }
}
// -----------------------------------
//             Object Selection
// -----------------------------------
void onMouse(int button, int state, int x, int y) {
    if(state != GLUT_DOWN)
        return;
    
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    
    GLbyte color[4];
    GLfloat depth;
    GLuint index;
    
    glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    
    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
           x, y, color[0], color[1], color[2], color[3], depth, index);
}

void createPopupMenus() {
    
    int menu;
    menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Create",CREATE);
    glutAddMenuEntry("Delete",DELETE);
    glutAddMenuEntry("Modify",MODIFY);
    
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // this will allow us to know if the menu is active
    glutMenuStatusFunc(processMenuStatus);
}


void init() // FOR GLUT LOOP
{
    glEnable(GL_DEPTH_TEST);            // Enable check for close and far objects.
    glClearColor(0.0, 0.0, 0.0, 0.0);    // Clear the color state.
    glMatrixMode(GL_MODELVIEW);            // Go to 3D mode.
    glLoadIdentity();                    // Reset 3D view matrix.
}

void display()                            // Called for each frame (about 60 times per second).
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                // Clear color and depth buffers.
    glLoadIdentity();                                                // Reset 3D view matrix.
    gluLookAt(0.0, 10.0, 10.0,                                        // Where the camera is.
              0.0, 0.0, 0.0,                                        // To where the camera points at.
              0.0, 1.0, 0.0);                                        // "UP" vector.
    
    
    glRotatef(rotationY*0.2f, 0, 1, 0);
    
    
    
    glBegin(GL_TRIANGLES); //Chair model
    {
        
        //Backside
        //Lower two triangles
        glColor3f(0.92f, 0.58f, 0.19f);
        glVertex3f(0,0,0);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(1.5,0,0);
        
        glColor3f(0.96f, 0.58f, 0.19f);
        glVertex3f(0,0,0);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(-1.5,0,0);
        
        
        //Middle two triangles
        glColor3f(0.96f, 0.67f, 0.20f);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(1,2.5,-0.5);
        glVertex3f(1.5,0,0);
        
        glColor3f(0.989f, 0.67f, 0.20f);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(-1,2.5,-0.5);
        glVertex3f(-1.5,0,0);
        
        //Top two triangles
        glColor3f(0.97f, 0.74f, 0.23f);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(0,2.75,-1.0);
        glVertex3f(1,2.5,-0.5);
        
        glColor3f(1.0f, 0.79f, 0.23f);
        glVertex3f(0,0.5,-0.5);
        glVertex3f(0,2.75,-1.0);
        glVertex3f(-1,2.5,-0.5);
        
        
        //Bottomside
        
        //Lower two triangles
        glColor3f(1.0f, 0.74f, 0.23f);
        glVertex3f(0,0,0);
        glVertex3f(0,0.25,1.5);
        glVertex3f(1.5,0,0);
        
        
        glVertex3f(0,0,0);
        glVertex3f(0,0.25,1.5);
        glVertex3f(-1.5,0,0);
        
        //Middle two triangles
        
        glColor3f(0.989f, 0.67f, 0.20f);
        glVertex3f(0,0.25,1.5);
        glVertex3f(1.5,0,0);
        glVertex3f(1.5,0,2.0);
        
        
        glVertex3f(0,0.25,1.5);
        glVertex3f(-1.5,0,0);
        glVertex3f(-1.5,0,2.0);
        
        //Bottom triangle
        glColor3f(1.0f, 0.79f, 0.23f);
        glVertex3f(0,0.25,1.5);
        glVertex3f(1.5,0,2.0);
        glVertex3f(-1.5,0,2.0);
        
    }
    glEnd();
    
    glLineWidth(7.0);
    
    glBegin(GL_LINES);
    {
        //Top handles
        glVertex3f(1.0,2.5,-0.5);
        glVertex3f(2.0,0.8,0.5);
        
        glVertex3f(-1.0,2.5,-0.5);
        glVertex3f(-2.0,0.8,0.5);
        
        //Lower handles
        glVertex3f(2.0,0.8,0.5);
        glVertex3f(1.5,0,2.0);
        
        glVertex3f(-2.0,0.8,0.5);
        glVertex3f(-1.5,0,2.0);
        
        //Connecting handles
        glVertex3f(1.5,0,0);
        glVertex3f(2.0,0.8,0.5);
        
        glVertex3f(-1.5,0,0);
        glVertex3f(-2.0,0.8,0.5);
        
        //Legs
        
        //Front legs
        glVertex3f(1.5,0,2.0);
        glVertex3f(1.60,-2.5,2.5);
        
        glVertex3f(-1.5,0,2.0);
        glVertex3f(-1.60,-2.5,2.5);
        
        //Front to back
        glVertex3f(1.60,-2.5,2.5);
        glVertex3f(1.5,0,0);
        
        glVertex3f(-1.60,-2.5,2.5);
        glVertex3f(-1.5,0,0);
        
        //Back legs
        glVertex3f(1.5,0,0);
        glVertex3f(1.0,-2.5,-1.0);
        
        glVertex3f(-1.5,0,0);
        glVertex3f(-1.0,-2.5,-1.0);
        
        //Back to back
        glVertex3f(1.0,-2.5,-1.0);
        glVertex3f(-1.0,-2.5,-1.0);
        
        //Back triangle
        glVertex3f(1.0,-2.5,-1.0);
        glVertex3f(0,0,0);
        
        glVertex3f(-1.0,-2.5,-1.0);
        glVertex3f(0,0,0);
        
    }
    glEnd();
    
    
    
    
    
    glutSwapBuffers();
}

void idle()
{
    rotationY += 3.01f;
    glutPostRedisplay();
}

void reshape(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
    gluLookAt(0.0, 1.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    display();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG IS COOL");
    
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(onMouse);
    createPopupMenus();
    
    glutMainLoop();
    return 0;
}
 */
