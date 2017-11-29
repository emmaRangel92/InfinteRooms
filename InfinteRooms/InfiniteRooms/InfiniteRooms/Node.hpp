#pragma once
#include <string>
#include <list>
#include <iostream>

#define NODE_SIZE 6

class Node{
private:
    void cleanup(){
        Node *temp [NODE_SIZE];
        
        int c = 0;
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            temp[i] = NULL;
        }
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            
            if (children[i] != NULL){
                temp[c] = children[i];
                children[i] = NULL;
                c++;
            }
        }
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            
            if(temp[i] != NULL){
                children[i] = temp[i];
            }else{
                break;
            }
        }
        
        
        
        
    }
public:
    std::string info;
    Node *parent;
    Node *children [NODE_SIZE];
    int childCounter;
    float previousX;
    float previousZ;
    
    Node(std::string info)
    {
        this->info = info;
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            children[i] = NULL;
        }
        
    }
    
    void setInfo(std::string text){
        info = text;
    }
    void add_child(Node *child) {
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            if (children[i] == NULL){
                children[i] = child;
                break;
            }
        }
        childCounter++;
    }
    
    void deleteChild(int index){
        Node *temp = children[index];
        children[index] = NULL;
        delete temp;
        childCounter--;
        cleanup();
    }
    
    int childNumber(){
        
        int counter = 0;
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            if (children[i] != NULL){
                counter++;
            }else{
                break;
            }
        }
        
        return counter;
    }
};
