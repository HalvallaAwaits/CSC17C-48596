/* 
 * File:   Hand.h
 * Author: Joe
 *
 * Created on November 10, 2014, 10:21 PM
 */

#include <iostream>
#include "Card.h"
using namespace std;

#ifndef HAND_H
#define	HAND_H

class HandQueue{
private:
    //structure for hand queue nodes
    struct HandNode{
        Card data;        //holds card data
        HandNode *next;   //pointer to next node
    };
    HandNode *front;      //front of the queue
    HandNode *rear;       //rear of the queue
    int numHand;          //number of cards in hand
public:
    //Constructor
    HandQueue();
    //Destructor
    ~HandQueue();
    //Mutators
    void enqueue(Card);   //place card in hand from deck
    void dequeue(Card &); //remove card from hand, used to put back in deck
    bool isEmpty()const;
    void clear();
    void resetNumHand();
    //Accessors
    int getNumHand();
};

#endif	/* HAND_H */