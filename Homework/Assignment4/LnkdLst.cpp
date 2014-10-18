/* 
 * File:   LnkdLst.h
 * Author: Joe
 *
 * Created on October 18, 2014, 9:37 AM
 */

#include "LnkdLst.h"
#include <sstream>
#include <string>
#include <iostream>

LnkdLst::LnkdLst(int d){
    //Initialize Head
    Node *clink = new Node;
    clink->data=d;
    clink->next=NULL;
    head=clink;
}

void LnkdLst::append(int d){
    //Create node at end of list
    Node *clink = new Node;
    clink->data=d;
    clink->next=NULL;
    //check if head exists or not
    if(!head)       //if not then set this first append as head
        head=clink;
    else{           //if exists, need to find end and append there
        //set worker to head
        worker=head;
        //find the last node in list
        while(worker->next)
            worker=worker->next;
        //add node to end of list
        worker->next=clink;
    }
}

string LnkdLst::toString(){
    stringstream out; //holds the data to output
    //make sure list exists
    if(head){
        //start at head
        worker=head;
        //output while worker points to a node
        while(worker){
            //add data points to string stream
            out<<"Data = "<<worker->data<<"\n";
            //move to next node
            worker=worker->next;
        }
    }
    return out.str();
}

LnkdLst::~LnkdLst(){
    while(head){
        worker = head;
        head = head->next;
        delete worker;
    }
}
