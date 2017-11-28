#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Room{
private:
    
public:
    void drawCeiling( int wSize){
        /* Ceiling */
        
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(-wSize,wSize,-wSize);
        glVertex3f(wSize,wSize,-wSize);
        glVertex3f(wSize,wSize,wSize);
        glVertex3f(-wSize,wSize,wSize);
    }
    void drawFloor( int wSize){
        /* Floor */
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(-wSize,-wSize,-wSize);
        glVertex3f(wSize,-wSize,-wSize);
        glVertex3f(wSize,-wSize,wSize);
        glVertex3f(-wSize,-wSize,wSize);
    }
    
    void drawWalls(int wSize){
        /* Walls */
        
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-wSize,-wSize,wSize);
        glVertex3f(wSize,-wSize,wSize);
        glVertex3f(wSize,wSize,wSize);
        glVertex3f(-wSize,wSize,wSize);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-wSize,-wSize,-wSize);
        glVertex3f(wSize,-wSize,-wSize);
        glVertex3f(wSize,wSize,-wSize);
        glVertex3f(-wSize,wSize,-wSize);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(wSize,wSize,wSize);
        glVertex3f(wSize,-wSize,wSize);
        glVertex3f(wSize,-wSize,-wSize);
        glVertex3f(wSize,wSize,-wSize);
        glColor3f(0.5f, 0.5f, 1.0f);
        glVertex3f(-wSize,wSize,wSize);
        glVertex3f(-wSize,-wSize,wSize);
        glVertex3f(-wSize,-wSize,-wSize);
        glVertex3f(-wSize,wSize,-wSize);
    }
    
    void drawRoom( int wSize){
        /* Floor */
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        /* Ceiling */
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(-wSize,wSize*.75,-wSize);
        glVertex3f(wSize,wSize*.75,-wSize);
        glVertex3f(wSize,wSize*.75,wSize);
        glVertex3f(-wSize,wSize*.75,wSize);
        /* Walls */
        //Back Door
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,wSize*.75,wSize);
        glVertex3f(-wSize,wSize*.75,wSize);
        //Front Door
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.75,-wSize);
        glVertex3f(-wSize,wSize*.75,-wSize);
        // Right Door
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(wSize,wSize*.75,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.75,-wSize);
        // Left Door
        glColor3f(0.5f, 0.5f, 1.0f);
        glVertex3f(-wSize,wSize*.75,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(-wSize,wSize*.75,-wSize);
    }
    
    
};


#endif // ROOM_H_INCLUDED

