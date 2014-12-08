/* 
 * File:   Card.cpp
 * Author: Joe
 *
 * Created on November 8, 2014, 11:51 AM
 */

//Our Libraries
#include "Card.h"

//Default Constructor
Card::Card(){
    number=' ';
    name=' ';
    suit=' ';
    value=0;
}

//Constructor
Card::Card(int num){
    if(num<0)num=0;
    if(num>51)num%=52;
    this->number=num;
    name=nameCard();
    suit=suitCard();
    value=valueCard();
}

//Determine card's "name" 
char Card::nameCard(){
    //Declare card name array
    char aName[]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    return aName[number%13];
}

//Determine suit of card
char Card::suitCard(){
    if(number<13)return 'S';
    if(number<26)return 'H';
    if(number<39)return 'C';
    else return 'D';
}

//Determine card value
int Card::valueCard(){
    int n=(number)%13+1;
    
    if(n>10)return 10;
    return n;
}