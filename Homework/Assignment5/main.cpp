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
    LnkdLst<int> list(0);
    //add a few nodes
    for(int i=1;i<=3;i++){
        list.append(i);
    }
    //output list
    cout<<"Starting list:"<<endl;
    cout<<list.toString()<<endl;
    //prepend
    list.prepend(4);
    cout<<"After prepend value 4:"<<endl;
    cout<<list.toString()<<endl;
    
    //get first
    cout<<"First function = "<<list.first()<<endl;
    //get last
    cout<<"Last function = "<<list.last()<<endl<<endl;
    
    //find data and extract
    cout<<"Find data = 3 and extract"<<endl;
    list.extract(3);
    cout<<list.toString()<<endl;
    
    //insert before
    cout<<"Insert value 6 before element 3 (becoming the new 3rd element)"<<endl;
    list.insertBefore(3,6);
    cout<<list.toString()<<endl;
    
    //insert after
    cout<<"Insert value 7 after element 3 (becoming the new 4th element)"<<endl;
    list.insertAfter(3,7);
    cout<<list.toString()<<endl;
    
    //create a second list via copy constructor
    cout<<"Second list created via copy constructor"<<endl;
    LnkdLst<int> list2(list);
    cout<<list2.toString()<<endl;
    
    //create third list via assignment operator
    cout<<"Third list created via assignment operator"<<endl;
    LnkdLst<int> list3=list;
    cout<<list3.toString()<<endl;
    
    //modify the first to check to make sure the third actually has it's own location
    list.extract(4);
    list.prepend(5);
    cout<<"Modifying first list to verify 3rd assignment operator is correct..."
            <<endl<<"Extracting leading 4 and prepending a 5."<<endl;
    cout<<list.toString()<<endl;
    
    //test output third which was "assigned" from the 
    //first to verify it's not just utilizing the same pointers
    cout<<"Third list final output"<<endl;
    cout<<list3.toString()<<endl;
    
    //Exit stage right!
    return 0;
}