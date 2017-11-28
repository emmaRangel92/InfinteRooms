#include <stdlib.h>
#include <math.h>
#include "Room.h"
#include "Node.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
//Room instantiate
Room *room;
Node *root;

#define CREATE 1
#define DELETE 2
#define MODIFY 3

//Name Variable

std::vector< std::string > names( 1 );

void keyboard( unsigned char key, int x, int y )
{
    if( key == 13 )
    {
        // enter key
        names.push_back( "" );
    }
    else if( key == 8 )
    {
        // backspace
        names.back().pop_back();
    }
    else
    {
        // regular text
        names.back().push_back( key );
    }
    
    glutPostRedisplay();
}



void processMenu(int option) {
    
    switch (option) {
        case CREATE : room->addBox("Hello");
            break;
        case DELETE : room->deleteBox();
            break;
        case MODIFY :break;
    }
}

void createPopupMenus() {
    
    int menu;
    menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Create",CREATE);
    glutAddMenuEntry("Delete",DELETE);
    glutAddMenuEntry("Modify",MODIFY);
    
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// -----------------------------------
//             Object Selection
// -----------------------------------
void onMouse(int button, int state, int x, int y) {
    if(state != GLUT_DOWN)
        return;
    
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    
    GLbyte data[4];
    GLfloat depth;
    GLuint index;
    
    glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    
    int pickedID =
    data[0] +
    data[1] * 256 +
    data[2] * 256*256;
    
    std::cout<<pickedID<<"\n";
    
    room->selectBox(pickedID*-1);
    
}




void changeSize(int w, int h) {
    
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio =  w * 1.0 / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Draw Body
    
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);
    
    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();
    
    // Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}



void computePos(float deltaMove) {

    float auxX = x+deltaMove * lx * 0.1f;
    float auxZ = z+deltaMove * lz * 0.1f;
    if(auxX >= -9.50 && auxX <= 9.50){
        x += deltaMove * lx * 0.1f;
    }
    if(auxZ >= -9.50 && auxZ <= 9.50){
        z += deltaMove * lz * 0.1f;
    }
}


void computeDir(float deltaAngle) {
    
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void renderScene(void) {
    
    if (deltaMove)
        computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);
    
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(    x, 1.0f, z,
              x+lx, 1.0f,  z+lz,
              0.0f, 1.0f,  0.0f);
    
    // Draw walls
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    glTranslated(0.08,10,0.08);
    room->drawRoom(10);
    glEnd();
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, 0, h, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    for( size_t i = 0; i < names.size(); ++i )
    {
        std::ostringstream oss;
        oss << ( i + 1 ) << ": " << names[i];
        
        void* font = GLUT_BITMAP_9_BY_15;
        const int fontHeight = glutBitmapWidth(font, 1);
        glRasterPos2i( 10, h - ( fontHeight * ( i + 1 ) ) );

        renderBitmapString(font, <#char *string#>)
        
        glutBitmapString( font, (const unsigned char*)( oss.str().c_str() ) );
    }
    
    
    glutSwapBuffers();
}

void renderBitmapString(void *font,char *string) {
    char *c;
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void pressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.05f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.05f; break;
        case GLUT_KEY_UP : deltaMove = 2.0f; break;
        case GLUT_KEY_DOWN : deltaMove = -2.0f; break;
    }
}

void releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

void init(){
    
    root = new Node("Root");
    root->parent = NULL;
    room = new Room();
    
    root->add_child(new Node("RoomN"));
    room->currentNode = root;

}

int main(int argc, char **argv) {
    
    // init GLUT and create window
    glutInit(&argc, argv);
    init();
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(3000,800);
    glutCreateWindow("Rooms - OpenGL");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutMouseFunc(onMouse);
    glutKeyboardFunc( keyboard );
    createPopupMenus();
    
    glutSpecialFunc(pressKey);
    
    // here are the new entries
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);
    
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}
