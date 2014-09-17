/* 
 * File:   main.cpp
 * Author: Joe Reimbold
 * Created on September 15, 2014, 4:32 PM
 * Assignment #2: Add push and pull to simple vector
 */

//Libraries
#include <cstdlib>
#include <iostream>

#include "SimpleVector.h"
using namespace std;

//No Globals

//No Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare variables
    int size=5;
    SimpleVector<int> vect(size);
    //fill simple vector class
    for(int i=0;i<size;i++){
        vect[i]=i+1;
    }
    //display default vector
    cout<<"Default Vector: \n";
    for(int i=0;i<vect.size();i++){
        cout<<vect[i]<<" ";
    }
    cout<<endl;
    //push back 3 elements
    for(int i=6;i<9;i++){
        vect.push(i);
    }
    //display new vector after pushing
    cout<<"Vector After Pushing: \n";
    for(int i=0;i<vect.size();i++){
        cout<<vect[i]<<" ";
    }
    cout<<endl;
    //pull 3 elements from end
    for(int i=0;i<3;i++){
        vect.pull();
    }
    //display vector after pulls
    cout<<"Vector After Pulling: \n";
    for(int i=0;i<vect.size();i++){
        cout<<vect[i]<<" ";
    }
    cout<<endl;
    return 0;
}

