#include <stdlib.h>
#include <math.h>
#include "Room.h"
#include "Node.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int h,w;

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
int roomCounter = 0;

#define CREATE 1
#define DELETE 2
#define MODIFY 3
#define EXPORT 4

//Name Variable





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
    
    outfile << "newmtl black" << std::endl;
    outfile << "Ka 0.0000 0.0000 0.0000" << std::endl;
    outfile << "Kd 0.0000 0.0000 0.0000" << std::endl;
    outfile << "illum 1" << std::endl;
    
    outfile << "newmtl white" << std::endl;
    outfile << "Ka 1.0000 1.0000 1.0000" << std::endl;
    outfile << "Kd 1.0000 1.0000 1.0000" << std::endl;
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
    outfile << "v 0.000000 " << wSize/2 << ".000000 " << wSize << ".000000" << std::endl; // 1 top right
    outfile << "v 0.000000 0.000000 " << wSize << ".000000" << std::endl; // 2 bottom right
    outfile << "v " << wSize << ".000000 0.000000 " << wSize << ".000000" << std::endl; // 3 bottomn left
    outfile << "v " << wSize << ".000000 " << wSize/2 << ".000000 " << wSize << ".000000" << std::endl; // 4 top left
    outfile << "v 0.000000 " << wSize/2 << ".000000 0.000000" << std::endl; // 5
    outfile << "v 0.000000 0.000000 0.000000" << std::endl; // 6
    outfile << "v " << wSize << ".000000 0.000000 0.000000" << std::endl; // 7
    outfile << "v " << wSize << ".000000 " << wSize/2 << ".000000 0.000000" << std::endl; // 8
    
    outfile << "g front" << std::endl;
    outfile << "usemtl grey" << std::endl;
    outfile << "f 1 2 3 4" << std::endl;
    
    outfile << "g back" << std::endl;
    outfile << "usemtl red" << std::endl;
    outfile << "f 8 7 6 5" << std::endl;
    
    outfile << "g right" << std::endl;
    outfile << "usemtl blue" << std::endl;
    outfile << "f 4 3 7 8" << std::endl;
    
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
    
    int doorDepth = .5;
    int doorLength = 1.5;
    int offset = 1;
    int doorHeight = 3;
    
    if(doors > 0){
        //Build first foor
        outfile << "v " << wSize - offset - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 9 top right  1
        outfile << "v " << wSize - offset - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 10 bottom right  2
        outfile << "v " << wSize - offset << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 11 bottom left  3
        outfile << "v " << wSize - offset << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 12 top left  4
        outfile << "v " << wSize - offset - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 13  5
        outfile << "v " << wSize - offset - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 14  6
        outfile << "v " << wSize - offset << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 15  7
        outfile << "v " << wSize - offset << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 16  8
        
        outfile << "g doorfront1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 9 10 11 12" << std::endl;
        
        outfile << "g doorback1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 16 15 14 13" << std::endl;
        
        outfile << "g doorright1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 12 11 15 16" << std::endl;
        
        outfile << "g doortop1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 13 9 12 16" << std::endl;
        
        outfile << "g doorleft1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 13 14 10 9" << std::endl;
        
        outfile << "g doorbottom1" << std::endl;
        outfile << "usemtl red" << std::endl;
        outfile << "f 10 14 15 11" << std::endl;
        
    }
    
    //    Second door vertices
    
    if(doors > 1){
        //Build second foor
        outfile << "v " << wSize - offset*2 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 17 top right  9
        outfile << "v " << wSize - offset*2 - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 18 bottom right  10
        outfile << "v " << wSize - offset*2 << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 19 bottom left  11
        outfile << "v " << wSize - offset*2 << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 20 top left  12
        outfile << "v " << wSize - offset*2 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 21  13
        outfile << "v " << wSize - offset*2 - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 22  14
        outfile << "v " << wSize - offset*2 << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 23  15
        outfile << "v " << wSize - offset*2 << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 24  16
        
        outfile << "g doorfront2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 17 18 19 20" << std::endl;
        
        outfile << "g doorback2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 24 23 22 21" << std::endl;
        
        outfile << "g doorright2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 20 19 23 24" << std::endl;
        
        outfile << "g doortop2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 21 17 20 24" << std::endl;
        
        outfile << "g doorleft2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 21 22 18 17" << std::endl;
        
        outfile << "g doorbottom2" << std::endl;
        outfile << "usemtl green" << std::endl;
        outfile << "f 18 22 23 19" << std::endl;
    }
    
    //    Third door vertices
    
    if(doors > 2){
        //Build third foor
        outfile << "v " << wSize - offset*3 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 25 top right  17
        outfile << "v " << wSize - offset*3 - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 26 bottom right  18
        outfile << "v " << wSize - offset*3 << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 27 bottom left  19
        outfile << "v " << wSize - offset*3 << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 28 top left  20
        outfile << "v " << wSize - offset*3 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 29  21
        outfile << "v " << wSize - offset*3 - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 30  22
        outfile << "v " << wSize - offset*3 << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 31  23
        outfile << "v " << wSize - offset*3 << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 32  24
        
        outfile << "g doorfront3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 25 26 27 28" << std::endl;
        
        outfile << "g doorback3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 32 31 30 29" << std::endl;
        
        outfile << "g doorright3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 28 27 31 32" << std::endl;
        
        outfile << "g doortop3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 29 25 28 32" << std::endl;
        
        outfile << "g doorleft3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 29 30 26 25" << std::endl;
        
        outfile << "g doorbottom3" << std::endl;
        outfile << "usemtl blue" << std::endl;
        outfile << "f 26 30 31 27" << std::endl;
    }
    
    //    Fourth door vertices
    
    if(doors > 3){
        //Build fourth foor
        outfile << "v " << wSize - offset*4 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 33 top right  25
        outfile << "v " << wSize - offset*4 - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 34 bottom right  26
        outfile << "v " << wSize - offset*4 << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 35 bottom left  27
        outfile << "v " << wSize - offset*4 << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 36 top left  28
        outfile << "v " << wSize - offset*4 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 37  29
        outfile << "v " << wSize - offset*4 - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 38  30
        outfile << "v " << wSize - offset*4 << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 39  31
        outfile << "v " << wSize - offset*4 << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 40  32
        
        outfile << "g doorfront4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 33 34 35 36" << std::endl;
        
        outfile << "g doorback4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 40 39 38 37" << std::endl;
        
        outfile << "g doorright4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 36 35 39 40" << std::endl;
        
        outfile << "g doortop4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 37 33 36 40" << std::endl;
        
        outfile << "g doorleft4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 37 38 34 33" << std::endl;
        
        outfile << "g doorbottom4" << std::endl;
        outfile << "usemtl black" << std::endl;
        outfile << "f 34 38 39 35" << std::endl;
    }
    
    //    Fifth door vertices
    
    if(doors > 4){
        //Build fifth foor
        outfile << "v " << wSize - offset*5 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 41 top right
        outfile << "v " << wSize - offset*5 - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 42 bottom right
        outfile << "v " << wSize - offset*5 << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 43 bottom left
        outfile << "v " << wSize - offset*5 << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 44 top left
        outfile << "v " << wSize - offset*5 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 45
        outfile << "v " << wSize - offset*5 - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 46
        outfile << "v " << wSize - offset*5 << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 47
        outfile << "v " << wSize - offset*5 << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 48
        
        outfile << "g doorfront5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 41 42 43 44" << std::endl;
        
        outfile << "g doorback5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 48 47 46 45" << std::endl;
        
        outfile << "g doorright5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 44 43 47 48" << std::endl;
        
        outfile << "g doortop5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 45 41 44 48" << std::endl;
        
        outfile << "g doorleft5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 45 46 42 41" << std::endl;
        
        outfile << "g doorbottom5" << std::endl;
        outfile << "usemtl white" << std::endl;
        outfile << "f 42 46 47 43" << std::endl;
    }
    
    //    Last door vertices
    
    if(doors > 4){
        //Build last foor
        outfile << "v " << wSize - offset*6 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 49 top right
        outfile << "v " << wSize - offset*6 - doorLength << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 50 bottom right
        outfile << "v " << wSize - offset*6 << ".000000 " << "0.000000 " << wSize  << ".000000" << std::endl; // 51 bottom left
        outfile << "v " << wSize - offset*6 << ".000000 " << doorHeight << ".000000 " << wSize << ".000000" << std::endl; // 52 top left
        outfile << "v " << wSize - offset*6 - doorLength << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 53
        outfile << "v " << wSize - offset*6 - doorLength << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 54
        outfile << "v " << wSize - offset*6 << ".000000 " << "0.000000 " << wSize - doorDepth << ".000000" << std::endl; // 55
        outfile << "v " << wSize - offset*6 << ".000000 " << doorHeight << ".000000 " << wSize - doorDepth << ".000000" << std::endl; // 56
        
        outfile << "g doorfront6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 49 50 51 52" << std::endl;
        
        outfile << "g doorback6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 56 55 54 53" << std::endl;
        
        outfile << "g doorright6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 52 51 55 56" << std::endl;
        
        outfile << "g doortop6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 53 49 52 56" << std::endl;
        
        outfile << "g doorleft6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 53 54 50 49" << std::endl;
        
        outfile << "g doorbottom6" << std::endl;
        outfile << "usemtl pink" << std::endl;
        outfile << "f 50 54 55 51" << std::endl;
    }
    
    
    
    outfile.close();
    
}


