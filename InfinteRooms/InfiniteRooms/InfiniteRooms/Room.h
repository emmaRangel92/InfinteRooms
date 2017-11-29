#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "Node.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
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
    std::vector<std::string> names;
    std::string savedString = " ";
    int saveString = -1;
    
public:
    Room() : names(20) {}
    int editingMode = -1;
    
    void keyboardEnter(){
        if (editingMode > 0){
            currentNode->children[selectedIndex]->info = savedString;
            editingMode = -1;
            clearNames();
        }
    }
    
    void backSpace(){
        
        if(editingMode > 0){
            names.back().pop_back();
        }

    }
    
    void keyPress(unsigned char key){
        if (editingMode> 0){
            names.back().push_back( key );
        }
    }
    
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
            case 3504370:selectedIndex=0; break;
            case 5738224:selectedIndex=1;break;
            case 7117808:selectedIndex=2;break;
            case 8234736:selectedIndex=3;break;
            case -7163408:selectedIndex=4;break;
            case -4535317:selectedIndex=5;break;
            default:
                selectedIndex = -1;
                break;
        }
        
        
    }
    
    void clearNames(){
        for( size_t i = 0; i < names.size(); ++i )
        {
            names.back().pop_back();
        }
        
    }
    
    void drawDoors(){
        
        int offSet = 0;

        for( int i = 0; i < (sizeof(currentNode->children)/sizeof(*currentNode->children)); i ++ ) {
            //draw a door
            
            switch (i) {
                case 0:glColor3d(0.949, 0.474, 0.207); break;
                case 1:glColor3d(0.9411, 0.560, 0.345);break;
                case 2:glColor3d(0.9411, 0.6117, 0.427);break;
                case 3:glColor3d(0.9411, 0.654, 0.494);break;
                case 4:glColor3d(0.9411, 0.70, 0.576);break;
                case 5:glColor3d(0.921, 0.8, 0.733);break;
            }
            
            if(currentNode->children[i] != NULL){

            
                glPushMatrix();{
                    glTranslated(offSet, 0, 0);
                    glutSolidCube(1);

                    //Bounding Box
                    if(selectedIndex == i){
                        glutWireCube(1.5);
                        
                        if(editingMode > 0)
                        {
                            currentNode->children[i]->info = " ";
                            for( size_t i = 0; i < names.size(); ++i )
                            {
                                std::ostringstream oss;
                                oss <<names[i];
                                void* font = GLUT_BITMAP_9_BY_15;
                                const int fontHeight = glutBitmapWidth(font, 1);
                                char *cstr = new char[oss.str().length() + 1];
                                strcpy(cstr, oss.str().c_str());
                                std::string str(cstr);
                                savedString = str;
                                renderBitmapString(-0.2f, 0.65f, 5.0f, (void *)font, cstr );
                                delete [] cstr;
                            }
                        }
                        
                    }
                    
                    std::string str = currentNode->children[i]->info;
                    
                    //Displaying Text
                    char *cstr = new char[str.length() + 1];
                    strcpy(cstr, str.c_str());
                    renderBitmapString(-0.2f, 0.65f, 5.0f, (void *)font, cstr );
                    delete [] cstr;
                    
                    
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
        glColor3d(0.74, 0.764, 0.780);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        /* Ceiling */
        glColor3d(0.74, 0.764, 0.780);
        glVertex3f(-wSize,wSize*.5,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(-wSize,wSize*.5,wSize);
        /* Walls */
        //Back Wall
        glColor3d(0.925, 0.925, 0.925);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(-wSize,wSize*.5,wSize);
        //Back door
        glColor3d(0.203, 0.286, 0.368);
        glVertex3f(-backdoorW,-0.0,wSize-.01);
        glVertex3f(backdoorW,-0.0,wSize-.01);
        glVertex3f(backdoorW,backdoorH,wSize-.01);
        glVertex3f(-backdoorW,backdoorH,wSize-.01);
        //Front Wall
        glColor3d(0.67, 0.717, 0.717);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        glVertex3f(-wSize,wSize*.5,-wSize);
        
        
        // Right Wall
        glColor3d(0.87, 0.87, 0.87);
        glVertex3f(wSize,wSize*.5,wSize);
        glVertex3f(wSize,-0.0,wSize);
        glVertex3f(wSize,-0.0,-wSize);
        glVertex3f(wSize,wSize*.5,-wSize);
        // Left Wall
        glColor3d(0.87, 0.87, 0.87);
        glVertex3f(-wSize,wSize*.5,wSize);
        glVertex3f(-wSize,-0.0,wSize);
        glVertex3f(-wSize,-0.0,-wSize);
        glVertex3f(-wSize,wSize*.5,-wSize);
        
        glPushMatrix();

    }
    
    
};


#endif // ROOM_H_INCLUDED

