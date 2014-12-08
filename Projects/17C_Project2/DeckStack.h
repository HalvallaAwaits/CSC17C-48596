/* 
 * File:   DeckStack.h
 * Author: Joe
 *
 * Created on November 10, 2014, 12:32 PM
 */

//Libraries
#include <iostream>
#include "Card.h"
using namespace std;

#ifndef DECKSTACK_H
#define	DECKSTACK_H

class DeckStack{
private:
    //Structure for the deck nodes
    struct DeckNode{
        Card data;      //value in node
        DeckNode *next;  //Pointer to next node
        
    };
    DeckNode *top;       //Points to top of deck stack
    DeckNode *worker;    //used to traverse
public:
    //Constructor
    DeckStack()
    {top=NULL;}
    //Destructor
    ~DeckStack();
    //Mutators
    void push(Card);
    void pop(Card &);
    //Accessors
    bool isEmpty()const;
};
#endif	/* DECKSTACK_H */