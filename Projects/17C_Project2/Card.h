/* 
 * File:   Card.h
 * Author: Joe
 *
 * Created on November 8, 2014, 11:51 AM
 */

#ifndef CARD_H
#define	CARD_H

class Card{
private:
    char number;     //card's creation number (used to determine following)
    char name;       //holds card's "name(1,5,10,J,A,etc)
    char suit;       //holds card's suit
    int value;      //holds card's value
public:
    //Constructors
    Card();
    Card(int);
    //Mutators
    char nameCard();
    char suitCard();
    int valueCard();
    //Accessor
    char getNumber(){return number;}
    char getName(){return name;}
    char getSuit(){return suit;}
    char getValue(){return value;}
};

#endif	/* CARD_H */