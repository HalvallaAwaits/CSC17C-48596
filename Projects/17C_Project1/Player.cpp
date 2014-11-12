/* 
 * File:   Player.cpp
 * Author: Joe
 *
 * Created on November 10, 2014, 9:15 PM
 */

#include <iostream>
#include "Player.h"
using namespace std;

//Constructor
Player::Player(){
    name="CPU";
    funds=100;
    value=0;
    wins=0;
    losses=0;
    pushes=0;
}

//Mutators
void Player::setName(string n) {
    name=n;
}

void Player::setFunds(int f){
    funds+=f;
}

void Player::resetValue(){
    value=0;
}

void Player::setValue(int v){
    value+=v;
}

void Player::setWins(int win){
    wins+=win;
}

void Player::setLosses(int loss){
    losses+=loss;
}

void Player::setPushes(int push){
    pushes+=push;
}

//Accessors
string Player::getName(){
    return name;
}
int Player::getFunds(){
    return funds;
}

int Player::getValue(){
    return value;
}

int Player::getWins(){
    return wins;
}

int Player::getLosses(){
    return losses;
}

int Player::getPushes(){
    return pushes;
}