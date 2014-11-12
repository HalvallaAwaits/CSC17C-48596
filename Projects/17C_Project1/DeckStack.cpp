/* 
 * File:   DeckStack.cpp
 * Author: Joe
 *
 * Created on November 10, 2014, 12:32 PM
 */

#include <iostream>
#include "DeckStack.h"
using namespace std;

//Destructor
DeckStack::~DeckStack(){
    DeckNode *nextNode;
    worker=top;
    //traverse the list and delete each node
    while(worker!=NULL){
        nextNode=worker->next;
        delete worker;
        worker=nextNode;
    }
}

//Mutators
//Add card to top of deck
void DeckStack::push(Card crd){
    //create new node to hold a new card
    DeckNode *newNode=new DeckNode;
    newNode->data=crd;
    //if no nodes make newNode the first
    if(isEmpty()){
        top=newNode;
        newNode->next=NULL;
    }
    //if not, insert before top
    else{
        newNode->next=top;
        top=newNode;
    }
}

//Remove card from top of deck and pass by reference out
void DeckStack::pop(Card &crd){
    DeckNode *temp;
    //Make sure not empty
    if(isEmpty())
        cout<<"The deck is empty!"<<endl;
    //if not, pop value off top and return card to deal
    else{
        crd=top->data;
        temp=top->next;
        delete top;
        top=temp;
    }
}

//Check to see if deck is empty
bool DeckStack::isEmpty() const{
    bool empty;
    if(!top)
        empty=true;
    else
        empty=false;
    return empty;
}