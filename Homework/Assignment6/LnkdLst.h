/* 
 * File:   LnkdLst.h
 * Author: Joe
 *
 * Created on October 18, 2014, 9:37 AM
 */

#ifndef LNKDLST_H
#define	LNKDLST_H

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

template<class T>
class LnkdLst {
private:
    struct Node{
        T data;
        Node *next;
    };
    Node *head;
    Node *worker;
public:
    //Constructors
    LnkdLst(T);
    LnkdLst(const LnkdLst&);
    //Assignment Operator
    LnkdLst &operator = (const LnkdLst&);
    //Mutators
    void append(T);
    void prepend(T);
    void extract(T);
    void insertBefore(int,T);
    void insertAfter(int,T);
    //Accessors
    string toString();
    T first();
    T last();
    virtual ~LnkdLst();
};

//Constructor
template <class T>
LnkdLst<T>::LnkdLst(T d){
    //Initialize Head
    Node *clink = new Node;
    clink->data=d;
    clink->next=NULL;
    head=clink;
}

//Copy Constructor
template <class T>
LnkdLst<T>::LnkdLst(const LnkdLst& oList){
    //Create new head
    Node *clink=new Node;
    clink->data=oList.head->data;
    clink->next=NULL;
    head=clink;
    worker=head;
    //move through and copy
    Node *tmpWork=new Node;
    tmpWork=oList.head;
    while(tmpWork->next){
        tmpWork=tmpWork->next;
        append(tmpWork->data);
    }
}

//Assignment Operator
template <class T>
LnkdLst<T>& LnkdLst<T>::operator =(const LnkdLst &oList){
    //Empty list
    while(head){
        worker = head;
        head = head->next;
        delete worker;
    }
    //Create new head
    Node *clink=new Node;
    clink->data=oList.head->data;
    clink->next=NULL;
    head=clink;
    worker=head;
    //move through and copy
    Node *tmpWork=new Node;
    tmpWork=oList.head;
    while(tmpWork->next){
        tmpWork=tmpWork->next;
        append(tmpWork->data);
    }
    return *this;
}

//Mutators
template <class T>
void LnkdLst<T>::append(T d){
    //Create node at end of list
    Node *clink = new Node;
    clink->data=d;
    clink->next=NULL;
    //check if head exists or not
    if(!head)       //if not then set this append as head
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

template <class T>
void LnkdLst<T>::prepend(T d){
    Node *newHead=new Node;
    newHead->data=d;
    newHead->next=head;
    head=newHead;
}

template <class T>
void LnkdLst<T>::extract(T d){
    Node *prvWork = new Node;
    //check for list head
    if(!head)return;
    //if head has data
    if(head->data==d){
        worker=head->next;
        delete head;
        head=worker;
    }
    //move through list until data is found
    else{
        worker=head;
        //move through list until end or data is found
        while(worker->next&&worker->data!=d){
            prvWork=worker;
            worker=worker->next;
        }    
        //if above loop ends due to finding data
        if(worker->data==d){
            prvWork->next=worker->next;
            delete worker;
        }
    }
}

template <class T>
void LnkdLst<T>::insertBefore(int pos,T d){
    //if before element 1, set as new head
    if(pos==1){
        prepend(d);
    }
    else{
        worker=head;
        for(int i=1;i<pos-1;i++)worker=worker->next;
        Node *insert=new Node;
        insert->data=d;
        insert->next=worker->next;
        worker->next=insert;
    }
}

template <class T>
void LnkdLst<T>::insertAfter(int pos,T d){
    //used to determine length of list
    int count=1;
    worker=head;
    while(worker->next){
        worker=worker->next;
        count++;
    }
    //check to make sure desired position is within list
    if(pos>count)cout<<"Outside link range, ERROR!"<<endl;
    //if last position is selected, just run append function
    else if(pos==count)append(d);
    //if in middle of list
    else{
        worker=head;
        Node *insert=new Node;
        for(int i=1;i<pos;i++)worker=worker->next;
        insert->data=d;
        insert->next=worker->next;
        worker->next=insert;
    }
}

//Accessors
template <class T>
string LnkdLst<T>::toString(){
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

template <class T>
T LnkdLst<T>::first(){
    return head->data;
}

template <class T>
T LnkdLst<T>::last(){
    worker=head;
    while(worker->next)
        worker=worker->next;
    return worker->data;
}

//Destructor
template <class T>
LnkdLst<T>::~LnkdLst(){
    while(head){
        worker = head;
        head = head->next;
        delete worker;
    }
}

#endif	/* LNKDLST_H */