void keyboard( unsigned char key, int x, int y )
{
    if( key == 13 )
    {

        room->keyboardEnter();
    }
    else if( key == 127 )
    {
        // backspace
        room->backSpace();
        
    }
    else
    {
        // regular text
        room->keyPress(key);
    }
    
    glutPostRedisplay();
}


void processMenu(int option) {
    
    switch (option) {
        case CREATE : room->addBox(" ");
            roomCounter ++;
            break;
        case DELETE : room->deleteBox();
            break;
        case MODIFY: room->editingMode = 1;
            break;
        case EXPORT: createOBJfile(10, room->currentNode->childNumber());
            break;
    }
}

void createPopupMenus() {
    
    int menu;
    menu = glutCreateMenu(processMenu);
    glutAddMenuEntry("Create",CREATE);
    glutAddMenuEntry("Delete",DELETE);
    glutAddMenuEntry("Modify",MODIFY);
    glutAddMenuEntry("Export",EXPORT);
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
    
    room->selectBox(pickedID);
    
}

void changeSize(int w1, int h1) {
    
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h1 == 0)
        h1 = 1;
    float ratio =  w1 * 1.0 / h1;
    
    w = w1;
    h = h1;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w1, h1);
    
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void resetToEntrance(){

    angle = 0.0f;
    // actual vector representing the camera's direction
    lx=0.0f;
    lz=-1.0f;
    // XZ position of the camera
    x=0.0f;
    z=5.0f;
}

