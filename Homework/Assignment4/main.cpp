/* 
 * File:   main.cpp
 * Author: Joe
 *
 * Created on October 18, 2014, 9:35 AM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
using namespace std;

//Our Libraries
#include "LnkdLst.h"

//No Global Constants

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //create linked list
    LnkdLst list(0);
    //add a few nodes
    for(int i=1;i<=3;i++){
        list.append(i);
    }
    //output list
    cout<<list.toString()<<endl;
    //Exit stage right!
    return 0;
}

