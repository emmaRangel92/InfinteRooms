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
    
    Node(std::string info)
    {
        this->info = info;
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            children[i] = NULL;
        }
        
    }
    
    void add_child(Node *child) {
        child->parent = this;
        
        for( int i = 0; i < (sizeof(children)/sizeof(*children)); i ++ ) {
            if (children[i] == NULL){
                children[i] = child;
                break;
            }
        }
        
    }
    
    void deleteChild(int index){
        Node *temp = children[index];
        children[index] = NULL;
        delete temp;
        cleanup();
    }
};
