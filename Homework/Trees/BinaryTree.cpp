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

//public insert function
void BinaryTree::insertNode(int num){
    //create new node to hold value
    TreeNode *newNode=new TreeNode;    //points to new node
    newNode->value=num;
    newNode->left=newNode->right=NULL;
    
    //Insert the node
    insert(root,newNode);
    
}

//insert function
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

//in order display function
void BinaryTree::displayInOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayInOrder(nodePtr->left);
        cout<<nodePtr->value<<endl;
        displayInOrder(nodePtr->right);
    }
}

//pre order display function
void BinaryTree::displayPreOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        cout<<nodePtr->value<<endl;
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

//post order display function
void BinaryTree::displayPostOrder(TreeNode *nodePtr) const{
    if(nodePtr){
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout<<nodePtr->value<<endl;
    }
}

//search function
bool BinaryTree::searchNode(int num){
    TreeNode *nodePtr=root;
    while (nodePtr){
        if(nodePtr->value==num)
            return true;
        else if(num<nodePtr->value)
            nodePtr=nodePtr->left;
        else
            nodePtr=nodePtr->right;
    }
    return false;    
}

//Destructor
void BinaryTree::destroySubTree(TreeNode *nodePtr){
    if(nodePtr){
        if(nodePtr->left)
            destroySubTree(nodePtr->left);
        if(nodePtr->right)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}