void resetToDoor(){
    float aux_x = room->currentNode->previousX;
    float aux_z = room->currentNode->previousZ;
    Node *temp = room->currentNode->parent;
    delete room;
    room = new Room();
    room->currentNode = temp;

    // actual vector representing the camera's direction
    lx = 0.0f;
    lz = 1.0f;
    // XZ position of the camera
    x = aux_x;
    z = aux_z+3;
    
}

void updateRoom(int index){
    Node *temp = room->currentNode->children[index];
    delete room;
    
    room = new Room();
    room->currentNode = temp;
    
    room->currentNode->previousX = x;
    room->currentNode->previousZ = z;
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
    
    if(x >= -1.00 && x <= 1.00 && z <= 9.5 && z>=9.2 && room->currentNode->parent != NULL){
        resetToDoor();
    }
    
    switch (room->currentNode->childNumber()) {
        case 1:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            break;
        case 2:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            else if(x >= -5.25 && x <= -4.75 && z <= -9.0){
                updateRoom(1);
                resetToEntrance();
            }
            break;
        case 3:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            else if(x >= -5.25 && x <= -4.75 && z <= -9.0){
                updateRoom(1);
                resetToEntrance();
            }
            else if(x >= -2.25 && x <= -1.75 && z <= -9.0){
                updateRoom(2);
                resetToEntrance();
            }
            break;
        case 4:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            else if(x >= -5.25 && x <= -4.75 && z <= -9.0){
                updateRoom(1);
                resetToEntrance();
            }
            else if(x >= -2.25 && x <= -1.75 && z <= -9.0){
                updateRoom(2);
                resetToEntrance();
            }
            else if(x >= 0.75 && x <= 1.25 && z <= -9.0){
                updateRoom(3);
                resetToEntrance();
            }
            break;
        case 5:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            else if(x >= -5.25 && x <= -4.75 && z <= -9.0){
                updateRoom(1);
                resetToEntrance();
            }
            else if(x >= -2.25 && x <= -1.75 && z <= -9.0){
                updateRoom(2);
                resetToEntrance();
            }
            else if(x >= 0.75 && x <= 1.25 && z <= -9.0){
                updateRoom(3);
                resetToEntrance();
            }
            else if(x >= 3.75 && x <= 4.25 && z <= -9.0){
                updateRoom(4);
                resetToEntrance();
            }
            break;
        case 6:
            if(x >= -8.25 && x <= -7.75 && z <= -9.0){
                updateRoom(0);
                resetToEntrance();
            }
            else if(x >= -5.25 && x <= -4.75 && z <= -9.0){
                updateRoom(1);
                resetToEntrance();
            }
            else if(x >= -2.25 && x <= -1.75 && z <= -9.0){
                updateRoom(2);
                resetToEntrance();
            }
            else if(x >= 0.75 && x <= 1.25 && z <= -9.0){
                updateRoom(3);
                resetToEntrance();
            }
            else if(x >= 3.75 && x <= 4.25 && z <= -9.0){
                updateRoom(4);
                resetToEntrance();
            }
            else if(x >= 6.75 && x <= 7.25 && z <= -9.0){
                updateRoom(5);
                resetToEntrance();
            }
            break;
        default:
            break;
            
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
    glPushMatrix();
    glTranslated(-8, 1.2, -10);
    glScaled(1.5, 3, 0.1);//Here you scale the doors
    
    room->drawDoors();
    glPopMatrix();
    
    
    
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

