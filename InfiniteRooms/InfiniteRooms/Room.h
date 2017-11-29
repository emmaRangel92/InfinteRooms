#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "Node.hpp"





class Room{
    void *font = GLUT_BITMAP_HELVETICA_18;
    
    void renderBitmapString(
                            float x,
                            float y,
                            float z,
                            void *font,
                            char *string) {
        char *c;
        glRasterPos3f(x, y,z);
        for (c=string; *c != '\0'; c++) {
            glutBitmapCharacter(font, *c);
        }
    }
    
    
private:
    
    
public:
    Node *currentNode;
    int selectedIndex = -1;
    
    void addBox(std::string roomName){
        
        Node* temp =new Node(roomName);
        currentNode->add_child(temp);
        temp->parent = currentNode;
        
        
    }
    
    void deleteBox(){
        currentNode->deleteChild(selectedIndex);
        selectedIndex = -1;
    }
    
    void selectBox(int id){
        
        switch (id) {
            case 1:selectedIndex=0; break;
            case 256:selectedIndex=1;break;
            case 65536:selectedIndex=2;break;
            case 0:selectedIndex=3;break;
            case 65793:selectedIndex=4;break;
            case 65537:selectedIndex=5;break;
            default:selectedIndex = -1;break;
        }
        
        
    }
    
    void drawDoors(){
        
        int offSet = 0;

        for( int i = 0; i < (sizeof(currentNode->children)/sizeof(*currentNode->children)); i ++ ) {
            //draw a door
            
            switch (i) {
                case 0:glColor3f(1, 0, 0); break;
                case 1:glColor3f(0, 1, 0);break;
                case 2:glColor3f(0, 0, 1);break;
                case 3:glColor3f(0, 0, 0);break;
                case 4:glColor3f(1, 1, 1);break;
                case 5:glColor3f(1, 0, 1);break;
            }
            
            if(currentNode->children[i] != NULL){

            
                glPushMatrix();{
                    glTranslated(offSet, 0, 0);
                    glutSolidCube(1);
                    
                    std::string str = currentNode->children[i]->info;
                    
                    //Displaying Text
                    char *cstr = new char[str.length() + 1];
                    strcpy(cstr, str.c_str());
                    renderBitmapString(-0.2f, 0.65f, 5.0f, (void *)font, cstr );
                    delete [] cstr;
                    
                    //Bounding Box
                    if(selectedIndex == i){
                        glutWireCube(1.5);
                    }
                    
                    
                }

                glPopMatrix();
                


                offSet += 2;
                
               
            }
            else break;
        }
    }
    
    
    void drawRoom( int wSize){
        
        
        
        //Backdoor Height
        double backdoorH = wSize*.3;
        //Backdoor Width
        double backdoorW = wSize *.15;
        // Doors Width
        double doorW = (wSize*0.10);
        // Doors Height
        double doorH = (wSize*0.3);
        
        /* Floor */
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        /* Ceiling */
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex3f(-wSize,wSize*.5,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(-wSize,wSize*.5,wSize);
        /* Walls */
        //Back Wall
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(-wSize,wSize*.5,wSize);
        //Back door
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3f(-backdoorW,-0.0,wSize-.01);
        glVertex3f(backdoorW,-0.0,wSize-.01);
        glVertex3f(backdoorW,backdoorH,wSize-.01);
        glVertex3f(-backdoorW,backdoorH,wSize-.01);
        //Front Wall
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        glVertex3f(-wSize,wSize*.5,-wSize);
        
        
        // Right Wall
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        // Left Wall
        glColor3f(0.5f, 0.5f, 1.0f);
        glVertex3f(-wSize,wSize*.5,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(-wSize,wSize*.5,-wSize);
        
        glPushMatrix();

    }
    
    
};


#endif // ROOM_H_INCLUDED

