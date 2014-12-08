/* 
 * File:   Player.h
 * Author: Joe
 *
 * Created on November 10, 2014, 9:15 PM
 */

#include <iostream>
#include <string>
#include <queue>
using namespace std;

#ifndef PLAYER_H
#define	PLAYER_H

class Player{
private:
    string name;        //holds player name
    size_t pwhash;      //holds password hash
    int funds;          //holds player's funds
    int value;          //holds player's hand value
    int wins;           //holds player's wins
    int losses;         //holds player's losses
    int pushes;         //holds player's pushes
public:
    //Constructor
    Player();
    //Mutators
    void setName(string);
    void hash(string);
    void setHash(size_t);
    void setFunds(int);
    void resetValue();
    void setValue(int);
    void setWins(int);
    void setLosses(int);
    void setPushes(int);
    //Accessors
    string getName();
    size_t getHash();
    int getFunds();
    int getValue();
    int getWins();
    int getLosses();
    int getPushes();
};

#endif	/* PLAYER_H */