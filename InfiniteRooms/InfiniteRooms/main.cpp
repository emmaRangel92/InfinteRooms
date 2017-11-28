#include <stdlib.h>
#include <math.h>
#include "Room.h"
#include "Node.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
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

void renderBitmapString(void *font,char *string) {
    char *c;
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void createMtlFile(){
    std::ofstream outfile ("master.mtl");

    outfile << "newmtl green" << std::endl;
    outfile << "Ka 0.0000 1.0000 0.0000" << std::endl;
    outfile << "Kd 0.0000 1.0000 0.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl red" << std::endl;
    outfile << "Ka 1.0000 0.0000 0.0000" << std::endl;
    outfile << "Kd 1.0000 0.0000 0.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl blue" << std::endl;
    outfile << "Ka 0.0000 0.0000 1.0000" << std::endl;
    outfile << "Kd 0.0000 0.0000 1.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl pink" << std::endl;
    outfile << "Ka 1.0000 0.0000 1.0000" << std::endl;
    outfile << "Kd 1.0000 0.0000 1.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl yellow" << std::endl;
    outfile << "Ka 1.0000 1.0000 0.0000" << std::endl;
    outfile << "Kd 1.0000 1.0000 0.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl purple" << std::endl;
    outfile << "Ka 0.5000 0.5000 1.0000" << std::endl;
    outfile << "Kd 0.5000 0.5000 1.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl grey" << std::endl;
    outfile << "Ka 0.4000 0.4000 0.4000" << std::endl;
    outfile << "Kd 0.4000 0.4000 0.4000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile.close();

}

void createOBJfile(int wSize, int doors){
    
    createMtlFile();
    
    std::ofstream outfile ("room.obj");

//    Main room
    outfile << "mtllib master.mtl" << std::endl;
    
//    Walls vertices
    outfile << "v 0.000000 " << wSize/2 << ".000000 " << wSize*3 << ".000000" << std::endl; // 1 top right
    outfile << "v 0.000000 0.000000 " << wSize*3 << ".000000" << std::endl; // 2 bottom right
    outfile << "v " << wSize << ".000000 0.000000 " << wSize*3 << ".000000" << std::endl; // 3 bottomn left
    outfile << "v " << wSize << ".000000 " << wSize/2 << ".000000 " << wSize << ".000000" << std::endl; // 4 top left
    outfile << "v 0.000000 " << wSize/2 << ".000000 0.000000" << std::endl; // 5
    outfile << "v 0.000000 0.000000 0.000000" << std::endl; // 6
    outfile << "v " << wSize << ".000000 0.000000 0.000000" << std::endl; // 7
    outfile << "v " << wSize << ".000000 " << wSize/2 << ".000000 0.000000" << std::endl; // 8
    
    outfile << "g front" << std::endl;
    outfile << "usemtl green" << std::endl;
    outfile << "f 1 2 3 4" << std::endl;
    
    outfile << "g back" << std::endl;
    outfile << "usemtl red" << std::endl;
    outfile << "f 8 7 6 5" << std::endl;
    
    outfile << "g right" << std::endl;
    outfile << "usemtl blue" << std::endl;
    outfile << "f 4 3 7 8" << std::endl;
    
    outfile << "g top" << std::endl;
    outfile << "usemtl grey" << std::endl;
    outfile << "f 5 1 4 8" << std::endl;
    
    outfile << "g left" << std::endl;
    outfile << "usemtl purple" << std::endl;
    outfile << "f 5 6 2 1" << std::endl;
    
    outfile << "g bottom" << std::endl;
    outfile << "usemtl yellow" << std::endl;
    outfile << "f 2 6 7 3" << std::endl;
    
//    First door vertices
    
    if(doors > 0){
        //Build first foor
    }
    
//    Second door vertices
    
    if(doors > 1){
        //Build second foor
    }

//    Third door vertices
    
    if(doors > 2){
        //Build third foor
    }
    
//    Fourth door vertices
    
    if(doors > 3){
        //Build fourth foor
    }
    
//    Fifth door vertices
    
    if(doors > 4){
        //Build fifth foor
    }

//    Last door vertices
    
    if(doors > 4){
        //Build last foor
    }
    
    
    
    outfile.close();

}


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
    
    room->drawRoom(10);
    glEnd();
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glTranslated(-8, 1.2, -10);
    glScaled(1.5, 3, 0.1);//Here you scale the doors

    room->drawDoors();
    glPopMatrix();
    
    /*
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
        
        char *cstr = new char[oss.str().length() + 1];
        strcpy(cstr, oss.str().c_str());
        renderBitmapString((void *) font, cstr);
        
        delete [] cstr;
        
    }
    */
    
    glutSwapBuffers();
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
    
    createOBJfile(10, 4);
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
