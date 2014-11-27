/* 
 * File:   main.cpp
 * Author: Joe
 *
 * Created on November 26, 2014, 2:29 PM
 * 
 * Functions to include would be -done-insert, -done-delete, balance, -done-print with the 3 types of traversals.
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
    tree.insertNode(3);
    tree.insertNode(8);
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
    
    //Search for a value in tree
    cout<<"Search for value 8 in tree: ";
    if(tree.searchNode(8)==1)cout<<"true!"<<endl;
    else
        cout<<"false!"<<endl;
    cout<<"Search for value 7 in tree: ";
    if(tree.searchNode(7)==1)cout<<"true!"<<endl;
    else
        cout<<"false!"<<endl;
    
    //remove a node
    cout<<"Removing 8."<<endl;
    tree.remove(8);
    cout<<"New tree:"<<endl;
    tree.displayInOrder();
    
    return 0;
}

