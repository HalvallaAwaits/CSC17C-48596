/* 
 * File:   BinaryTree.cpp
 * Author: Joe
 *
 * Created on November 26, 2014, 5:21 PM
 */

//Libraries
#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"
using namespace std;


void BinaryTree::insertNode(int num){
    //create new node to hold value
    TreeNode *newNode=new TreeNode;    //points to new node
    newNode->value=num;
    newNode->left=newNode->right=NULL;
    
    //Insert the node
    insert(root,newNode);
    
}

void BinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
    //if insert location is NULL then insert
    if(nodePtr==NULL)
        nodePtr=newNode;
    //if node exists, compare new value, if lesser, continue search left
    else if(newNode->value<nodePtr->value)
        insert(nodePtr->left,newNode);
    //if node exists, compare new value, if greater, continue search right
    else
        insert(nodePtr->right,newNode);
}

void BinaryTree::displayInOrder(TreeNode *nodePtr) const{
    if(nodePtr){     //if root exists output via in order traversal
        
    }
}