/* 
 * File:   Hand.cpp
 * Author: Joe
 *
 * Created on November 10, 2014, 10:21 PM
 */

#include <iostream>
#include "Hand.h"
using namespace std;

//Constructor
HandQueue::HandQueue(){
    front=NULL;
    rear=NULL;
    numHand=0;
}

//Destructor
HandQueue::~HandQueue(){
    clear();
}

void HandQueue::clear(){
    Card val;    //temp for dequeue
    while(!isEmpty())
        dequeue(val);
}

//Mutators
void HandQueue::enqueue(Card crd){
    //create new hand node and store card info
    HandNode *newNode=new HandNode;
    newNode->data=crd;
    newNode->next=NULL;
    //adjust front and rear
    if(isEmpty()){
        front=newNode;
        rear=newNode;
    }
    else{
        rear->next=newNode;
        rear=newNode;
    }
    //increment numHand
    numHand++;
}

void HandQueue::dequeue(Card& crd){
    HandNode *temp;
    if(isEmpty())
        cout<<"The hand is empty!"<<endl;
    else{
        //save front card into crd to pass back by reference
        crd=front->data;
        //remove front node and delete it
        temp=front;
        front=front->next;
        delete temp;
        //decrement numHand
        numHand--;
    }
}

bool HandQueue::isEmpty() const{
    bool status;
    if(numHand>0)
        status=false;
    else
        status=true;
    return status;
}

void HandQueue::resetNumHand(){
    numHand=0;
}

//Accessors
int HandQueue::getNumHand(){
    return numHand;
}