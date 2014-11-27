/* 
 * File:   main.cpp
 * Author: Joe
 *
 * Created on November 26, 2014, 2:29 PM
 * 
 * Functions to include would be insert, delete, balance, print with the 3 types of traversals.
 * Show that it works by randomly filling the tree, and selectively deleting elements and then traversing the tree.
 */

//Libraries
#include <iostream>
#include <cstdlib>
using namespace std;

//Our Libraries
#include "BinaryTree.h"

//Begin main
int main(int argc, char** argv) {
    //Declare Variables
    BinaryTree tree;
    
    cout<<"Inserting nodes. ";
    tree.insertNode(5);
    tree.insertNode(8);
    tree.insertNode(3);
    tree.insertNode(12);
    tree.insertNode(9);
    cout<<"Done."<<endl;
    
    //Display In Order
    cout<<"In order traversal:"<<endl;
    tree.displayInOrder();
    cout<<endl;
    
    //Display Pre Order
    cout<<"Pre order traversal:"<<endl;
    tree.displayPreOrder();
    cout<<endl;
    
    //Display In Order
    cout<<"Post order traversal:"<<endl;
    tree.displayPostOrder();
    cout<<endl;
    
    return 0;
}

